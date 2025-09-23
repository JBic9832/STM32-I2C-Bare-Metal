# STM32F407 I2C Implementation
This project showcases a minimal hardware abstraction layer around the STM32F407 and its I2C functionality. There will also be a wrapper for SSD1306 as that is the device I decided to use to learn to write I2C code on the board.

# Usage
The end goal is to have this be a header only library. It has no dependencies apart from the standard c library. The implementation is at the register level so there is no need for additional HAL libraries. 

# Resources
[STM32F407 Reference Manual](https://www.st.com/resource/en/reference_manual/dm00031020-stm32f405-415-stm32f407-417-stm32f427-437-and-stm32f429-439-advanced-arm-based-32-bit-mcus-stmicroelectronics.pdf)

STM32407G Discovery
