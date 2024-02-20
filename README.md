# Project3

Student 1: Paul Wang (921248970)

Student 2: William Yu (921166191)

## Project Status
This the current status of the project is finished! The core functionalities of parsing bus route information and Open Street Map (OSM) have been implemented and tested. 
## Known Issues:
The project has no known issues based on testing.
## Code References:
Stacksoverflow:https://git-scm.com/book/en/v2/Git-Tools-Stashing-and-Cleaning
Discussion notes

## Generative AI Use
we used ChatGPT to help us create tests for our CCSVBusSystem and OpenStreetMap files.

### Prompt 1
How can I create some tests to test CCSVBusSystem and OpenStreetMap

### Response 1

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