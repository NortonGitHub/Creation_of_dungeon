#include "RenderManager.h"
#include "Texture2D.h"

static const double WINDOW_WIDTH = 1280.0;
static const double WINDOW_HEIGHT = 720.0;
static const double VIEWPORT_WIDTH = 1280.0;
static const double VIEWPORT_HEIGHT = 720.0;

RenderManager::RenderManager()
    : _clearColor(1.0, 1.0, 1.0, 1.0)
    , _defaultCamera(Vector2D(0, 0), 0, Vector2D(VIEWPORT_WIDTH, VIEWPORT_HEIGHT))
    , _uiCamera(Vector2D(0, 0), 0, Vector2D(VIEWPORT_WIDTH, VIEWPORT_HEIGHT))
{
    Camera::_mainCamera = &_defaultCamera;
}


RenderManager::~RenderManager()
{
    ClearModel();
}


void RenderManager::ClearModel()
{
    //_poolingSystem.Clear();
    _defaultCamera.Clear();
    _uiCamera.Clear();
}


void RenderManager::Init()
{
}


void RenderManager::ClearScreen()
{
}


void RenderManager::RenderImage()
{
    //ブレンド係数を設定する
    //glBlendFunc(_defaultBlendRatio.first, _defaultBlendRatio.second);
    
    //レンダリング前に諸々設定を初期化
    //glColor4f(0.0, 0.0, 1.0, 1.0);

    _defaultCamera.Render();

    for (size_t i = 0; i < _debugDrawCalls.size(); ++i)
    {
        _debugDrawCalls[i]->Draw();
        delete _debugDrawCalls[i];
    }

    _debugDrawCalls.clear();
    _debugDrawCalls.resize(0);

    _uiCamera.Render();
}


void RenderManager::AddRenderModel(Texture2D *model)
{
    auto type = model->GetRenderType();
    switch(type)
    {
        case Texture2D::RenderType::UI:
            _uiCamera.AddRenderModel(model);
            break;
            
        case Texture2D::RenderType::DEFAULT:
            _defaultCamera.AddRenderModel(model);
            break;
    }
    //_poolingSystem.Add(model);
}


void RenderManager::RemoveRenderModel(Texture2D *model)
{
    auto type = model->GetRenderType();
    switch(type)
    {
        case Texture2D::RenderType::UI:
            _uiCamera.RemoveRenderModel(model);
            break;
            
        case Texture2D::RenderType::DEFAULT:
            _defaultCamera.RemoveRenderModel(model);
            break;
    }
    //_poolingSystem.Remove(model);
}


void RenderManager::ChangePriority(Texture2D* model, int oldPriority, int newPriority)
{
    auto type = model->GetRenderType();
    switch(type)
    {
        case Texture2D::RenderType::UI:
            _uiCamera.ChangePriority(oldPriority, newPriority);
            break;
            
        case Texture2D::RenderType::DEFAULT:
            _defaultCamera.ChangePriority(oldPriority, newPriority);
            break;
    }
    //_poolingSystem.Remove(model);
}


void RenderManager::Update()
{
    //_poolingSystem.Update();
}
