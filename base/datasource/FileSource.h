#pragma once
#include <fstream>
#include <iostream>

class FileSource : public DataSource<FileSource>
{
public:
    explicit FileSource(const std::string& path)
        : file_(path, std::ios::binary)
    {}

    bool openImpl()
    {
        std::cout << "Opening file\n";
        return file_.is_open();
    }

    bool readImpl(std::vector<uint8_t>& buffer)
    {
        buffer.resize(4);
        file_.read(reinterpret_cast<char*>(buffer.data()), 4);
        return file_.gcount() > 0;
    }

    void closeImpl()
    {
        file_.close();
        std::cout << "Closing file\n";
    }

private:
    std::ifstream file_;
};