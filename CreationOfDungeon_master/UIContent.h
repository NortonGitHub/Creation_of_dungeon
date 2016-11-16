#pragma once
#include <string>
#include<vector>
#include<stdexcept>
#include "Graph.h"
class UIContent
{
public:
	UIContent();
	UIContent(int data_number,
		std::string data_name,
		int x, int y,
		int width, int height,
		std::string type_name,
		std::string graph_name) {
		_data_number = data_number;
		_data_name = data_name;
		_x = x;
		_y = y;
		_width = width;
		_height = height;
		_type_name = type_name;
		_graph_name = graph_name;
	}

	UIContent(int x, int y, int width, int height, std::string scene_name,std::string str) {
		_x = x;
		_y = y;
		_width = width;
		_height = height;
		_type_name = scene_name;

		try {
			_int_data = std::stoi(str, nullptr, 10);
		}
		catch (const std::invalid_argument& e) {
			_string_data = str;
		}

	}
	~UIContent() {
		std::vector<Graph*>().swap(_graph_array);
	};

	int GetDataNum() const { return _data_number; }
	int GetPosX() const { return _x; }
	int GetPosY() const { return _y; }
	int GetWidth() const { return _width; }
	int GetHeight() const { return _height; }
	std::string GetStr() const {
		return _string_data;
	}
	int GetInt() const {
		return _int_data;
	}

	Graph GetGraph() const { return _graph_data; }
	void GetGraphArray(std::vector<Graph*> &graph_array) {
		for (size_t i = 0; i < _graph_array.size(); i++) {
			graph_array[i] = _graph_array[i];
		}
	}

	std::string GetDataName() const { return _data_name; }
	std::string GetTypeName() const { return _type_name; }
	std::string GetGraphName() const { return _graph_name; }

#if 0
	/*StringŒ^‚âintŒ^‚È‚Ç‚Ìƒf[ƒ^Œ^‚ğŠi”[‚Å‚«‚é*/
	template<typename T>
	class Type {
	public:
		void Set(T value) { _value = value; }
		T Get() const { return _value; }
	private:
		T _value;
	};
#endif


private:
	int _data_number;
	std::string _data_name;	//ƒf[ƒ^‚Ì–¼Ì
	int _x, _y;
	int _width, _height;
	std::string _type_name;	//UI‚Ìí—Ş
	std::string _graph_name;

	Graph  _graph_data;
	std::vector<Graph*> _graph_array;

	std::string _string_data;
	int _int_data;

};

