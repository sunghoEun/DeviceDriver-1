#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../Project0707//DeviceDriver.cpp"

using namespace std;
using namespace testing;

class FlashMemoryDeviceMock : public FlashMemoryDevice {
public:
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, unsigned char data), (override));
};

TEST(TestDeviceDriver, ReadException) {
	FlashMemoryDeviceMock mockhardware{};

	EXPECT_CALL(mockhardware, read(_))
		.Times(AtMost(5))
		.WillOnce(Return(1))
		.WillRepeatedly(Return(0));

	DeviceDriver dd{ &mockhardware };
	EXPECT_THROW(dd.read(0), ReadFailException);
}
TEST(TestDeviceDriver, TestRead5repeat) {

	FlashMemoryDeviceMock mockhardware;
	DeviceDriver dd(&mockhardware);

	EXPECT_CALL(mockhardware, read(0))
		.Times(5);

	dd.read(0);
}

TEST(TestDeviceDriver, TestReadValue) {

	FlashMemoryDeviceMock mockhardware;
	DeviceDriver dd(&mockhardware);

	EXPECT_CALL(mockhardware, read(0))
		.Times(5)
		.WillRepeatedly(Return(1));

	int ret = dd.read(0);

	EXPECT_EQ(1, ret);
}