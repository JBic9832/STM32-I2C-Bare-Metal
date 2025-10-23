/*
 *
 * This file contains the minimal tools needed to create an I2C application using the STM32F407.
 * This is not a full HAL for the device and there may be functionality missing.
 *
 */
#include <stdint.h>

typedef struct {
	uint32_t MODER0  : 2;
	uint32_t MODER1  : 2;
	uint32_t MODER2  : 2;
	uint32_t MODER3  : 2;
	uint32_t MODER4  : 2;
	uint32_t MODER5  : 2;
	uint32_t MODER6  : 2;
	uint32_t MODER7  : 2;
	uint32_t MODER8  : 2;
	uint32_t MODER9  : 2;
	uint32_t MODER10 : 2;
	uint32_t MODER11 : 2;
	uint32_t MODER12 : 2;
	uint32_t MODER13 : 2;
	uint32_t MODER14 : 2;
	uint32_t MODER15 : 2;
} GPIO_MODER_t;

typedef struct {
	uint32_t OT0      : 1;
	uint32_t OT1      : 1;
	uint32_t OT2      : 1;
	uint32_t OT3      : 1;
	uint32_t OT4      : 1;
	uint32_t OT5      : 1;
	uint32_t OT6      : 1;
	uint32_t OT7      : 1;
	uint32_t OT8      : 1;
	uint32_t OT9      : 1;
	uint32_t OT10     : 1;
	uint32_t OT11     : 1;
	uint32_t OT12     : 1;
	uint32_t OT13     : 1;
	uint32_t OT14     : 1;
	uint32_t OT15     : 1;
	uint32_t reserved :16;
} GPIO_OTYPER_t;

typedef struct {
	uint32_t OSPEEDR0  : 2;
	uint32_t OSPEEDR1  : 2;
	uint32_t OSPEEDR2  : 2;
	uint32_t OSPEEDR3  : 2;
	uint32_t OSPEEDR4  : 2;
	uint32_t OSPEEDR5  : 2;
	uint32_t OSPEEDR6  : 2;
	uint32_t OSPEEDR7  : 2;
	uint32_t OSPEEDR8  : 2;
	uint32_t OSPEEDR9  : 2;
	uint32_t OSPEEDR10 : 2;
	uint32_t OSPEEDR11 : 2;
	uint32_t OSPEEDR12 : 2;
	uint32_t OSPEEDR13 : 2;
	uint32_t OSPEEDR14 : 2;
	uint32_t OSPEEDR15 : 2;
} GPIO_OSPEEDR_t;

typedef struct {
	uint32_t PUPDR0  : 2;
	uint32_t PUPDR1  : 2;
	uint32_t PUPDR2  : 2;
	uint32_t PUPDR3  : 2;
	uint32_t PUPDR4  : 2;
	uint32_t PUPDR5  : 2;
	uint32_t PUPDR6  : 2;
	uint32_t PUPDR7  : 2;
	uint32_t PUPDR8  : 2;
	uint32_t PUPDR9  : 2;
	uint32_t PUPDR10 : 2;
	uint32_t PUPDR11 : 2;
	uint32_t PUPDR12 : 2;
	uint32_t PUPDR13 : 2;
	uint32_t PUPDR14 : 2;
	uint32_t PUPDR15 : 2;
} GPIO_PUPDR_t;

typedef struct {
	uint32_t IDR0     : 1;
	uint32_t IDR1     : 1;
	uint32_t IDR2     : 1;
	uint32_t IDR3     : 1;
	uint32_t IDR4     : 1;
	uint32_t IDR5     : 1;
	uint32_t IDR6     : 1;
	uint32_t IDR7     : 1;
	uint32_t IDR8     : 1;
	uint32_t IDR9     : 1;
	uint32_t IDR10    : 1;
	uint32_t IDR11    : 1;
	uint32_t IDR12    : 1;
	uint32_t IDR13    : 1;
	uint32_t IDR14    : 1;
	uint32_t IDR15    : 1;
	uint32_t reserved :16;
} GPIO_IDR_t;

