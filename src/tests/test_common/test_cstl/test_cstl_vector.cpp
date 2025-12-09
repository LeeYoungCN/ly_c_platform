#include <cstdint>

#include "common/types/error_code.h"
#include "cstl/cstl_vector.h"
#include "gtest/gtest.h"

using namespace std;

class Test_StlVector : public testing::Test {
protected:
    static void SetUpTestSuite() {}
    static void TearDownTestSuite() {}
    void SetUp() override;
    void TearDown() override;
    CStlVector *m_vector;
    uint32_t elemSize = sizeof(uint64_t);
};

void Test_StlVector::SetUp() {}

void Test_StlVector::TearDown()
{
    CStlVector_Delete(m_vector);
    m_vector = nullptr;
}

TEST_F(Test_StlVector, NewVector)
{
    m_vector = CStlVector_New(elemSize);
    ASSERT_NE(m_vector, nullptr);
    EXPECT_EQ(CStlVector_Length(m_vector), 0);
    EXPECT_GT(CStlVector_Capacity(m_vector), 0);
}

TEST_F(Test_StlVector, NewVectorBySize)
{
    m_vector = CStlVector_NewByCapacity(elemSize, 100);
    ASSERT_NE(m_vector, nullptr);
    EXPECT_EQ(CStlVector_Length(m_vector), 0);
    EXPECT_EQ(CStlVector_Capacity(m_vector), 100);
}

TEST_F(Test_StlVector, PushAndPop)
{
    const uint64_t maxNum = 1024;
    m_vector = CStlVector_New(elemSize);
    ASSERT_NE(m_vector, nullptr);
    EXPECT_EQ(CStlVector_Length(m_vector), 0);
    for (uint64_t i = 1; i <= maxNum; i++) {
        EXPECT_EQ(CStlVector_Push(m_vector, &i), ERR_COMM_SUCCESS);
        EXPECT_EQ(CStlVector_Length(m_vector), i);
    }
    for (uint64_t i = maxNum; CStlVector_Length(m_vector) > 0 && i > 0; i--) {
        uint64_t n = 0;
        EXPECT_EQ(CStlVector_Pop(m_vector, &n), ERR_COMM_SUCCESS);
        EXPECT_EQ(n, i);
    }
}

TEST_F(Test_StlVector, GetValue)
{
    const uint64_t maxNum = 1024;
    m_vector = CStlVector_New(elemSize);
    ASSERT_NE(m_vector, nullptr);
    EXPECT_EQ(CStlVector_Length(m_vector), 0);
    for (uint64_t i = 0; i < maxNum; i++) {
        EXPECT_EQ(CStlVector_Push(m_vector, &i), ERR_COMM_SUCCESS);
        EXPECT_EQ(CStlVector_Length(m_vector), i + 1);
    }

    for (uint32_t i = 0; i < CStlVector_Length(m_vector); i++) {
        uint64_t val = 0;
        EXPECT_EQ(CStlVector_GetElem(m_vector, i, &val), ERR_COMM_SUCCESS);
        EXPECT_EQ(val, i);
    }
}

TEST_F(Test_StlVector, SetValue)
{
    const uint64_t maxNum = 1024;
    m_vector = CStlVector_New(elemSize);
    ASSERT_NE(m_vector, nullptr);
    EXPECT_EQ(CStlVector_Length(m_vector), 0);
    for (uint64_t i = 0; i < maxNum; i++) {
        EXPECT_EQ(CStlVector_Push(m_vector, &i), ERR_COMM_SUCCESS);
        EXPECT_EQ(CStlVector_Length(m_vector), i + 1);
    }

    for (uint32_t i = 0; i < CStlVector_Length(m_vector); i++) {
        uint64_t newVal = maxNum + i;
        uint64_t oldVal = 0;

        EXPECT_EQ(CStlVector_SetElem(m_vector, i, &newVal, &oldVal), ERR_COMM_SUCCESS);
        EXPECT_EQ(oldVal, i);

        uint64_t getVal = 0;
        EXPECT_EQ(CStlVector_GetElem(m_vector, i, &getVal), ERR_COMM_SUCCESS);
        EXPECT_EQ(getVal, newVal);
    }
}
