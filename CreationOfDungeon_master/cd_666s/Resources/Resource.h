#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>

//typedef int Handle;

class Resource
{
public:
    
    Resource(std::string fileName);
    virtual ~Resource();
    
    //リソースのロード
    virtual bool Load();
    //リソースの削除
    virtual bool Unload();
    
    std::string GetName() const { return _fileName; }
    //Handle GetHandle() const { return _handle; }
    
protected:
    
    //リソースハンドルの本体
    //Handle _handle;
    
    //リソースを読み込むファイル名
    std::string _fileName;
};

#endif