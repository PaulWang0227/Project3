#include <gtest/gtest.h>
#include "StringUtils.h"

TEST(StringUtilsTest, SliceTest){
    std::string Base="Test";
    EXPECT_EQ(StringUtils::Slice(Base,0),"Test");
    EXPECT_EQ(StringUtils::Slice(Base,1),"est");
}

TEST(StringUtilsTest, Capitalize){
    EXPECT_EQ(StringUtils::Capitalize(""), "");
    EXPECT_EQ(StringUtils::Capitalize("test"), "Test");
    EXPECT_EQ(StringUtils::Capitalize("TEST"), "Test");
    EXPECT_EQ(StringUtils::Capitalize("1Test"), "1test");
    EXPECT_EQ(StringUtils::Capitalize("!Test"), "!test");
    EXPECT_EQ(StringUtils::Capitalize("Test String"), "Test string");
}

TEST(StringUtilsTest, Upper){
    EXPECT_EQ(StringUtils::Upper(""), "");
    EXPECT_EQ(StringUtils::Upper("Test"), "TEST");
    EXPECT_EQ(StringUtils::Upper("TEST"), "TEST");
    EXPECT_EQ(StringUtils::Upper("Test String"), "TEST STRING");
    EXPECT_EQ(StringUtils::Upper("1test!"), "1TEST!");
}

TEST(StringUtilsTest, Lower){
    EXPECT_EQ(StringUtils::Lower(""), "");
    EXPECT_EQ(StringUtils::Lower("TEST"), "test");
    EXPECT_EQ(StringUtils::Lower("test"), "test");
    EXPECT_EQ(StringUtils::Lower("Test String"), "test string");
    EXPECT_EQ(StringUtils::Lower("1TEST!"), "1test!");
}

TEST(StringUtilsTest, LStrip){
    EXPECT_EQ(StringUtils::LStrip(""), "");
    EXPECT_EQ(StringUtils::LStrip("no_space"), "no_space");
    EXPECT_EQ(StringUtils::LStrip("   left"), "left");
    EXPECT_EQ(StringUtils::LStrip("   both sides    "), "both sides    ");
}

TEST(StringUtilsTest, RStrip){
    EXPECT_EQ(StringUtils::RStrip(""), "");
    EXPECT_EQ(StringUtils::LStrip("no_space"), "no_space");
    EXPECT_EQ(StringUtils::RStrip("right   "), "right");
    EXPECT_EQ(StringUtils::RStrip("    both sides  "), "    both sides");
}

TEST(StringUtilsTest, Strip){
    EXPECT_EQ(StringUtils::Strip(""), "");
    EXPECT_EQ(StringUtils::Strip("   left"), "left");
    EXPECT_EQ(StringUtils::Strip("right   "), "right");
    EXPECT_EQ(StringUtils::Strip("    both sides  "), "both sides");
    EXPECT_EQ(StringUtils::Strip("    "), "");
    
}

TEST(StringUtilsTest, Center){
    EXPECT_EQ(StringUtils::Center("test", 10), "   test   ");
    EXPECT_EQ(StringUtils::Center("test", 9), "  test   ");
    EXPECT_EQ(StringUtils::Center("test", 4), "test");
    EXPECT_EQ(StringUtils::Center("test", 3), "test"); 
    
}

TEST(StringUtilsTest, LJust){
    EXPECT_EQ(StringUtils::LJust("test", 10), "test      ");
    EXPECT_EQ(StringUtils::LJust("test", 4), "test");
    EXPECT_EQ(StringUtils::LJust("test", 3), "test");
}

TEST(StringUtilsTest, RJust){
    EXPECT_EQ(StringUtils::RJust("test", 10), "      test");
    EXPECT_EQ(StringUtils::RJust("test", 4), "test");
    EXPECT_EQ(StringUtils::RJust("test", 3), "test");
}

TEST(StringUtilsTest, Replace){
    EXPECT_EQ(StringUtils::Replace("hello world", "world", "there"), "hello there");
    EXPECT_EQ(StringUtils::Replace("hello world", "planet", "there"), "hello world");
    EXPECT_EQ(StringUtils::Replace("hello world", "world", ""), "hello ");
    EXPECT_EQ(StringUtils::Replace("hello world world", "world", "there"), "hello there there");
}

TEST(StringUtilsTest, Split){
    EXPECT_EQ(StringUtils::Split("a,b,c", ","), std::vector<std::string>({"a", "b", "c"}));
    EXPECT_EQ(StringUtils::Split("a b c"), std::vector<std::string>({"a", "b", "c"}));
    EXPECT_EQ(StringUtils::Split("a->b->c", "->"), std::vector<std::string>({"a", "b", "c"}));
    EXPECT_EQ(StringUtils::Split("hello world"), std::vector<std::string>({"hello", "world"}));
}

TEST(StringUtilsTest, Join){
    EXPECT_EQ(StringUtils::Join("1", {"one", "two", "three"}), "1onetwothree");
    EXPECT_EQ(StringUtils::Join("", {"one", "two", "three"}), "onetwothree");
    EXPECT_EQ(StringUtils::Join("1", {}), "1");
}

TEST(StringUtilsTest, ExpandTabs){
    
}

TEST(StringUtilsTest, EditDistance){
    
}