typedef struct {
	uint32_t ODR0     : 1;
	uint32_t ODR1     : 1;
	uint32_t ODR2     : 1;
	uint32_t ODR3     : 1;
	uint32_t ODR4     : 1;
	uint32_t ODR5     : 1;
	uint32_t ODR6     : 1;
	uint32_t ODR7     : 1;
	uint32_t ODR8     : 1;
	uint32_t ODR9     : 1;
	uint32_t ODR10    : 1;
	uint32_t ODR11    : 1;
	uint32_t ODR12    : 1;
	uint32_t ODR13    : 1;
	uint32_t ODR14    : 1;
	uint32_t ODR15    : 1;
	uint32_t RESERVED :16;
} GPIO_ODR_t;

typedef struct {
	uint32_t BS0  : 1;
	uint32_t BS1  : 1;
	uint32_t BS2  : 1;
	uint32_t BS3  : 1;
	uint32_t BS4  : 1;
	uint32_t BS5  : 1;
	uint32_t BS6  : 1;
	uint32_t BS7  : 1;
	uint32_t BS8  : 1;
	uint32_t BS9  : 1;
	uint32_t BS10 : 1;
	uint32_t BS11 : 1;
	uint32_t BS12 : 1;
	uint32_t BS13 : 1;
	uint32_t BS14 : 1;
	uint32_t BS15 : 1;
	uint32_t BR0  : 1;
	uint32_t BR1  : 1;
	uint32_t BR2  : 1;
	uint32_t BR3  : 1;
	uint32_t BR4  : 1;
	uint32_t BR5  : 1;
	uint32_t BR6  : 1;
	uint32_t BR7  : 1;
	uint32_t BR8  : 1;
	uint32_t BR9  : 1;
	uint32_t BR10 : 1;
	uint32_t BR11 : 1;
	uint32_t BR12 : 1;
	uint32_t BR13 : 1;
	uint32_t BR14 : 1;
	uint32_t BR15 : 1;
} GPIO_BSRR_t;

typedef struct {
	uint32_t LCK0     : 1;
	uint32_t LCK1     : 1;
	uint32_t LCK2     : 1;
	uint32_t LCK3     : 1;
	uint32_t LCK4     : 1;
	uint32_t LCK5     : 1;
	uint32_t LCK6     : 1;
	uint32_t LCK7     : 1;
	uint32_t LCK8     : 1;
	uint32_t LCK9     : 1;
	uint32_t LCK10    : 1;
	uint32_t LCK11    : 1;
	uint32_t LCK12    : 1;
	uint32_t LCK13    : 1;
	uint32_t LCK14    : 1;
	uint32_t LCK15    : 1;
	uint32_t LCKK     : 1;
	uint32_t RESERVED :15;
} GPIO_LCKR_t;

/*
 * To properly obtain the correct GPIO number you must do the following:
 * If using AFRL then this register matches the GPIO outputs already.
 * If using AFRH then add subtract 8 from the output you want and that will be
 * its value in this struct.
 * For example to access AFRH15 -> 15 - 8 = 7 -> AFR7 is the correct choice.
 * The memory is mapped by the GPIOReg_t struct already so no need to do furter work.
 */
typedef struct {
	uint32_t AFR0 : 4;
	uint32_t AFR1 : 4;
	uint32_t AFR2 : 4;
	uint32_t AFR3 : 4;
	uint32_t AFR4 : 4;
	uint32_t AFR5 : 4;
	uint32_t AFR6 : 4;
	uint32_t AFR7 : 4;
} GPIO_AFR_t;


typedef struct {
	volatile GPIO_MODER_t MODER;
	volatile GPIO_OTYPER_t OTYPER;
	volatile GPIO_OSPEEDR_t OSPEEDR;
	volatile GPIO_PUPDR_t PUPDR;
	volatile GPIO_IDR_t IDR;
	volatile GPIO_ODR_t ODR;
	volatile GPIO_BSRR_t BSRR;
	volatile GPIO_LCKR_t LCKR;
	volatile GPIO_AFR_t AFRL;
	volatile GPIO_AFR_t AFRH;
} GPIOReg_t;

