#include <cstdio>
#include "LSM6DS3Sensor.h"
#include "i2cTinker.h"
#include <chrono>
#include <thread>
//#include <linux/i2c-dev.h>
//#include <sys/ioctl.h>
//#include <linux/types.h>
//#include <fcntl.h>
//#include <string.h>

using namespace std;

int main()
{
	printf("main()\n");
/*
	int res, bus,  size, file;

        char filename[20];
	sprintf(filename, "/dev/i2c-%d", 1);
	file = open(filename, O_RDWR);
	if (file<0) {
		printf("Unable to open I2C bus!");
		exit(1);
	}

	if (ioctl(file, I2C_SLAVE, 0x6B) < 0) {
		fprintf(stderr,
			"Error: Could not select device, %s\n",
			strerror(errno));
		exit(1);
	}

	uint8_t data[100];
	int result = i2c_smbus_read_i2c_block_data(file, 22, 1, data);
	printf("Result: %d\n", result);

	return 0;
*/

	tI2CTinker i2c(tI2CTinker::eI2CBus::One);
	if (i2c.IsValid())
	{
		LSM6DS3Sensor sensor(&i2c);
		if (sensor.IsValid())
		{
			uint8_t id;
			sensor.ReadID(&id);
			printf("Sensor ID: %d\n", id);
			printf("Enable: %d\n", sensor.Enable_X());
			float fs;
			printf("Get Full Scale: %d, %f\n", sensor.Get_X_FS(&fs), fs);
			printf("Set Full Scale: %d\n", sensor.Set_X_FS(16.0F));
			printf("Get Full Scale: %d, %f\n", sensor.Get_X_FS(&fs), fs);


			int i = 0;
			while (i++ < 5)
			{
				int32_t accAxis[3];
				printf("Get_X_Axes(): %d\n", sensor.Get_X_Axes(accAxis));
				printf("%d\n", accAxis[0]);
				this_thread::sleep_for(chrono::milliseconds(1000));
			}
		}
		else
		{
			printf("Sensor failed to initialise\n");
		}
	}

	return 0;
}
