// Masks
#define s1M 0x01 // 0000 0001
#define s2M 0x10 // 0001 0000

//colors
#define RED 0x02
#define GREEN 0x08
#define BLUE 0x04
#define VIOLET (RED | BLUE)
#define YELLOW (GREEN | RED)
#define LIGHT_BLUE (GREEN | BLUE)
#define RGB (GREEN | RED | BLUE) // same as 0x0E

//*****************************************************************************
// Enable the clock to the appropriate GPIO module
// (RCGCGPIO), offset 0x608, Base RCGCGPIO 0x400FE000
// Here we "give a name" to the RCGCGPIO adress
// basically we have a pointer to the address of the register
//*****************************************************************************
#define RCGCGPIO (*((unsigned long *)0x400FE608))

//*****************************************************************************
// Data Direction Operation
// GPIO Direction (GPIODIR)
// Set the direction of the GPIO port pins by programming the GPIODIR register.
// A write of a 1 indicates output and a write of a 0 indicates input.
//*****************************************************************************
#define GPIO_PORT_A_DIR (*((unsigned long *)0x40004400))
#define GPIO_PORT_Aa_DIR (*((unsigned long *)0x40058400))
#define GPIO_PORT_B_DIR (*((unsigned long *)0x40005400))
#define GPIO_PORT_Bb_DIR (*((unsigned long *)0x40059400))
#define GPIO_PORT_C_DIR (*((unsigned long *)0x40006400))
#define GPIO_PORT_Cc_DIR (*((unsigned long *)0x4005A400))
#define GPIO_PORT_D_DIR (*((unsigned long *)0x40007400))
#define GPIO_PORT_Dd_DIR (*((unsigned long *)0x4005B400))
#define GPIO_PORT_E_DIR (*((unsigned long *)0x40024400))
#define GPIO_PORT_Ee_DIR (*((unsigned long *)0x4005C400))
#define GPIO_PORT_F_DIR (*((unsigned long *)0x40025400))
#define GPIO_PORT_Ff_DIR (*((unsigned long *)0x4005D400))
//*****************************************************************************
// GPIO Data (GPIODATA)
// GPIO Port F (APB) base: 0x4002.5000
// specify the port data by the bits [9:2] in the address
// [9:2] = 0x3FC = 1111100
//*****************************************************************************
#define GPIO_PORT_A_DATA (*((unsigned long *)0x400043FC))
#define GPIO_PORT_Aa_DATA (*((unsigned long *)0x400583FC))
#define GPIO_PORT_B_DATA (*((unsigned long *)0x400053FC))
#define GPIO_PORT_Bb_DATA (*((unsigned long *)0x400593FC))
#define GPIO_PORT_C_DATA (*((unsigned long *)0x400063FC))
#define GPIO_PORT_Cc_DATA (*((unsigned long *)0x4005A3FC))
#define GPIO_PORT_D_DATA (*((unsigned long *)0x400073FC))
#define GPIO_PORT_Dd_DATA (*((unsigned long *)0x4005B3FC))
#define GPIO_PORT_E_DATA (*((unsigned long *)0x400243FC))
#define GPIO_PORT_Ee_DATA (*((unsigned long *)0x4005C3FC))
#define GPIO_PORT_F_DATA (*((unsigned long *)0x400253FC))
#define GPIO_PORT_Ff_DATA (*((unsigned long *)0x4005D3FC))
//*****************************************************************************
// Register 19: GPIO Lock (GPIOLOCK), offset 0x520
// GPIOLOCK register enables write access to the GPIOCR register
// Writing 0x4C4F434B to the GPIOLOCK register unlocks the GPIOCR register. Writing any other value to
// the GPIOLOCK register re-enables the locked state.
//
// GPIO Port F (APB) base: 0x4002.5000
// Offset 0x520
//*****************************************************************************
#define GPIO_PORT_A_LOCK (*((unsigned long *)0x40004520))
#define GPIO_PORT_Aa_LOCK (*((unsigned long *)0x40058520))
#define GPIO_PORT_B_LOCK (*((unsigned long *)0x40005520))
#define GPIO_PORT_Bb_LOCK (*((unsigned long *)0x40059520))
#define GPIO_PORT_C_LOCK (*((unsigned long *)0x40006520))
#define GPIO_PORT_Cc_LOCK (*((unsigned long *)0x4005A520))
#define GPIO_PORT_D_LOCK (*((unsigned long *)0x40007520))
#define GPIO_PORT_Dd_LOCK (*((unsigned long *)0x4005B520))
#define GPIO_PORT_E_LOCK (*((unsigned long *)0x40024520))
#define GPIO_PORT_Ee_LOCK (*((unsigned long *)0x4005C520))
#define GPIO_PORT_F_LOCK (*((unsigned long *)0x40025520))
#define GPIO_PORT_Ff_LOCK (*((unsigned long *)0x4005D520))
//*****************************************************************************
// Register 20: GPIO Commit (GPIOCR), offset 0x524
//
// The GPIOCR register is the commit register. The value of the GPIOCR register determines which
// bits of the GPIOAFSEL, GPIOPUR, GPIOPDR, and GPIODEN registers are committed when a
// write to these registers is performed.
// GPIO Port F (APB) base: 0x4002.5000
// Offset 0x524
//*****************************************************************************
#define GPIO_PORT_A_CR (*((unsigned long *)0x40004524))
#define GPIO_PORT_Aa_CR (*((unsigned long *)0x40058524))
#define GPIO_PORT_B_CR (*((unsigned long *)0x40005524))
#define GPIO_PORT_Bb_CR (*((unsigned long *)0x40059524))
#define GPIO_PORT_C_CR (*((unsigned long *)0x40006524))
#define GPIO_PORT_Cc_CR (*((unsigned long *)0x4005A524))
#define GPIO_PORT_D_CR (*((unsigned long *)0x40007524))
#define GPIO_PORT_Dd_CR (*((unsigned long *)0x4005B524))
#define GPIO_PORT_E_CR (*((unsigned long *)0x40024524))
#define GPIO_PORT_Ee_CR (*((unsigned long *)0x4005C524))
#define GPIO_PORT_F_CR (*((unsigned long *)0x40025524))
#define GPIO_PORT_Ff_CR (*((unsigned long *)0x4005D524))
//*****************************************************************************
// Register 15: GPIO Pull-Up Select (GPIOPUR), offset 0x510
//
// The GPIOPUR register is the pull-up control register. When a bit is set, a weak pull-up resistor on
// the corresponding GPIO signal is enabled.
//
// GPIO PORT F (APB) base: 0x4002.5000
// Offset 0x510
//*****************************************************************************
#define GPIO_PORT_A_PUR (*((unsigned long *)0x40004510))
#define GPIO_PORT_Aa_PUR (*((unsigned long *)0x40058510))
#define GPIO_PORT_B_PUR (*((unsigned long *)0x40005510))
#define GPIO_PORT_Bb_PUR (*((unsigned long *)0x40059510))
#define GPIO_PORT_C_PUR (*((unsigned long *)0x40006510))
#define GPIO_PORT_Cc_PUR (*((unsigned long *)0x4005A510))
#define GPIO_PORT_D_PUR (*((unsigned long *)0x40007510))
#define GPIO_PORT_Dd_PUR (*((unsigned long *)0x4005B510))
#define GPIO_PORT_E_PUR (*((unsigned long *)0x40024510))
#define GPIO_PORT_Ee_PUR (*((unsigned long *)0x4005C510))
#define GPIO_PORT_F_PUR (*((unsigned long *)0x40025510))
#define GPIO_PORT_Ff_PUR (*((unsigned long *)0x4005D510))

// This register controls the clock gating logic in normal Run mode. Each bit controls a clock enablefor a given interface, function, or module
// Base 0x400F.E000
// Offset 0x108
#define RCGC2_PA (*((unsigned long *)0x400FE108))
// Offset 0x100
#define RCGC0_PA (*((unsigned long *)0x400FE100))