typedef struct {
	uint32_t PE        : 1;
	uint32_t SMBUS     : 1;
	uint32_t RESERVED0 : 1;
	uint32_t SMBTYPE   : 1;
	uint32_t ENARP     : 1;
	uint32_t PEC_EN    : 1;
	uint32_t ENGC      : 1;
	uint32_t NOSTRETCH : 1;
	uint32_t START     : 1;
	uint32_t STOP      : 1;
	uint32_t ACK       : 1;
	uint32_t POS       : 1;
	uint32_t PEC       : 1;
	uint32_t ALERT     : 1;
	uint32_t RESERVED1 : 1;
	uint32_t SWRST     : 1;
	uint32_t RESERVED  :16;
} I2C_CR1_t;

typedef struct {
	 uint32_t FREQ      : 6;
	 uint32_t RESERVED0 : 2;
	 uint32_t ITERREN   : 1;
	 uint32_t ITEVTEN   : 1;
	 uint32_t ITBUFEN   : 1;
	 uint32_t DMAEN     : 1;
	 uint32_t LAST      : 1;
	 uint32_t RESERVED1 :19;
 } I2C_CR2_t;

typedef struct {
	uint32_t ADD0      : 1;
	uint32_t ADDR      : 7;
	uint32_t ADD       : 2;
	uint32_t RESERVED0 : 5;
	uint32_t ADDMODE   : 1;
	uint32_t RESERVED1 :16;
} I2C_OAR1_t;

typedef struct {
	uint32_t ENDUAL   : 1;
	uint32_t ADD2     : 7;
	uint32_t RESERVED :24;
} I2C_OAR2_t;

typedef struct {
	uint32_t DATA     : 8;
	uint32_t RESERVED :24;
} I2C_DR_t;

typedef struct {
	uint32_t SB        : 1;
	uint32_t ADDR      : 1;
	uint32_t BTF       : 1;
	uint32_t ADD10     : 1;
	uint32_t STOPF     : 1;
	uint32_t RESERVED0 : 1;
	uint32_t RxNE      : 1;
	uint32_t TxE       : 1;
	uint32_t BERR      : 1;
	uint32_t ARLO      : 1;
	uint32_t AF        : 1;
	uint32_t OVR       : 1;
	uint32_t PECERR    : 1;
	uint32_t RESERVED1 : 1;
	uint32_t TIMEOUT   : 1;
	uint32_t SMBALERT  : 1;
	uint32_t RESERVED2 :16;
} I2C_SR1_t;

typedef struct {
	uint32_t MSL        : 1;
	uint32_t BUSY       : 1;
	uint32_t TRA        : 1;
	uint32_t RESERVED0  : 1;
	uint32_t GENCALL    : 1;
	uint32_t SMBDEFAULT : 1;
	uint32_t SMBHOST    : 1;
	uint32_t DUALF      : 1;
	uint32_t PEC        : 8;
	uint32_t RESERVED1  :16;
} I2C_SR2_t;

typedef struct {
	uint32_t CCR       :12;
	uint32_t RESERVED0 : 2;
	uint32_t DUTY      : 1;
	uint32_t FS        : 1;
	uint32_t RESERVED1 :16;
} I2C_CCR_t;

typedef struct {
	uint32_t TRISE    : 6;
	uint32_t RESERVED :26;
} I2C_TRISE_t;

typedef struct {
	uint32_t DNF      : 4;
	uint32_t ANOFF    : 1;
	uint32_t RESERVED :27;
} I2C_FLTR_t;

typedef struct {
	volatile I2C_CR1_t CR1;
	volatile I2C_CR2_t CR2;
	volatile I2C_OAR1_t OAR1;
	volatile I2C_OAR2_t OAR2; 
	volatile I2C_DR_t DR; 
	volatile I2C_SR1_t SR1; 
	volatile I2C_SR2_t SR2; 
	volatile I2C_CCR_t CCR; 
	volatile I2C_TRISE_t TRISE; 
	volatile I2C_FLTR_t FLTR; 
} I2CReg_t;

typedef struct {
	uint32_t HSION     : 1;
	uint32_t HSIRDY    : 1;
	uint32_t RESERVED0 : 1;
	uint32_t HSITRIM   : 5;
	uint32_t HSICAL    : 8;
	uint32_t HSEON     : 1;
	uint32_t HSERDY    : 1;
	uint32_t HSEBYP    : 1;
	uint32_t CSSON     : 1;
	uint32_t RESERVED1 : 4;
	uint32_t PLLON     : 1;
	uint32_t PLLRDY    : 1;
	uint32_t PLLI2SON  : 1;
	uint32_t PLLI2SRDY : 1;
	uint32_t RESERVED2 : 4;
} RCC_CR_t;

