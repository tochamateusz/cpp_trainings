#include <gtest/gtest.h>

namespace {
int GetMeaningOfLife() { return 42; };
} // namespace
//
TEST(TestTopic, TrivialEquality) { EXPECT_EQ(GetMeaningOfLife(), 42); }
TEST(TestTopic, MoreEqualityTests) { ASSERT_EQ(GetMeaningOfLife(), 0) << "Oh"; }
