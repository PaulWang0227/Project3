#include <gtest/gtest.h>
#include "StringDataSource.h"
#include "StringDataSink.h"
#include "DSVReader.h"
#include "DSVWriter.h"

TEST(DSVTest,DSVReader){
    auto Source = std::make_shared<CStringDataSource>("Hello&World!");
    CDSVReader Reader(Source,'&');
    std::vector<std::string> output;

    EXPECT_TRUE(Reader.ReadRow(output));
    ASSERT_EQ(output.size(),2);
    EXPECT_EQ(output[0],"Hello");
    EXPECT_EQ(output[1],"World!");
}
TEST(DSVTest, DSVReader_EmptySource) {
    auto Source = std::make_shared<CStringDataSource>("");
    CDSVReader Reader(Source, '&');
    std::vector<std::string> output;

    EXPECT_FALSE(Reader.ReadRow(output));
    EXPECT_TRUE(output.empty());
}
TEST(DSVTest, DSVReader_OnlyDelimiters) {
    auto Source = std::make_shared<CStringDataSource>("&&&");
    CDSVReader Reader(Source, '&');
    std::vector<std::string> output;

    EXPECT_TRUE(Reader.ReadRow(output));
    ASSERT_EQ(output.size(), 4);
    EXPECT_TRUE(std::all_of(output.begin(), output.end(), [](const std::string& s) { return s.empty(); }));
}

TEST(DSVTest, NoDelimiters) {
    auto Source = std::make_shared<CStringDataSource>("SingleValue");
    CDSVReader Reader(Source,'&');
    std::vector<std::string> output;

    EXPECT_TRUE(Reader.ReadRow(output));
    ASSERT_EQ(output.size(), 1);
    EXPECT_EQ(output[0], "SingleValue");
}

TEST(DSVTest,DSVWriter){
    auto Sink = std::make_shared<CStringDataSink>();
    CDSVWriter Writer(Sink,'&');
    std::vector<std::string> input = {"Hello", "World!"};

    EXPECT_TRUE(Writer.WriteRow(input));
    EXPECT_EQ(Sink->String(),"Hello&World!");
}
TEST(DSVTest, DSVWriter_EmptyRow) {
    auto Sink = std::make_shared<CStringDataSink>();
    CDSVWriter Writer(Sink, '&');
    std::vector<std::string> input;

    EXPECT_FALSE(Writer.WriteRow(input));
    EXPECT_EQ(Sink->String(), "");
}

