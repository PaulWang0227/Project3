#include "OpenStreetMap.h"
#include <unordered_map>
#include <vector>

struct COpenStreetMap::SImplementation{

    struct SNode : public CStreetMap::SNode{
        TNodeID DID;
        TLocation DLocation;
        std::unordered_map<std::string, std::string> DAttributes;
        std::vector<std::string> DAttributeKeys;

        SNode(){

        }

        ~SNode(){

        }

        TNodeID ID() const noexcept override{
            return DID;
        }

        TLocation Location() const noexcept override{
            return DLocation;
        }

        std::size_t AttributeCount() const noexcept override{
            return DAttributeKeys.size();
        }

        std::string GetAttributeKey(std::size_t index) const noexcept override{
            if(index <DAttributeKeys.size()){
                return DAttributeKeys[index];
            }
            return std::string();
        }

        bool HasAttribute(const std::string &key) const noexcept override{
            auto Search = DAttributes.find(key);
            return DAttributes.end() != Search;
        }

        std::string GetAttribute(const std::string &key) const noexcept override{
            auto Search = DAttributes.find(key);
            if(DAttributes.end() != Search){
                return Search->second;
            }
            return std::string();
        }

        void SetAttribute(const std::string &key, const std::string &value){
            DAttributeKeys.push_back(key);
            DAttributes[key] = value;
        }
    };

    struct SWay : public CStreetMap::SWay{

        TWayID WID;
        std::vector<TNodeID> NodeIDs;
        std::unordered_map<std::string, std::string> Attributes;
        std::vector<std::string> AttributeKeys;

        SWay(){

        }

        ~SWay(){

        }

        TWayID ID() const noexcept override{
            return WID;
        }

        std::size_t NodeCount() const noexcept override{
            return NodeIDs.size();
        }

        TNodeID GetNodeID(std::size_t index) const noexcept override{
            if(index < NodeIDs.size()){
                return NodeIDs[index];
            }
        }

        std::size_t AttributeCount() const noexcept override{
            return Attributes.size();
        }

        std::string GetAttributeKey(std::size_t index) const noexcept override{
            if(index < AttributeKeys.size()){
                return AttributeKeys[index];
            }
            return std::string();
        }

        bool HasAttribute(const std::string &key) const noexcept override{
            return Attributes.find(key) != Attributes.end();
        }

        std::string GetAttribute(const std::string &key) const noexcept override{
            auto it = Attributes.find(key);
            if (it != Attributes.end()) {
                return it->second;
            }
            return std::string();
        }
    };

    std::unordered_map<TNodeID, std::shared_ptr<CStreetMap::SNode> > DNodeIDToNode;
    std::vector< std::shared_ptr<CStreetMap::SNode> > DNodesByIndex;
    std::unordered_map<TWayID, std::shared_ptr<CStreetMap::SWay> > DWayIDToWay;
    std::vector< std::shared_ptr<CStreetMap::SWay> > DWaysByIndex;

    SImplementation(std::shared_ptr<CXMLReader> src){
        SXMLEntity TempEntity;

        while(src->ReadEntity(TempEntity,true)){
            if((TempEntity.DNameData == "osm")&&(SXMLEntity::EType::EndElement == TempEntity.DType)){
                //reached end
                break;
            }
            else if((TempEntity.DNameData == "node")&&(SXMLEntity::EType::StartElement == TempEntity.DType)){
                //parse node
                TNodeID NewNodeID = std::stoull(TempEntity.AttributeValue("id"));
                double Lat = std::stod(TempEntity.AttributeValue("lat"));
                double Lon = std::stod(TempEntity.AttributeValue("lon"));
                TLocation NewNodeLocation = std::make_pair(Lat,Lon);
                auto NewNode = std::make_shared<SNode>(NewNodeID,NewNodeLocation);
                DNodesByIndex.push_back(NewNode);
                DNodeIDToNode[NewNodeID] = NewNode;
                while(src->ReadEntity(TempEntity,true)){
                    if((TempEntity.DNameData == "node")&&(SXMLEntity::EType::EndElement == TempEntity.DType)){
                        break;
                    }
                    else if((TempEntity.DNameData == "tag")&&(SXMLEntity::EType::StartElement == TempEntity.DType)){
                        NewNode->SetAttribute(TempEntity.AttributeValue("k"),TempEntity.AttributeValue("v"));
                    }
                }
            }

            else if((TempEntity.DNameData == "way")&&(SXMLEntity::EType::StartElement == TempEntity.DType)){
                //parse way
                TWayID NewWayID = std::stoull(TempEntity.AttributeValue("id"));
                auto NewWay = std::make_shared<SWay>();
                NewWay->WID = NewWayID;

                // Read nested entities within the way element
                while(src->ReadEntity(TempEntity, true)){
                    // If it's the end of the way element, break the loop
                    if((TempEntity.DNameData == "way") && (SXMLEntity::EType::EndElement == TempEntity.DType)){
                        break;
                    }
                    // If it's a node reference (nd element), add the node ID to the way's node list
                    else if((TempEntity.DNameData == "nd") && (SXMLEntity::EType::StartElement == TempEntity.DType)){
                        TNodeID NodeID = std::stoull(TempEntity.AttributeValue("ref"));
                        NewWay->NodeIDs.push_back(NodeID);
                    }
                    // If it's a tag element, add the attribute to the way's attribute map
                    else if((TempEntity.DNameData == "tag") && (SXMLEntity::EType::StartElement == TempEntity.DType)){
                        std::string Key = TempEntity.AttributeValue("k");
                        std::string Value = TempEntity.AttributeValue("v");
                        NewWay->Attributes[Key] = Value;
                    }
                }
                // Once all nd and tag elements have been processed, add the way to the data structures
                DWayIDToWay[NewWayID] = NewWay;
                DWaysByIndex.push_back(NewWay);
            }
        }
    }

    std::size_t NodeCount() const {
        return DNodesByIndex.size();
    }
    
    std::size_t WayCount() const noexcept {
        return DWaysByIndex.size();
    }
    
    std::shared_ptr<CStreetMap::SNode> NodeByIndex(std::size_t index) const {
        if(index < DNodesByIndex.size()){
            return DNodesByIndex[index];
        }
        return nullptr;
    }
    
    std::shared_ptr<CStreetMap::SNode> NodeByID(TNodeID id) const noexcept {
        auto Search = DNodeIDToNode.find(id);
        if(DNodeIDToNode.end() != Search){
            return Search->second;
        }
        return nullptr;
    }
    
    std::shared_ptr<CStreetMap::SWay> WayByIndex(std::size_t index) const noexcept {
        if(index < DWaysByIndex.size()){
            return DWaysByIndex[index];
        }
        return nullptr;
    }
    
    std::shared_ptr<CStreetMap::SWay> WayByID(TWayID id) const noexcept {
        auto Search = DWayIDToWay.find(id);
        if(DWayIDToWay.end() != Search){
            return Search->second;
        }
        return nullptr;
    }
};
