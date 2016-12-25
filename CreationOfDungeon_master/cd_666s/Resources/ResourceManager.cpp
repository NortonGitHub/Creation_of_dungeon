#include "ResourceManager.h"
//#include "ImageResource.h"
//#include "SoundResource.h"
using namespace std;

ResourceManager::ResourceManager()
: _filePath("resource/")    //���\�[�X�f�B���N�g���̍ŏ�ʃp�X
, _empty(nullptr)
{
}

std::weak_ptr<Resource> ResourceManager::GetResource(std::string name)
{
    auto it = _nameMap.find(name);
    bool hasLoaded = (it != _nameMap.end()
                      && _resourceTable[it->second] != nullptr);
    
    //���[�h�ς݂Ȃ�|�C���^��
    if (hasLoaded)
    {
        return _resourceTable[(*it).second];
    }
    //�������null��Ԃ�
    else
    {
        return _empty;
    }
}


shared_ptr<Resource> ResourceManager::Create(shared_ptr<Resource> resource)
{
    //���[�h�ς݂��`�F�b�N
    auto it = _nameMap.find(resource->GetName());
    bool hasLoaded = (it != _nameMap.end()
                      && _resourceTable[it->second] != nullptr);
    
    //���[�h�ς݂Ȃ�|�C���^��
    if (hasLoaded)
        return _resourceTable[(*it).second];
    
    for (size_t i = 0; i < _resourceTable.size(); ++i)
    {
        //null�̂Ƃ��낪�����
        if (_resourceTable[i].get() == nullptr)
        {
            //�����ɐ������ďI��
            _resourceTable[i] = resource;
            _nameMap.insert(make_pair(resource->GetName(), i));
            return resource;
        }
    }
    
    //null��������΍Ō�ɐ������ďI��
    _resourceTable.push_back(resource);
    _nameMap.insert(make_pair(resource->GetName(), _resourceTable.size() - 1));
    
    return resource;
}


void ResourceManager::Update()
{
    for (size_t i = 0; i < _resourceTable.size(); ++i)
    {
        //�󃊃\�[�X�Ȃ疳��
        if (_resourceTable[i].get() == nullptr)
            continue;
        
        
        //�g�p���� vector�Ɋi�[����Q�� + �ꎞ�ϐ�resource �����Ȃ�
        // = ������Q�Ƃ���Ȃ��Ȃ����@��폜����
        if (1 < _resourceTable[i].use_count())
            continue;
        
        Remove(_resourceTable[i].get()->GetName());
    }
}

void ResourceManager::Debug()
{
    /*
    for (size_t i = 0; i < _resourceTable.size(); ++i)
    {
        std::weak_ptr<Resource> resource = _resourceTable[i];
        
        //�󃊃\�[�X�Ȃ疳��
        if (resource._Get() == nullptr)
            continue;
        
        DrawFormatString(0,  0 + (i + 1) * 60, GetColor(0x00, 0x00, 0x00), (_resourceTable[i]->GetName()).c_str());
        DrawFormatString(0, 30 + (i + 1) * 60, GetColor(0x00, 0x00, 0x00), "%d:", _resourceTable[i].use_count());
    }
    
    DrawFormatString(0, 0, GetColor(0x00, 0x00, 0x00), "list size : %d", _resourceTable.size());
    */
}

void ResourceManager::Remove(const string name)
{
    if (    _nameMap.size() == 0
        && _resourceTable.size() == 0)
        return;
    
    //���[�h�ς݃}�b�v����폜
    size_t index = _nameMap[name];
    _nameMap.erase(_nameMap.find(name));
    _resourceTable[index] = _empty;
}

void ResourceManager::Refresh()
{
    vector<shared_ptr<Resource>> swaped;
    
    for (size_t i = 0; i < _resourceTable.size(); ++i)
    {
        if (_resourceTable[i] == _empty)
            continue;
        
        //empty�ȊO��ǉ�����
        swaped.push_back( _resourceTable[i] );
        
        //�؂�l�ߎ��̃C���f�N�X�̕ύX��K�p����
        _nameMap[_resourceTable[i]->GetName()] = swaped.size() - 1;
    }
    
    //�؂�l�߂����X�g�Ɠ���ւ���
    _resourceTable = std::move(swaped);
}


void ResourceManager::Clear()
{
    for (size_t i = 0; i < _resourceTable.size(); ++i)
    {
        //�󃊃\�[�X�Ȃ疳��
        if (_resourceTable[i].get() == nullptr)
            continue;
        
        Remove(_resourceTable[i].get()->GetName());
    }
}


ResourceManager::~ResourceManager()
{
    _resourceTable.clear();
    _nameMap.clear();
}
