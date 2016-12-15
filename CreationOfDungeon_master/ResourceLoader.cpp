#include "ResourceLoader.h"
#include <istream>


ResourceLoader::ResourceLoader()
{
}


ResourceLoader::~ResourceLoader()
{
}


std::vector<int> ResourceLoader::Load(std::string file_name, int all_num, int x_num, int y_num, int x_size, int y_size)
{
    //�摜�z��̃n���h���̂܂Ƃ܂�
    std::vector<int> handles(all_num, 0);

    //png�`���摜�̃��[�h
    std::string format = ".png";
    LoadDivGraph((file_name + format).c_str(), all_num, x_num, y_num, x_size, y_size, handles.data());

    //�֐��𔲂���Ə��ł���̂�move�n����
    //�C���X�^���X��n��
    return std::move(handles);
}


int ResourceLoader::Load(std::string file_name)
{
    std::string format = ".png";
    return LoadGraph((file_name + format).c_str());
}
