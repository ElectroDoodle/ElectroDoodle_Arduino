#ifndef __HEADER_MCP23X17__
#define __HEADER_MCP23X17__

#include <Arduino.h>
#include <Wire.h>

#define ADDR_DEFAULT (0X20)

#define REG_DIRECTION    0x00
#define REG_POLARITY     0x02
#define REG_INT_ENABLE   0x04
#define REG_DEF_COMPARE  0x06
#define REG_INT_CTRL     0x08
#define REG_CTRL         0x0A
#define REG_PULLUP       0x0C
#define REG_INT_FLAG     0x0E
#define REG_INT_CAPTURE  0x10
#define REG_PORT_VALUES  0x12
#define REG_OUTPUT_LATCH 0x14

#define IO_0   (1 << 0)
#define IO_1   (1 << 1)
#define IO_2   (1 << 2)
#define IO_3   (1 << 3)
#define IO_4   (1 << 4)
#define IO_5   (1 << 5)
#define IO_6   (1 << 6)
#define IO_7   (1 << 7)
#define IO_ALL (0xFF)

class MCP23x17
{

	public:
		enum Mode { MODE_I2C, MODE_SPI };
		enum PinDir { DIR_OUTPUT = 0, DIR_INPUT = 1 };
		enum Port { PORT_A, PORT_B };


		MCP23x17(MCP23x17::Mode);
		int Connect();
		void SetAddress(uint8_t address);
		int GetAddress() { return m_address; }

		int SetDirection(MCP23x17::Port, uint8_t pins, MCP23x17::PinDir);
		int SetPortValues(MCP23x17::Port port, uint8_t pins, int set);

	private:
		Mode m_mode;
		uint8_t m_address = ADDR_DEFAULT;

		int WriteRegister(uint8_t reg, uint8_t val);
		int ReadRegister(uint8_t reg, uint8_t count, uint8_t *outBytes);
};

#endif

