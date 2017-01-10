#include "AllResourceManager.h"

AllResourceManager::AllResourceManager()
{
}

AllResourceManager::~AllResourceManager()
{
}


void AllResourceManager::SetAllTypesFolderPath(std::string str)
{
    SetFolderPath(str);
    IMAGE_RESOURCE_TABLE->SetFolderPath(str);
    SOUND_RESOURCE_TABLE->SetFolderPath(str);
}


//リソースの参照カウンタをチェックして不要なものを管理から外す
void AllResourceManager::Update()
{
    IMAGE_RESOURCE_TABLE->Update();
    SOUND_RESOURCE_TABLE->Update();
}

//リソースごとの参照数をDrawFormatStringで出力
void AllResourceManager::Debug()
{
    IMAGE_RESOURCE_TABLE->Debug();
    SOUND_RESOURCE_TABLE->Debug();
}

void AllResourceManager::Clear()
{
    IMAGE_RESOURCE_TABLE->Clear();
    SOUND_RESOURCE_TABLE->Clear();
}

//リスト中のemptyを切り詰める
void AllResourceManager::Refresh()
{
    IMAGE_RESOURCE_TABLE->Refresh();
    SOUND_RESOURCE_TABLE->Refresh();
}