// Register 22: GPIO Port Control (GPIOPCTL), offset 0x52C
// The GPIOPCTL register is used in conjunction with the GPIOAFSEL register and selects the specific
// peripheral signal for each GPIO pin when using the alternate function mode. Most bits in the
// GPIOAFSEL register are cleared on reset, therefore most GPIO pins are configured as GPIOs by
// default. When a bit is set in the GPIOAFSEL register, the corresponding GPIO signal is controlled
// by an associated peripheral. The GPIOPCTL register selects one out of a set of peripheral functions
// for each GPIO, providing additional flexibility in signal definition. For information on the defined
// encodings for the bit fields in this register, refer to Table 23-5 on page 1351. The reset value for this
// register is 0x0000.0000 for GPIO ports that are not listed in the table below.
// Note: If a particular input signal to a peripheral is assigned to two different GPIO port pins, the
// signal is assigned to the port with the lowest letter and the assignment to the higher letter
// port is ignored. If a particular output signal from a peripheral is assigned to two different
// GPIO port pins, the signal will output to both pins. Assigning an output signal from a
// peripheral to two different GPIO pins is not recommended.
#define GPIO_PORT_A_PCTL  (*((unsigned long *)0x4000452C))
#define GPIO_PORT_Aa_PCTL (*((unsigned long *)0x4005852C))
#define GPIO_PORT_B_PCTL  (*((unsigned long *)0x4000552C))
#define GPIO_PORT_Bb_PCTL (*((unsigned long *)0x4005952C))
#define GPIO_PORT_C_PCTL  (*((unsigned long *)0x4000652C))
#define GPIO_PORT_Cc_PCTL (*((unsigned long *)0x4005A52C))
#define GPIO_PORT_D_PCTL  (*((unsigned long *)0x4000752C))
#define GPIO_PORT_Dd_PCTL (*((unsigned long *)0x4005B52C))
#define GPIO_PORT_E_PCTL  (*((unsigned long *)0x4002452C))
#define GPIO_PORT_Ee_PCTL (*((unsigned long *)0x4005C52C))
#define GPIOF_PCTL        (*((unsigned long *)0x4002552C))
#define GPIO_PORT_Ff_PCTL (*((unsigned long *)0x4005D52C))


// Register 21: GPIO Analog Mode Select (GPIOAMSEL), offset 0x528
// !Important:This register is only valid for ports and pins that can be used as ADC AINx inputs.
// !If any pin is to be used as an ADC input, the appropriate bit in GPIOAMSEL must beset to disable the analog isolation circuit.
// The GPIOAMSEL register controls isolation circuits to the analog side of a unified I/O pad.
// Because the GPIOs may be driven by a 5-V source and affect analog operation, analog circuitry requiresisolation from the pins when they are not used in their analog function.
// Each bit of this register controls the isolation circuitry for the corresponding GPIO signal.
// For information on which GPIO pins can be used for ADC functions, refer to Table 23-5 on page 1351.

#define GPIO_PORT_A_AMSEL (*((unsigned long *)0x40004528))
#define GPIO_PORT_Aa_AMSEL (*((unsigned long *)0x40058528))
#define GPIO_PORT_B_AMSEL (*((unsigned long *)0x40005528))
#define GPIO_PORT_Bb_AMSEL (*((unsigned long *)0x40059528))
#define GPIO_PORT_C_AMSEL (*((unsigned long *)0x40006528))
#define GPIO_PORT_Cc_AMSEL (*((unsigned long *)0x4005A528))
#define GPIO_PORT_D_AMSEL (*((unsigned long *)0x40007528))
#define GPIO_PORT_Dd_AMSEL (*((unsigned long *)0x4005B528))
#define GPIO_PORT_E_AMSEL (*((unsigned long *)0x40024528))
#define GPIO_PORT_Ee_AMSEL (*((unsigned long *)0x4005C528))
#define GPIO_PORT_F_AMSEL (*((unsigned long *)0x40025528))
#define GPIO_PORT_Ff_AMSEL (*((unsigned long *)0x4005D528))

// Register 10: GPIO Alternate Function Select (GPIOAFSEL), offset 0x420
// The mode control select register. If a bit is clear, the pin is used as aGPIO and is controlled by the GPIO registers.
// Setting a bit in this register configures thecorresponding GPIO line to be controlled by an associated peripheral.
// Several possible peripheralfunctions are multiplexed on each GPIO.
// The GPIO Port Control (GPIOPCTL)register is used to select one of the possible functions
#define GPIO_PORT_A_AFSEL (*((unsigned long *)0x40004420))
#define GPIO_PORT_Aa_AFSEL (*((unsigned long *)0x40058420))
#define GPIO_PORT_B_AFSEL (*((unsigned long *)0x40005420))
#define GPIO_PORT_Bb_AFSEL (*((unsigned long *)0x40059420))
#define GPIO_PORT_C_AFSEL (*((unsigned long *)0x40006420))
#define GPIO_PORT_Cc_AFSEL (*((unsigned long *)0x4005A420))
#define GPIO_PORT_D_AFSEL (*((unsigned long *)0x40007420))
#define GPIO_PORT_Dd_AFSEL (*((unsigned long *)0x4005B420))
#define GPIO_PORT_E_AFSEL (*((unsigned long *)0x40024420))
#define GPIO_PORT_Ee_AFSEL (*((unsigned long *)0x4005C420))
#define GPIOF_AFSEL       (*((unsigned long *)0x40025420))
#define GPIO_PORT_Ff_AFSEL (*((unsigned long *)0x4005D420))

// Register 18: GPIO Digital Enable (GPIODEN), offset 0x51C
// Note:Pins configured as digital inputs are Schmitt-triggered.
// TheGPIODENregister is the digital enable register.
// By default, all GPIO signals except those listedbelow are
// configured out of reset to be undriven (tristate). Their digital function is disabled;
// they donot drive a logic value on the pin and they do not allow the
// pin voltage into the GPIO receiver. Touse the pin as a digital input or output
// (either GPIO or alternate function), the correspondingGPIODENbit must be set.
#define GPIO_PORT_A_DEN (*((unsigned long *)0x4000451C))
#define GPIO_PORT_Aa_DEN (*((unsigned long *)0x4005851C))
#define GPIO_PORT_B_DEN (*((unsigned long *)0x4000551C))
#define GPIO_PORT_Bb_DEN (*((unsigned long *)0x4005951C))
#define GPIO_PORT_C_DEN (*((unsigned long *)0x4000651C))
#define GPIO_PORT_Cc_DEN (*((unsigned long *)0x4005A51C))
#define GPIO_PORT_D_DENL (*((unsigned long *)0x4000751C))
#define GPIO_PORT_Dd_DEN (*((unsigned long *)0x4005B51C))
#define GPIO_PORT_E_DEN (*((unsigned long *)0x4002451C))
#define GPIO_PORT_Ee_DEN (*((unsigned long *)0x4005C51C))
#define GPIO_PORT_F_DEN (*((unsigned long *)0x4002551C))
#define GPIO_PORT_Ff_DEN (*((unsigned long *)0x4005D51C))

// data register for port A
#define PORTA_DATA_R (*((unsigned long *)0x400043FC))

// Register 8: Run-Mode Clock Configuration (RCC), offset 0x060
// The bits in this register configure the system clock and oscillators.
// Important:Write theRCCregister prior to writing theRCC2register
// Run-Mode Clock Configuration (RCC)
// Base 0x400FE000

#define RCC (*((unsigned long *)0x400FE060))


//Register 10: Run-Mode Clock Configuration 2 (RCC2), offset 0x070
// This register overrides the RCC equivalent register fields, as shown in Table 5-8, when the USERCC2
// bit is set, allowing the extended capabilities of the RCC2 register to be used while also providing a
// means to be backward-compatible to previous parts. Each RCC2 field that supersedes an RCC
// field is located at the same LSB bit position; however, some RCC2 fields are larger than the
// corresponding RCC field.
#define RCC2 (*((unsigned long *)0x400FE070))

// Register 68: Analog-to-Digital Converter Run Mode Clock Gating Control(RCGCADC), offset 0x638
// TheRCGCADCregister provides software the capability to enable and disable the ADC modulesin Run mode.
// When enabled, a module is provided a clock and accesses to module registers are allowed.
// When disabled, the clock is disabled to save power and accesses to module registersgenerate a bus fault.
// This register provides the same capability as the legacy Run Mode ClockGating Control Register n RCGCn registers
// specifically for the watchdog modules and has thesame bit polarity as the corresponding RCGCn bits.
// Important:This register should be used to control the clocking for the ADC modules.
// To supportlegacy software, the RCGC0 register is available.
// A write to the RCGC0 register alsowrites the corresponding bit in this register.
// Any bits that are changed by writing to theRCGC0 register can be read back correctly with a read of the RCGC0 register.
// If softwareuses this register to write a legacy peripheral (such as ADC0), the write causes properoperation,
// but the value of that bit is not reflected in the RCGC0 register.
// If softwareuses both legacy and peripheral-specific register accesses, the peripheral-specificregisters
// must be accessed by read-modify-write operations that affect only peripherals that are not present in the legacy registers.
// In this manner, both the peripheral-specificand legacy registers have coherent information.

#define RCGCADC (*((unsigned long *)0x400FE638))

// timer Stuff
// ****************************************************************************************************
// 1.) Enable the appropriate TIMERn bit in the RCGCTIMER register.
// Register59:16/32-BitGeneral-PurposeTimerRunModeClockGatingControl (RCGCTIMER),offset0x604
// The RCGCTIMER register provides software the capability to enable and disable 16/32-bit timer modulesinRunmode.
// When enabled,a module is provided a clock and accesses to module registers are allowed.
// When disabled,the clock is disabled to save power and accesses to module registers generate a bus fault.
// activate tIMERn
#define RCGCTIMER_TIMERn (*((unsigned long *)0x400FE604))
// ****************************************************************************************************

