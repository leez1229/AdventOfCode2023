#include "FileLineReader.h"

FileLineReader::FileLineReader(const std::string& filePath, const std::string& deliminator)
:deliminator(deliminator)
{
    file.open(filePath);
}

FileLineReader::~FileLineReader()
{
    file.close();
}