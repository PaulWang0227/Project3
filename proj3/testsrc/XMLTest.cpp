#include <gtest/gtest.h>
#include "StringDataSource.h"
#include "StringDataSink.h"
#include "XMLReader.h"
#include "XMLWriter.h"

TEST(XMLTest, XMLWriter){
auto OutputStream = std::make_shared<CStringDataSink>();
CXMLWriter Writer(OutputStream);

EXPECT_TRUE(Writer.WriteEntity({SXMLEntity::EType::StartElement, "example", {{"attr","Hello World"}}}));
EXPECT_TRUE(Writer.WriteEntity({SXMLEntity::EType::EndElement, "example", {}}));

EXPECT_EQ(OutputStream->String(), "<example attr=\"Hello World\"></example>");

}
TEST(XMLTest, XMLWriter_Flush) {
    auto OutputStream = std::make_shared<CStringDataSink>();
    CXMLWriter Writer(OutputStream);

    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity::EType::StartElement, "example", {}}));
    // Do not manually close the "example" tag
    EXPECT_TRUE(Writer.Flush());  // This should close any open tags

    // The expected output should have the "example" tag closed
    EXPECT_EQ(OutputStream->String(), "<example></example>");
}
/*TEST(XMLTest, XMLReader_EmptyDocument) {
    auto InputStream = std::make_shared<CStringDataSource>("");
    CXMLReader Reader(InputStream);
    SXMLEntity E;

    EXPECT_FALSE(Reader.ReadEntity(E));
}*/
/*TEST(XMLTest, XMLReader){
auto InputStream = std::make_shared<CStringDataSource>("<example attr=\"Hello World\"></example>");
CXMLReader Reader(InputStream);
SXMLEntity E;

EXPECT_TRUE(Reader.ReadEntity(E));
EXPECT_EQ(E.DType, SXMLEntity::EType::StartElement);
EXPECT_EQ(E.AttributeValue("attr"), "Hello World");

EXPECT_TRUE(Reader.ReadEntity(E));
EXPECT_EQ(E.DType, SXMLEntity::EType::EndElement);
}*/