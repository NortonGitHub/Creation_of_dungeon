#include "ResourceManager.h"
using namespace std;

template <typename T>
ResourceManager<T>::ResourceManager()
: _filePath("resource/")    //リソースディレクトリの最上位パス
, _empty(nullptr)
{
}

template <typename T>
std::weak_ptr<T> ResourceManager<T>::GetResource(std::string name)
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


template <typename T>
shared_ptr<T> ResourceManager<T>::Create(std::string fileName)
{
    //ロード済みかチェック
    auto it = _nameMap.find(fileName);
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
            _resourceTable[i] = std::make_shared<T>(fileName);
            _nameMap.insert(make_pair(fileName, i));
            return _resourceTable[i];
        }
    }
    
    //nullが無ければ最後に生成して終了
    _resourceTable.push_back(std::make_shared<T>(fileName));
    _nameMap.insert(make_pair(fileName, _resourceTable.size() - 1));
    
    return _resourceTable[_resourceTable.size() - 1];
}


template <typename T>
void ResourceManager<T>::Update()
{
    for (size_t i = 0; i < _resourceTable.size(); ++i)
    {
        //空リソースなら無視
        if (_resourceTable[i].get() == nullptr)
            continue;
        
        size_t count = _resourceTable[i].use_count();
        
        //使用数が vectorに格納する参照 + 一時変数resource しかない
        // = 他から参照されなくなった　ら削除する
        if (1 < count)
            continue;
        
        Remove(_resourceTable[i].get()->GetName());
    }
}


template <typename T>
void ResourceManager<T>::Debug()
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


template <typename T>
void ResourceManager<T>::Remove(const string name)
{
    if (    _nameMap.size() == 0
        && _resourceTable.size() == 0)
        return;
    
    //ロード済みマップから削除
    size_t index = _nameMap[name];
    _nameMap.erase(_nameMap.find(name));
    _resourceTable[index].reset();
    _resourceTable[index] = _empty;
}


template <typename T>
void ResourceManager<T>::Refresh()
{
    //まずカラ要素を更新
    Update();

    vector<shared_ptr<T>> swaped;
    
    for (size_t i = 0; i < _resourceTable.size(); ++i)
    {
        if (_resourceTable[i].get() == nullptr)
            continue;
        
        //empty以外を追加する
        swaped.push_back( _resourceTable[i] );
        
        //切り詰め時のインデクスの変更を適用する
        _nameMap[_resourceTable[i]->GetName()] = swaped.size() - 1;
    }
    
    //切り詰めたリストと入れ替える
    _resourceTable = std::move(swaped);
}


template <typename T>
void ResourceManager<T>::Clear()
{
    for (size_t i = 0; i < _resourceTable.size(); ++i)
    {
        //空リソースなら無視
        if (_resourceTable[i].get() == nullptr)
            continue;
        
        Remove(_resourceTable[i].get()->GetName());
    }
    
    _resourceTable.clear();
    _resourceTable.resize(0);
    _nameMap.clear();
}


template <typename T>
ResourceManager<T>::~ResourceManager()
{
    _resourceTable.clear();
    _nameMap.clear();
}