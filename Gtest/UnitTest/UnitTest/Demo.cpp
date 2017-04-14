#include <stdio.h>
#include <time.h>
#include <windows.h>
#include "gtest/gtest.h"
class UnitTest{
public:
	UnitTest(){
		printf("start\n");
		srand(time(0));
	}
	~UnitTest(){
		printf("close\n");
	}

public:
	int GetRand()
	{
		//return 4;
		return rand()%100;
	}
};

TEST(testClass,simpletest)
{
	UnitTest mytest;
	int iCount=115;
	while(iCount-->0)
	{
		int iResult=mytest.GetRand();
		//EXPECT_EQ(4,iResult);
		//EXPECT_EXIT(4,iResult);
		//ASSERT_EQ(4,iResult);
		//EXPECT_EQ(0,iResult);
		EXPECT_TRUE(iResult>0)<<"当前数值为："<<iResult<<std::endl;
	}
}