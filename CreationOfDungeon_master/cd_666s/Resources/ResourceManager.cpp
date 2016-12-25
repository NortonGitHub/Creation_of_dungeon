#include "ResourceManager.h"
//#include "ImageResource.h"
//#include "SoundResource.h"
using namespace std;

ResourceManager::ResourceManager()
: _filePath("resource/")    //リソースディレクトリの最上位パス
, _empty(nullptr)
{
}

std::weak_ptr<Resource> ResourceManager::GetResource(std::string name)
{
    auto it = _nameMap.find(name);
    bool hasLoaded = (it != _nameMap.end()
                      && _resourceTable[it->second] != nullptr);
    
    //ロード済みならポインタを
    if (hasLoaded)
    {
        return _resourceTable[(*it).second];
    }
    //無ければnullを返す
    else
    {
        return _empty;
    }
}


shared_ptr<Resource> ResourceManager::Create(shared_ptr<Resource> resource)
{
    //ロード済みかチェック
    auto it = _nameMap.find(resource->GetName());
    bool hasLoaded = (it != _nameMap.end()
                      && _resourceTable[it->second] != nullptr);
    
    //ロード済みならポインタを
    if (hasLoaded)
        return _resourceTable[(*it).second];
    
    for (size_t i = 0; i < _resourceTable.size(); ++i)
    {
        //nullのところがあれば
        if (_resourceTable[i].get() == nullptr)
        {
            //そこに生成して終了
            _resourceTable[i] = resource;
            _nameMap.insert(make_pair(resource->GetName(), i));
            return resource;
        }
    }
    
    //nullが無ければ最後に生成して終了
    _resourceTable.push_back(resource);
    _nameMap.insert(make_pair(resource->GetName(), _resourceTable.size() - 1));
    
    return resource;
}


void ResourceManager::Update()
{
    for (size_t i = 0; i < _resourceTable.size(); ++i)
    {
        //空リソースなら無視
        if (_resourceTable[i].get() == nullptr)
            continue;
        
        
        //使用数が vectorに格納する参照 + 一時変数resource しかない
        // = 他から参照されなくなった　ら削除する
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
        
        //空リソースなら無視
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
    
    //ロード済みマップから削除
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
        
        //empty以外を追加する
        swaped.push_back( _resourceTable[i] );
        
        //切り詰め時のインデクスの変更を適用する
        _nameMap[_resourceTable[i]->GetName()] = swaped.size() - 1;
    }
    
    //切り詰めたリストと入れ替える
    _resourceTable = std::move(swaped);
}


void ResourceManager::Clear()
{
    for (size_t i = 0; i < _resourceTable.size(); ++i)
    {
        //空リソースなら無視
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
