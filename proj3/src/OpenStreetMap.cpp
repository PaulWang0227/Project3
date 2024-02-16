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

        virtual TWayID ID() const noexcept = 0;
            virtual std::size_t NodeCount() const noexcept = 0;
            virtual TNodeID GetNodeID(std::size_t index) const noexcept = 0;
            virtual std::size_t AttributeCount() const noexcept = 0;
            virtual std::string GetAttributeKey(std::size_t index) const noexcept = 0;
            virtual bool HasAttribute(const std::string &key) const noexcept = 0;
            virtual std::string GetAttribute(const std::string &key) const noexcept = 0;
    };
};
