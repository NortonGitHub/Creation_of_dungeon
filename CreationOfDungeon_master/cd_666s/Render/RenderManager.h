#ifndef RenderManager_h
#define RenderManager_h

#include <vector>
#include <functional>
#include "../Utility/Singleton.h"
#include "../Utility/PoolingSystem.h"
#include "../Color.h"
#include "../DebugDraw.h"
#include "Camera.h"

class Texture2D;
class DebugDraw;

class RenderManager : public Singleton<RenderManager>
{
    friend class Singleton<RenderManager>;

public:
    RenderManager();
    ~RenderManager();
    
    void AddDebugCall(Debug::DebugDraw* debugDrawCall) { _debugDrawCalls.push_back(debugDrawCall); }
    void AddRenderModel(Texture2D *model);
    void RemoveRenderModel(Texture2D *model);
    void ClearModel();
    
    void Init();
    void ClearScreen();
    void RenderImage();
    void Update();
    
    //画面の初期化色を設定する
    void SetClearColor(Color4 color) { _clearColor = color; };
    void ChangePriority(Texture2D *model, int oldPriority, int newPriority);
    
private:
    
    Color4 _clearColor;
    Camera _defaultCamera, _uiCamera;

    //TODO : ちゃんとデバッグ描画用のものを作る
    std::vector<Debug::DebugDraw*> _debugDrawCalls;
};


#define RENDER_MGR RenderManager::GetInstance()

#endif /* RenderManager_h */