typedef struct {
	uint32_t PLLM0     : 1;
	uint32_t PLLM1     : 1;
	uint32_t PLLM2     : 1;
	uint32_t PLLM3     : 1;
	uint32_t PLLM4     : 1;
	uint32_t PLLM5     : 1;
	uint32_t PLLN      : 9;
	uint32_t RESERVED0 : 1;
	uint32_t PLLP0     : 1;
	uint32_t PLLP1     : 1;
	uint32_t RESERVED1 : 4;
	uint32_t PLLSRC    : 1;
	uint32_t RESERVED2 : 1;
	uint32_t PLLQ0     : 1;
	uint32_t PLLQ1     : 1;
	uint32_t PLLQ2     : 1;
	uint32_t PLLQ3     : 1;
	uint32_t RESERVED3 : 4;
} RCC_PLLCFGR_t;

typedef struct {
	uint32_t SW0       : 1;
	uint32_t SW1       : 1;
	uint32_t SWS0      : 1;
	uint32_t SWS1      : 1;
	uint32_t HPRE      : 4;
	uint32_t RESERVED0 : 2;
	uint32_t PPRE1     : 3;
	uint32_t PPRE2     : 3;
	uint32_t RTCPRE    : 5;
	uint32_t MCO1      : 2;
	uint32_t I2SSCR    : 1;
	uint32_t MCO1PRE   : 3;
	uint32_t MCO2PRE   : 3;
	uint32_t MCO2      : 2;
} RCC_CFGR_t;

typedef struct {
	uint32_t LSIRDYF     : 1;
	uint32_t LSERDYF     : 1;
	uint32_t HSIRDYF     : 1;
	uint32_t HSERDYF     : 1;
	uint32_t PLLRDYF     : 1;
	uint32_t PLLI2SRDYF  : 1;
	uint32_t RESERVED0   : 1;
	uint32_t CSSF        : 1;
	uint32_t LSIRDYIE    : 1;
	uint32_t LSERDYIE    : 1;
	uint32_t HSIRDYIE    : 1;
	uint32_t HSERDYIE    : 1;
	uint32_t PLLRDYIE    : 1;
	uint32_t PLLI2SRDYIE : 1;
	uint32_t RESERVED1   : 2;
	uint32_t LSIRDYC     : 1;
	uint32_t LSERDYC     : 1;
	uint32_t HSIRDYC     : 1;
	uint32_t HSERDYC     : 1;
	uint32_t PLLRDYC     : 1;
	uint32_t PLLI2SRDYC  : 1;
	uint32_t RESERVED2   : 1;
	uint32_t CSSC        : 1;
	uint32_t RESERVED3   : 8;
} RCC_CIR_t;

typedef struct {
	uint32_t GPIOARST  : 1;
	uint32_t GPIOBRST  : 1;
	uint32_t GPIOCRST  : 1;
	uint32_t GPIODRST  : 1;
	uint32_t GPIOERST  : 1;
	uint32_t GPIOFRST  : 1;
	uint32_t GPIOGRST  : 1;
	uint32_t GPIOHRST  : 1;
	uint32_t GPIOIRST  : 1;
	uint32_t RESERVED0 : 3;
	uint32_t CRCRST    : 1;
	uint32_t RESERVED1 : 8;
	uint32_t DMA1RST   : 1;
	uint32_t DMA2RST   : 1;
	uint32_t RESERVED2 : 2;
	uint32_t ETHMACRST : 1;
	uint32_t RESERVED3 : 3;
	uint32_t OTGHSRST  : 1;
	uint32_t RESERVED4 : 2;
} RCC_AHB1_RSTR_t;

typedef struct {
	uint32_t DCMIRST   : 1;
	uint32_t RESERVED0 : 3;
	uint32_t CRYPRST   : 1;
	uint32_t HASRST    : 1;
	uint32_t RNGRST    : 1;
	uint32_t OTGFSRST  : 1;
	uint32_t RESERVED1 :24;
} RCC_AHB2_RSTR_t;

