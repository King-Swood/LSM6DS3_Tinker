#include "i2cTinker.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <i2c/smbus.h>
#include <stdio.h>

tI2CTinker::tI2CTinker(eI2CBus i2cBus)
	: tI2CTinker(LSM6DS3_ACC_GYRO_I2C_ADDRESS_HIGH, i2cBus)
{

}

tI2CTinker::tI2CTinker(uint8_t slaveAddress, eI2CBus i2cBus)
	: fileHandle_(-1),
	  valid_(false)
{
	if (i2cBus < eI2CBus::Size)
	{
		static const char FilenameLength = 20;
		char filename[FilenameLength];
		sprintf(filename, "/dev/i2c-%d", i2cBus);
		fileHandle_ = open (filename, O_RDWR);
		if (fileHandle_ >= 0)
		{
			if (ioctl(fileHandle_, I2C_SLAVE, slaveAddress))
			{
				valid_ = true;
			}
			else
			{
				printf("Failed to select I2C device with slave address %d\n", slaveAddress);
				close(fileHandle_);
			}
		}
		else
		{
			printf("Failed to open I2C bus %d\n", i2cBus);
		}
	}
}

tI2CTinker::~tI2CTinker()
{
	if (valid_)
	{
		close(fileHandle_);
	}
}

uint8_t tI2CTinker::Write(uint8_t address, const uint8_t *buffer, uint16_t length)
{
	uint8_t bytesWritten = i2c_smbus_write_block_data(fileHandle_, address, length, buffer);
	return bytesWritten;
}

uint8_t tI2CTinker::Read(uint8_t address, uint8_t *buffer, uint16_t length)
{
	uint8_t bytesRead = i2c_smbus_read_i2c_block_data(fileHandle_, address, length, buffer);
	return bytesRead;
}
