#include "common/debug/working_env.h"
#include "gtest/gtest.h"
#include "logging/logging.h"

int main(int argc, char *argv[])
{
    ShowWorkingEnv();
    Logging_SetAllowedLevel(LOG_DEBUG);
    Logging_Init();
    LOG(LOG_INFO, "Running main() from: %s.\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
