#pragma once
#include <iostream>
#include <fstream>
#include <string>

class DataRead
{
public: 
    int FileDataRead();
    void DataFileOpen(std::string filepath, void(*func)(std::wifstream& file));
private:
};

