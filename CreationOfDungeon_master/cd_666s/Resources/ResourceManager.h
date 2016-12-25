#ifndef RESOURCE_MGR
#define RESOURCE_MGR

#include <memory>
#include <map>
#include <vector>
#include "../Utility/Singleton.h"
#include "Resource.h"

/*
 生成されるリソースハンドルを
 一意なファイル名 と shared_ptrのインデクスのペア で管理するクラス
 */

class ResourceManager : public Singleton<ResourceManager>
{
    friend class Singleton<ResourceManager>;
    
public:
    
    //リソースを作成・取得
    std::shared_ptr<Resource> Create(std::shared_ptr<Resource> resource);
    
    //リソースの参照カウンタをチェックして不要なものを管理から外す
    void Update();
    //リソースごとの参照数をDrawFormatStringで出力
    void Debug();
    
    void Clear();
    
    //リスト中のemptyを切り詰める
    void Refresh();
    
    //リソース群の最上位フォルダ名を取得
    std::string GetFolderPath() const { return _filePath; }
    void SetFolderPath(std::string str){ _filePath = str; }
    
    //リソースのweak_ptrを取得
    std::weak_ptr<Resource> GetResource(std::string name);
    
    
private:
    
    //リソースを管理から外して削除
    void Remove(const std::string name);
    void Push(std::string name);
    
    ResourceManager();
    ~ResourceManager();
    
    //リソースディレクトリの最上位パス
    std::string _filePath;
    
    //削除されたリソースの位置に代入しておくための空のリソース
    const std::shared_ptr<Resource> _empty;
    
    //リソースの配列
    std::vector< std::shared_ptr<Resource> > _resourceTable;
    
    //リソースの管理名の配列
    std::map<std::string, size_t> _nameMap;
};

#define RESOURCE_TABLE ResourceManager::GetInstance()

#endif