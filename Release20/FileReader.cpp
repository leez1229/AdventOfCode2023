#include "FileReader.h"

FileReader::FileReader(const std::string& filePath, const std::string& deliminator)
:deliminator(deliminator)
{
    file.open(filePath);
}

FileReader::~FileReader()
{
    file.close();
}