#pragma once
#include <string>
#include <vector>
#include "DxLib.h"
#include "Graph.h"

class ResourceLoader
{
public:
    ResourceLoader();
    ~ResourceLoader();

    static std::vector<int> Load(std::string file_name, int all_num, int x_num, int y_num, int x_size, int y_size);
    static int Load(std::string file_name);
};