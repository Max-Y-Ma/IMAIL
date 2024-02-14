#include <gtest/gtest.h>

#include "thread_test.h"

TEST(ThreadPool, ThreadPool) {
    thread_pool_test();
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS();
}