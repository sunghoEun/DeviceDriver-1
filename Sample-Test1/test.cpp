#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../Project0707//cal.cpp"

using namespace std;
using namespace testing;

class DBMock : public DBAPI {
public:
	MOCK_METHOD(string, getDBName, (), (override));
};

TEST(TestCaseName, TestName) {
	//Mock을 사용하지 않고, LogSystem 사용방법
	DBAPI* db = new DatabaseAPI();
	LogSystem app(db);
	cout << app.getLogMessage(); //DB 트래픽 발생!

	//Mock을 사용한 LogSystem 사용방법

	//DBMock mock;
	//EXPECT_CALL(mock, getDBName())
	//	.WillRepeatedly(Return(string("K~F~C")));
	//LogSystem app2(&mock);

	DBMock* mock = new DBMock();
	EXPECT_CALL(*mock, getDBName())
		.WillRepeatedly(Return(string("K~F~C")));
	LogSystem app2(mock);


	cout << app2.getLogMessage(); //DB 트래픽 발생 안함.
}
