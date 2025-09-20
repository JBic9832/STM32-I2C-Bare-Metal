#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <characters.h>

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

// I2C1 clock PB6
// I2C1 data  PB7

typedef struct {
	volatile uint32_t MODER;
	volatile uint32_t OTYPER;
	volatile uint32_t OSPEEDR;
	volatile uint32_t PUPDR;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t LCKR;
	volatile uint32_t AFRL;
	volatile uint32_t AFRH;
} GPIOReg_t;

#define GPIOB_BASE_ADDR 0x40020400u
#define GPIOB ((GPIOReg_t*)GPIOB_BASE_ADDR)

typedef struct {
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t OAR1;
	volatile uint32_t OAR2; 
	volatile uint32_t DR; 
	volatile uint32_t SR1; 
	volatile uint32_t SR2; 
	volatile uint32_t CCR; 
	volatile uint32_t TRISE; 
	volatile uint32_t FLTR; 
} I2CReg_t;

#define I2C1_BASE_ADDR 0x40005400u
#define I2C1 ((I2CReg_t*)I2C1_BASE_ADDR)

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

#define RCC_BASE_ADDR 0x40023800u
#define RCC ((RCCReg_t*)RCC_BASE_ADDR)

uint8_t I2C_SLAVE_ADDR = 0x78;

/*
 *
 * If things don't work first check if it is an issue of pull up resistors not being present.
 */

typedef struct {
	uint16_t column;
	uint16_t page;
	uint8_t  bit;
} PixelLocation_t;

void I2C1_SendCommand(uint8_t cmd) {
    volatile uint32_t tmp;

    // START
    I2C1->CR1 |= (1 << 8);
    while (!(I2C1->SR1 & (1 << 0))); // SB

    // Address + W
    I2C1->DR = (I2C_SLAVE_ADDR) | 0; // 7-bit addr << 1, write
    while (!(I2C1->SR1 & (1 << 1))); // ADDR
    tmp = I2C1->SR1;
    tmp = I2C1->SR2; (void)tmp;

    // Control byte = 0x00 (command)
    I2C1->DR = 0x00;
    while (!(I2C1->SR1 & (1 << 7))); // TXE

    // Actual command
    I2C1->DR = cmd;
    while (!(I2C1->SR1 & (1 << 2))); // BTF = byte transfer finished

    // STOP
    I2C1->CR1 |= (1 << 9);
}

void I2C1_SendData(uint8_t data) {
    volatile uint32_t tmp;

    // START
    I2C1->CR1 |= (1 << 8);
    while (!(I2C1->SR1 & (1 << 0))); // SB

    // Address + W
    I2C1->DR = (I2C_SLAVE_ADDR) | 0; // 7-bit addr << 1, write
    while (!(I2C1->SR1 & (1 << 1))); // ADDR
    tmp = I2C1->SR1;
    tmp = I2C1->SR2; (void)tmp;

    // Control byte = 0x00 (command)
    I2C1->DR = 0x40;
    while (!(I2C1->SR1 & (1 << 7))); // TXE

    // Actual command
    I2C1->DR = data;
    while (!(I2C1->SR1 & (1 << 2))); // BTF = byte transfer finished

    // STOP
    I2C1->CR1 |= (1 << 9);
}

PixelLocation_t GetPixelLocation(uint16_t x, uint16_t y) {
	PixelLocation_t pixelLoc;

	pixelLoc.column = x;
	pixelLoc.page   = y / 8;
	pixelLoc.bit    = y % 8;

	return pixelLoc;
}

void SetPageAndColToZeroAddr() {
	I2C1_SendCommand(0x21);
	I2C1_SendCommand(0x00);
	I2C1_SendCommand(0x7F);

	I2C1_SendCommand(0x22);
	I2C1_SendCommand(0x00);
	I2C1_SendCommand(0x07);
}

typedef struct {
	int pos_x;
	int pos_y;
} Cursor_t;

void DrawCharToFramebuffer(uint8_t* character, uint8_t* framebuffer, Cursor_t* cursor) {
	for (int row = 0; row < 7; row++) {
		uint8_t rowbits = character[row];
		for (int col = 0; col < 5; col++) {
			if (rowbits & (1 << (4 - col))) {
				PixelLocation_t l = GetPixelLocation(cursor->pos_x + col, cursor->pos_y + row);
				uint16_t index = l.page * 128 + l.column;
				framebuffer[index] |= 1 << l.bit;
			}
		}
	}

	cursor->pos_x += 8;
}

