#include "DSVReader.h"
#include "DataSource.h"
struct CDSVReader::SImplementation{
    std::shared_ptr< CDataSource > source;
    char delimiter;
    bool AtEnd;
     SImplementation(std::shared_ptr<CDataSource> src, char delimiter)
        :source(std::move(src)), delimiter(delimiter),AtEnd(false){}
    bool End() const {
        return AtEnd;
    }
    bool ReadRow(std::vector<std::string> &row){
        std::string line;
        std::vector<char> buffer;
        row.clear();
        const std::size_t bufferSize = 1000;
        bool newlineEncountered = false;

        while (!newlineEncountered && source->Read(buffer, bufferSize)) {
            for (char ch : buffer) {
                if (ch == '\n' || ch == '\r') {
                    newlineEncountered = true;
                    break;
                }
                line += ch;
            }
        }

        if (line.empty() && buffer.empty()) {
            AtEnd = true;
            return false;
        }
        // Parse the line
        std::vector<std::string> output;
        size_t start = 0;
        size_t end = line.find(delimiter);
        while (end != std::string::npos) {
            row.push_back(line.substr(start, end - start));
            start = end + 1;
            end = line.find(delimiter, start);
        }
        row.push_back(line.substr(start));
        return true;
    }
};
    bool CDSVReader::End() const {
    return DImplementation->End();
}
    CDSVReader::CDSVReader(std::shared_ptr< CDataSource > src, char delimiter)
    : DImplementation(std::make_unique<SImplementation>(src, delimiter)) {
    // Code to initialize the CDSVWriter
}
    CDSVReader::~CDSVReader()=default;

    bool CDSVReader::ReadRow(std::vector<std::string> &row) {
    return DImplementation->ReadRow(row);
}