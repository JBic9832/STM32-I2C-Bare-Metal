#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "characters.h"
#include "I2C_Hal.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

// I2C1 clock PB6
// I2C1 data  PB7


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
    volatile I2C_SR1_t tmp1;
    volatile I2C_SR2_t tmp2;

    // START
    I2C1->CR1.START = 1;
    while (!(I2C1->SR1.SB == 1)); // SB

    // Address + W
    I2C1->DR.DATA = (I2C_SLAVE_ADDR) | 0; // 7-bit addr << 1, write
    while (!(I2C1->SR1.ADDR == 1)); // ADDR
    tmp1 = I2C1->SR1;
    tmp2 = I2C1->SR2; (void)tmp1; (void)tmp2;

    // Control byte = 0x00 (command)
    I2C1->DR.DATA = 0x00;
    while (!(I2C1->SR1.TxE == 1)); // TXE

    // Actual command
    I2C1->DR.DATA = cmd;
    while (!(I2C1->SR1.BTF == 1)); // BTF = byte transfer finished

    // STOP
    I2C1->CR1.STOP = 1;
}

void I2C1_SendData(uint8_t data) {
    volatile I2C_SR1_t tmp1;
    volatile I2C_SR2_t tmp2;

    // START
    I2C1->CR1.START = 1;
    while (!(I2C1->SR1.SB == 1)); // SB

    // Address + W
    I2C1->DR.DATA = (I2C_SLAVE_ADDR) | 0; // 7-bit addr << 1, write
    while (!(I2C1->SR1.ADDR == 1)); // ADDR
    tmp1 = I2C1->SR1;
    tmp2 = I2C1->SR2; (void)tmp1; (void)tmp2;

    // Control byte = 0x00 (command)
    I2C1->DR.DATA = 0x40;
    while (!(I2C1->SR1.TxE == 1)); // TXE

    // Actual command
    I2C1->DR.DATA = data;
    while (!(I2C1->SR1.BTF == 1)); // BTF = byte transfer finished

    // STOP
    I2C1->CR1.STOP = 1;
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

void DrawCharToFramebuffer(char character, uint8_t* framebuffer, Cursor_t* cursor) {
	int idx = character - 32;
	uint8_t* characterBitmap = characters[idx];
	for (int row = 0; row < 7; row++) {
		uint8_t rowbits = characterBitmap[row];
		for (int col = 0; col < 5; col++) {
			if (rowbits & (1 << (4 - col))) {
				PixelLocation_t l = GetPixelLocation(cursor->pos_x + col, cursor->pos_y + row);
				uint16_t index = l.page * 128 + l.column;
				framebuffer[index] |= 1 << l.bit;
			}
		}
	}

	if (cursor->pos_x + 8 >= 120) {
		cursor->pos_y += 8;
		cursor->pos_x = 0;
	} else {
		cursor->pos_x += 8;
	}
}

void WriteMessageToFramebuffer(const char* message, uint8_t* framebuffer, Cursor_t* cursor) {
	size_t len = strlen(message);
	printf("Size of message is %d\n", len);
	for (int i = 0; i < len; i++) {
		DrawCharToFramebuffer(message[i], framebuffer, cursor);
	}
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
	GPIOB->MODER.MODER6 = 2;
	GPIOB->MODER.MODER7 = 2;

	/**
	 * Enable AFRL
	 */
	// We need AF4 for I2C
	GPIOB->AFRL.AFR6 = 4;
	GPIOB->AFRL.AFR7 = 4;

	/**
	 * Set Output type to open drain
	 */
	GPIOB->OTYPER.OT6 = 1;
	GPIOB->OTYPER.OT7 = 1;

	/**
	 * Set output speed to high speed
	 */
	GPIOB->OSPEEDR.OSPEEDR6 = 2;
	GPIOB->OSPEEDR.OSPEEDR7 = 2;

	/**
	 * Set the I2C peripheral clock frequency 
	 * in the second I2C control register
	 */
	// Set frequency to 16MHz
	I2C1->CR2.FREQ = 16;

	/*
	 * Configure I2C clock control register
	 */
	// Set I2C master mode to standard mode (Sm)
	I2C1->CCR.CCR = 0x50;
	I2C1->TRISE.TRISE = 17;

	/*
	 * Enable I2C peripheral
	 */
	//I2C1->CR1 |= 1 << 0;
	I2C1->CR1.PE = 1;
	
	while(!(I2C1->CR1.PE == 1));  // wait for PE

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
	cursor.pos_y = 0;

	// Draw message
	const char* message = "Testing DR...";
	WriteMessageToFramebuffer(message, framebuffer, &cursor);

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

