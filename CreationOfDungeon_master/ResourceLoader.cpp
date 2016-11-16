#include "ResourceLoader.h"
#include <istream>


ResourceLoader::ResourceLoader()
{
}


ResourceLoader::~ResourceLoader()
{
}

void ResourceLoader::Load(std::vector<Graph>& graph_array, std::string file_name, int all_num, int x_num, int y_num, int x_size, int y_size)
{
	int buf[256];
	char c_file_name[100];

	sprintf_s(c_file_name,100, "%s.png", file_name.c_str());

	LoadDivGraph(c_file_name, all_num, x_num, y_num, x_size, y_size, buf);

	for (int i = 0; all_num; i++) {
		graph_array.push_back(Graph(buf[i], x_size, y_size));
	}

}

int ResourceLoader::Load(std::string file_name)
{
	int graph = 0;


	char c_file_name[100];

	sprintf_s(c_file_name,100, "%s.png", file_name.c_str());

	graph = LoadGraph(c_file_name);

	return graph;
}
