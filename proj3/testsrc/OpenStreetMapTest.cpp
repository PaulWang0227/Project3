#include <gtest/gtest.h>
#include "OpenStreetMap.h"
#include "StreetMap.h"
#include "StringDataSource.h"
#include "XMLReader.h"
TEST(OpenStreetMap, SimpleExampleTest){
    auto InStream = std::make_shared<CStringDataSource>("<?xml version='1.0' encoding='UTF-8'?>"
                                                        "<osm version=\"0.6\" generator=\"osmconvert 0.8.5\">"
                                                        "<node id=\"1\" lat=\"1.0\" lon=\"-1.0\"/>"
                                                        "</osm>");
    auto Reader = std::make_shared<CXMLReader>(InStream);
    COpenStreetMap StreetMap(Reader);
    
    EXPECT_EQ(StreetMap.NodeCount(),1);
    EXPECT_EQ(StreetMap.WayCount(),0);
    EXPECT_EQ(StreetMap.NodeByIndex(0)->ID(),1);
}
TEST(OpenStreetMap, MultipleNodesTest) {
    auto InStream = std::make_shared<CStringDataSource>(
        "<?xml version='1.0' encoding='UTF-8'?>"
        "<osm>"
        "<node id=\"1\" lat=\"1.0\" lon=\"-1.0\"/>"
        "<node id=\"2\" lat=\"2.0\" lon=\"-2.0\"/>"
        "</osm>");
    auto Reader = std::make_shared<CXMLReader>(InStream);
    COpenStreetMap StreetMap(Reader);
    
    EXPECT_EQ(StreetMap.NodeCount(), 2);
    EXPECT_EQ(StreetMap.NodeByIndex(1)->ID(), 2);
}
TEST(OpenStreetMap, WayParsingTest) {
    auto InStream = std::make_shared<CStringDataSource>(
        "<?xml version='1.0' encoding='UTF-8'?>"
        "<osm>"
        "<node id=\"1\" lat=\"1.0\" lon=\"-1.0\"/>"
        "<node id=\"2\" lat=\"2.0\" lon=\"-2.0\"/>"
        "<way id=\"10\">"
        "<nd ref=\"1\"/>"
        "<nd ref=\"2\"/>"
        "</way>"
        "</osm>");
    auto Reader = std::make_shared<CXMLReader>(InStream);
    COpenStreetMap StreetMap(Reader);
    
    EXPECT_EQ(StreetMap.WayCount(), 1);
    auto way = StreetMap.WayByIndex(0);
    EXPECT_NE(way, nullptr);
    EXPECT_EQ(way->NodeCount(), 2);
    EXPECT_EQ(way->GetNodeID(0), 1);
    EXPECT_EQ(way->GetNodeID(1), 2);
}