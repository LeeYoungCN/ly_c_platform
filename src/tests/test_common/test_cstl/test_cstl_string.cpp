#include <cstdint>
#include <cstdio>

#include "common/common_error_code.h"
#include "common/cstl/cstl_string.h"
#include "common/types/error_code_types.h"
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
    CString *m_string;
    char expectBuffer[EXPECT_BUFFER_LEN] = "\0";
};

void Test_StlString::SetUp() {}

void Test_StlString::TearDown()
{
    CString_Delete(m_string);
    m_string = nullptr;
}

TEST_F(Test_StlString, OnlyFormat)
{
    const char *testStr = "test string";
    m_string = CString_New(testStr);
    ASSERT_NE(m_string, nullptr);
    ASSERT_NE(CString_CStr(m_string), nullptr);
    EXPECT_STREQ(CString_CStr(m_string), testStr);
    EXPECT_EQ(CString_Length(m_string), strlen(testStr));
    EXPECT_EQ(CString_GetLastError(m_string), ERR_COMM_SUCCESS);
}

TEST_F(Test_StlString, FormatAndParams)
{
    const char *testFormat = "%s,%d";
    sprintf(expectBuffer, testFormat, "Hello world", 20);

    m_string = CString_New(testFormat, "Hello world", 20);
    ASSERT_NE(m_string, nullptr);
    ASSERT_NE(CString_CStr(m_string), nullptr);
    EXPECT_STREQ(CString_CStr(m_string), expectBuffer);
    EXPECT_EQ(CString_Length(m_string), strlen(expectBuffer));
    EXPECT_EQ(CString_GetLastError(m_string), ERR_COMM_SUCCESS);
}

TEST_F(Test_StlString, FormatNULL)
{
    m_string = CString_New(nullptr);
    EXPECT_NE(m_string, nullptr);
    ASSERT_NE(CString_CStr(m_string), nullptr);
    EXPECT_STREQ(CString_CStr(m_string), "");
    EXPECT_EQ(CString_Length(m_string), 0);
    EXPECT_EQ(CString_GetLastError(m_string), ERR_COMM_SUCCESS);
}

TEST_F(Test_StlString, EmptyFormat)
{
    m_string = CString_New("");
    EXPECT_NE(m_string, nullptr);
    EXPECT_STREQ(CString_CStr(m_string), "");
    EXPECT_EQ(CString_Length(m_string), 0);
    EXPECT_EQ(CString_GetLastError(m_string), ERR_COMM_SUCCESS);
}

TEST_F(Test_StlString, StringCopy)
{
    const char *testFormat = "%s,%d";
    sprintf(expectBuffer, testFormat, "Hello world", 20);

    m_string = CString_New(testFormat, "Hello world", 20);
    ASSERT_NE(m_string, nullptr);
    ASSERT_NE(CString_CStr(m_string), nullptr);
    EXPECT_STREQ(CString_CStr(m_string), expectBuffer);
    EXPECT_EQ(CString_Length(m_string), strlen(expectBuffer));
    EXPECT_EQ(CString_GetLastError(m_string), ERR_COMM_SUCCESS);

    auto newStr = CString_Copy(m_string);
    ASSERT_NE(newStr, nullptr);
    ASSERT_NE(CString_CStr(newStr), nullptr);

    EXPECT_STREQ(CString_CStr(m_string), CString_CStr(newStr));
    EXPECT_EQ(CString_Length(m_string), CString_Length(m_string));
    EXPECT_EQ(CString_GetLastError(newStr), ERR_COMM_SUCCESS);
    CString_Delete(newStr);
}

TEST_F(Test_StlString, LongString)
{
    m_string = CString_New("");
    EXPECT_NE(m_string, nullptr);
    EXPECT_EQ(CString_Length(m_string), 0);
    uint32_t testLen = 1024;
    for (uint32_t i = 0; i < testLen; i++) {
        CString_Append(m_string, "%u", 0);
        EXPECT_EQ(CString_Length(m_string), i + 1);
        EXPECT_EQ(CString_GetLastError(m_string), ERR_COMM_SUCCESS);
    }
}

TEST_F(Test_StlString, NewWithSize)
{
    m_string = CString_NewBySize(1024, nullptr);
    EXPECT_EQ(CString_Length(m_string), 0);
    EXPECT_EQ(CString_Capacity(m_string), 1024);
    EXPECT_EQ(CString_GetLastError(m_string), ERR_COMM_SUCCESS);
}

TEST_F(Test_StlString, ResizeSuccess)
{
    m_string = CString_NewBySize(1024, nullptr);
    EXPECT_EQ(CString_Length(m_string), 0);
    EXPECT_EQ(CString_Capacity(m_string), 1024);
    EXPECT_EQ(CString_GetLastError(m_string), ERR_COMM_SUCCESS);
    for (uint32_t i = CString_Length(m_string) + 1; i <= CSTL_STRING_MAX_CAPACITY; i++) {
        CString_Resize(m_string, i);
        EXPECT_EQ(CString_GetLastError(m_string), ERR_COMM_SUCCESS);
        EXPECT_EQ(CString_Capacity(m_string), i);
    }
}

TEST_F(Test_StlString, ResizeInvalid)
{
    m_string = CString_NewBySize(1024, nullptr);
    EXPECT_EQ(CString_Length(m_string), 0);
    EXPECT_EQ(CString_Capacity(m_string), 1024);
    EXPECT_EQ(CString_GetLastError(m_string), ERR_COMM_SUCCESS);

    CString_Resize(m_string, CSTL_STRING_MAX_CAPACITY + 1);
    EXPECT_EQ(CString_GetLastError(m_string), ERR_COMM_PARAM_CAPACITY_INVALID);
    CString_Resize(m_string, 0);
    EXPECT_EQ(CString_GetLastError(m_string), ERR_COMM_PARAM_CAPACITY_INVALID);
    CString_Resize(m_string, CString_Length(m_string) - 1);
    EXPECT_EQ(CString_GetLastError(m_string), ERR_COMM_PARAM_CAPACITY_INVALID);

    ErrorCode errCode = CString_Resize(nullptr, 1);
    EXPECT_EQ(errCode, ERR_COMM_PARAM_NULL);
}
