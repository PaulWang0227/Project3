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