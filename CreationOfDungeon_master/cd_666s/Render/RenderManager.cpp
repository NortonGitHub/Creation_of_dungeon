#include "RenderManager.h"
#include "Texture2D.h"
#include "../../Main.h"
#include "DxLib.h"

RenderManager::RenderManager()
    : _clearColor(1.0, 1.0, 1.0, 1.0)
    , _defaultCamera(Vector2D(0, 0), 0, Vector2D(VIEWPORT_WIDTH, VIEWPORT_HEIGHT))
    , _uiCamera(Vector2D(0, 0), 0, Vector2D(VIEWPORT_WIDTH, VIEWPORT_HEIGHT))
{
    Camera::_mainCamera = &_defaultCamera;

    _debugDrawCalls.reserve(64);
}


RenderManager::~RenderManager()
{
    ClearModel();
}


void RenderManager::ClearModel()
{
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
    _defaultCamera.Render();
    _uiCamera.Render();

    for (size_t i = 0; i < _debugDrawCalls.size(); ++i)
    {
        _debugDrawCalls[i]->Draw();
    }

    _debugDrawCalls.clear();
    _debugDrawCalls.resize(0);

    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}


void RenderManager::AddRenderModel(std::weak_ptr<Texture2D> model)
{
    auto type = model.lock()->GetRenderType();
    switch(type)
    {
        case Texture2D::RenderType::UI:
            _uiCamera.AddRenderModel(model);
            break;
            
        case Texture2D::RenderType::DEFAULT:
            _defaultCamera.AddRenderModel(model);
            break;
    }
}


void RenderManager::RemoveRenderModel(std::weak_ptr<Texture2D> model)
{
    auto type = model.lock()->GetRenderType();
    switch(type)
    {
        case Texture2D::RenderType::UI:
            _uiCamera.RemoveRenderModel(model);
            break;
            
        case Texture2D::RenderType::DEFAULT:
            _defaultCamera.RemoveRenderModel(model);
            break;
    }
}


void RenderManager::ChangePriority(std::weak_ptr<Texture2D> model, int oldPriority, int newPriority)
{
    auto type = model.lock()->GetRenderType();
    switch(type)
    {
        case Texture2D::RenderType::UI:
            _uiCamera.ChangePriority(oldPriority, newPriority);
            break;
            
        case Texture2D::RenderType::DEFAULT:
            _defaultCamera.ChangePriority(oldPriority, newPriority);
            break;
    }
}


void RenderManager::Update()
{
}
