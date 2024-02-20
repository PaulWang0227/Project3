#include <gtest/gtest.h>
#include "CSVBusSystem.h"
#include "StringDataSource.h"
#include "DSVReader.h"
#include "BusSystem.h"

TEST(CSVBusSystem, SimpleExampleTest){
    auto InStreamStops = std::make_shared<CStringDataSource>("stop_id,node_id\n1,1001");
    auto InStreamRoutes = std::make_shared<CStringDataSource>("route,stop_id");
    auto CSVReaderStops = std::make_shared<CDSVReader>(InStreamStops,',');
    auto CSVReaderRoutes = std::make_shared<CDSVReader>(InStreamRoutes,',');
    CCSVBusSystem BusSystem(CSVReaderStops, CSVReaderRoutes);

    EXPECT_EQ(BusSystem.StopCount(),1);
    EXPECT_EQ(BusSystem.RouteCount(),0);
    EXPECT_EQ(BusSystem.StopByIndex(0)->ID(),1);
}
TEST(CSVBusSystem, StopByIDTest) {
    auto InStreamStops = std::make_shared<CStringDataSource>("stop_id,node_id\n1,1001\n2,1002");
    auto InStreamRoutes = std::make_shared<CStringDataSource>("route,stop_id\nRouteA,1\nRouteA,2");
    auto CSVReaderStops = std::make_shared<CDSVReader>(InStreamStops, ',');
    auto CSVReaderRoutes = std::make_shared<CDSVReader>(InStreamRoutes, ',');
    CCSVBusSystem BusSystem(CSVReaderStops, CSVReaderRoutes);

    auto stop = BusSystem.StopByID(1);
    EXPECT_NE(stop, nullptr);
    EXPECT_EQ(stop->ID(), 1);
    EXPECT_EQ(stop->NodeID(), 1001);
}
TEST(CSVBusSystem, RouteByIndexTest) {
    auto InStreamStops = std::make_shared<CStringDataSource>("stop_id,node_id\n1,1001\n2,1002");
    auto InStreamRoutes = std::make_shared<CStringDataSource>("route,stop_id\nRouteA,1\nRouteA,2");
    auto CSVReaderStops = std::make_shared<CDSVReader>(InStreamStops, ',');
    auto CSVReaderRoutes = std::make_shared<CDSVReader>(InStreamRoutes, ',');
    CCSVBusSystem BusSystem(CSVReaderStops, CSVReaderRoutes);

    auto route = BusSystem.RouteByIndex(0);
    EXPECT_NE(route, nullptr);
    EXPECT_EQ(route->Name(), "RouteA");
    EXPECT_EQ(route->StopCount(), 2);
}
TEST(CSVBusSystem, RouteByNameTest) {
    auto InStreamStops = std::make_shared<CStringDataSource>("stop_id,node_id\n1,1001\n2,1002");
    auto InStreamRoutes = std::make_shared<CStringDataSource>("route,stop_id\nRouteA,1\nRouteA,2");
    auto CSVReaderStops = std::make_shared<CDSVReader>(InStreamStops, ',');
    auto CSVReaderRoutes = std::make_shared<CDSVReader>(InStreamRoutes, ',');
    CCSVBusSystem BusSystem(CSVReaderStops, CSVReaderRoutes);

    auto route = BusSystem.RouteByName("RouteA");
    EXPECT_NE(route, nullptr);
    EXPECT_EQ(route->Name(), "RouteA");
    EXPECT_EQ(route->StopCount(), 2);
}
TEST(CSVBusSystem, EmptyDataSources) {
    auto InStreamStops = std::make_shared<CStringDataSource>("");
    auto InStreamRoutes = std::make_shared<CStringDataSource>("");
    auto CSVReaderStops = std::make_shared<CDSVReader>(InStreamStops, ',');
    auto CSVReaderRoutes = std::make_shared<CDSVReader>(InStreamRoutes, ',');
    CCSVBusSystem BusSystem(CSVReaderStops, CSVReaderRoutes);

    EXPECT_EQ(BusSystem.StopCount(), 0);
    EXPECT_EQ(BusSystem.RouteCount(), 0);
}
TEST(CSVBusSystem, IndexOutOfBounds) {
    auto InStreamStops = std::make_shared<CStringDataSource>("stop_id,node_id\n1,1001");
    auto InStreamRoutes = std::make_shared<CStringDataSource>("route,stop_id\nRouteA,1");
    auto CSVReaderStops = std::make_shared<CDSVReader>(InStreamStops, ',');
    auto CSVReaderRoutes = std::make_shared<CDSVReader>(InStreamRoutes, ',');
    CCSVBusSystem BusSystem(CSVReaderStops, CSVReaderRoutes);

    EXPECT_EQ(BusSystem.StopByIndex(1), nullptr); // Out of bounds
    EXPECT_EQ(BusSystem.RouteByIndex(1), nullptr); // Out of bounds
}
