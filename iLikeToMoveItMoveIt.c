// SSD2119.c

// Runs on LM4F120/TM4C123
// Driver for the SSD2119 interface on a Kentec 320x240x16 BoosterPack
// - Uses all 8 bits on PortB for writing data to LCD
//   and bits 4-7 on Port A for control signals
//
//
//  Data pin assignments:
//  PB0-7   LCD parallel data input
//
//  Control pin assignments:
//  PA4     RD  Read control signal             -------------------------
//  PA5     WR  Write control signal            | PA7 | PA6 | PA5 | PA4 |
//  PA6     RS  Register/Data select signal     | CS  | RS  | WR  | RD  |
//  PA7     CS  Chip select signal              -------------------------
//
//  Touchpad pin assignments:
//  PA2     Y-                                  -------------  -------------
//  PA3     X-                                  | PA3 | PA2 |  | PE5 | PE4 |
//  PE4     X+    AIN9                          | X-  | Y-  |  | Y+  | X+  |
//  PE5     Y+    AIN8                          -------------  -------------
//
//  Touchscreen resistance measurements:
//  -------------------
//  |1               2|                XN->YP       XP->YN
//  |                 |         1       1150         1400
//  |                 |         2       640           800
//  |        5        |         3       1400         1100
//  |                 |         4       870           580
//  |3               4|         5       1000          960
//  -------------------
//
//  XP->XN = 651

#include <stdint.h>
// #include "inc/tm4c123gh6pm.h"
#include "tm4c123gh6pm.h"
#include <ChentyleLab5.h>
#include "SSD2119.h"

// 4 bit Color 	 red,green,blue to 16 bit color
// bits 15-11 5 bit red
// bits 10-5  6-bit green
// bits  4-0  5-bit blue
unsigned short const Color4[16] = {
    0,                                                      //0 � black                   (#000000) 	000000 	0
    ((0x00 >> 3) << 11) | ((0x00 >> 2) << 5) | (0xAA >> 3), //1 � blue                    (#0000AA) 	000001 	1
    ((0x00 >> 3) << 11) | ((0xAA >> 2) << 5) | (0x00 >> 3), //2 � green                   (#00AA00) 	000010 	2
    ((0x00 >> 3) << 11) | ((0xAA >> 2) << 5) | (0xAA >> 3), //3 � cyan                    (#00AAAA) 	000011 	3
    ((0xAA >> 3) << 11) | ((0x00 >> 2) << 5) | (0x00 >> 3), //4 � red                     (#AA0000) 	000100 	4
    ((0xAA >> 3) << 11) | ((0x00 >> 2) << 5) | (0xAA >> 3), //5 � magenta                 (#AA00AA) 	000101 	5
    ((0xAA >> 3) << 11) | ((0x55 >> 2) << 5) | (0x00 >> 3), //6 � brown                   (#AA5500) 	010100 	20
    ((0xAA >> 3) << 11) | ((0xAA >> 2) << 5) | (0xAA >> 3), //7 � white / light gray      (#AAAAAA) 	000111 	7
    ((0x55 >> 3) << 11) | ((0x55 >> 2) << 5) | (0x55 >> 3), //8 � dark gray /bright black (#555555) 	111000 	56
    ((0x55 >> 3) << 11) | ((0x55 >> 2) << 5) | (0xFF >> 3), //9 � bright blue             (#5555FF) 	111001 	57
    ((0x55 >> 3) << 11) | ((0xFF >> 2) << 5) | (0x55 >> 3), //10 � bright green           (#55FF55) 	111010 	58
    ((0x55 >> 3) << 11) | ((0xFF >> 2) << 5) | (0xFF >> 3), //11 � bright cyan            (#55FFFF) 	111011 	59
    ((0xFF >> 3) << 11) | ((0x55 >> 2) << 5) | (0x55 >> 3), //12 � bright red             (#FF5555) 	111100 	60
    ((0xFF >> 3) << 11) | ((0x55 >> 2) << 5) | (0xFF >> 3), //13 � bright magenta         (#FF55FF) 	111101 	61
    ((0xFF >> 3) << 11) | ((0xFF >> 2) << 5) | (0x55 >> 3), //14 � bright yellow          (#FFFF55) 	111110 	62
    ((0xFF >> 3) << 11) | ((0xFF >> 2) << 5) | (0xFF >> 3)  //15 � bright white           (#FFFFFF) 	111111 	63
};

unsigned short cursorX;
unsigned short cursorY;
unsigned short textColor;
int invisible;

typedef struct
{
    short x;
    short y;
} coord;

// dimensions of the LCD in pixels
#define LCD_HEIGHT 240
#define LCD_WIDTH 320

// converts 24bit RGB color to display color
//#define CONVERT24BPP(c) ( (((c) & 0x00f80000) >> 8) | (((c) & 0x0000fc00) >> 5) | (((c) & 0x000000f8) >> 3) )
#define CONVERT24BPP(c) ((((c)&0x00f80000) >> 8) | (((c)&0x0000fc00) >> 5) | (((c)&0x000000f8) >> 3))

// converts 8bit greyscale to display color
#define CONVERT8BPP(c) ((((c) >> 3) << 11) | (((c) >> 2) << 5) | ((c) >> 3))

// converts 4bit greyscale to display color
#define CONVERT4BPP(c) (((c) << 12) | ((c) << 7) | ((c) << 1))

// define BMP offsets
#define BMP_WIDTH_OFFSET 0x0012
#define BMP_HEIGHT_OFFSET 0x0016
#define BMP_DATA_OFFSET 0x000A
#define BMP_BPP_OFFSET 0x001C

// define command codes
#define SSD2119_DEVICE_CODE_READ_REG 0x00
#define SSD2119_OSC_START_REG 0x00
#define SSD2119_OUTPUT_CTRL_REG 0x01
#define SSD2119_LCD_DRIVE_AC_CTRL_REG 0x02
#define SSD2119_PWR_CTRL_1_REG 0x03
#define SSD2119_DISPLAY_CTRL_REG 0x07
#define SSD2119_FRAME_CYCLE_CTRL_REG 0x0B
#define SSD2119_PWR_CTRL_2_REG 0x0C
#define SSD2119_PWR_CTRL_3_REG 0x0D
#define SSD2119_PWR_CTRL_4_REG 0x0E
#define SSD2119_GATE_SCAN_START_REG 0x0F
#define SSD2119_SLEEP_MODE_REG 0x10
#define SSD2119_ENTRY_MODE_REG 0x11
#define SSD2119_GEN_IF_CTRL_REG 0x15
#define SSD2119_PWR_CTRL_5_REG 0x1E
#define SSD2119_RAM_DATA_REG 0x22
#define SSD2119_FRAME_FREQ_REG 0x25
#define SSD2119_VCOM_OTP_1_REG 0x28
#define SSD2119_VCOM_OTP_2_REG 0x29
#define SSD2119_GAMMA_CTRL_1_REG 0x30
#define SSD2119_GAMMA_CTRL_2_REG 0x31
#define SSD2119_GAMMA_CTRL_3_REG 0x32
#define SSD2119_GAMMA_CTRL_4_REG 0x33
#define SSD2119_GAMMA_CTRL_5_REG 0x34
#define SSD2119_GAMMA_CTRL_6_REG 0x35
#define SSD2119_GAMMA_CTRL_7_REG 0x36
#define SSD2119_GAMMA_CTRL_8_REG 0x37
#define SSD2119_GAMMA_CTRL_9_REG 0x3A
#define SSD2119_GAMMA_CTRL_10_REG 0x3B
#define SSD2119_V_RAM_POS_REG 0x44
#define SSD2119_H_RAM_START_REG 0x45
#define SSD2119_H_RAM_END_REG 0x46
#define SSD2119_X_RAM_ADDR_REG 0x4E
#define SSD2119_Y_RAM_ADDR_REG 0x4F
#define ENTRY_MODE_DEFAULT 0x6830

// number of 5x8 characters that will fit on the screen
#define MAX_CHARS_X 53
#define MAX_CHARS_Y 26

