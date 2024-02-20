#include "CSVBusSystem.h"
<<<<<<< HEAD
#include <vector>
#include <unordered_map>

// Implementation structure defined within CCSVBusSystem to encapsulate details
struct CCSVBusSystem::SImplementation {

    struct SStop : public CCSVBusSystem::SStop{
        
        SStop(){

        }

        ~SStop(){

        }

        TStopID SID;
        CStreetMap::TNodeID NID;

        TStopID ID() const noexcept override {
            return SID;
        }
        
        CStreetMap::TNodeID NodeID() const noexcept override{
            return NID;
        }
    };

    struct SRoute : public CCSVBusSystem::SRoute{

        SRoute(){

        }

        ~SRoute(){

        }

        std::string RName;
        std::vector<TStopID> StopIDs;

        std::string Name() const noexcept override{
            return RName;
        }

        std::size_t StopCount() const noexcept {
            return StopIDs.size();
        }

        TStopID GetStopID(std::size_t index) const noexcept {
            if (index < StopIDs.size()) {
                return StopIDs[index];
            }
            return CBusSystem::InvalidStopID;
        }
    };

    // Maps and vectors to store stops and routes
    std::unordered_map<TStopID, std::shared_ptr<SStop>> StopsByID;
    std::vector<std::shared_ptr<SStop>> StopsByIndex;
    std::unordered_map<std::string, std::shared_ptr<SRoute>> RoutesByName;
    std::vector<std::shared_ptr<SRoute>> RoutesByIndex;

    // Constructor: Parses the CSV data for stops and routes
    SImplementation(std::shared_ptr<CDSVReader> stopsrc, std::shared_ptr<CDSVReader> routesrc) {
        // Parsing logic would go here
    }

    // Returns the number of stops in the system
    std::size_t StopCount() const noexcept{
        return StopsByIndex.size();
    }

    std::size_t RouteCount() const noexcept{
        return RoutesByIndex.size();
    }

    std::shared_ptr<SStop> StopByIndex(std::size_t index) const noexcept{
        if(index < StopsByIndex.size()){
            return StopsByIndex[index];
        }
        return nullptr;
    }

    std::shared_ptr<SStop> StopByID(TStopID id) const noexcept{
        auto Search = StopsByID.find(id);
        if(StopsByID.end() != Search){
            return Search->second;
        }
        return nullptr;
    }

    std::shared_ptr<SRoute> RouteByIndex(std::size_t index) const noexcept{
        if(index < RoutesByIndex.size()){
            return RoutesByIndex[index];
        }
        return nullptr;
    }

    std::shared_ptr<SRoute> RouteByName(const std::string &name) const noexcept{
        auto Search = RoutesByName.find(name);
        if(RoutesByName.end() != Search){
            return Search->second;
        }
        return nullptr;
    }
};

// Constructor for the CCSVBusSystem
CCSVBusSystem::CCSVBusSystem(std::shared_ptr<CDSVReader> stopsrc, std::shared_ptr<CDSVReader> routesrc)
: DImplementation(std::make_unique<SImplementation>(stopsrc, routesrc)) {}

// Destructor
CCSVBusSystem::~CCSVBusSystem(){};

// Returns the number of stops in the system
std::size_t CCSVBusSystem::StopCount() const noexcept {
    return DImplementation->StopsByIndex.size();
}

// Returns the number of routes in the system
std::size_t CCSVBusSystem::RouteCount() const noexcept {
    return DImplementation->RoutesByIndex.size();
}

// Returns the stop specified by the index
std::shared_ptr<CBusSystem::SStop> CCSVBusSystem::StopByIndex(std::size_t index) const noexcept {
    if (index < DImplementation->StopsByIndex.size()) {
        return DImplementation->StopsByIndex[index];
    }
    return nullptr;
}

// Returns the stop specified by the stop id
std::shared_ptr<CBusSystem::SStop> CCSVBusSystem::StopByID(TStopID id) const noexcept {
    auto it = DImplementation->StopsByID.find(id);
    if (it != DImplementation->StopsByID.end()) {
        return it->second;
    }
    return nullptr;
}

// Returns the route specified by the index
std::shared_ptr<CBusSystem::SRoute> CCSVBusSystem::RouteByIndex(std::size_t index) const noexcept {
    if (index < DImplementation->RoutesByIndex.size()) {
        return DImplementation->RoutesByIndex[index];
    }
    return nullptr;
}

// Returns the route specified by the name
std::shared_ptr<CBusSystem::SRoute> CCSVBusSystem::RouteByName(const std::string &name) const noexcept {
    auto it = DImplementation->RoutesByName.find(name);
    if (it != DImplementation->RoutesByName.end()) {
        return it->second;
    }
    return nullptr;
}
=======
>>>>>>> f8e65107f8f424e20c27e7ab48be824d0add1ff3
