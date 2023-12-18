#include "FileBlockReader.h"

FileBlockReader::FileBlockReader(const std::string& filePath, const std::string& deliminator)
:deliminator(deliminator)
{
    file.open(filePath);
}

FileBlockReader::~FileBlockReader()
{
    file.close();
}