// entry mode macros
#define HORIZ_DIRECTION 0x28
#define VERT_DIRECTION 0x20
#define ENTRY_MODE_DEFAULT 0x6830 // 0110.1000.0011.0000
#define MAKE_ENTRY_MODE(x) ((ENTRY_MODE_DEFAULT & 0xFF00) | (x))

// bit-banded addresses for port stuff
#define LCD_RD_PIN (*((volatile unsigned long *)0x40004040)) // PA4
#define LCD_WR_PIN (*((volatile unsigned long *)0x40004080)) // PA5
#define LCD_RS_PIN (*((volatile unsigned long *)0x40004100)) // PA6
#define LCD_CS_PIN (*((volatile unsigned long *)0x40004200)) // PA7
#define LCD_CTRL (*((volatile unsigned long *)0x400043C0))   // PA4-7
#define LCD_DATA (*((volatile unsigned long *)0x400053FC))   // PB0-7
// ************** ADC_Init *********************************
// - Initializes the ADC to use a specficed channel on SS3
// *********************************************************
// Input: channel number
// Output: none
// *********************************************************
void ADC_Init(void);

// ************** ADC_Read *********************************
// - Takes a sample from the ADC
// *********************************************************
// Input: none
// Output: sampled value from the ADC
// *********************************************************
unsigned long ADC_Read(void);

// ************** ADC_SetChannel ***************************
// - Configures the ADC to use a specific channel
// *********************************************************
// Input: none
// Output: none
// *********************************************************
void ADC_SetChannel(unsigned char channelNum);

/* *************************************************************
TODO: Please fill the information based on the pseudocode
******************************************************************/

// ************** TODO: LCD_GPIOInit ****************************
// - Initializes Port B 0-7 of port B to be used as the data bus and
//   Port A 4-7 as controller signals
// ********************************************************
void LCD_GPIOInit(void)
{
    unsigned long wait = 0;
    RCGCGPIO |= 0x2;            // activate port B
    wait++;                     // wait for port activation
    wait++;                     // wait for port activation
    GPIO_PORT_B_DIR = 0xFF;     // make PB0-7 outputs
    GPIO_PORT_B_AFSEL &= ~0xFF; // Disable alternate functions on PB0-7
    GPIO_PORT_B_DEN = 0xFF;     // enable digital I/O on PB0-7

    // activate control pins

    RCGCGPIO |= 0x1;            // activate port A
    wait++;                     // wait for port activation
    wait++;                     // wait for port activation
    GPIO_PORT_A_DIR = 0xF0;     // make PA4-7 outputs
    GPIO_PORT_A_AFSEL &= ~0xF0; // disable alternate functions
    GPIO_PORT_A_DEN = 0xF0;     // enable digital I/O on PA4-7

    for (wait = 0; wait < 500; wait++)
    {
    }
}

// ************** LCD_WriteCommand ************************
// - Writes a command to the LCD controller
// - RS low during command write
// ********************************************************
//  PA4     RD  Read control signal             -------------------------
//  PA5     WR  Write control signal            | PA7 | PA6 | PA5 | PA4 |
//  PA6     RS  Register/Data select signal     | CS  | RS  | WR  | RD  |
//  PA7     CS  Chip select signal              -------------------------
void LCD_WriteCommand(unsigned char data)
{
    volatile unsigned long delay;
    LCD_CTRL = 0x30; // Set CS=0, RS=0, WR=1, RD=1
    LCD_DATA = 0x00; // Write 0 as MSB of command data
    delay++;
    LCD_CTRL = 0x10; // Set WR low
    delay++;
    LCD_CTRL = 0x30; // Set WR high
    LCD_DATA = data; // Write data as LSB of command data
    delay++;
    LCD_CTRL = 0x10; // Set WR low
    delay++;
    LCD_CTRL = 0xF0; // Set all high
}

// ************** LCD_WriteData ***************************
// - Writes data to the LCD controller
// - RS high during data write
// ********************************************************
//  PA4     RD  Read control signal             -------------------------
//  PA5     WR  Write control signal            | PA7 | PA6 | PA5 | PA4 |
//  PA6     RS  Register/Data select signal     | CS  | RS  | WR  | RD  |
//  PA7     CS  Chip select signal              -------------------------
void LCD_WriteData(unsigned short data)
{
    volatile unsigned long delay;
    LCD_CTRL = 0x70;        // CS low
    LCD_DATA = (data >> 8); // Write MSB to LCD data bus
    delay++;
    LCD_CTRL = 0x50; // Set WR low
    delay++;
    LCD_CTRL = 0x70; // Set WR high
    LCD_DATA = data; // Write LSB to LCD data bus
    delay++;
    LCD_CTRL = 0x50; // Set WR low
    delay++;
    LCD_CTRL = 0xF0; // Set CS, WR high
}

// ************** LCD_Init ********************************
// - Initializes the LCD
// - Command sequence verbatim from original driver
// ********************************************************
void LCD_Init(void)
{
    unsigned long count = 0;

    LCD_GPIOInit();

    // Enter sleep mode (if we are not already there).
    LCD_WriteCommand(SSD2119_SLEEP_MODE_REG);
    LCD_WriteData(0x0001);

    // Set initial power parameters.
    LCD_WriteCommand(SSD2119_PWR_CTRL_5_REG);
    LCD_WriteData(0x00BA);
    LCD_WriteCommand(SSD2119_VCOM_OTP_1_REG);
    LCD_WriteData(0x0006);

    // Start the oscillator.
    LCD_WriteCommand(SSD2119_OSC_START_REG);
    LCD_WriteData(0x0001);

    // Set pixel format and basic display orientation (scanning direction).
    LCD_WriteCommand(SSD2119_OUTPUT_CTRL_REG);
    LCD_WriteData(0x72EF);                           //0x72EF = 0,0 in top left, scan right
    LCD_WriteCommand(SSD2119_LCD_DRIVE_AC_CTRL_REG); //0x30EF = 0,0 in bottom right, scan left
    LCD_WriteData(0x0600);                           //0x32EF = 0,0 in top right, scan left

    // Exit sleep mode.
    LCD_WriteCommand(SSD2119_SLEEP_MODE_REG);
    LCD_WriteData(0x0000);

    // Delay 30mS
    for (count = 0; count < 200000; count++)
    {
    }

    // Configure pixel color format and MCU interface parameters.
    LCD_WriteCommand(SSD2119_ENTRY_MODE_REG);
    LCD_WriteData(ENTRY_MODE_DEFAULT);

    // Enable the display.
    LCD_WriteCommand(SSD2119_DISPLAY_CTRL_REG);
    LCD_WriteData(0x0033);

    // Set VCIX2 voltage to 6.1V.
    LCD_WriteCommand(SSD2119_PWR_CTRL_2_REG);
    LCD_WriteData(0x0005);

    // Configure gamma correction.
    LCD_WriteCommand(SSD2119_GAMMA_CTRL_1_REG);
    LCD_WriteData(0x0000);
    LCD_WriteCommand(SSD2119_GAMMA_CTRL_2_REG);
    LCD_WriteData(0x0400);
    LCD_WriteCommand(SSD2119_GAMMA_CTRL_3_REG);
    LCD_WriteData(0x0106);
    LCD_WriteCommand(SSD2119_GAMMA_CTRL_4_REG);
    LCD_WriteData(0x0700);
    LCD_WriteCommand(SSD2119_GAMMA_CTRL_5_REG);
    LCD_WriteData(0x0002);
    LCD_WriteCommand(SSD2119_GAMMA_CTRL_6_REG);
    LCD_WriteData(0x0702);
    LCD_WriteCommand(SSD2119_GAMMA_CTRL_7_REG);
    LCD_WriteData(0x0707);
    LCD_WriteCommand(SSD2119_GAMMA_CTRL_8_REG);
    LCD_WriteData(0x0203);
    LCD_WriteCommand(SSD2119_GAMMA_CTRL_9_REG);
    LCD_WriteData(0x1400);
    LCD_WriteCommand(SSD2119_GAMMA_CTRL_10_REG);
    LCD_WriteData(0x0F03);

    // Configure Vlcd63 and VCOMl.
    LCD_WriteCommand(SSD2119_PWR_CTRL_3_REG);
    LCD_WriteData(0x0007);
    LCD_WriteCommand(SSD2119_PWR_CTRL_4_REG);
    LCD_WriteData(0x3100);

    // Set the display size and ensure that the GRAM window is set to allow
    // access to the full display buffer.
    LCD_WriteCommand(SSD2119_V_RAM_POS_REG);
    LCD_WriteData((LCD_HEIGHT - 1) << 8);
    LCD_WriteCommand(SSD2119_H_RAM_START_REG);
    LCD_WriteData(0x0000);
    LCD_WriteCommand(SSD2119_H_RAM_END_REG);
    LCD_WriteData(LCD_WIDTH - 1);
    LCD_WriteCommand(SSD2119_X_RAM_ADDR_REG);
    LCD_WriteData(0x00);
    LCD_WriteCommand(SSD2119_Y_RAM_ADDR_REG);
    LCD_WriteData(0x00);

    // Clear the contents of the display buffer.
    LCD_WriteCommand(SSD2119_RAM_DATA_REG);
    for (count = 0; count < (320 * 240); count++)
    {
        LCD_WriteData(0x0000);
    }

    // Set text cursor to top left of screen
    LCD_SetCursor(0, 0);

    // Set default text color to white
    LCD_SetTextColor(255, 255, 255);
}

