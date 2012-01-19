#include <fstream>

#include <sys/types.h>
#include <sys/stat.h>

#ifdef __linux__
#include <unistd.h>
#endif

bool readBinaryFile(const std::string& path, char* buffer)
{
    std::ifstream file(path.c_str(), std::ifstream::binary);
    if(!file.is_open())
        return false;

    struct stat results;
    stat(path.c_str(), &results);

    file.read(buffer, results.st_size);
	file.close();
    return true;
}

bool saveToBinaryFile(const std::string& path, char* buffer, bool append = false)
{
    std::ofstream outputFile;
	struct stat results;
    stat(path.c_str(), &results);
	if(!append)
		outputFile.open(path.c_str(), std::ofstream::binary);
	else 
		outputFile.open(path.c_str(), std::ofstream::binary | std::ofstream::app);
    if(!outputFile.is_open())
        return false;

    outputFile.write(buffer, results.st_size);
	outputFile.close();
    return true;
}

bool saveToTextFile(const std::string& path, const std::string& text)
{
    std::ofstream file;
    file.open(path.c_str());
    if(!file.is_open())
        return false;

    file<<text;
    return true;
}

bool readTextFile(const std::string& path, std::string& text)
{
    std::ifstream file;
    file.open(path.c_str());
    if(!file.is_open())
        return false;

    text = "";
    char c;
    while(!file.eof())
    {
        file.get(c);
        text += c;
    }
    return true;
}

unsigned long long getFileSize(const std::string& path)
{
	struct stat results;
	if(!stat(path.c_str(), &results))
        return 0;
	return results.st_size;
}

