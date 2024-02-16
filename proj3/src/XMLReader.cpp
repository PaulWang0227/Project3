#include "XMLReader.h"
#include "XMLEntity.h"
#include "StringDataSource.h"
#include <expat.h>
#include <queue>
struct CXMLReader::SImplementation{
    std::shared_ptr<CDataSource> DDataSource;
    XML_Parser DXMLParser;
    std::queue<SXMLEntity>DEntityQueue;
    void StartELementHandler(const std::string &name, const std::vector<std::string> &attrs){
        SXMLEntity TempEntity;
        TempEntity.DNameData=name;
        TempEntity.DType=SXMLEntity::EType::StartElement;
        for(size_t Index=0; Index <attrs.size(); Index+=2){
            TempEntity.SetAttribute(attrs[Index], attrs[Index+1]);
        }
        DEntityQueue.push(TempEntity);
    };
    void EndElementHandler(const std::string &name){
    SXMLEntity TempEntity;
    TempEntity.DNameData = name;
    TempEntity.DType = SXMLEntity::EType::EndElement;
    DEntityQueue.push(TempEntity);
    };
    void CharacterDataHandler(const std::string &cdata){
   if (!cdata.empty()) {
        SXMLEntity TempEntity;
        TempEntity.DType = SXMLEntity::EType::CharData;
        TempEntity.DNameData = cdata;
        DEntityQueue.push(TempEntity);
    }
    };

    static void StartElementHandlerCallback(void *context, const XML_Char *name, const XML_Char **atts){
        SImplementation *ReaderObject=static_cast<SImplementation*>(context);
        std::vector<std::string> Attributes;
        auto Attrptr=atts;
        while(*Attrptr){
            Attributes.push_back(*Attrptr);
            Attrptr++;
        }
        ReaderObject->StartELementHandler(name,Attributes);
    };
    static void EndElementHandlerCallback(void *context, const XML_Char *name){
        SImplementation *ReaderObject=static_cast<SImplementation*>(context);
        ReaderObject->EndElementHandler(name);
    };
    static void CharacterDataHandlerCallback(void *context, const XML_Char *s, int len){
        SImplementation *ReaderObject=static_cast<SImplementation*>(context);
        ReaderObject->CharacterDataHandler(std::string(s,len));
    };

    SImplementation(std::shared_ptr<CDataSource> src){
        DDataSource=src;
        DXMLParser=XML_ParserCreate(NULL);
        XML_SetStartElementHandler(DXMLParser,  StartElementHandlerCallback);
        XML_SetEndElementHandler(DXMLParser, EndElementHandlerCallback);
        XML_SetCharacterDataHandler(DXMLParser, CharacterDataHandlerCallback);
        XML_SetUserData(DXMLParser,this);
    };
    bool End() const{
        return DEntityQueue.empty() && DDataSource->End();
    };
    bool ReadEntity(SXMLEntity &entity, bool skipcdata){
        //Reader from source if necessary
        //Pass to XMLParser
        //Return Entity
        std::vector<char> DataBuffer;
        if (!DDataSource->Read(DataBuffer, 256)) {
        return false;
        }
        while(DEntityQueue.empty()){

            if(DDataSource->Read(DataBuffer, 256)){
                XML_Parse(DXMLParser,DataBuffer.data(),DataBuffer.size(), DataBuffer.size()<256);
            }
            else{
                XML_Parse(DXMLParser,DataBuffer.data(),0, true);
            }

        }
        if(DEntityQueue.empty()){
            return false;
        }
        entity=DEntityQueue.front();
        DEntityQueue.pop();
        return true;

   };

};
CXMLReader::CXMLReader(std::shared_ptr< CDataSource > src){
    DImplementation = std::make_unique<SImplementation>(src);
}

CXMLReader::~CXMLReader()=default;

bool CXMLReader::End() const{
    return DImplementation->End();
 }
bool CXMLReader::ReadEntity(SXMLEntity &entity, bool skipcdata) {
    return DImplementation->ReadEntity(entity, skipcdata);
}