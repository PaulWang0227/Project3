Overview
COpenStreetMap provides functionality for parsing and interacting with OpenStreetMap (OSM) data. It extends CStreetMap, focusing on handling OSM-specific elements like nodes and ways from XML data sources.

Constructor
COpenStreetMap(std::shared_ptr<CXMLReader> src): Initializes the map with an XML reader for OSM data.
Destructor
~COpenStreetMap(): Cleans up resources.
Methods
std::size_t NodeCount() const noexcept: Returns the count of nodes.
std::size_t WayCount() const noexcept: Returns the count of ways.
std::shared_ptr<CStreetMap::SNode> NodeByIndex(std::size_t index) const noexcept: Retrieves a node by index.
std::shared_ptr<CStreetMap::SNode> NodeByID(TNodeID id) const noexcept: Retrieves a node by ID.
std::shared_ptr<CStreetMap::SWay> WayByIndex(std::size_t index) const noexcept: Retrieves a way by index.
std::shared_ptr<CStreetMap::SWay> WayByID(TWayID id) const noexcept: Retrieves a way by ID.

Sample Usage:
#include "OpenStreetMap.h"
#include "XMLReader.h"
#include "StringDataSource.h"

int main() {
    auto xmlSource = std::make_shared<CStringDataSource>("<osm>...</osm>");
    auto reader = std::make_shared<CXMLReader>(xmlSource);
    COpenStreetMap osmMap(reader);

    // Example: Accessing node count
    std::cout << "Node Count: " << osmMap.NodeCount() << std::endl;

    return 0;
}
This class simplifies accessing OSM data, allowing for efficient queries and data manipulation.