// Register 3: GPIO Interrupt Sense (GPIOIS), offset 0x404
// The GPIOIS register is the interrupt sense register. Setting a bit in the GPIOIS register configures the corresponding pin to detect levels,
// while clearing a bit configures the corresponding pin to detectedges. All bits are cleared by a reset.
// Note:To prevent false interrupts, the following steps should be taken when re-configuring GPIO edge and interrupt sense registers:
// 1.Mask the corresponding port by clearing the IME field in the GPIOIM register.
// 2.Configure the IS field in the GPIOIS register and the IBE field in the GPIOIBE register.
// 3.Clear the GPIORIS register.
// 4.Unmask the port by setting the IME field in the GPIOIM register.

#define GPIO_PORT_A_IS (*((unsigned long *)0x40004404))
#define GPIO_PORT_Aa_IS (*((unsigned long *)0x40058404))
#define GPIO_PORT_B_IS (*((unsigned long *)0x40005404))
#define GPIO_PORT_Bb_IS (*((unsigned long *)0x40059404))
#define GPIO_PORT_C_IS (*((unsigned long *)0x40006404))
#define GPIO_PORT_Cc_IS (*((unsigned long *)0x4005A404))
#define GPIO_PORT_D_IS (*((unsigned long *)0x40007404))
#define GPIO_PORT_Dd_IS (*((unsigned long *)0x4005B404))
#define GPIO_PORT_E_IS (*((unsigned long *)0x40024404))
#define GPIO_PORT_Ee_IS (*((unsigned long *)0x4005C404))
#define GPIO_PORT_F_IS (*((unsigned long *)0x40025404))
#define GPIO_PORT_Ff_IS (*((unsigned long *)0x4005D404))

// Register 4: GPIO Interrupt Both Edges (GPIOIBE), offset 0x408
// The GPIOIBE register allows both edges to cause interrupts.
// When the corresponding bit in theGPIO Interrupt Sense (GPIOIS)register (see page 664) is set to detect edges, setting a bit in the GPIOIBE register configures the corresponding pin
// to detect both rising and falling edges, regardlessof the corresponding bit in the GPIO Interrupt Event (GPIOIEV) register (see page 666).
// Clearing a bit configures the pin to be controlled by the GPIOIEV register.
// All bits are cleared by a reset.Note:To prevent false interrupts, the following steps should be taken when re-configuring GPIO edge and interrupt sense registers:
// 1.Mask the corresponding port by clearing the IME field in the GPIOIM register.
// 2.Configure the IS field in the GPIOIS register and the IBE field in the GPIOIBE register.
// 3.Clear the GPIORIS register.
// 4.Unmask the port by setting the IME field in the GPIOIM register.GPIO Interrupt Both Edges (GPIOIBE)
#define GPIO_PORT_A_IBE (*((unsigned long *)0x40004408))
#define GPIO_PORT_Aa_IBE (*((unsigned long *)0x40058408))
#define GPIO_PORT_B_IBE (*((unsigned long *)0x40005408))
#define GPIO_PORT_Bb_IBE (*((unsigned long *)0x40059408))
#define GPIO_PORT_C_IBE (*((unsigned long *)0x40006408))
#define GPIO_PORT_Cc_IBE (*((unsigned long *)0x4005A408))
#define GPIO_PORT_D_IBE (*((unsigned long *)0x40007408))
#define GPIO_PORT_Dd_IBE (*((unsigned long *)0x4005B408))
#define GPIO_PORT_E_IBE (*((unsigned long *)0x40024408))
#define GPIO_PORT_Ee_IBE (*((unsigned long *)0x4005C408))
#define GPIO_PORT_F_IBE (*((unsigned long *)0x40025408))
#define GPIO_PORT_Ff_IBE (*((unsigned long *)0x4005D408))

// Register 5: GPIO Interrupt Event (GPIOIEV), offset 0x40C
// TheGPIOIEVregister is the interrupt event register.
// Setting a bit in theGPIOIEVregister configuresthe corresponding pin to detect rising edges
// or high levels, depending on the corresponding bitvalue in the
// GPIO Interrupt Sense (GPIOIS)register (see page 664).
// Clearing a bit configures thepin to detect falling edges or low levels,
// depending on the corresponding bit value in theGPIOISregister.
// All bits are cleared by a reset.

#define GPIO_PORT_A_IEV (*((unsigned long *)0x4000440C))
#define GPIO_PORT_Aa_IEV (*((unsigned long *)0x4005840C))
#define GPIO_PORT_B_IEV (*((unsigned long *)0x4000540C))
#define GPIO_PORT_Bb_IEV (*((unsigned long *)0x4005940C))
#define GPIO_PORT_C_IEV (*((unsigned long *)0x4000640C))
#define GPIO_PORT_Cc_IEV (*((unsigned long *)0x4005A40C))
#define GPIO_PORT_D_IEV (*((unsigned long *)0x4000740C))
#define GPIO_PORT_Dd_IEV (*((unsigned long *)0x4005B40C))
#define GPIO_PORT_E_IEV (*((unsigned long *)0x4002440C))
#define GPIO_PORT_Ee_IEV (*((unsigned long *)0x4005C40C))
#define GPIO_PORT_F_IEV (*((unsigned long *)0x4002540C))
#define GPIO_PORT_Ff_IEV (*((unsigned long *)0x4005D40C))

// Register 6: GPIO Interrupt Mask (GPIOIM), offset 0x410
// TheGPIOIMregister is the interrupt mask register.
// Setting a bit in the GPIOIM register allowsinterrupts that are generated by the
// corresponding pin to be sent to the interrupt controller on thecombined interrupt signal.
// Clearing a bit prevents an interrupt on the corresponding pin from beingsent to the interrupt
// controller. All bits are cleared by a reset.GPIO Interrupt Mask (GPIOIM)
#define GPIO_PORT_A_IM (*((unsigned long *)0x40004410))
#define GPIO_PORT_Aa_IM (*((unsigned long *)0x40058410))
#define GPIO_PORT_B_IM (*((unsigned long *)0x40005410))
#define GPIO_PORT_Bb_IM (*((unsigned long *)0x40059410))
#define GPIO_PORT_C_IM (*((unsigned long *)0x40006410))
#define GPIO_PORT_Cc_IM (*((unsigned long *)0x4005A410))
#define GPIO_PORT_D_IM (*((unsigned long *)0x40007410))
#define GPIO_PORT_Dd_IM (*((unsigned long *)0x4005B410))
#define GPIO_PORT_E_IM (*((unsigned long *)0x40024410))
#define GPIO_PORT_Ee_IM (*((unsigned long *)0x4005C410))
#define GPIO_PORT_F_IM (*((unsigned long *)0x40025410))
#define GPIO_PORT_Ff_IM (*((unsigned long *)0x4005D410))

// Register 7: GPIO Raw Interrupt Status (GPIORIS), offset 0x414
// The GPIORIS register is the raw interrupt status register.
// A bit in this register is set when an interruptcondition
// occurs on the corresponding GPIO pin. If the corresponding
// bit in theGPIO InterruptMask (GPIOIM)register (see page 667) is
// set, the interrupt is sent to the interrupt controller.
// Bitsread as zero indicate that corresponding input pins have not initiated an interrupt.
//  For a GPIOlevel-detect interrupt, the interrupt signal generating the interrupt must be
//   held until serviced. Oncethe input signal deasserts from the interrupt generating logical
//   sense, the corresponding RIS bit in the GPIORIS register clears. For a GPIO edge-detect interrupt,
//   the RIS bit in the GPIORIS register is cleared by writing a ‘1’ to the corresponding bit in theGPIO
//    Interrupt Clear (GPIOICR)register.The corresponding GPIOMIS bit reflects the masked value of
//    theRISbi

#define GPIO_PORT_F_RIS (*((unsigned long *)0x40025414))

// Register 8: GPIO Masked Interrupt Status (GPIOMIS), offset 0x418
// The GPIOMIS register is the masked interrupt status register. If a bit is set in this register, the
// corresponding interrupt has triggered an interrupt to the interrupt controller. If a bit is clear, either
// no interrupt has been generated, or the interrupt is masked.
// Note that if the Port B GPIOADCCTL register is cleared, PB4 can still be used as an external trigger
// for the ADC. This is a legacy mode which allows code written for previous devices to operate on
// this microcontroller.
// GPIOMIS is the state of the interrupt after masking.

#define GPIO_PORT_A_MIS (*((unsigned long *)0x40004418))
#define GPIO_PORT_Aa_MIS (*((unsigned long *)0x40058418))
#define GPIO_PORT_B_MIS (*((unsigned long *)0x40005418))
#define GPIO_PORT_Bb_MIS (*((unsigned long *)0x40059418))
#define GPIO_PORT_C_MIS (*((unsigned long *)0x40006418))
#define GPIO_PORT_Cc_MIS (*((unsigned long *)0x4005A418))
#define GPIO_PORT_D_MIS (*((unsigned long *)0x40007418))
#define GPIO_PORT_Dd_MIS (*((unsigned long *)0x4005B418))
#define GPIO_PORT_E_MIS (*((unsigned long *)0x40024418))
#define GPIO_PORT_Ee_MIS (*((unsigned long *)0x4005C418))
#define GPIO_PORT_F_MIS (*((unsigned long *)0x40025418))
#define GPIO_PORT_Ff_MIS (*((unsigned long *)0x4005D418))

