#include "setstr.h"
#include <iostream>
#include "gtest/gtest.h"

class SetStrTest : public testing::Test {
protected:
	// You can remove any or all of the following functions if its body is empty.

	SetStrTest() {
		// You can do set-up work for each test here.
	}

	virtual ~SetStrTest() {
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
    SetStr set;
};

TEST_F(SetStrTest, empty)
{
    EXPECT_TRUE(set.empty());
    set.insert("one");
    EXPECT_FALSE(set.empty());
}

TEST_F(SetStrTest, insert)
{
    set.insert("one");
    set.insert("hi");
    EXPECT_TRUE(set.exists("hi"));
    EXPECT_EQ(2, set.size());
    set.insert("hi");
    EXPECT_EQ(2, set.size());
    set.insert("bye");
    EXPECT_TRUE(set.exists("bye"));
    EXPECT_EQ(3, set.size());
}

TEST_F(SetStrTest, exists)
{
    set.insert("hi");
    EXPECT_TRUE(set.exists("hi"));
    EXPECT_FALSE(set.exists("potatoe"));
}

TEST_F(SetStrTest, firstandnext)
{
    EXPECT_TRUE(set.empty());
    set.insert("one");
    set.insert("hi");
    EXPECT_TRUE(set.exists("hi"));
    set.insert("hi");
    EXPECT_EQ(2, set.size());
    set.insert("bye");
    EXPECT_EQ("one", *set.next());
    EXPECT_EQ("hi", *set.next());
    EXPECT_EQ("bye", *set.next());
    EXPECT_EQ(NULL, set.next());
    SetStr set2;
    EXPECT_EQ(NULL, set2.first());
}

TEST_F(SetStrTest, remove)
{
    set.insert("one");
    set.insert("hi");
    set.insert("bye");
    set.remove("potatoe");
    EXPECT_EQ(3, set.size());
    set.remove("hi");
    EXPECT_EQ(2, set.size());
    set.remove("one");
    set.remove("bye");
    EXPECT_TRUE(set.empty());
    EXPECT_EQ(0, set.size());
}

TEST_F(SetStrTest, setunion)
{
    set.insert("one");
    set.insert("two");
    set.insert("three");
    SetStr set2;
    set2.insert("one");
    set2.insert("ten");
    set2.insert("thirty");
    set2.insert("three");
    SetStr set3 = set&set2;
    EXPECT_TRUE(set3.exists("one"));
    EXPECT_TRUE(set3.exists("two"));
    EXPECT_TRUE(set3.exists("three"));
    EXPECT_TRUE(set3.exists("ten"));
    EXPECT_TRUE(set3.exists("thirty"));
    EXPECT_EQ(5, set3.size());
}

TEST_F(SetStrTest, setintersect)
{
    set.insert("one");
    set.insert("two");
    set.insert("three");
    SetStr set2;
    set2.insert("one");
    set2.insert("ten");
    set2.insert("thirty");
    set2.insert("three");
    SetStr set3 = set|set2;
    EXPECT_TRUE(set3.exists("one"));
    EXPECT_FALSE(set3.exists("two"));
    EXPECT_TRUE(set3.exists("three"));
    EXPECT_FALSE(set3.exists("ten"));
    EXPECT_FALSE(set3.exists("thirty"));
    EXPECT_EQ(2, set3.size());
}
