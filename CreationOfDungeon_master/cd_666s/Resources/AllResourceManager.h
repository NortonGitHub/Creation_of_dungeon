#ifndef AllResourceManager_h
#define AllResourceManager_h

#include "../Utility/Singleton.h"
#include "ResourceManager.h"

class AllResourceManager : public Singleton<AllResourceManager>
{
    friend class Singleton<AllResourceManager>;
    
public:
    
    //リソースの参照カウンタをチェックして不要なものを管理から外す
    void Update();
    
    //リソースごとの参照数をDrawFormatStringで出力
    void Debug();
    
    void Clear();
    
    //リスト中のemptyを切り詰める
    void Refresh();
    
    //リソース群の最上位フォルダ名を取得
    std::string GetFolderPath() const { return _filePath; }
    void SetFolderPath(std::string str) { _filePath = str; }
    void SetAllTypesFolderPath(std::string str);

private:
    
    AllResourceManager();
    ~AllResourceManager();
    
    //リソースディレクトリの最上位パス
    std::string _filePath;
};

#define RESOURCE_TABLE AllResourceManager::GetInstance()
#endif /* AllResourceManager_h */