// Register 9: GPIO Interrupt Clear (GPIOICR), offset 0x41C
// The GPIOICR register is the interrupt clear register. For edge-detect interrupts, writing a 1 to the
// IC bit in the GPIOICR register clears the corresponding bit in the GPIORIS and GPIOMIS registers.
// If the interrupt is a level-detect, the IC bit in this register has no effect. In addition, writing a 0 to any
// of the bits in the GPIOICR register has no effect.
#define GPIO_PORT_A_ICR (*((unsigned long *)0x4000441C))
#define GPIO_PORT_Aa_ICR (*((unsigned long *)0x4005841C))
#define GPIO_PORT_B_ICR (*((unsigned long *)0x4000541C))
#define GPIO_PORT_Bb_ICR (*((unsigned long *)0x4005941C))
#define GPIO_PORT_C_ICR (*((unsigned long *)0x4000641C))
#define GPIO_PORT_Cc_ICR (*((unsigned long *)0x4005A41C))
#define GPIO_PORT_D_ICR (*((unsigned long *)0x4000741C))
#define GPIO_PORT_Dd_ICR (*((unsigned long *)0x4005B41C))
#define GPIO_PORT_E_ICR (*((unsigned long *)0x4002441C))
#define GPIO_PORT_Ee_ICR (*((unsigned long *)0x4005C41C))
#define GPIO_PORT_F_ICR (*((unsigned long *)0x4002541C))
#define GPIO_PORT_Ff_ICR (*((unsigned long *)0x4005D41C))

// Register 29: Interrupt 0-3 Priority (PRI0), offset 0x400
// Register 30: Interrupt 4-7 Priority (PRI1), offset 0x404
// Register 31: Interrupt 8-11 Priority (PRI2), offset 0x408
// Register 32: Interrupt 12-15 Priority (PRI3), offset 0x40C
// Register 33: Interrupt 16-19 Priority (PRI4), offset 0x410
// Register 34: Interrupt 20-23 Priority (PRI5), offset 0x414

#define PRI0 (*((unsigned long *)0xE000E400))
#define PRI1 (*((unsigned long *)0xE000E404))
#define PRI2 (*((unsigned long *)0xE000E408))
#define PRI3 (*((unsigned long *)0xE000E40C))
#define PRI4 (*((unsigned long *)0xE000E410))
#define PRI5 (*((unsigned long *)0xE000E414))

// ****************************************************************************************************
// 2.) Disable the timer using the GPTMCTL register.
// Register4:GPTMControl(GPTMCTL),offset0x00C
// This register is used alongside the GPTMCFG and GMTMTnMR registers to fine-tune the timer configuration,
// and to enable other features such as timer stall and the output trigger.
// The output trigger can be used to initiate transfers on the ADC module.
#define GPTMCTL_TIMER0 (*((unsigned long *)0x4003000C)) // 16/32-bit Timer 0
#define GPTMCTL_TIMER1 (*((unsigned long *)0x4003100C)) // 16/32-bit Timer 1
#define GPTMCTL_TIMER2 (*((unsigned long *)0x4003200C)) // 16/32-bit Timer 2
#define GPTMCTL_TIMER3 (*((unsigned long *)0x4003300C)) // 16/32-bit Timer 3
#define GPTMCTL_TIMER4 (*((unsigned long *)0x4003400C)) // 16/32-bit Timer 4
#define GPTMCTL_TIMER5 (*((unsigned long *)0x4003500C)) // 16/32-bit Timer 5

#define GPTMCTL_WIDE_TIMER0 (*((unsigned long *)0x4003600C)) // 32/64-bit Wide Timer 0
#define GPTMCTL_WIDE_TIMER1 (*((unsigned long *)0x4003700C)) // 32/64-bit Wide Timer 1
#define GPTMCTL_WIDE_TIMER2 (*((unsigned long *)0x4004C00C)) // 32/64-bit Wide Timer 2
#define GPTMCTL_WIDE_TIMER3 (*((unsigned long *)0x4004D00C)) // 32/64-bit Wide Timer 3
#define GPTMCTL_WIDE_TIMER4 (*((unsigned long *)0x4004E00C)) // 32/64-bit Wide Timer 4
#define GPTMCTL_WIDE_TIMER5 (*((unsigned long *)0x4004F00C)) // 32/64-bit Wide Timer 5

// ****************************************************************************************************

// ****************************************************************************************************
// 3.) Select 32-bit mode using the GPTMCFG register.
// Register1:GPTMConfiguration(GPTMCFG),offset0x000
// This register configures the global operation of the GPTM module.The value written to this
// register determines whether the GPTM is in 32- or 64-bit mode (concatenated timers) or in 16- or 32-bit mode (individual, split timers).
// Bits in this register should only be changed when the TAEN and TBEN bits
// in the GPTMCTL register are cleared.
// for timer 0
#define GPTMCFG_TIMER0 (*((unsigned long *)0X40030000)) // 16/32-bit Timer 0
#define GPTMCFG_TIMER1 (*((unsigned long *)0X40031000)) // 16/32-bit Timer 1
#define GPTMCFG_TIMER2 (*((unsigned long *)0X40032000)) // 16/32-bit Timer 2
#define GPTMCFG_TIMER3 (*((unsigned long *)0X40033000)) // 16/32-bit Timer 3
#define GPTMCFG_TIMER4 (*((unsigned long *)0X40034000)) // 16/32-bit Timer 4
#define GPTMCFG_TIMER5 (*((unsigned long *)0X40035000)) // 16/32-bit Timer 5

#define GPTMCFG_WIDE_TIMER0 (*((unsigned long *)0X40036000)) // 32/64-bit Wide Timer 0
#define GPTMCFG_WIDE_TIMER1 (*((unsigned long *)0X40037000)) // 32/64-bit Wide Timer 1
#define GPTMCFG_WIDE_TIMER2 (*((unsigned long *)0X4004C000)) // 32/64-bit Wide Timer 2
#define GPTMCFG_WIDE_TIMER3 (*((unsigned long *)0X4004D000)) // 32/64-bit Wide Timer 3
#define GPTMCFG_WIDE_TIMER4 (*((unsigned long *)0X4004E000)) // 32/64-bit Wide Timer 4
#define GPTMCFG_WIDE_TIMER5 (*((unsigned long *)0X4004F000)) // 32/64-bit Wide Timer 5
// ****************************************************************************************************

// ****************************************************************************************************
// 4.) Configure the TAMR bit of the GPTMTAMR register to be in periodic timer mode.
// 5.) Configure the TACDIR bit of the GPTMTAMR register to count down.
// Register2: GPTM Timer A Mode (GPTMTAMR),offset0x004
// This register configures the GPTM based on the configuration selected in theGPTMCFGregister. WheninPWMmode,settheTAAMSbit,cleartheTACMRbit,andconfiguretheTAMRfieldto0x1or 0x2. This register controls the modes for Timer A when it is used individually. When Timer A and Timer Bareconcatenated,thisregistercontrolsthemodesforbothTimerAandTimerB,andthecontents of GPTMTBMR are ignored.
// Important: Bits in this register should only be changed when the TAEN bit in the GPTMCTL register is cleared.

#define GPTMTAMR_TIMER0 (*((unsigned long *)0x40030004)) // 16/32-bit Timer 0
#define GPTMTAMR_TIMER1 (*((unsigned long *)0x40031004)) // 16/32-bit Timer 1
#define GPTMTAMR_TIMER2 (*((unsigned long *)0x40032004)) // 16/32-bit Timer 2
#define GPTMTAMR_TIMER3 (*((unsigned long *)0x40033004)) // 16/32-bit Timer 3
#define GPTMTAMR_TIMER4 (*((unsigned long *)0x40034004)) // 16/32-bit Timer 4
#define GPTMTAMR_TIMER5 (*((unsigned long *)0x40035004)) // 16/32-bit Timer 5

#define GPTMTAMR_WIDE_TIMER0 (*((unsigned long *)0x40036004)) // 32/64-bit Wide Timer 0
#define GPTMTAMR_WIDE_TIMER1 (*((unsigned long *)0x40037004)) // 32/64-bit Wide Timer 1
#define GPTMTAMR_WIDE_TIMER2 (*((unsigned long *)0x4004C004)) // 32/64-bit Wide Timer 2
#define GPTMTAMR_WIDE_TIMER3 (*((unsigned long *)0x4004D004)) // 32/64-bit Wide Timer 3
#define GPTMTAMR_WIDE_TIMER4 (*((unsigned long *)0x4004E004)) // 32/64-bit Wide Timer 4
#define GPTMTAMR_WIDE_TIMER5 (*((unsigned long *)0x4004F004)) // 32/64-bit Wide Timer 5
// ****************************************************************************************************

