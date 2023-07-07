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
	//Mock�� ������� �ʰ�, LogSystem �����
	DBAPI* db = new DatabaseAPI();
	LogSystem app(db);
	cout << app.getLogMessage(); //DB Ʈ���� �߻�!

	//Mock�� ����� LogSystem �����

	//DBMock mock;
	//EXPECT_CALL(mock, getDBName())
	//	.WillRepeatedly(Return(string("K~F~C")));
	//LogSystem app2(&mock);

	DBMock* mock = new DBMock();
	EXPECT_CALL(*mock, getDBName())
		.WillRepeatedly(Return(string("K~F~C")));
	LogSystem app2(mock);


	cout << app2.getLogMessage(); //DB Ʈ���� �߻� ����.
}
