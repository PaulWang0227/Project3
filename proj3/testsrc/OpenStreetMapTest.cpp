#include <gtest/gtest.h>
#include "OpenStreetMap.h"
#include "StringDataSource.h"
#include "XMLReader.h"

TEST(OpenStreetMap, SimpleExampleTest){
    auto InStream = std::make_shared<CStringDataSource>(
      "<?xml version='1.0' encoding='UTF-8'?>"
        "<osm version=\"0.6\" generator=\"osmconvert 0.8.5\">"
        "<node id=\"1\" lat=\"38.5178523\" lon=\"-121.7712408\"/>"
        "<node id=\"2\" lat=\"38.535052\" lon=\"-121.7408606\"/>"
        "</osm>");
    auto Reader = std::make_shared<XMLReader>(InStream);
    COpenStreetMap StreetMap(Reader);
}