// ****************************************************************************************************
// 6.) Load a value of 16,000,000 into the GPTMTAILR to achieve a 1 Hz blink rate using the 16 MHz oscillator.
// Register10:GPTMTimerAIntervalLoad(GPTMTAILR),offset0x028
// When the timer is counting down,this register isused to load the starting count value into the timer
// When the timer is counting up, this register sets the upper bound for the timeout event.
// When a 16/32-bit GPTM is configured to one of the 32-bitmodes,GPTMTAILR appears as a 32-bit register (the upper 16-bits correspond to the contents of theGPTMTimerBIntervalLoad (GPTMTBILR)register).
//In a 16-bitmode,the upper 16 bits of this register read as 0s and have no effect on the state of GPTMTBILR.
// When a 32/64-bit Wide GPTM is configured to one of the 64-bit modes,GPTMTAILR contains bits 31:0 of the 64-bit count and the GPTMTimerB Interval Load(GPTMTBILR) register containsbits 63:32.
#define GPTMTAILR_TIMER0 (*((unsigned long *)0x40030028)) // 16/32-bit Timer 0
#define GPTMTAILR_TIMER1 (*((unsigned long *)0x40031028)) // 16/32-bit Timer 1
#define GPTMTAILR_TIMER2 (*((unsigned long *)0x40032028)) // 16/32-bit Timer 2
#define GPTMTAILR_TIMER3 (*((unsigned long *)0x40033028)) // 16/32-bit Timer 3
#define GPTMTAILR_TIMER4 (*((unsigned long *)0x40034028)) // 16/32-bit Timer 4
#define GPTMTAILR_TIMER5 (*((unsigned long *)0x40035028)) // 16/32-bit Timer 5

#define GPTMTAILR_WIDE_TIMER0 (*((unsigned long *)0x40036028)) // 32/64-bit Wide Timer 0
#define GPTMTAILR_WIDE_TIMER1 (*((unsigned long *)0x40037028)) // 32/64-bit Wide Timer 1
#define GPTMTAILR_WIDE_TIMER2 (*((unsigned long *)0x4004C028)) // 32/64-bit Wide Timer 2
#define GPTMTAILR_WIDE_TIMER3 (*((unsigned long *)0x4004D028)) // 32/64-bit Wide Timer 3
#define GPTMTAILR_WIDE_TIMER4 (*((unsigned long *)0x4004E028)) // 32/64-bit Wide Timer 4
#define GPTMTAILR_WIDE_TIMER5 (*((unsigned long *)0x4004F028)) // 32/64-bit Wide Timer 5

// ****************************************************************************************************

// ****************************************************************************************************
// 7.) If using interrupts, configure the GPTMIMR register. This is not necessary for task 1.
// Register6:GPTM Interrupt Mask(GPTMIMR),offset0x018
// This register allows software to enable/disable GPTM controller-level interrupts.
// Setting a bit enables the corresponding interrupt, while clearing a bit disables it.
#define GPTMIMR_TIMER0 (*((unsigned long *)0x40030018))
#define GPTMIMR_TIMER1 (*((unsigned long *)0x40031018))
#define GPTMIMR_TIMER2 (*((unsigned long *)0x40032018))
#define GPTMIMR_TIMER3 (*((unsigned long *)0x40033018))
#define GPTMIMR_TIMER4 (*((unsigned long *)0x40034018))
#define GPTMIMR_TIMER5 (*((unsigned long *)0x40035018))
#define GPTMIMR_WIDE_TIMER0 (*((unsigned long *)0x40036018))
#define GPTMIMR_WIDE_TIMER1 (*((unsigned long *)0x40037018))
#define GPTMIMR_WIDE_TIMER2 (*((unsigned long *)0x4004C018))
#define GPTMIMR_WIDE_TIMER3 (*((unsigned long *)0x4004D018))
#define GPTMIMR_WIDE_TIMER4 (*((unsigned long *)0x4004E018))
#define GPTMIMR_WIDE_TIMER5 (*((unsigned long *)0x4004F018))

// ****************************************************************************************************

// 8.) Enable the timer using the GPTMCTL register.

// Register7:GPTMRawInterruptStatus(GPTMRIS),offset0x01C
// This register shows the state of the GPTM's internal interrupt signal.
// These bits are set whether or not the interrupt is masked in the GPTMIMR register.
// Each bit can be cleared by writing a 1 to its corresponding bit in GPTMICR.
// Note: The state of the GPTMRISregister is not affected by disabling and then re-enabling
// the timer using theTnENbits in the GPTMControl(GPTMCTL) register.
// If an application requiresthatallorcertainstatusbitsshouldnotcarryoverafterre-enablingthetimer,
// then the appropriate bits in the GPTMRIS register shouldbeclearedusingtheGPTMICRregister
// priortore-enablingthetimer.Ifthisisnotdone,anystatusbitssetintheGPTMRISregister
// andunmaskedintheGPTMIMRregistergenerateaninterruptoncethetimerisre-enabled.
#define GPTMRIS_TIMER0 (*((unsigned long *)0x4003001C))
#define GPTMRIS_TIMER1 (*((unsigned long *)0x4003101C))
#define GPTMRIS_TIMER2 (*((unsigned long *)0x4003201C))
#define GPTMRIS_TIMER3 (*((unsigned long *)0x4003301C))
#define GPTMRIS_TIMER4 (*((unsigned long *)0x4003401C))
#define GPTMRIS_TIMER5 (*((unsigned long *)0x4003501C))
#define GPTMRIS_WIDE_TIMER0 (*((unsigned long *)0x4003601C))
#define GPTMRIS_WIDE_TIMER1 (*((unsigned long *)0x4003701C))
#define GPTMRIS_WIDE_TIMER2 (*((unsigned long *)0x4004C01C))
#define GPTMRIS_WIDE_TIMER3 (*((unsigned long *)0x4004D01C))
#define GPTMRIS_WIDE_TIMER4 (*((unsigned long *)0x4004E01C))
#define GPTMRIS_WIDE_TIMER5 (*((unsigned long *)0x4004F01C))

// Register9:GPTM Interrupt Clear(GPTMICR),offset0x024
// This register is used to clear the status bits in the GPTMRISand GPTMMIS registers.
// Writing a 1 to a bit clears the corresponding bit in theGPTMRISand GPTMMIS registers.
#define GPTMICR_TIMER0 (*((unsigned long *)0x40030024))
#define GPTMICR_TIMER1 (*((unsigned long *)0x40031024))
#define GPTMICR_TIMER2 (*((unsigned long *)0x40032024))
#define GPTMICR_TIMER3 (*((unsigned long *)0x40033024))
#define GPTMICR_TIMER4 (*((unsigned long *)0x40034024))
#define GPTMICR_TIMER5 (*((unsigned long *)0x40035024))
#define GPTMICR_WIDE_TIMER0 (*((unsigned long *)0x40036024))
#define GPTMICR_WIDE_TIMER1 (*((unsigned long *)0x40037024))
#define GPTMICR_WIDE_TIMER2 (*((unsigned long *)0x4004C024))
#define GPTMICR_WIDE_TIMER3 (*((unsigned long *)0x4004D024))
#define GPTMICR_WIDE_TIMER4 (*((unsigned long *)0x4004E024))
#define GPTMICR_WIDE_TIMER5 (*((unsigned long *)0x4004F024))

// Register 4: Interrupt 0-31 Set Enable (EN0), offset 0x100
// Register 5: Interrupt 32-63 Set Enable (EN1), offset 0x104
// Register 6: Interrupt 64-95 Set Enable (EN2), offset 0x108
// Register 7: Interrupt 96-127 Set Enable (EN3), offset 0x10C
// Note: This register can only be accessed from privileged mode.
// The ENn registers enable interrupts and show which interrupts are enabled. Bit 0 of EN0 corresponds
// to Interrupt 0; bit 31 corresponds to Interrupt 31. Bit 0 of EN1 corresponds to Interrupt 32; bit 31
// corresponds to Interrupt 63. Bit 0 of EN2 corresponds to Interrupt 64; bit 31 corresponds to Interrupt
// 95. Bit 0 of EN3 corresponds to Interrupt 96; bit 31 corresponds to Interrupt 127. Bit 0 of EN4 (see
// page 143) corresponds to Interrupt 128; bit 10 corresponds to Interrupt 138.
// See Table 2-9 on page 104 for interrupt assignments.
// If a pending interrupt is enabled, the NVIC activates the interrupt based on its priority. If an interrupt
// is not enabled, asserting its interrupt signal changes the interrupt state to pending, but the NVIC
// never activates the interrupt, regardless of its priority.
#define inter_0_31_EN0 (*((unsigned long *)0xE000E100))
#define inter_32_63_EN1 (*((unsigned long *)0xE000E104))
#define inter_64_95_EN2 (*((unsigned long *)0xE000E108))
#define inter_96_127_EN3 (*((unsigned long *)0xE000E10C))

