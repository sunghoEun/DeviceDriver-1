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

class DeviceDriverFixture : public Test
{
public:
	void SetUp() override
	{
		dd = new DeviceDriver(&mockhardware);
	}
	void TearDown() override
	{
		delete dd;
	}

	FlashMemoryDeviceMock mockhardware;
	DeviceDriver *dd;
};

TEST_F(DeviceDriverFixture, ReadException) {

	EXPECT_CALL(mockhardware, read(0))
		.Times(AtMost(5))
		.WillOnce(Return(1))
		.WillRepeatedly(Return(0));

	EXPECT_THROW(dd->read(0), ReadFailException);
}
TEST_F(DeviceDriverFixture, TestRead5repeat) {

	EXPECT_CALL(mockhardware, read(0))
		.Times(5);

	dd->read(0);
}

TEST_F(DeviceDriverFixture, TestReadValue) {

	EXPECT_CALL(mockhardware, read(0))
		.Times(5)
		.WillRepeatedly(Return(1));

	EXPECT_EQ(1, dd->read(0));
}

TEST_F(DeviceDriverFixture, TestWriteException) {
	EXPECT_CALL(mockhardware, read(0x8000))
		.WillRepeatedly(Return(0));

	EXPECT_THROW(dd->write(0x8000, 0x2), WriteFailException);
}

TEST_F(DeviceDriverFixture, TestWriteValue) {
	EXPECT_CALL(mockhardware, read(0x8000))
		.WillRepeatedly(Return(0xff));

	EXPECT_CALL(mockhardware, write(0x8000, 1))
		.Times(1);

	dd->write(0x8000, 1);
}
