#include <stdint.h>
#include "tm4c123gh6pm.h"
#include <ChentyleLab5.h>
// #include "SSD2119.h"

//#include <stdio.h>
//#include <stdlib.h>
//#include <stdint.h>
//#include <stdbool.h>

//#include "ez123G.h"     // ezTivaLIB
uint16_t cmpN90 = 4875/* 4750 4875*/; // CMP value for 0 degree
uint16_t cmp0 = 4625;   // CMP value for 0 degree
uint16_t cmp90 = 4375 /* 4500 4375*/;  // CMP value for 180 degree
uint16_t cmp1, cmp2, cmp;
int count = 0;

void Setup_PWM(void);
void Setup_GPIO(void);

void sway(void);
void cheeta (void);
void leftRight(void);
void turtle(void);
void Stop(void);
void sayHi(void);
void sayHi1(void);
void sayHi2(void);
void sayHi3(void);
void Hola(void);


int main()
{
    //    uint16_t cmp1, cmp2, cmp;

    Setup_PWM();
    Setup_GPIO();

    cmp = cmp0;
    Stop();
    Hola();
    // update PWM CMP register value in range of cmp90 ~ cmpN90
    while (1)
    {
//      turtle();
        cheeta();
//      sway();
//      leftRight();
      
    }
}
void Hola(void)
{
    sayHi();
   sayHi1(); 
   sayHi2();
   sayHi3();
}


void sayHi(void) 
{
   for (int j = 0; j < 16000000; j++)
    {
    }
    PWM1_2_CMPA = cmp90;
    for (int j = 0; j < 1000000; j++)
    {
    }
    PWM1_2_CMPA = cmp0;
    for (int j = 0; j < 1000000; j++)
    {
    }
    PWM1_2_CMPA = cmp90;
    for (int j = 0; j < 1000000; j++)
    {
    }
    PWM1_2_CMPA = cmp0;
    for (int j = 0; j < 1000000; j++)
    {
    }
}

void sayHi1(void) 
{
    PWM1_2_CMPB = cmpN90;
    for (int j = 0; j < 1000000; j++)
    {
    }
    PWM1_2_CMPB = cmp0;
    for (int j = 0; j < 1000000; j++)
    {
    }
    PWM1_2_CMPB = cmpN90;
    for (int j = 0; j < 1000000; j++)
    {
    }
    PWM1_2_CMPB = cmp0;
    for (int j = 0; j < 1000000; j++)
    {
    }
}

void sayHi2(void) 
{
    PWM1_3_CMPA = cmpN90;
    for (int j = 0; j < 1000000; j++)
    {
    }
    PWM1_3_CMPA = cmp0;
    for (int j = 0; j < 1000000; j++)
    {
    }
    PWM1_3_CMPA = cmpN90;
    for (int j = 0; j < 1000000; j++)
    {
    }
    PWM1_3_CMPA = cmp0;
    for (int j = 0; j < 1000000; j++)
    {
    }
}

void sayHi3(void) 
{
    PWM1_3_CMPB = cmp90;
    for (int j = 0; j < 1000000; j++)
    {
    }
    PWM1_3_CMPB = cmp0;
    for (int j = 0; j < 1000000; j++)
    {
    }
    PWM1_3_CMPB = cmp90;
    for (int j = 0; j < 1000000; j++)
    {
    }
    PWM1_3_CMPB = cmp0;
    for (int j = 0; j < 1000000; j++)
    {
    }
}
void Stop(void)
{
    PWM1_2_CMPA = cmp0;
    PWM1_2_CMPB = cmp0;
    PWM1_3_CMPA = cmp0;
    PWM1_3_CMPB = cmp0;
}
 
void turtle(void)
{
    PWM1_2_CMPA = cmp90;
    PWM1_2_CMPB = cmpN90;

    for (int j = 0; j < 2000000 /*800000*/; j++) //~50ms wait
    {
    }
    
    PWM1_3_CMPA = cmpN90;
    PWM1_3_CMPB = cmp90;
    for (int j = 0; j < 2000000 /*800000*/; j++) //~50ms wait
    {
    }
   
    PWM1_3_CMPA = cmp90;
    PWM1_3_CMPB = cmpN90;
    for (int j = 0; j < 2000000 /*800000*/; j++) //~50ms wait
    {
    }
}

void cheeta (void)
{
    cmpN90 = 4750/* 4875*/; // CMP value for 0 degree
    cmp90 = 4500 /* 4375*/;  // CMP value for 180 degree
    PWM1_2_CMPA = cmp90;
    PWM1_2_CMPB = cmpN90;

    for (int j = 0; j < 2000000 /*800000*/; j++) //~50ms wait
    {
    }
    
    
    PWM1_3_CMPA = cmp90;
    PWM1_3_CMPB = cmpN90;
    

    for (int j = 0; j < 2000000 /*800000*/; j++) //~50ms wait
    {
    }
    
    PWM1_2_CMPA = cmp0;
    PWM1_2_CMPB = cmp0;
    for (int j = 0; j < 2000000 /*800000*/; j++) //~50ms wait
    {
    }
    
    PWM1_3_CMPA = cmp0;
    PWM1_3_CMPB = cmp0;
    for (int j = 0; j < 2000000 /*800000*/; j++) //~50ms wait
    {
    }
}

void sway(void)
{
    cmpN90 = 4750; // CMP value for 0 degree
    cmp90 = 4500;  // CMP value for 180 degree
    PWM1_2_CMPA = cmp90;
    PWM1_3_CMPB = cmp90;

    PWM1_3_CMPA = cmpN90;
    PWM1_2_CMPB = cmpN90;

    for (int j = 0; j < 2000000 /*800000*/; j++) //~50ms wait
    {
    }
    PWM1_2_CMPA = cmpN90;
    PWM1_3_CMPB = cmpN90;

    PWM1_3_CMPA = cmp90;
    PWM1_2_CMPB = cmp90;
    for (int j = 0; j < 2000000 /*800000*/; j++) //~50ms wait
    {
    }
}

void leftRight(void)
{
    PWM1_2_CMPA = cmp90;
    PWM1_3_CMPB = cmp90;

    PWM1_3_CMPA = cmp90;
    PWM1_2_CMPB = cmp90;

    for (int j = 0; j < 2000000 /*800000*/; j++) //~50ms wait
    {
    }
    PWM1_2_CMPA = cmpN90;
    PWM1_3_CMPB = cmpN90;

    PWM1_3_CMPA = cmpN90;
    PWM1_2_CMPB = cmpN90;
    for (int j = 0; j < 2000000 /*800000*/; j++) //~50ms wait
    {
    }
}
//------------------------------------------------------------------------------
void Setup_PWM(void)
{
    // GPIO for PWM: PF0
    // M1PWM4 - PWM Module 1, generator 2, PWM4
    // SysClk = 16000000 Hz, PWMDIV = /64, Freq for PWMTimer = 250000 Hz
    // PWM frequency = 50 Hz
    // LOAD = 5000
    // CMP = 4625

    // 1. Enable Clock for PWM Modules
    RCGCPWM |= (1u << 1);
    while ((PRPWM & (0x2)) != (0x2))
    {
    };
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
void Setup_GPIO(void)
{
    // GPIO Initialization and Configuration
    // 1. Enable Clock to the GPIO Modules (SYSCTL->RCGCGPIO)
    RCGCGPIO |= (0x20);
    // allow time for clock to stabilize (SYSCTL->PRGPIO)
    while ((PRGPIO & (0x20)) != (0x20))
    {
    };

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