// Register 1: ADC Active Sample Sequencer (ADCACTSS), offset 0x000 This register controls the activation of the sample sequencers. Each sample sequencer can beenabled or disabled independently.ADC Active Sample Sequencer (ADCACTSS)ADC0 base: 0x4003.8000ADC1 base: 0x4003.9000
#define ADC_0_ACTSS (*((unsigned long *)0x40038000))
#define ADC_1_ACTSS (*((unsigned long *)0x40039000))

// Register 9: ADC Sample Sequencer Priority (ADCSSPRI), offset 0x020 This register sets the priority for each of the sample sequencers. Out of reset, Sequencer 0 has thehighest priority, and Sequencer 3 has the lowest priority. When reconfiguring sequence priorities,each sequence must have a unique priority for the ADC to operate properly.ADC Sample Sequencer Priority (ADCSSPRI)ADC0 base: 0x4003.8000ADC1 base: 0x4003.9000Offset 0x020
#define ADC_0_SSPRI (*((unsigned long *)0x40038020))
#define ADC_1_SSPRI (*((unsigned long *)0x40039020))

// Register 6: ADC Event Multiplexer Select (ADCEMUX), offset 0x014
// The ADCEMUX selects the event (trigger) that initiates sampling for each sample sequencer. Each sample sequencer can be configured with a unique trigger source. When using a PWM generatoras the trigger source, the ADCEMUX register selects which generator within a PWM module is usedas a trigger and thePSnfield in theADC Trigger Source Select (ADCTSSEL)register specifiesthe PWM module instance in which the generator is located. ADC Event Multiplexer Select (ADCEMUX)ADC0 base: 0x4003.8000ADC1 base: 0x4003.9000 Offset 0x014
#define ADC_0_EMUX (*((unsigned long *)0x40038014))
#define ADC_1_EMUX (*((unsigned long *)0x40039014))

// Register 15: ADC Sample Sequence Input Multiplexer Select 0 (ADCSSMUX0),offset 0x040This register defines the analog input configuration for each sample in a sequence executed withSample Sequencer 0. This register is 32 bits wide and contains information for eight possiblesamples.
#define ADC_0_SSMUX0 (*((unsigned long *)0x40038040))
#define ADC_1_SSMUX0 (*((unsigned long *)0x40039040))

//Register 35: ADC Sample Sequence Input Multiplexer Select 3 (ADCSSMUX3),offset 0x0A0This register defines the analog input configuration for the sample executed with Sample Sequencer3. This register is 4 bits wide and contains information for one possible sample. See theADCSSMUX0register on page 851 for detailed bit descriptions.
#define ADC_0_SSMUX3 (*((unsigned long *)0x400380A0))
#define ADC_1_SSMUX3 (*((unsigned long *)0x400390A0))


//Register 36: ADC Sample Sequence Control 3 (ADCSSCTL3), offset 0x0A4This register contains the configuration information for a sample executed with Sample Sequencer3. This register is 4 bits wide and contains information for one possible sample. See theADCSSCTL0register on page 853 for detailed bit descriptions.Note:When configuring a sample sequence in this register, theEND0bit must be set.
#define ADC_0_SSCTL3 (*((unsigned long *)0x400380A4))
#define ADC_1_SSCTL3 (*((unsigned long *)0x400390A4))



// Register 11: ADC Processor Sample Sequence Initiate (ADCPSSI), offset 0x028This register provides a mechanism for application software to initiate sampling in the samplesequencers. Sample sequences can be initiated individually or in any combination. When multiplesequences are triggered simultaneously, the priority encodings inADCSSPRIdictate executionorder.This register also provides a means to configure and then initiate concurrent sampling on all ADCmodules. To do this, the first ADC module should be configured. TheADCPSSIregister for thatmodule should then be written. The appropriateSSbits should be set along with theSYNCWAITbit.Additional ADC modules should then be configured following the same procedure. Once the finalADC module is configured, itsADCPSSIregister should be written with the appropriateSSbits setalong with theGSYNCbit. All of the ADC modules then begin concurrent sampling according to theirconfiguration.
#define ADC_0_PSSI (*((unsigned long *)0x40038028))
#define ADC_1_PSSI (*((unsigned long *)0x40039028))


//Register 2: ADC Raw Interrupt Status (ADCRIS), offset 0x004 This register shows the status of the raw interrupt signal of each sample sequencer. These bits maybe polled by software to look for interrupt conditions without sending the interrupts to the interruptcontroller.
#define ADC_0_RIS (*((unsigned long *)0x40038004))
#define ADC_1_RIS (*((unsigned long *)0x40039004))

//***********************************************************************
// This register contains the conversion results for samples collected with the sample sequencer (the ADCSSFIFO0 register is used for Sample Sequencer 0,ADCSSFIFO1 for Sequencer 1, ADCSSFIFO2 for Sequencer 2, and ADCSSFIFO3 for Sequencer 3). Reads of this register returnconversion result data in the order sample 0, sample 1, and so on, until the FIFO is empty. If the FIFO is not properly handled by software, overflow and underflow conditions are registered in the ADCOSTAT and ADCUSTAT registers.
// Register 17: ADC Sample Sequence Result FIFO 0 (ADCSSFIFO0), offset 0x048
#define ADC_0_SSFIFO0 (*((unsigned long *)0x40038048))
#define ADC_1_SSFIFO0 (*((unsigned long *)0x40039048))
// Register 18: ADC Sample Sequence Result FIFO 1 (ADCSSFIFO1), offset 0x068
#define ADC_0_SSFIFO1 (*((unsigned long *)0x40038068))
#define ADC_1_SSFIFO1 (*((unsigned long *)0x40039068))
// Register 19: ADC Sample Sequence Result FIFO 2 (ADCSSFIFO2), offset 0x088
#define ADC_0_SSFIFO2 (*((unsigned long *)0x40038088))
#define ADC_1_SSFIFO2 (*((unsigned long *)0x40039088))
// Register 20: ADC Sample Sequence Result FIFO 3 (ADCSSFIFO3), offset 0x0A8
#define ADC_0_SSFIFO3 (*((unsigned long *)0x400380A8))
#define ADC_1_SSFIFO3 (*((unsigned long *)0x400390A8))
//! Important:This register is read-sensitive. See the register description for details.
//***********************************************************************

// Register 3: ADC Interrupt Mask (ADCIM), offset 0x008
// This register controls whether the sample sequencer and digital comparator raw interrupt signals are sent to the interrupt controller. Each raw interrupt signal can be masked independently.
//Note: Only a singleDCONSSnbit should be set at any given time. Setting more than one of thesebits results in the INRDC bit from the ADCRIS register being masked, and no interrupt isgenerated on any of the sample sequencer interrupt lines. It is recommended that when interrupts are used, they are enabled on alternating samples or at the end of the samplesequence.
#define ADC_0_IM (*((unsigned long *)0x40038008))
#define ADC_1_IM (*((unsigned long *)0x40039008))



// Register 4: ADC Interrupt Status and Clear (ADCISC), offset 0x00C
// This register provides the mechanism for clearing sample sequencer interrupt conditions and shows
// the status of interrupts generated by the sample sequencers and the digital comparators which have
// been sent to the interrupt controller. When read, each bit field is the logical AND of the respective
// INR and MASK bits. Sample sequencer interrupts are cleared by writing a 1 to the corresponding
// bit position. Digital comparator interrupts are cleared by writing a 1 to the appropriate bits in the
// ADCDCISC register. If software is polling the ADCRIS instead of generating interrupts, the sample
// sequence INRn bits are still cleared via the ADCISC register, even if the INn bit is not set.
#define ADC_0_ISC (*((unsigned long *)0x4003800C))
#define ADC_1_ISC (*((unsigned long *)0x4003900C))

// Register 4: Raw Interrupt Status (RIS), offset 0x050
// This register indicates the status for system control raw interrupts. An interrupt is sent to the interrupt
// controller if the corresponding bit in the Interrupt Mask Control (IMC) register is set. Writing a 1
// to the corresponding bit in the Masked Interrupt Status and Clear (MISC) register clears an interrupt
// status bit.
#define RIS (*((unsigned long *)0x400FE050))


// Register 6: Masked Interrupt Status and Clear (MISC), offset 0x058
// On a read, this register gives the current masked status value of the corresponding interrupt in the
// Raw Interrupt Status (RIS) register. All of the bits are RW1C, thus writing a 1 to a bit clears the
// corresponding raw interrupt bit in the RIS register (see page 244).
#define MISC (*((unsigned long *)0x400FE058))

