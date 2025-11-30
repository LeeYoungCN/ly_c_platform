#include <cstdint>
#include <cstdio>

#include "common/stl/stl_string.h"
#include "gtest/gtest.h"

using namespace std;

namespace {
const uint32_t EXPECT_BUFFER_LEN = 256;
}

class Test_StlString : public testing::Test {
protected:
    static void SetUpTestSuite() {}
    static void TearDownTestSuite() {}
    void SetUp() override;
    void TearDown() override;
    Stl_String *m_string;
    char expectBuffer[EXPECT_BUFFER_LEN] = "\0";
};

void Test_StlString::SetUp() {}

void Test_StlString::TearDown()
{
    StlString_Delete(m_string);
}

TEST_F(Test_StlString, OnlyFormat)
{
    const char *testStr = "test string";
    m_string = StlString_New(testStr);
    ASSERT_NE(m_string, nullptr);
    ASSERT_NE(StlString_CStr(m_string), nullptr);
    EXPECT_STREQ(StlString_CStr(m_string), testStr);
    EXPECT_EQ(StlString_Length(m_string), strlen(testStr));
}

TEST_F(Test_StlString, FormatAndParams)
{
    const char *testFormat = "%s,%d";
    sprintf(expectBuffer, testFormat, "Hello world", 20);

    m_string = StlString_New(testFormat, "Hello world", 20);
    ASSERT_NE(m_string, nullptr);
    ASSERT_NE(StlString_CStr(m_string), nullptr);
    EXPECT_STREQ(StlString_CStr(m_string), expectBuffer);
    EXPECT_EQ(StlString_Length(m_string), strlen(expectBuffer));
}

TEST_F(Test_StlString, FormatNULL)
{
    m_string = StlString_New(nullptr);
    EXPECT_EQ(m_string, nullptr);
}

TEST_F(Test_StlString, EmptyFormat)
{
    m_string = StlString_New("");
    EXPECT_NE(m_string, nullptr);
    EXPECT_EQ(StlString_Length(m_string), 0);
}

TEST_F(Test_StlString, LongString)
{
    m_string = StlString_New("");
    EXPECT_NE(m_string, nullptr);
    EXPECT_EQ(StlString_Length(m_string), 0);
    uint32_t testLen = 1024;
    for (uint32_t i = 0; i < testLen; i++) {
        StlString_Append(m_string, "%u", 0);
        EXPECT_EQ(StlString_Length(m_string), i + 1);
    }
}