#include "DeviceDriver.h"
#include <stdexcept>

using namespace std;

class ReadFailException : public std::exception
{
public:
	char const* what() const override
	{
		return "READ Fail";
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
    m_hardware->write(address, (unsigned char)data);
}
