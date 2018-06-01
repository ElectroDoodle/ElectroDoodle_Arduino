#include "MCP23x17.h"


MCP23x17::MCP23x17(MCP23x17::Mode mode)
{
	m_mode = mode;
}


int MCP23x17::SetPortValues(MCP23x17::Port port, uint8_t pins, int set)
{
	uint8_t reg = REG_PORT_VALUES;
	uint8_t current;

	if(port == PORT_B) {
		reg += 1;
	}

	int ret = this->ReadRegister(reg, 1, &current);

	if(!ret) return 0;

	for(int x = 0; x < 8; x++) {
		if(pins && (1<<x)) {
			if(!set) {
				current &= ~(1<<x);
			}
			else {
				current |= (1<<x);
			}
		}
	}

	return this->WriteRegister(reg, current);
}

int MCP23x17::SetDirection(MCP23x17::Port port, uint8_t pins, MCP23x17::PinDir dir)
{
	uint8_t reg = REG_DIRECTION;
	uint8_t current;

	if(port == PORT_B) {
		reg += 1;
	}


	int ret = this->ReadRegister(reg, 1, &current);

	if(!ret) return 0;

	for(int x = 0; x < 8; x++) {
		if(pins && (1<<x)) {
			if(dir == DIR_OUTPUT) {
				current &= ~(1<<x);
			}
			else {
				current |= (1<<x);
			}
		}
	}

	return this->WriteRegister(reg, current);
}


int MCP23x17::ReadRegister(uint8_t reg, uint8_t count, uint8_t *outBytes)
{
	Wire.beginTransmission(m_address);

	Wire.write(reg);

	int ret = Wire.endTransmission();

	if(ret) {
		return 0;
	}

	Wire.requestFrom(m_address, count);

	int x;
	for(x = 0; Wire.available() && x < count; x++) {
		uint8_t value = Wire.read();
		if(outBytes) {
			outBytes[x] = value;
		}
	}

	while(Wire.available()) Wire.read();

	if(x != count) {
		return 0;
	}

	return 1;
}


int MCP23x17::WriteRegister(uint8_t reg, uint8_t val)
{
	Wire.beginTransmission(m_address);

	Wire.write(reg);

	Wire.write(val);

	int ret = Wire.endTransmission();

	if(ret) {
		return 0;
	}

	return 1;
}

int MCP23x17::Connect()
{
	return this->ReadRegister(0, 1, 0);
}