// Register 63: Universal Asynchronous Receiver/Transmitter Run Mode Clock
// Gating Control (RCGCUART), offset 0x618
// The RCGCUART register provides software the capability to enable and disable the UART modules
// in Run mode. When enabled, a module is provided a clock and accesses to module registers are
// allowed. When disabled, the clock is disabled to save power and accesses to module registers
// generate a bus fault. This register provides the same capability as the legacy Run Mode Clock
// Gating Control Register n RCGCn registers specifically for the watchdog modules and has the
// same bit polarity as the corresponding RCGCn bits.
// Important: This register should be used to control the clocking for the UART modules. To support
// legacy software, the RCGC1 register is available. A write to the RCGC1 register also
// writes the corresponding bit in this register. Any bits that are changed by writing to the
// RCGC1 register can be read back correctly with a read of the RCGC1 register. Software
// must use this register to support modules that are not present in the legacy registers.
// If software uses this register to write a legacy peripheral (such as UART0), the write
// causes proper operation, but the value of that bit is not reflected in the RCGC1 register.
// If software uses both legacy and peripheral-specific register accesses, the
// peripheral-specific registers must be accessed by read-modify-write operations that
// affect only peripherals that are not present in the legacy registers. In this manner, both
// the peripheral-specific and legacy registers have coherent information.
#define RCGCUART (*((unsigned long *)0x400FE618))


// Register 5: UART Integer Baud-Rate Divisor (UARTIBRD), offset 0x024
// The UARTIBRD register is the integer part of the baud-rate divisor value. All the bits are cleared
// on reset. The minimum possible divide ratio is 1 (when UARTIBRD=0), in which case the UARTFBRD
// register is ignored. When changing the UARTIBRD register, the new value does not take effect until
// transmission/reception of the current character is complete. Any changes to the baud-rate divisor
// must be followed by a write to the UARTLCRH register. See “Baud-Rate Generation” on page 896
// for configuration details.

#define UART0_IBRD (*((unsigned long *)0x4000C024)) 
#define UART1_IBRD (*((unsigned long *)0x4000D024)) 
#define UART2_IBRD (*((unsigned long *)0x4000E024)) 
#define UART3_IBRD (*((unsigned long *)0x4000F024)) 
#define UART4_IBRD (*((unsigned long *)0x40010024)) 
#define UART5_IBRD (*((unsigned long *)0x40011024)) 
#define UART6_IBRD (*((unsigned long *)0x40012024)) 
#define UART7_IBRD (*((unsigned long *)0x40013024)) 

// Register 6: UART Fractional Baud-Rate Divisor (UARTFBRD), offset 0x028
// The UARTFBRD register is the fractional part of the baud-rate divisor value. All the bits are cleared
// on reset. When changing the UARTFBRD register, the new value does not take effect until
// transmission/reception of the current character is complete. Any changes to the baud-rate divisor
// must be followed by a write to the UARTLCRH register. See “Baud-Rate Generation” on page 896
// for configuration details.
#define UART0_FBRD (*((unsigned long *)0x4000C028)) 
#define UART1_FBRD (*((unsigned long *)0x4000D028)) 
#define UART2_FBRD (*((unsigned long *)0x4000E028)) 
#define UART3_FBRD (*((unsigned long *)0x4000F028)) 
#define UART4_FBRD (*((unsigned long *)0x40010028)) 
#define UART5_FBRD (*((unsigned long *)0x40011028)) 
#define UART6_FBRD (*((unsigned long *)0x40012028)) 
#define UART7_FBRD (*((unsigned long *)0x40013028)) 


// Register 7: UART Line Control (UARTLCRH), offset 0x02C
// The UARTLCRH register is the line control register. Serial parameters such as data length, parity,
// and stop bit selection are implemented in this register.
// When updating the baud-rate divisor (UARTIBRD and/or UARTIFRD), the UARTLCRH register
// must also be written. The write strobe for the baud-rate divisor registers is tied to the UARTLCRH
// register.
#define UART0_LCRH (*((unsigned long *)0x4000C02C))
#define UART1_LCRH (*((unsigned long *)0x4000D02C))
#define UART2_LCRH (*((unsigned long *)0x4000E02C))
#define UART3_LCRH (*((unsigned long *)0x4000F02C))
#define UART4_LCRH (*((unsigned long *)0x4001002C))
#define UART5_LCRH (*((unsigned long *)0x4001102C))
#define UART6_LCRH (*((unsigned long *)0x4001202C))
#define UART7_LCRH (*((unsigned long *)0x4001302C)) 

// Register 8: UART Control (UARTCTL), offset 0x030
// The UARTCTL register is the control register. All the bits are cleared on reset except for the Transmit
// Enable (TXE) and Receive Enable (RXE) bits, which are set.
// To enable the UART module, the UARTEN bit must be set. If software requires a configuration change
// in the module, the UARTEN bit must be cleared before the configuration changes are written. If the
// UART is disabled during a transmit or receive operation, the current transaction is completed prior
// to the UART stopping.
// Note: The UARTCTL register should not be changed while the UART is enabled or else the results
// are unpredictable. The following sequence is recommended for making changes to the
// UARTCTL register.
// 1. Disable the UART.
// 2. Wait for the end of transmission or reception of the current character.
// 3. Flush the transmit FIFO by clearing bit 4 (FEN) in the line control register (UARTLCRH).
// 4. Reprogram the control register.
// 5. Enable the UART.
#define UART0_CTL (*((unsigned long *)0x4000C030))
#define UART1_CTL (*((unsigned long *)0x4000D030))
#define UART2_CTL (*((unsigned long *)0x4000E030))
#define UART3_CTL (*((unsigned long *)0x4000F030))
#define UART4_CTL (*((unsigned long *)0x40010030))
#define UART5_CTL (*((unsigned long *)0x40011030))
#define UART6_CTL (*((unsigned long *)0x40012030))
#define UART7_CTL (*((unsigned long *)0x40013030)) 

// Register 18: UART Clock Configuration (UARTCC), offset 0xFC8
// The UARTCC register controls the baud clock source for the UART module. For more information,
// see the section called “Communication Clock Sources” on page 222.
// Note: If the PIOSC is used for the UART baud clock, the system clock frequency must be at least
// 9 MHz in Run mode.
#define UART0_CC (*((unsigned long *)0x4000CFC8))
#define UART1_CC (*((unsigned long *)0x4000DFC8))
#define UART2_CC (*((unsigned long *)0x4000EFC8))
#define UART3_CC (*((unsigned long *)0x4000FFC8))
#define UART4_CC (*((unsigned long *)0x40010FC8))
#define UART5_CC (*((unsigned long *)0x40011FC8))
#define UART6_CC (*((unsigned long *)0x40012FC8))
#define UART7_CC (*((unsigned long *)0x40013FC8)) 

// Register 3: UART Flag (UARTFR), offset 0x018
// The UARTFR register is the flag register. After reset, the TXFF, RXFF, and BUSY bits are 0, and
// TXFE and RXFE bits are 1. The CTS bit indicate the modem flow control. Note that the modem bits
// are only implemented on UART1 and are reserved on UART0 and UART2.
#define UART0_FR (*((unsigned long *)0x4000C018))
#define UART1_FR (*((unsigned long *)0x4000D018))
#define UART2_FR (*((unsigned long *)0x4000E018))
#define UART3_FR (*((unsigned long *)0x4000F018))
#define UART4_FR (*((unsigned long *)0x40010018))
#define UART5_FR (*((unsigned long *)0x40011018))
#define UART6_FR (*((unsigned long *)0x40012018))
#define UART7_FR (*((unsigned long *)0x40013018)) 

// Register 1: UART Data (UARTDR), offset 0x000
// Important: This register is read-sensitive. See the register description for details.
// This register is the data register (the interface to the FIFOs).
// For transmitted data, if the FIFO is enabled, data written to this location is pushed onto the transmit
// FIFO. If the FIFO is disabled, data is stored in the transmitter holding register (the bottom word of
// the transmit FIFO). A write to this register initiates a transmission from the UART.
// For received data, if the FIFO is enabled, the data byte and the 4-bit status (break, frame, parity,
// and overrun) is pushed onto the 12-bit wide receive FIFO. If the FIFO is disabled, the data byte and
// status are stored in the receiving holding register (the bottom word of the receive FIFO). The received
// data can be retrieved by reading this register.
#define UART0_DR (*((unsigned long *)0x4000C000))
#define UART1_DR (*((unsigned long *)0x4000D000))
#define UART2_DR (*((unsigned long *)0x4000E000))
#define UART3_DR (*((unsigned long *)0x4000F000))
#define UART4_DR (*((unsigned long *)0x40010000))
#define UART5_DR (*((unsigned long *)0x40011000))
#define UART6_DR (*((unsigned long *)0x40012000))
#define UART7_DR (*((unsigned long *)0x40013000))


// Register 2: GPTM Timer A Mode (GPTMTAMR), offset 0x004
// This register configures the GPTM based on the configuration selected in the GPTMCFG register. When in PWM mode, set the TAAMS bit, clear the TACMR bit, and configure the TAMR field to 0x1 or 0x2.
// This register controls the modes for Timer A when it is used individually. When Timer A and Timer B are concatenated, this register controls the modes for both Timer A and Timer B, and the contents of GPTMTBMR are ignored.
// Important: Bitsinthisreg



