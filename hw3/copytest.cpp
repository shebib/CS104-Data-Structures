#include "lliststr.h"
#include "gtest/gtest.h"

class LListStrTest : public testing::Test {
protected:
	// You can remove any or all of the following functions if its body is empty.

	LListStrTest() {
		// You can do set-up work for each test here.
	}

	virtual ~LListStrTest() {
		// You can do clean-up work that doesn't throw exceptions here.		
	}

	// If the constructor and destructor are not enough for setting up
	// and cleaning up each test, you can define the following methods:
	virtual void SetUp() {
		// Code here will be called immediately after the constructor (right
		// before each test).
	}

	virtual void TearDown() {

		// Code here will be called immediately after each test (right
		// before the destructor).
	}

	// Objects declared here can be used by all tests in the test case.
LListStr list;
};

TEST_F(LListStrTest, CopyConstructor)
{
    list.insert(0, "hi"); 
    list.insert(1, "one");
    list.insert(2, "two");
    LListStr list2(list);
    EXPECT_EQ("hi", list2.get(0));
    EXPECT_EQ("one", list2.get(1));
    EXPECT_EQ("two", list2.get(2));
}

TEST_F(LListStrTest, pushback)
{
    list.insert(0, "hi");
    list.push_back("end");
    EXPECT_EQ("end", list.get(1));
}

TEST_F(LListStrTest, assignmentOp)
{
    list.insert(0, "hi"); 
    list.insert(1, "one");
    list.insert(2, "two");
    LListStr list2; 
    list2 = list;
    EXPECT_EQ("hi", list2.get(0));
    EXPECT_EQ("one", list2.get(1));
    EXPECT_EQ("two", list2.get(2));
}
