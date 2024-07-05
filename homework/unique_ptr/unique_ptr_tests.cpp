#include <gtest/gtest.h>
#include <memory>
#include "unique_ptr.hpp"

struct uniqAddTest {
    uniqAddTest(int value1, int value2)
        : value1_(value1),
          value2_(value2) {}
    int checkAddTest() {
        return value1_ + value2_;
    }

private:
    int value1_{};
    int value2_{};
};

TEST(uniqAddTest, ArrowTest) {
    my::unique_ptr<uniqAddTest> uniq = new uniqAddTest(20, 30);
    auto result = 50;

    EXPECT_EQ(uniq->checkAddTest(), result);
}

TEST(int, DereferenceTest) {
    my::unique_ptr<int> uniq = new int(100);
    auto result = 100;

    EXPECT_EQ(*uniq, result);
}

TEST(uniqIntTest, MoveTest) {
    my::unique_ptr<uniqAddTest> uniq = new uniqAddTest(100, 100);
    auto uniq1{std::move(uniq)};

    EXPECT_EQ(uniq.get(), nullptr);

    my::unique_ptr<uniqAddTest> uniq2{};

    EXPECT_EQ(uniq2.get(), nullptr);

    auto uniq3 = std::move(uniq1);

    EXPECT_EQ(uniq1.get(), nullptr);
}

TEST(int, ResetTest) {
    my::unique_ptr<int> uniq = new int(8);
    constexpr int newValue = 6;

    uniq.reset(new int(newValue));

    ASSERT_EQ(*uniq, newValue);

    uniq.reset();

    EXPECT_EQ(uniq.get(), nullptr);
}

TEST(uniqAddTest, ReleaseTest) {
    my::unique_ptr<uniqAddTest> uniq = new uniqAddTest(100, 100);

    my::unique_ptr<uniqAddTest> uniq2 = uniq.release();

    EXPECT_EQ(uniq.get(), nullptr);
    EXPECT_NE(uniq2.get(), nullptr);
}