// Register 12: PWM0 Control (PWM0CTL), offset 0x040
// This register configures the PWM signal generation blocks (PWM0CTL controls the PWM generator 0 block, and so on). The Register Update mode, Debug mode, Counting mode, and Block Enable mode are all controlled via these registers.
// The blocks produce the PWM signals, which can be either two independent PWM signals (from the same counter), or a paired set of PWM signals with dead-band delays added.
#define PWM0_CTL (*((unsigned long *)0x40028040))
#define PWM1_CTL (*((unsigned long *)0x40029080))
#define PWM2_CTL (*((unsigned long *)0x400280C0))
#define PWM3_CTL (*((unsigned long *)0x40028100))

// Register 44: PWM0 Generator A Control (PWM0GENA), offset 0x060
// This register controls the generation of the pwmA signal based on the load and zero output puleses from the counter,
// as well as the compare A and compare B pulses from the comparators (PWM0GENA controls the PWM generator 0 block, and so on). When the counter is running in Count-Down mode, only four of these events occur; when running in Count-Up/Down mode, all six occur. 
// These events provide great flexibility in the positioning and duty cycle of the resulting PWM signal.
#define PWM0_GENA (*((unsigned long *)0x40028060))
#define PWM1_GENA (*((unsigned long *)0x400290A0))
#define PWM2_GENA (*((unsigned long *)0x400280E0))
#define PWM3_GENA (*((unsigned long *)0x40028120))

// Register 48: PWM0 Generator B Control (PWM0GENB), offset 0x064
// These registers control the generation of the pwmB signal based on the load and zero output pulses from the counter, as well as the compare A and compare B pulses from the comparators (PWM0GENB controls the PWM generator 0 block, and so on). 
// When the counter is running in Count-Down mode, only four of these events occur; when running in Count-Up/Down mode, all six occur. These events provide great flexibility in the positioning and duty cycle of the resulting PWM signal.
#define PWM0_GENB (*((unsigned long *)0x40028064))
#define PWM1_GENB (*((unsigned long *)0x400290A4))
#define PWM2_GENB (*((unsigned long *)0x400280E4))
#define PWM3_GENB (*((unsigned long *)0x40028124))

// Register 28: PWM0 Load (PWM0LOAD), offset 0x050
// These registers contain the load value for the PWM counter (PWM0LOAD controls the PWM generator 0 block, and so on). Based on the counter mode configured by the MODE bit in the PWMnCTL register, 
// this value is either loaded into the counter after it reaches zero or is the limit of up-counting after which the counter decrements back to zero. When this value matches the counter, a pulse is output which can be configured to drive the generation of the pwmA and/or pwmB signal 
// (via the PWMnGENA/PWMnGENB register) or drive an interruptor ADC trigger (via the PWMnINTEN register).
#define PWM0_LOAD (*((unsigned long *)0x40028050))
#define PWM1_LOAD (*((unsigned long *)0x40029090))
#define PWM2_LOAD (*((unsigned long *)0x400280D0))
#define PWM3_LOAD (*((unsigned long *)0x40028110))

// Register 36: PWM0 Compare A (PWM0CMPA), offset 0x058
// These registers contain a value to be compared against the counter (PWM0CMPA controls the PWM generator 0 block, and so on). When this value matches the counter, a pulse is output which can be configured to drive the generation of the pwmA and pwmB signals (via the PWMnGENA and PWMnGENB registers) 
// or drive an interrupt or ADC trigger (via the PWMnINTEN register). If the value of this register is greater than the PWMnLOAD register (see page 1278), then no pulse is ever output.
#define PWM0_CMPA (*((unsigned long *)0x40028058))
#define PWM1_CMPA (*((unsigned long *)0x40029098))
#define PWM2_CMPA (*((unsigned long *)0x400280D8))
#define PWM3_CMPA (*((unsigned long *)0x40028118))

// Register 40: PWM0 Compare B (PWM0CMPB), offset 0x05C
// These registers contain a value to be compared against the counter (PWM0CMPB controls the PWM generator 0 block, and so on). When this value matches the counter, a pulse is output which can be configured to drive the generation of the pwmA and pwmB signals (via the PWMnGENA and PWMnGENB registers) 
// or drive an interrupt or ADC trigger (via the PWMnINTEN register). If the value of this register is greater than the PWMnLOAD register, no pulse is ever output.
#define PWM0_CMPB (*((unsigned long *)0x4002805C))
#define PWM1_CMPB (*((unsigned long *)0x4002909C))
#define PWM2_CMPB (*((unsigned long *)0x400280DC))
#define PWM3_CMPB (*((unsigned long *)0x4002811C))

// Register 3: PWM Output Enable (PWMENABLE), offset 0x008
// This register provides a master control of which generated pwmA' and pwmB' signals are output to the MnPWMn pins. By disabling a PWM output, the generation process can continue (for example, when the time bases are synchronized) without driving PWM signals to the pins. When bits in this register are set, 
// the corresponding pwmA' or pwmB' signal is passed through to the output stage. When bits are clear, the pwmA' or pwmB' signal is replaced by a zero value which is also passed to the output stage. The PWMINVERT register controls the output stage, so if the corresponding bit is set in that register, 
// the value seen on the MnPWMn signal is inverted from what is configured by the bits in this register. Updates to the bits in this register can be immediate or locally or globally synchronized to the next synchronous update as controlled by the ENUPDn fields in the PWMENUPD register.
#define PWM_ENABLE (*((unsigned long *)0x40028008))






/**********************************************************
 * EJEMPLO 6.1
 * Programa que aumenta y disminiye el duty cycle
 * de un pwm a 1KHZ por el pin PF3 usando el modulo PWM1 con el generador 3B
 * y haciendo la comparacion con el comparador A

 * by Miguel Lozano (A.K.A. BLAM)                                                *
 **********************************************************
*/
#include "tm4c123gh6pm.h"
#include "stdint.h"
#include <stdio.h>
void delayms(int x);

int main(void)
{


    SYSCTL_RCGCPWM_R |= (1<<1);  /* habilitamos el clock para el modulo PWM1 (bit R1 de RCGCPWM) */

    SYSCTL_RCGCGPIO_R |= (1<<5);   /* habilitamos el clock del puerto F () */

    SYSCTL_RCC_R &= ~(1<<20); /* sin pre escalador para el clock del pwm (bit 20 USEPWMDIV de RCC */

    /* habilitamos la funcion alternativa para PF3 (M1PWM7) */
    GPIO_PORTF_AFSEL_R = (1<<3);           /* habilitamos funcion alternativa para PF3 */
    GPIO_PORTF_PCTL_R =(GPIO_PORTF_PCTL_R&~0x0000F000)| 0x00005000 ;      /* valor para usar el pin PF3 como M1PWM7 */

    GPIO_PORTF_DEN_R |= (1<<3);  /* habilitamos pin PF3 como pin digital */

    PWM1_3_CTL_R&=~(1<<0);       /* deshabilitamos el conteo (bit 0 de PWM1CTL) */


    PWM1_3_GENB_R = 0x0000008C;  /* configuramos para generar la señal PWM con el generador 3 salida B y usando el comparador A*/
                                 /* Teniendo un contador descedente, cuando el contador llegue a un valor igual */
                                 /* al valor del comparador A, la señal pwm se pondrá en LOW (bits D3D2 del registro PWM1GENB 11=0x3) */

                                 /* luego cuando el valor del contador llegue a 0,la señal PWM se pondra en HIGH (bits D3D2 de PWM1GENB 10=0x2)*/
                                 /* con esto el valor de PWM1GENB es 0x8C*/

  //PWM1_INVERT_R |=(1<<6);

    PWM1_3_LOAD_R = 16000;       /* valor tope para Fpwm = 1KHZ-> valor_tope=(16000000Hz/1000)=16000  */
    PWM1_3_CMPA_R = 8000;        /* iniciamos con el valor minimo dt =50 */
    PWM1_3_CTL_R  = 1;           /* activamos el contador del modulo PWM1 */
    PWM1_ENABLE_R = (1<<7);      /* activamos la salida pwm7pin (que corresponde a PF3) del Modulo PWM1 */

    // hacemos un retardo para que un inicio nos muestre la señal con DC=50%
    delayms(5000);
    delayms(5000);
    delayms(5000);
    // luego hacemos un efecto fadding disminuyendo y aumentando el DT progresivamente

    int x;
    while(1)

    {
        for(x=15900;x>=100;x-=100)
            {
                  PWM1_3_CMPA_R = x;
                  delayms(20);
            }

         delayms(50);

        for(x=100;x<=15900;x+=100)
            {
                PWM1_3_CMPA_R = x;
                delayms(20);
            }

        delayms(50);

   }
}


void delayms(int x)
{
    int a, b;
    for( a= 0 ; a < x; a++)
        for(b = 0; b < 3180; b++)
            {}
}