typedef struct {
	uint32_t FSMCRST  : 1;
	uint32_t RESERVED :31;
} RCC_AHB3_RSTR_t;

typedef struct {
	uint32_t TIM2RST   : 1;
	uint32_t TIM3RST   : 1;
	uint32_t TIM4RST   : 1;
	uint32_t TIM5RST   : 1;
	uint32_t TIM6RST   : 1;
	uint32_t TIM7RST   : 1;
	uint32_t TIM12RST  : 1;
	uint32_t TIM13RST  : 1;
	uint32_t TIM14RST  : 1;
	uint32_t RESERVED0 : 2;
	uint32_t WWDGRST   : 1;
	uint32_t RESERVED1 : 2;
	uint32_t SPI2RST   : 1;
	uint32_t SPI3RST   : 1;
	uint32_t RESERVED2 : 1;
	uint32_t UART2RST  : 1;
	uint32_t UART3RST  : 1;
	uint32_t UART4RST  : 1;
	uint32_t UART5RST  : 1;
	uint32_t I2C1RST   : 1;
	uint32_t I2C2RST   : 1;
	uint32_t I2C3RST   : 1;
	uint32_t RESERVED3 : 1;
	uint32_t CAN1RST   : 1;
	uint32_t CAN2RST   : 1;
	uint32_t RESERVED4 : 1;
	uint32_t PWRRST    : 1;
	uint32_t DACRST    : 1;
	uint32_t RESERVED5 : 2;
} RCC_APB1_RSTR_t;

typedef struct {
	uint32_t TIM1RST   : 1;
	uint32_t TIM8RST   : 1;
	uint32_t RESERVED0 : 2;
	uint32_t USART1RST : 1;
	uint32_t USART6RST : 1;
	uint32_t RESERVED1 : 2;
	uint32_t ADCRST    : 1;
	uint32_t RESERVED2 : 2;
	uint32_t SDIORST   : 1;
	uint32_t SPI1RST   : 1;
	uint32_t RESERVED3 : 1;
	uint32_t SYSCFGRST : 1;
	uint32_t RESERVED4 : 1;
	uint32_t TIM9RST   : 1;
	uint32_t TIM10RST  : 1;
	uint32_t TIM11RST  : 1;
	uint32_t RESERVED5 :13;
} RCC_APB2_RSTR_t;

typedef struct {
	volatile uint32_t CR;
	volatile uint32_t PLLCFGR;
	volatile uint32_t CFGR;
	volatile uint32_t CIR;
	volatile uint32_t AHB1RSTR;
	volatile uint32_t AHB2RSTR;
	volatile uint32_t AHB3RSTR;
	uint32_t RESERVED0;
	volatile uint32_t APB1RSTR;
	volatile uint32_t APB2RSTR;
	uint32_t RESERVED1[2];
	volatile uint32_t AHB1ENR;
	volatile uint32_t AHB2ENR;
	volatile uint32_t AHB3ENR;
	uint32_t RESERVED2;
	volatile uint32_t APB1ENR;
	volatile uint32_t APB2ENR;
	uint32_t RESERVED3[2];
	volatile uint32_t AHB1LPENR;
	volatile uint32_t AHB2LPENR;
	volatile uint32_t AHB3LPENR;
	uint32_t RESERVED4;
	volatile uint32_t APB1LPENR;
	volatile uint32_t APB2LPENR;
	uint32_t RESERVED5[2];
	volatile uint32_t BDCR;
	volatile uint32_t CSR;
	uint32_t RESERVED6[2];
	volatile uint32_t SSCGR;
	volatile uint32_t PLLI2SCFGR;
} RCCReg_t;

// Addresses are specific to the STM32F405/415/407/417/427/437/429/439
#define GPIOB_BASE_ADDR 0x40020400u
#define GPIOB ((GPIOReg_t*)GPIOB_BASE_ADDR)

#define RCC_BASE_ADDR 0x40023800u
#define RCC ((RCCReg_t*)RCC_BASE_ADDR)

#define I2C1_BASE_ADDR 0x40005400u
#define I2C1 ((I2CReg_t*)I2C1_BASE_ADDR)