int main(void)
{
	// Enable peripheral clock for GPIOA
	RCC->AHB1ENR |= 1 << 1;
	// Enable I2C1 Clock
	RCC->APB1ENR |= 1 << 21;

	/**
	 * For PB6 & PB7 enable Alternate Function Mode.
	 */
	// Clear mode bits for PB7 and PB6
	GPIOB->MODER &= ~(0xF << 12);
	// Set bits to Alternate Mode
	// 1 0 <- for 2 pins = 1 0 1 0 = 10
	GPIOB->MODER |=   0xA << 12;

	/**
	 * Enable AFRL
	 */
	// Clear bits 24:31 in AFRL for pins 6 and 7
	GPIOB->AFRL &= ~(0xFF << 24);
	// Set bits for AF4
	// 0 1 0 0 <- for 2 pins = 0 1 0 0 0 1 0 0 = 0x44
	GPIOB->AFRL |=   0x44 << 24;

	/**
	 * Set Output type to open drain
	 */
	GPIOB->OTYPER |= 3 << 6;

	/**
	 * Set output speed to high speed
	 */
	GPIOB->OSPEEDR &= ~(0xF << 12);
	GPIOB->OSPEEDR |=   0xA << 12;

	/**
	 * Set the I2C peripheral clock frequency 
	 * in the second I2C control register
	 */
	// Clear the frequency bits
	I2C1->CR2 &= ~(0x3F << 0);
	// Set frequency to 16MHz
	I2C1->CR2 |=   0x10 << 0;

	/*
	 * Configure I2C clock control register
	 */
	// Set I2C master mode to standard mode (Sm)
	I2C1->CCR   = 0x50;
	I2C1->TRISE = 17;

	/*
	 * Enable I2C peripheral
	 */
	I2C1->CR1 |= 1 << 0;
	
	while(!(I2C1->CR1 & 1));  // wait for PE

    // Minimal command sequence
    I2C1_SendCommand(0xAE); // Display OFF
    I2C1_SendCommand(0xD5); // Set display clock div
    I2C1_SendCommand(0x80); // Suggested ratio
    I2C1_SendCommand(0xA8); // Set multiplex
    I2C1_SendCommand(0x3F); // 1/64 duty
    I2C1_SendCommand(0xD3); // Set display offset
    I2C1_SendCommand(0x00); // No offset
    I2C1_SendCommand(0x40); // Set start line
    I2C1_SendCommand(0x8D); // Charge pump
    I2C1_SendCommand(0x14); // Enable
    I2C1_SendCommand(0x20); // Memory mode
    I2C1_SendCommand(0x00); // Horizontal addressing
    I2C1_SendCommand(0xA0); // Seg remap
    I2C1_SendCommand(0xC0); // COM scan dec
    I2C1_SendCommand(0xDA); // COM pins
    I2C1_SendCommand(0x12);
    I2C1_SendCommand(0x81); // Contrast
    I2C1_SendCommand(0x7F);
    I2C1_SendCommand(0xD9); // Pre-charge
    I2C1_SendCommand(0xF1);
    I2C1_SendCommand(0xDB); // VCOM detect
    I2C1_SendCommand(0x40);
    I2C1_SendCommand(0xA4); // Resume RAM
    I2C1_SendCommand(0xA6); // Normal display
    I2C1_SendCommand(0xAF); // Display ON
	I2C1_SendCommand(0x2E); // Deactivate scroll (Prevent ram corruption)

	uint8_t framebuffer[1024];
	memset(framebuffer, 0, sizeof(framebuffer));

	// Clear display
	SetPageAndColToZeroAddr();

	for (int i = 0; i < 1024; i++) {
		I2C1_SendData(framebuffer[i]);
	}

	static Cursor_t cursor;
	cursor.pos_x = 0;
	cursor.pos_y = 10;

	// Draw message
	DrawCharToFramebuffer(h, framebuffer, &cursor);
	DrawCharToFramebuffer(e, framebuffer, &cursor);
	DrawCharToFramebuffer(l, framebuffer, &cursor);
	DrawCharToFramebuffer(l, framebuffer, &cursor);
	DrawCharToFramebuffer(o, framebuffer, &cursor);
	DrawCharToFramebuffer(comma, framebuffer, &cursor);
	DrawCharToFramebuffer(space, framebuffer, &cursor);
	DrawCharToFramebuffer(w, framebuffer, &cursor);
	DrawCharToFramebuffer(o, framebuffer, &cursor);
	DrawCharToFramebuffer(r, framebuffer, &cursor);
	DrawCharToFramebuffer(l, framebuffer, &cursor);
	DrawCharToFramebuffer(d, framebuffer, &cursor);
	DrawCharToFramebuffer(exclamation, framebuffer, &cursor);

	SetPageAndColToZeroAddr();
	for (int i = 0; i < 1024; i++) {
		I2C1_SendData(framebuffer[i]);
	}


	I2C1_SendCommand(0x27); // Horizontal scroll command
	I2C1_SendCommand(0x00); // Dummy byte 
	I2C1_SendCommand(0x00); // Start page address
	I2C1_SendCommand(0x07); // Scroll interval
	I2C1_SendCommand(0x07); // End page address
	I2C1_SendCommand(0x00); // Dummy bytes
	I2C1_SendCommand(0xFF);

	I2C1_SendCommand(0x2F); // Activate scroll

    /* Loop forever */
	for(;;);
}

