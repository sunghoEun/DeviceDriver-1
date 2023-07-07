#include "DeviceDriver.h"
#include <stdexcept>

using namespace std;

class ReadFailException : public exception
{
public:
	char const* what() const override
	{
		return "READ Fail";
	}
};

class WriteFailException : public exception
{
public:
	char const* what() const override
	{
		return "WRITE Fail";
	}
};

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
    // TODO: implement this method properly
	unsigned char ret = m_hardware->read(address);

	for (int i = 0; i < 4; i++)
	{
		if (ret != m_hardware->read(address))
		{
			throw ReadFailException();
		}
	}
    return ret;
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
	unsigned char ret = m_hardware->read(address);
	if (ret != 0xff) throw WriteFailException();

    m_hardware->write(address, (unsigned char)data);
}
