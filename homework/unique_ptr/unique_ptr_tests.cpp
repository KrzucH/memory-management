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

template class my::unique_ptr<uniqAddTest>;

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

TEST(uniqAddTest, MoveTestV1) {
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

    uniq.reset();

    EXPECT_EQ(uniq.get(), nullptr);
}

TEST(uniqAddTest, ReleaseTest) {
    my::unique_ptr<uniqAddTest> uniq = new uniqAddTest(100, 100);

    my::unique_ptr<uniqAddTest> uniq2 = uniq.release();

    EXPECT_EQ(uniq.get(), nullptr);
}

TEST(uniqAddTest, MoveTestV2) {
    my::unique_ptr<uniqAddTest> uniq = new uniqAddTest(50, 50);

    auto newPtr = std::move(uniq);

    EXPECT_NE(newPtr.get(), nullptr);
}

TEST(uniqAddTest, ValueTest) {
    my::unique_ptr<uniqAddTest> uniq = new uniqAddTest(100, 200);
    auto value = uniq->checkAddTest();
    auto result = 300;

    EXPECT_EQ(value, result);
}

TEST(uniqAddTest, ValueTestV2) {
    my::unique_ptr<uniqAddTest> uniq = new uniqAddTest(50, 70);
    auto result = 120;
    my::unique_ptr<uniqAddTest> uniq1 = std::move(uniq);
    auto uniq2 = std::move(uniq1);

    EXPECT_EQ(uniq2->checkAddTest(), result);
    EXPECT_EQ(uniq.get(), nullptr);
    EXPECT_EQ(uniq1.get(), nullptr);
    EXPECT_NE(uniq2.get(), nullptr);
}

TEST(uniqAddTest, ResetValueTest) {
    my::unique_ptr<uniqAddTest> uniq = new uniqAddTest(10, 20);
    uniq.reset(new uniqAddTest(30, 20));
    auto result = 50;

    EXPECT_EQ(uniq->checkAddTest(), result);
}

TEST(uniqAddTest, DefaultCtrTest) {
    my::unique_ptr<uniqAddTest> uniq;

    EXPECT_EQ(uniq.get(), nullptr);
}

TEST(uniqAddTest, NotEqualTest) {
    my::unique_ptr<uniqAddTest> uniq = new uniqAddTest(10, 10);
    my::unique_ptr<uniqAddTest> uniq1 = std::move(uniq);

    EXPECT_NE(uniq1.get(), nullptr);
}

TEST(uniqAddTest, ReleaseTestV2) {
    my::unique_ptr<uniqAddTest> uniq = new uniqAddTest(10, 20);
    auto uniq2 = uniq.release();
    auto result = 30;

    EXPECT_EQ(uniq2->checkAddTest(), result);
}

TEST(uniqAddTest, ResetTestV2) {
    my::unique_ptr<uniqAddTest> uniq = new uniqAddTest(20, 50);

    auto result = 100;

    uniq.reset(new uniqAddTest(50, 50));

    ASSERT_EQ(uniq->checkAddTest(), result);
}