#pragma once
#include "LSM6DS3Sensor.h"

// https://raspberry-projects.com/pi/programming-in-c/i2c/using-the-i2c-interface

class tI2CTinker : public tI2CInterface
{
public:
	enum eI2CBus {
		One = 1,
		Four = 4,
		Size
	};

	tI2CTinker(eI2CBus i2cBus = eI2CBus::One);
	tI2CTinker(uint8_t slaveAddress, eI2CBus i2cBus = eI2CBus::One);
	~tI2CTinker();
	bool IsValid() const {return valid_;}
	uint8_t Write (uint8_t address, const uint8_t *buffer, uint16_t length) override;
	uint8_t Read (uint8_t address, uint8_t *buffer, uint16_t length) override;
private:
	int fileHandle_;
	bool valid_;
};
