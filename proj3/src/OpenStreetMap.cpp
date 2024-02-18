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
        SWay(){

        }

        ~SWay(){

        }

        TWayID ID() const noexcept override{

        }

        std::size_t NodeCount() const noexcept override{

        }

        TNodeID GetNodeID(std::size_t index) const noexcept override{

        }

        std::size_t AttributeCount() const noexcept override{

        }

        std::string GetAttributeKey(std::size_t index) const noexcept override{

        }

        bool HasAttribute(const std::string &key) const noexcept override{

        }
        std::string GetAttribute(const std::string &key) const noexcept override{
            
        }
    };

    std::unordered_map<TNodeID, std::shared_ptr<CStreetMap::SNode> > DNodeIDToNode;
    std::vector< std::shared_ptr<CStreetMap::SNode> > DNodesByIndex;

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
            }
        }
    }

    std::size_t NodeCount() const {
        return DNodesByIndex.size();
    }
    
    std::size_t WayCount() const noexcept {
        
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
        
    }
    
    std::shared_ptr<CStreetMap::SWay> WayByID(TWayID id) const noexcept {
        
    }
};