// ************** convertColor ****************************
// - Converts 8-8-8 RGB values into 5-6-5 RGB
// ********************************************************
unsigned short convertColor(unsigned char r, unsigned char g, unsigned char b)
{
    return ((r >> 3) << 11) | ((g >> 2) << 5) | (b >> 3);
}

// ************** LCD_ColorFill ***************************
// - Fills the screen with the specified color
// ********************************************************
void LCD_ColorFill(unsigned short color)
{
    LCD_DrawFilledRect(0, 0, LCD_WIDTH, LCD_HEIGHT, color);
}

// ************** abs *************************************
// - Returns the absolute value of an integer
// - Used to help with circle drawing
// ********************************************************
int abs(int a)
{
    if (a < 0)
        return -a;
    else
        return a;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//                                 PRINTING FUNCTIONS                                            //
///////////////////////////////////////////////////////////////////////////////////////////////////

// ************** LCD_PrintChar ***************************
// - Prints a character to the screen
// ********************************************************
void LCD_PrintChar(unsigned char data)
{
    unsigned char i, j, tempData;

    // Return cursor to new line if requested
    if (data == '\n')
    {
        LCD_SetCursor(0, cursorY + 9);
    }

    // Don't print characters outside of this range
    if (data < 0x20 || data > 0x7e)
        return;

    // If character would print beyond LCD_WIDTH, go to new line
    if (cursorX + 5 >= LCD_WIDTH)
    {
        LCD_SetCursor(0, cursorY + 9);
    }

    // If character would print beyond LCD_HEIGHT, return to top of screen
    if (cursorY + 8 >= LCD_HEIGHT)
    {
        LCD_SetCursor(cursorX, 0);
    }

    // Print our character
    for (i = 0; i < 5; i = i + 1)
    {
        tempData = ASCII[data - 0x20][i];
        for (j = 0; j < 8; j = j + 1)
        {
            // This would print transparent letters
            if (invisible) {
                LCD_DrawPixel(cursorX + i, cursorY + j, textColor);
            } else {
               // This will overwrite the entire character block (non-transparent)
               LCD_DrawPixel(cursorX + i, cursorY + j, (tempData & 0x01) * textColor);

               // Shift to our next pixel
               tempData = tempData >> 1;
            }
        }
    }

    // Set cursor to next location
    LCD_SetCursor(cursorX + 6, cursorY);
}

// ************** LCD_PrintString *************************
// - Prints a string to the screen
// ********************************************************
void LCD_PrintString(char data[])
{
    unsigned short i = 0;

    // While data[i] is not a null terminator, print out characters
    while (data[i] != 0)
    {
        LCD_PrintChar(data[i]);
        i += 1;
    }
}

// ************** LCD_SetCursor ***************************
// - Sets character printing cursor position
// ********************************************************
void LCD_SetCursor(unsigned short xPos, unsigned short yPos)
{
    // Set the X address of the display cursor.
    cursorX = xPos;
    //    LCD_WriteCommand(SSD2119_X_RAM_ADDR_REG);
    //    LCD_WriteData(xPos);

    // Set the Y address of the display cursor.
    cursorY = yPos;
    //    LCD_WriteCommand(SSD2119_Y_RAM_ADDR_REG);
    //    LCD_WriteData(yPos);
}

// ************** LCD_Goto ********************************
// - Sets character printing cursor position in terms of
//   character positions rather than pixels.
// - Ignores invalid position requests.
// ********************************************************
void LCD_Goto(unsigned char x, unsigned char y)
{
    if (x > MAX_CHARS_X - 1 || y > MAX_CHARS_Y - 1)
        return;
    LCD_SetCursor(x * 6, y * 9);
}

// ************** LCD_SetTextColor ************************
// - Sets the color that characters will be printed in
// ********************************************************
void LCD_SetTextColor(unsigned char r, unsigned char g, unsigned char b)
{
    textColor = convertColor(r, g, b);
}

// ************** printf **********************************
// - Basic printf() implementation
// - Adapted from Craig Chase, EE312 printf() case study
// - Supports:
//   - %d   Signed decimal integer
//   - %c   Character
//   - %s   String of characters
//   - %f   Decimal floating point          (NYI)
//   - %x   Unsigned hexadecimal integer
//   - %b   Binary integer
//   - %%   A single % output
// ********************************************************
void printf(char fmt[], ...)
{
    unsigned char k = 0;
    void *next_arg = &fmt + 1;
    while (fmt[k] != 0)
    {
        if (fmt[k] == '%')
        { // Special escape, look for next arg
            if (fmt[k + 1] == 'd')
            { // Display integer
                long *p = (long *)next_arg;
                long x = *p;
                next_arg = p + 1;
                LCD_PrintInteger(x);
            }
            else if (fmt[k + 1] == 'c')
            { // Display character
                long *p = (long *)next_arg;
                char x = *p;
                next_arg = p + 1;
                LCD_PrintChar(x);
            }
            else if (fmt[k + 1] == 's')
            { // Display string
                char **p = (char **)next_arg;
                char *x = *p;
                next_arg = p + 1;
                LCD_PrintString(x);
            }
            else if (fmt[k + 1] == 'f')
            { // Display float (not yet working)
                float *p = (float *)next_arg;
                float x = *p;
                next_arg = p + 1;
                LCD_PrintFloat(x);
            }
            else if (fmt[k + 1] == 'x')
            { // Display hexadecimal
                long *p = (long *)next_arg;
                long x = *p;
                next_arg = p + 1;
                LCD_PrintHex(x);
            }
            else if (fmt[k + 1] == 'b')
            { // Display binary
                long *p = (long *)next_arg;
                long x = *p;
                next_arg = p + 1;
                LCD_PrintBinary(x);
            }
            else if (fmt[k + 1] == '%')
            { // Display '%'
                LCD_PrintChar('%');
            }
            else
            {
                // Otherwise, just ignore the unrecognized escape
            }
            k = k + 2;
        }
        else
        { // Normal output, just print the character
            LCD_PrintChar(fmt[k]);
            k = k + 1;
        }
    }
}

// ************** LCD_PrintInteger ************************
// - Prints a signed integer to the screen
// ********************************************************
void LCD_PrintInteger(long n)
{
    unsigned char i = 0;
    unsigned char sign = ' ';
    unsigned char tempString[16];

    // If our number is 0, print 0
    if (n == 0)
    {
        LCD_PrintChar('0');
        return;
    }

    // If our number is negative, remember and unsign it
    if (n < 0)
    {
        n = -n;
        sign = '-';
    }

    // Build our number string via repeated division
    while (n > 0)
    {
        tempString[i] = (n % 10) + 48;
        n = n / 10;
        i += 1;
    }

    // Apply our sign if necessary
    if (sign == '-')
    {
        LCD_PrintChar('-');
    }

    // Print out our string in reverse order
    while (i)
    {
        LCD_PrintChar(tempString[i - 1]);
        i -= 1;
    }
}

// ************** LCD_PrintHex ****************************
// - Prints a number in hexidecimal format
// ********************************************************
void LCD_PrintHex(unsigned long n)
{
    unsigned char i = 0;
    unsigned char tempString[16];

    // Print hex prefix
    LCD_PrintString("0x");

    // If our number is 0, print 0
    if (n == 0)
    {
        LCD_PrintString("00");
        return;
    }

    // Build hexidecimal string via repeated division
    while (n > 0)
    {
        tempString[i] = (n % 16) + 48;
        if (tempString[i] > 57)
            tempString[i] += 7;
        n = n / 16;
        i += 1;
    }

    // Print an even number of zeros
    if (i & 0x01)
    {
        tempString[i] = '0';
        i += 1;
    }

    // Print out our string in reverse order
    while (i)
    {
        LCD_PrintChar(tempString[i - 1]);
        i -= 1;
    }
}

// ************** LCD_PrintBinary *************************
// - Prints a number in binary format
// ********************************************************
void LCD_PrintBinary(unsigned long n)
{
    unsigned char i = 0;
    unsigned char j = 0;
    unsigned char tempString[32];

    // Print binary prefix
    LCD_PrintString("0b");

    // If our number is 0, print 0
    if (n == 0)
    {
        LCD_PrintString("0000");
        return;
    }

    // Build hexidecimal string via repeated division
    while (n > 0)
    {
        tempString[i] = (n % 2) + 48;
        n = n / 2;
        i += 1;
    }

    // Print in nibbles
    for (j = 0; j < (i % 4); j++)
    {
        tempString[i] = '0';
        i += 1;
    }

    // Print out our string in reverse order
    while (i)
    {
        LCD_PrintChar(tempString[i - 1]);
        i -= 1;
        // add nibble seperators
        if (i % 4 == 0 && i != 0)
            LCD_PrintChar('.');
    }
}

// ************** LCD_PrintFloat **************************
// - Prints a floating point number (doesn't work right now)
// ********************************************************
void LCD_PrintFloat(float num)
{
    long temp;

    // Decode exponent
    printf("binary = %b\n", num);
    printf("hex    = %x\n", num);
    // printf("Float    = %f\n", num);
    temp = ((long)num);
    printf("exponent = %d\n", temp);

    LCD_PrintChar('\n');
    // temp = (long)(num*(1<<12));
    // printf("%d.%d", temp>>12,  (temp&0xFFF)*1000/(1<<12));
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//                                 DRAWING FUNCTIONS                                             //
///////////////////////////////////////////////////////////////////////////////////////////////////

// ************** LCD_DrawPixel ***************************
// - Draws a 16-bit pixel on the screen
// ********************************************************
void LCD_DrawPixel(unsigned short x, unsigned short y, unsigned short color)
{
    // Set the X address of the display cursor.
    LCD_WriteCommand(SSD2119_X_RAM_ADDR_REG);
    LCD_WriteData(x);

    // Set the Y address of the display cursor.
    LCD_WriteCommand(SSD2119_Y_RAM_ADDR_REG);
    LCD_WriteData(y);

    // Write the pixel value.
    if(!invisible) {
      LCD_WriteCommand(SSD2119_RAM_DATA_REG);
      LCD_WriteData(color);
    }
}

// ************** LCD_DrawPixelRGB ************************
// - Draws a 16-bit representation of a 24-bit color pixel
// ********************************************************
void LCD_DrawPixelRGB(unsigned short x, unsigned short y, unsigned char r, unsigned char g, unsigned char b)
{
    LCD_DrawPixel(x, y, convertColor(r, g, b));
}

// ************** LCD_DrawLine ****************************
// - Draws a line using the Bresenham line algrorithm from
//   http://rosettacode.org/wiki/Bitmap/Bresenham%27s_line_algorithm
// ********************************************************
void LCD_DrawLine(unsigned short startX, unsigned short startY, unsigned short endX, unsigned short endY, unsigned short color)
{
    short x0 = startX;
    short x1 = endX;
    short y0 = startY;
    short y1 = endY;

    short dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    short dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    short err = (dx > dy ? dx : -dy) / 2, e2;

    for (;;)
    {
        LCD_DrawPixel(x0, y0, color);
        if (x0 == x1 && y0 == y1)
            break;
        e2 = err;
        if (e2 > -dx)
        {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dy)
        {
            err += dx;
            y0 += sy;
        }
    }
}

// ************** LCD_DrawRect ****************************
// - Draws a rectangle, top left corner at (x,y)
// ********************************************************
void LCD_DrawRect(unsigned short x, unsigned short y, short width, short height, unsigned short color)
{
    LCD_DrawLine(x, y, x + width, y, color);
    LCD_DrawLine(x, y + 1, x, y + height - 1, color);
    LCD_DrawLine(x, y + height, x + width, y + height, color);
    LCD_DrawLine(x + width, y + 1, x + width, y + height - 1, color);
}

// ************** LCD_DrawFilledRect **********************
// - Draws a filled rectangle, top left corner at (x,y)
// ********************************************************
void LCD_DrawFilledRect(unsigned short x, unsigned short y, short width, short height, unsigned short color)
{
    int i, j;

    for (i = 0; i < height; i++)
    {
        // Set the X address of the display cursor.
        LCD_WriteCommand(SSD2119_X_RAM_ADDR_REG);
        LCD_WriteData(x);

        // Set the Y address of the display cursor.
        LCD_WriteCommand(SSD2119_Y_RAM_ADDR_REG);
        LCD_WriteData(y + i);

        LCD_WriteCommand(SSD2119_RAM_DATA_REG);
        for (j = 0; j < width; j++)
        {
            LCD_WriteData(color);
        }
    }
}

// ************** LCD_DrawCircle **************************
// - Draws a circle centered at (x0, y0)
// ********************************************************
void LCD_DrawCircle(unsigned short x0, unsigned short y0, unsigned short radius, short color)
{
    int f = 1 - radius;
    int ddF_x = 1;
    int ddF_y = -2 * radius;
    int x = 0;
    int y = radius;

    LCD_DrawPixel(x0, y0 + radius, color);
    LCD_DrawPixel(x0, y0 - radius, color);
    LCD_DrawPixel(x0 + radius, y0, color);
    LCD_DrawPixel(x0 - radius, y0, color);

    while (x < y)
    {
        // ddF_x == 2 * x + 1;
        // ddF_y == -2 * y;
        // f == x*x + y*y - radius*radius + 2*x - y + 1;
        if (f >= 0)
        {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;
        LCD_DrawPixel(x0 + x, y0 + y, color);
        LCD_DrawPixel(x0 - x, y0 + y, color);
        LCD_DrawPixel(x0 + x, y0 - y, color);
        LCD_DrawPixel(x0 - x, y0 - y, color);
        LCD_DrawPixel(x0 + y, y0 + x, color);
        LCD_DrawPixel(x0 - y, y0 + x, color);
        LCD_DrawPixel(x0 + y, y0 - x, color);
        LCD_DrawPixel(x0 - y, y0 - x, color);
    }
}

// ************** LCD_DrawFilledCircle ********************
// - Draws a filled circle centered at (x0, y0)
// ********************************************************
void LCD_DrawFilledCircle(unsigned short x0, unsigned short y0, unsigned short radius, short color)
{
    short x = radius, y = 0;
    short radiusError = 1 - x;
    short i = 0;

    while (x >= y)
    {

        //LCD_DrawLine(x0 + x, y0 + y, x0 - x, y0 + y, color);
        for (i = x0 - x; i < x0 + x; i++)
        {
            LCD_DrawPixel(i, y0 + y, color);
        }

        //LCD_DrawLine(x0 + x, y0 - y, x0 - x, y0 - y, color);
        for (i = x0 - x; i < x0 + x; i++)
        {
            LCD_DrawPixel(i, y0 - y, color);
        }

        //LCD_DrawLine(x0 + y, y0 + x, x0 + y, y0 - x, color);
        for (i = y0 - x; i < y0 + x; i++)
        {
            LCD_DrawPixel(x0 + y, i, color);
        }

        //LCD_DrawLine(x0 - y, y0 + x, x0 - y, y0 - x, color);
        for (i = y0 - x; i < y0 + x; i++)
        {
            LCD_DrawPixel(x0 - y, i, color);
        }

        y++;

        // Calculate whether we need to move inward a pixel
        if (radiusError < 0)
        {
            radiusError += 2 * y + 1;
        }
        else
        {
            x--;
            radiusError += 2 * (y - x + 1);
        }
    }
}

#define TOUCH_YN (*((volatile unsigned long *)0x40004010)) // PA2
#define TOUCH_XP (*((volatile unsigned long *)0x40004020)) // PA3
#define TOUCH_XN (*((volatile unsigned long *)0x40024040)) // PE4 / AIN9
#define TOUCH_YP (*((volatile unsigned long *)0x40024080)) // PE5 / AIN8

#define PA2 0x04
#define PA3 0x08
#define PE4 0x10
#define PE5 0x20

#define NUM_SAMPLES 4
#define NUM_VALS_TO_AVG 8

#define XVAL_MIN 100
#define YVAL_MIN 150

unsigned char Touch_WaitForInput = 0;
short Touch_XVal;
short Touch_YVal;

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts

//short xVals[NUM_VALS_TO_AVG];
//short yVals[NUM_VALS_TO_AVG];
//unsigned char filterCounter = 0;
//unsigned char numVals = 0;

//         YP / PE5 / AIN8
//      ---------------------
//      |                   |
//   XP |                   | XN
//  PA3 |                   | PE4
//      |                   | AIN9
//      |                   |
//      |                   |
//      ---------------------
//             YN / PA2

// **************  Touch_Init *******************************
// - Initializes the GPIO used for the touchpad
// *********************************************************
// Input: none
// Output: none
// *********************************************************
void Touch_Init(void)
{
    unsigned long wait = 0;
    // Initialize ADC for use with touchscreen
    ADC_Init();

    // Activate PORTA GPIO clock
    SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOA;
    wait++;
    wait++;

    //    // Configure PA2/PA3 for GPIO digital output
    GPIO_PORTA_DIR_R |= 0x0C;
    //    GPIO_PORTA_AFSEL_R  &= ~0x0C;
    //    GPIO_PORTA_DEN_R    |=  0x0C;
    //
    //    // Set XN and YN low
    //    TOUCH_XN = 0x00;
    //    TOUCH_YN = 0x00;

    // Activate PORTE GPIO clock
    SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOE;
    wait++;
    wait++;

    //    // Configure PE4/PE5 for GPIO digital output
    GPIO_PORTE_DIR_R |= 0x30;
    //    GPIO_PORTE_AFSEL_R  &= ~0x30;
    //    GPIO_PORTE_DEN_R    |=  0x30;
    //    GPIO_PORTE_AMSEL_R  &= ~0x30;
    //
    //    // Set XP and YP high
    //    TOUCH_XP = 0xFF;
    //    TOUCH_YP = 0xFF;
}

// ************** ADC_Init *********************************
// - Initializes the ADC to use a specficed channel on SS3
// - This one is different from section A, please write your own
//    part A code. We consider it is
// *********************************************************
// Input: channel number
// Output: none
// *********************************************************
void ADC_Init(void)
{
    long wait = 0;

    // Set bit 0 in SYSCTL_RCGCADC_R to enable ADC0
    SYSCTL_RCGCADC_R |= 0x01;
    for (wait = 0; wait < 50; wait++)
    {
    }

    SYSCTL_RCGCGPIO_R |= 0x10;

    // Set ADC sample to 125KS/s
    ADC0_PC_R = 0x01;

    // Disable all sequencers for configuration
    ADC0_ACTSS_R &= ~0x000F;

    // Set ADC0 SS3 to highest priority
    ADC0_SSPRI_R = 0x0123;

    // Set bits 12-15 to 0x00 to enable software trigger on SS3
    ADC0_EMUX_R &= ~0xF000;

    // Set sample channel for sequencer 3
    ADC0_SSMUX3_R &= 0xFFF0;
    ADC0_SSMUX3_R += 9;

    // TS0 = 0, IE0 = 1, END0 = 1, D0 = 0
    ADC0_SSCTL3_R = 0x006;

    // Disable ADC interrupts on SS3 by clearing bit 3
    ADC0_IM_R &= ~0x0008;

    // Re-enable sample sequencer 3
    ADC0_ACTSS_R |= 0x0008;
}

// ************** ADC_Read *********************************
// - Takes a sample from the ADC
// *********************************************************
// Input: none
// Output: sampled value from the ADC
// *********************************************************
unsigned long ADC_Read(void)
{
    unsigned long result;

    // Set bit 3 to trigger sample start
    ADC0_PSSI_R = 0x008;

    // Wait for SS3 RIS bit to be set to 1
    while ((ADC0_RIS_R & 0x08) == 0)
    {
    };

    // Read 12-bit result from ADC from FIFO
    result = ADC0_SSFIFO3_R & 0xFFF;

    // Clear SS3 RIS bit to 0 to acknowledge completion
    ADC0_ISC_R = 0x0008;

    return result;
}

// ************** ADC_SetChannel ***************************
// - Configures the ADC to use a specific channel
// *********************************************************
// Input: none
// Output: none
// *********************************************************
void ADC_SetChannel(unsigned char channelNum)
{
    // Disable all sequencers for configuration
    ADC0_ACTSS_R &= ~0x000F;

    // Set sample channel for sequencer 3
    ADC0_SSMUX3_R &= 0xFFF0;
    ADC0_SSMUX3_R += channelNum;

    // Re-enable sample sequencer 3
    ADC0_ACTSS_R |= 0x0008;
}

// ************** ADC_ReadXVal *****************************
// -
// *********************************************************
// Input: none
// Output: none
// *********************************************************
unsigned long Touch_ReadX(void)
{
    long i = 0;
    long sum = 0;
    long result = 0;

    GPIO_PORTA_DATA_R &= ~PA2;

    // Configure PA3 (XP) for GPIO HIGH
    GPIO_PORTA_AFSEL_R &= ~PA3; // ASFEL = 0
    GPIO_PORTA_DEN_R |= PA3;    // DEN = 1
    GPIO_PORTA_DIR_R |= PA3;    // DIR = 1
    GPIO_PORTA_DATA_R |= PA3;   // DATA = 1

    // Configure PE4 (XN) for GPIO LOW
    GPIO_PORTE_AFSEL_R &= ~PE4; // ASFEL = 0
    GPIO_PORTE_DEN_R |= PE4;    // DEN = 1
    GPIO_PORTE_DIR_R |= PE4;    // DIR = 1
    GPIO_PORTE_DATA_R &= ~PE4;  // DATA = 0

    // Configure PA2 (YN) for analog hi-Z
    GPIO_PORTA_AFSEL_R &= ~PA2; // AFSEL = 0
    GPIO_PORTA_DEN_R &= ~PA2;   // DEN = 0
    GPIO_PORTA_DIR_R &= ~PA2;   // DIR = 0

    // Configure PE5 (YP) for ADC use
    GPIO_PORTE_AFSEL_R |= PE5; // AFSEL = 1
    GPIO_PORTE_DEN_R &= ~PE5;  // DEN = 0
    GPIO_PORTE_AMSEL_R |= PE5; // AMSEL = 1

    // Configure ADC to read from AIN8 (PE5, YP)
    ADC_SetChannel(8);

    // Take some samples to average
    for (i = 0; i < NUM_SAMPLES; i++)
    {
        sum += ADC_Read();
    }

    GPIO_PORTE_AMSEL_R &= ~PE5; // AMSEL = 0

    // Compute average
    result = sum / NUM_SAMPLES;

    Touch_XVal = result;

    return result;
}

// ************** ADC_ReadYVal *****************************
// -
// *********************************************************
// Input: none
// Output: none
// *********************************************************
unsigned long Touch_ReadY(void)
{
    long i = 0;
    long sum = 0;
    long result = 0;

    // Configure PE5 (YP) for GPIO HIGH
    GPIO_PORTE_AFSEL_R &= ~PE5; // ASFEL = 0
    GPIO_PORTE_DEN_R |= PE5;    // DEN = 1
    GPIO_PORTE_DIR_R |= PE5;    // DIR = 1
    GPIO_PORTE_DATA_R |= PE5;   // DATA = 1
    //TOUCH_XP = 0xFF;

    // Configure PA2 (YN) for GPIO LOW
    GPIO_PORTA_AFSEL_R &= ~PA2; // ASFEL = 0
    GPIO_PORTA_DEN_R |= PA2;    // DEN = 1
    GPIO_PORTA_DIR_R |= PA2;    // DIR = 1
    GPIO_PORTA_DATA_R &= ~PA2;  // DATA = 0

    // Configure PA3 (XP) for analog hi-Z
    GPIO_PORTA_AFSEL_R &= ~PA3; // AFSEL = 0
    GPIO_PORTA_DEN_R &= ~PA3;   // DEN = 0
    GPIO_PORTA_DIR_R &= ~PA3;   // DIR = 0

    // Configure PE4 (XN) for ADC use
    GPIO_PORTE_AFSEL_R |= PE4; // AFSEL = 1
    GPIO_PORTE_DEN_R &= ~PE4;  // DEN = 0
    GPIO_PORTE_AMSEL_R |= PE4; // AMSEL = 1

    // Configure ADC to read from AIN9 (PE4, XN)
    ADC_SetChannel(9);

    // Take some samples to average
    for (i = 0; i < NUM_SAMPLES; i++)
    {
        sum += ADC_Read();
    }

    // Compute average
    result = sum / NUM_SAMPLES;

    Touch_YVal = result;

    return result;
}

// ************** ADC_ReadZ1 *******************************
// -
// *********************************************************
// Input: none
// Output: none
// *********************************************************
unsigned long Touch_ReadZ1(void)
{
    long i = 0;
    long sum = 0;
    long result = 0;

    // Configure PA2 (YN) for GPIO HIGH
    GPIO_PORTA_AFSEL_R &= ~PA2; // ASFEL = 0
    GPIO_PORTA_DEN_R |= PA2;    // DEN = 1
    GPIO_PORTA_DIR_R |= PA2;    // DIR = 1
    GPIO_PORTA_DATA_R |= PA2;   // DATA = 1

    // Configure PA3 (XP) for GPIO LOW
    GPIO_PORTA_AFSEL_R &= ~PA3; // ASFEL = 0
    GPIO_PORTA_DEN_R |= PA3;    // DEN = 1
    GPIO_PORTA_DIR_R |= PA3;    // DIR = 1
    GPIO_PORTA_DATA_R &= ~PA3;  // DATA = 0

    // Configure PE5 (YP) for analog hi-Z
    GPIO_PORTE_AFSEL_R &= ~PE5; // AFSEL = 0
    GPIO_PORTE_DEN_R &= ~PE5;   // DEN = 0
    GPIO_PORTE_DIR_R &= ~PE5;   // DIR = 0

    // Configure PE4 (XN) for ADC use
    GPIO_PORTE_AMSEL_R |= PE4; // AMSEL = 1
    GPIO_PORTE_AFSEL_R |= PE4; // AFSEL = 1
    GPIO_PORTE_DEN_R &= ~PE4;  // DEN = 0
    //GPIO_PORTE_DIR_R    &= ~PE4;       // DIR = 0

    // Configure ADC to read from AIN9 (PE4, XN)
    ADC_SetChannel(9);

    // Take some samples to average
    for (i = 0; i < NUM_SAMPLES; i++)
    {
        sum += ADC_Read();
    }

    // Compute average
    result = sum / NUM_SAMPLES;

    return result;
}

// ************** ADC_ReadZ1 *******************************
// -
// *********************************************************
// Input: none
// Output: none
// *********************************************************
unsigned long Touch_ReadZ2(void)
{
    long i = 0;
    long sum = 0;
    long result = 0;

    // Configure PA2 (YN) for GPIO HIGH
    GPIO_PORTA_AFSEL_R &= ~PA2; // ASFEL = 0
    GPIO_PORTA_DEN_R |= PA2;    // DEN = 1
    GPIO_PORTA_DIR_R |= PA2;    // DIR = 1
    GPIO_PORTA_DATA_R |= PA2;   // DATA = 1

    // Configure PA3 (XP) for GPIO LOW
    GPIO_PORTA_AFSEL_R &= ~PA3; // ASFEL = 0
    GPIO_PORTA_DEN_R |= PA3;    // DEN = 1
    GPIO_PORTA_DIR_R |= PA3;    // DIR = 1
    GPIO_PORTA_DATA_R &= ~PA3;  // DATA = 0

    // Configure PE4 (XN) for analog hi-Z
    GPIO_PORTE_AFSEL_R &= ~PE4; // AFSEL = 0
    GPIO_PORTE_DEN_R &= ~PE4;   // DEN = 0
    GPIO_PORTE_DIR_R &= ~PE4;   // DIR = 0
    GPIO_PORTE_AMSEL_R &= ~PE4; // AMSEL = 0

    // Configure PE5 (YP) for ADC use
    GPIO_PORTE_AFSEL_R |= PE5; // AFSEL = 1
    GPIO_PORTE_DEN_R &= ~PE5;  // DEN = 0
    GPIO_PORTE_DIR_R &= ~PE5;  // DIR = 0
    GPIO_PORTE_AMSEL_R |= PE5; // AMSEL = 1

    // Configure ADC to read from AIN9 (PE5, YP)
    ADC_SetChannel(8);

    // Take some samples to average
    for (i = 0; i < NUM_SAMPLES; i++)
    {
        sum += ADC_Read();
    }

    // Compute average
    result = sum / NUM_SAMPLES;

    return result;
}

//! Doesn't work because there's no disable/enable functionality
void Touch_BeginWaitForTouch(void)
{
    // XP = 1  XN = DIG IN, INT ON FALL EDGE YP = Hi-Z YN = 0
    DisableInterrupts();

    // Set XP high
    TOUCH_XP = 0xFF;

    // Set YN low
    TOUCH_YN = 0x00;

    // Configure XN (PA3) for digital input
    GPIO_PORTA_DIR_R &= ~0x08;

    // Configure YP (PE5) for analog Hi-Z
    GPIO_PORTE_DIR_R &= ~0x20;
    GPIO_PORTE_DEN_R &= ~0x20;

    // Setup falling edge interrupt on XN (PA3)
    GPIO_PORTA_PUR_R |= 0x08;  // enable weak pull up
    GPIO_PORTA_IS_R &= ~0x08;  // (d) PF4 is edge-sensitive
    GPIO_PORTA_IBE_R &= ~0x08; //     PF4 is not both edges
    GPIO_PORTA_IEV_R &= ~0x08; //     PF4 falling edge event
    GPIO_PORTA_ICR_R = 0x08;   // (e) clear flag4
    GPIO_PORTA_IM_R |= 0x08;   // (f) arm interrupt on PF4

    NVIC_PRI0_R = (NVIC_PRI7_R & 0xFFFFFF00) | 0x000000a0;
    NVIC_EN0_R = 1; // (h) enable IRQ=0, interrupt 16 in NVIC

    EnableInterrupts();
}

long Touch_GetCoords(void)
{
    long result, temp, xPos, yPos;

    long cal[7] = {
        280448,     //   86784,          // M0
        -3200,      // -1536,          // M1
        -220093760, //-17357952,      // M2
        -3096,      //-144,           // M3
        -275592,    //-78576,         // M4
        866602824,  // 69995856,       // M5
        2287498     //201804,         // M6
    };

    xPos = Touch_XVal;
    yPos = Touch_YVal;

    temp = (((xPos * cal[0]) + (yPos * cal[1]) + cal[2]) / cal[6]);
    yPos = (((xPos * cal[3]) + (yPos * cal[4]) + cal[5]) / cal[6]);
    xPos = temp;

    result = xPos << 16;
    result += yPos;

    return result;
}

int integer;
int decimal;
unsigned long counter;
unsigned long buttonCount;
enum movement{sfrog, stwist, sdisco, ssway, sneutral};
enum movement movementState = sneutral; // default movementState is neutral
int frogP;
int twistP;
int discoP;
int swayP; 

// Set up servos
#define d90  4875 // CMP value for 90 degree
#define nd90 4375 // CMP value for -90 degree
#define d80  4750 // CMP value for 80 degree
#define nd80 4500 // CMP value for -80 degree
#define d0   4625 // CMP value for 0 degree
uint16_t cmpN90 = nd80; 
uint16_t cmp0   = d0;   
uint16_t cmp90  = d80;
uint16_t cmp1, cmp2, cmp;
int count = 0;

void Timer0_Init(volatile unsigned long);
void ADC1_Init(void);
void ADC1_Handler(void);
void printFloat(float value);
//enum movement systemSwitch(enum colors color);
int frogPress(void);
int twistPress(void);
int discoPress(void);
int swayPress(void);
void Setup_PWM(void);
void Setup_GPIO(void);
void sway(void);
void disco (void);
void twist(void);
void frog(void);
void Stop(void);
void sayHi(void);
void sayHi1(void);
void sayHi2(void);
void sayHi3(void);
void Hola(void);
void neutralScreen(void);
void stopScreen(void);

int main() {
  Timer0_Init(16000000);
  Touch_Init();
  LCD_Init();
  Setup_PWM();
  Setup_GPIO();
  
  // sets up LCD push buttons on screen
  invisible = 0;
  neutralScreen(); 
  
  // Set text cursor to top left of screen
  LCD_SetCursor(0, 0);
  counter = 0;
  
  // Set up servo
  cmp = cmp0;
  PWM1_2_CMPA = cmp0;
  PWM1_2_CMPB = cmp0;
  PWM1_3_CMPA = cmp0;
  PWM1_3_CMPB = cmp0;
  
  Hola();
  movementState = sneutral;
  
  while (1) {
    Touch_ReadX();
    Touch_ReadY();
    frogP  = frogPress();
    twistP = twistPress();
    discoP = discoPress();
    swayP  = swayPress(); 
    
    LCD_SetCursor(0, 0);
    //LCD_PrintInteger(movementState);
    //LCD_PrintInteger(Touch_XVal); LCD_PrintChar(','); LCD_PrintInteger(Touch_YVal); LCD_PrintString("\n\r");
    // LCD_ColorFill(Color4[0]); // clears the screen
    
    if(!(((2630 >= Touch_XVal) && (Touch_XVal >= 2600)) && ((1720 >= Touch_YVal) && (Touch_YVal >= 1700)))) {
      if(movementState == sneutral) {
        if(frogP == 1) {
          movementState = sfrog;
        } else if(discoP == 1) {
          movementState = sdisco;
        } else if(twistP == 1) {
          movementState = stwist;
        } else if(swayP == 1) {
          movementState = ssway;
        }
      } else {
        if((frogP == 1) || (discoP == 1) || (twistP == 1) || (swayP == 1)) {
          neutralScreen();
          movementState = sneutral;
        }
      }
    }
    
    if(movementState == sneutral) {
      neutralScreen();
      LCD_SetCursor(0, 0);
      LCD_PrintInteger(movementState);
      Stop();
    } else if(movementState == sfrog) {
      stopScreen();
      frog();
    } else if(movementState == stwist) {
      stopScreen();
      twist();
    } else if(movementState == ssway) {
      stopScreen();
      sway();
    } else if(movementState == sdisco) {
      stopScreen();
      disco();
    } 
  }
  return 1;
}

// Initializes the timer
// configured to trigger the ADC
// take in a variable for determining clock speed
void Timer0_Init(volatile unsigned long count) {
    RCGCTIMER_TIMERn |= 0x01;  // Enable and provide a clock to 16/32-bit general-purpose timer module 0 in Run mode.
    GPTMCTL_TIMER0    = 0x0;   // The goal of this line: Timer A is disabled.
    GPTMCFG_TIMER0    = 0x0;   // 0x0: For a 16/32-bit timer, this value selects the 32-bit timer configuration.
    GPTMTAMR_TIMER0  |= 0x2;   // set TIMER A Direction: count down set and TIMER A mode: Periodic Timer mode //!note: timer counts down by default
    GPTMTAILR_TIMER0  = count; // Load max count value the GPTMTAILR.
    GPTMCTL_TIMER0   |= 0x20;  // The output Timer A ADC trigger is enabled.
    GPTMCTL_TIMER0   |= 0x1;   // Timer A is enabled and begins counting or the capture logic is enabled based on the GPTMCFG register.
}

// Print floater type
void printFloat(float value) {
    integer = (int)(value*100.0);
    decimal = (int)(integer%100);
    LCD_PrintInteger(integer/100);
    LCD_PrintChar('.');
    LCD_PrintInteger(decimal);
    LCD_PrintString("\n\r");
}

// Check to see if the turtle button has been clicked
int frogPress(void) {
  if((3250 >= Touch_XVal) && (Touch_XVal >= 2500) && (2850 >= Touch_YVal) && (Touch_YVal >= 2200)) {
    return 1;
  } else {
    return 0;
  }
}

// Check to see if the march button has been clicked
int twistPress(void) {
  if((1900 >= Touch_XVal) && (Touch_XVal >= 1200) && (2850 >= Touch_YVal) && (Touch_YVal >= 2300)) {
    return 1;
  } else {
    return 0;
  }
}

// Check to see if the cheetah button has been clicked
int discoPress(void) {
  if((3250 >= Touch_XVal) && (Touch_XVal >= 2600) && (1675 >= Touch_YVal) && (Touch_YVal >= 1360)) {
    return 1;
  } else {
    return 0;
  }
}

// Check to see if the sway button has been clicked
int swayPress(void) {
  if((2000 >= Touch_XVal) && (Touch_XVal >= 1200) && (1900 >= Touch_YVal) && (Touch_YVal >= 1375)) {
    return 1;
  } else {
    return 0;
  }
}
 
void frog(void) {
    PWM1_3_CMPA = cmpN90; // yellow
    PWM1_3_CMPB = cmp90;  // purple
    PWM1_2_CMPB = cmp90;  // blue
    PWM1_2_CMPA = cmpN90; // green
    for (int j = 0; j < 2000000 /*800000*/; j++) {} //~50ms wait
    PWM1_3_CMPA = cmp90; // yellow
    PWM1_3_CMPB = cmpN90; // purple
    for (int j = 0; j < 500000 /*800000*/; j++) {} // shorter wait
    PWM1_2_CMPB = cmp0; // blue
    PWM1_2_CMPA = cmp0; // green
    for (int j = 0; j < 2000000 /*800000*/; j++) {} //~50ms wait
}

void disco (void) {
    cmpN90 = 4750/* 4875*/; // CMP value for 0 degree
    cmp90 = 4500 /* 4375*/;  // CMP value for 180 degree
    PWM1_2_CMPA = cmpN90; //green
    PWM1_3_CMPA = cmp90; // yellow
    PWM1_2_CMPB = cmpN90; // blue
    PWM1_3_CMPB = cmp90; // purple
    for (int j = 0; j < 2000000 /*800000*/; j++) {} //~50ms wait
    PWM1_2_CMPA = cmp90; //green
    PWM1_3_CMPA = cmpN90; // yellow
    PWM1_2_CMPB = cmp90; // blue
    PWM1_3_CMPB = cmpN90; // purple
    for (int j = 0; j < 2000000 /*800000*/; j++) {} //~50ms wait
}

void sway(void) {
    PWM1_2_CMPA = cmp90;
    PWM1_3_CMPB = cmp90;
    PWM1_3_CMPA = cmpN90;
    PWM1_2_CMPB = cmpN90;
    for (int j = 0; j < 2000000 /*800000*/; j++) {} //~50ms wait
    PWM1_2_CMPA = cmpN90;
    PWM1_3_CMPB = cmpN90;
    PWM1_3_CMPA = cmp90;
    PWM1_2_CMPB = cmp90;
    for (int j = 0; j < 2000000 /*800000*/; j++) {} //~50ms wait
}

void twist(void) {
    PWM1_2_CMPA = cmp90;
    PWM1_3_CMPB = cmp90;
    PWM1_3_CMPA = cmp90;
    PWM1_2_CMPB = cmp90;

    for (int j = 0; j < 2000000 /*800000*/; j++) {} //~50ms wait
    PWM1_2_CMPA = cmpN90;
    PWM1_3_CMPB = cmpN90;
    PWM1_3_CMPA = cmpN90;
    PWM1_2_CMPB = cmpN90;
    for (int j = 0; j < 2000000 /*800000*/; j++) {} //~50ms wait
}
//------------------------------------------------------------------------------
void Setup_PWM(void) {
    // GPIO for PWM: PF0
    // M1PWM4 - PWM Module 1, generator 2, PWM4
    // SysClk = 16000000 Hz, PWMDIV = /64, Freq for PWMTimer = 250000 Hz
    // PWM frequency = 50 Hz
    // LOAD = 5000
    // CMP = 4625

    // 1. Enable Clock for PWM Modules
    RCGCPWM |= (1u << 1);
    while ((PRPWM & (0x2)) != (0x2)) {};
    // 2. Enable and Setup Clock Divider for PWM Timer
    RCC |= (1 << 20);    // RCC[20]=1:USEPWMDIV
    RCC &= ~(0x7 << 17); // RCC[19:17]=000 PWMDIV
    RCC |= (0x7 << 17);  // RCC[19:17] PWMDIV value
    // 3. Disable PWM Generator and Setup the Timer Counting Mode
    PWM1_2_CTL = 0x00; // Disable PWM Generator, and set to count-down mode
    PWM1_3_CTL = 0x00; // Disable PWM Generator, and set to count-down mode

    // 4. Configure LOAD (Period), CMP (Duty), GEN (PWM Mode) values
    PWM1_2_LOAD = 4999; // Setup the period of the PWM signal
    PWM1_3_LOAD = 4999; // Setup the period of the PWM signal

    PWM1_2_CMPA = 4625; // Setup the initial duty cycle
    PWM1_2_CMPB = 4625; // Setup the initial duty cycle

    PWM1_3_CMPA = 4625; // Setup the initial duty cycle
    PWM1_3_CMPB = 4625; // Setup the initial duty cycle

    PWM1_2_GENA = (0x3 << 2) | (0x2 << 6);  // generate Left-Aligned PWM
    PWM1_2_GENB = (0x3 << 2) | (0x2 << 10); // generate Left-Aligned PWM // TODO double check register config

    PWM1_3_GENA = (0x3 << 2) | (0x2 << 6);  // generate Left-Aligned PWM
    PWM1_3_GENB = (0x3 << 2) | (0x2 << 10); // generate Left-Aligned PWM // TODO double check register config

    // 5. Enable PWM Generator
    PWM1_2_CTL |= 0x1;
    PWM1_3_CTL |= 0x1;

    // 6. Enable PWM Output
    PWM1_ENABLE = 0xF0; // 0x30;     // Enable PWMx
                        // The generated pwm3B' signal is passed to the MnPWM7 pin
                        // The generated pwm3A' signal is passed to the MnPWM6 pin.
                        // The generated pwm2B' signal is passed to the MnPWM5 pin.
                        // The generated pwm2A' signal is passed to the MnPWM4 pin.
}
void Setup_GPIO(void) {
    // GPIO Initialization and Configuration
    // 1. Enable Clock to the GPIO Modules (SYSCTL->RCGCGPIO)
    RCGCGPIO |= (0x20);
    // allow time for clock to stabilize (SYSCTL->PRGPIO)
    while ((PRGPIO & (0x20)) != (0x20)) {};

    // 2. Unlock GPIO only PD7, PF0 on TM4C123G; PD7, PE7 on TM4C1294 (GPIO->LOCK and GPIO->CR)
    GPIO_PORT_F_LOCK = 0x4C4F434B; // The GPIOCR register is unlocked and may be modified
    GPIO_PORT_F_CR = 0x1;          // GPIOCR register must be configured

    // 3. Set Analog Mode Select bits for each Port (GPIO->AMSEL 0=digital, 1=analog)
    // GPIO_PORT_F_AMSEL //? non needded worked without
    // 4. Set Port Control Register for each Port (GPIO->PCTL, check the PCTL table)
    GPIOF_PCTL = 0x5555;
    // 5. Set Alternate Function Select bits for each Port (GPIO->AFSEL 0=regular I/O, 1=PCTL peripheral)
    GPIOF_AFSEL |= 0xF; // Enable alternate function

    // 6. Set Output pins for each Port (Direction of the Pins: GPIO->DIR 0=input, 1=output)
    GPIO_PORT_F_DIR |= 0xF; // set PF0 as output

    // 7. Set PUR bits for internal pull-up, PDR for pull-down reg, ODR for open drain (0: disable, 1=enable)
    // GPIO_PORT_F_PDR
    // 8. Set Digital ENable register on all GPIO pins (GPIO->DEN 0=disable, 1=enable)
    GPIO_PORT_F_DEN = 0xF;
}

void Stop(void) {
    PWM1_2_CMPA = cmp0;
    PWM1_2_CMPB = cmp0;
    PWM1_3_CMPA = cmp0;
    PWM1_3_CMPB = cmp0;
}

void Hola(void) {
   sayHi();
   sayHi1(); 
   sayHi2();
   sayHi3();
}

void sayHi(void) {
    for (int j = 0; j < 400000; j++) {}
    PWM1_2_CMPA = cmpN90;
    for (int j = 0; j < 1000000; j++) {}
    PWM1_2_CMPA = cmp0;
    for (int j = 0; j < 1000000; j++) {}
    PWM1_2_CMPA = cmpN90;
    for (int j = 0; j < 1000000; j++) {}
    PWM1_2_CMPA = cmp0;
    for (int j = 0; j < 1000000; j++) {}
}

void sayHi1(void) {
   PWM1_2_CMPB = cmp90;
    for (int j = 0; j < 1000000; j++) {}
    PWM1_2_CMPB = cmp0;
    for (int j = 0; j < 1000000; j++) {}
    PWM1_2_CMPB = cmp90;
    for (int j = 0; j < 1000000; j++) {}
    PWM1_2_CMPB = cmp0;
    for (int j = 0; j < 1000000; j++) {}
}

void sayHi2(void) {
    PWM1_3_CMPA = cmpN90;
    for (int j = 0; j < 1000000; j++) {}
    PWM1_3_CMPA = cmp0;
    for (int j = 0; j < 1000000; j++) {}
    PWM1_3_CMPA = cmpN90;
    for (int j = 0; j < 1000000; j++) {}
    PWM1_3_CMPA = cmp0;
    for (int j = 0; j < 1000000; j++) {}
}

void sayHi3(void) {
    PWM1_3_CMPB = cmp90;
    for (int j = 0; j < 1000000; j++) {}
    PWM1_3_CMPB = cmp0;
    for (int j = 0; j < 1000000; j++) {}
    PWM1_3_CMPB = cmp90;
    for (int j = 0; j < 1000000; j++) {}
    PWM1_3_CMPB = cmp0;
    for (int j = 0; j < 1000000; j++) {}
}

// Draw neutral screen
void neutralScreen(void) {
  LCD_SetCursor(0, 0);
  LCD_PrintInteger(movementState);
  LCD_DrawFilledRect(0, 0, 160, 120, Color4[2]);
  LCD_SetCursor(60, 60);
  LCD_PrintString("Frog"); 
  LCD_DrawFilledRect(160, 0, 160, 120, Color4[4]);
  LCD_SetCursor(230, 60);
  LCD_PrintString("Twist"); 
  LCD_DrawFilledRect(0, 120, 160, 120, Color4[14]);
  LCD_SetCursor(60, 180);
  LCD_PrintString("Disco"); 
  LCD_DrawFilledRect(160, 120, 160, 120, Color4[11]);
  LCD_SetCursor(230, 180);
  LCD_PrintString("Sway");
}

// Draw Stop screen
void stopScreen(void) {
  // set background
  LCD_SetCursor(0, 0);
  LCD_PrintInteger(movementState);
  LCD_ColorFill(Color4[12]);
  LCD_SetCursor(145, 120);
  LCD_PrintString("Stop");
  LCD_SetCursor(0, 0);
  LCD_PrintInteger(movementState);
}

