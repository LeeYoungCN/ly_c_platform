#include "common/os/file_system.h"
#include <filesystem>
#include "gtest/gtest.h"

class Test_FileSystem : public testing::Test {
protected:
    static void SetUpTestSuite() {}
    static void TearDownTestSuite() {}
    void SetUp() override;
    void TearDown() override;
};

void Test_FileSystem::SetUp() {}

void Test_FileSystem::TearDown()
{
}

TEST_F(Test_FileSystem, FileName)
{
    auto expect = std::filesystem::path(__FILE__).filename().string();
    auto result = FS_GetFileName(__FILE__);
    EXPECT_STREQ(result, expect.c_str());
}
