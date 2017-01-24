#include "Camera.h"
#include <algorithm>

Camera* Camera::_mainCamera = nullptr;

Camera::Camera(Vector2D pos, double angle, Vector2D viewPortSize)
: _position(pos)
, _angle(angle)
, _viewPortSize(viewPortSize)
, _needResize(false)
, _needAliment(false)
{
}


Camera::~Camera()
{
    Clear();
}


void Camera::Clear()
{
    _renderModels.Clear();
    _renderOrders.clear();
    _priorityTable.clear();
}


void Camera::AddRenderModel(std::weak_ptr<Texture2D> model)
{
    _renderModels.Add(model);
    CountPriority(model.lock()->GetPriority());
    _needResize = true;
    _needAliment = true;
}


void Camera::RemoveRenderModel(std::weak_ptr<Texture2D> model)
{
    _renderModels.Remove(model);
    DiscountPriority(model.lock()->GetPriority());
    _needResize = true;
    _needAliment = true;
}


void Camera::CountPriority(int priority)
{
    for (size_t i = 0; i< _priorityTable.size(); ++i)
    {
        PriorityInfo* pInfo = &_priorityTable[i];
        if (priority != pInfo->_priority)
            continue;
        
        pInfo->_size++;
        return;
    }
    
    //ここまで抜けたらpriority値がなかった = 新しいpriority値
    PriorityInfo pInfo = { priority, 1, 0 };
    _priorityTable.push_back(std::move(pInfo));
}


void Camera::DiscountPriority(int priority)
{
    for (size_t i = 0; i<_priorityTable.size(); ++i)
    {
        PriorityInfo* pInfo = &_priorityTable[i];
        if (priority != pInfo->_priority)
            continue;
        
        pInfo->_size--;
        return;
    }
}


void Camera::ChangePriority(int oldPriority, int newPriority)
{
    DiscountPriority(oldPriority);
    CountPriority(newPriority);
    _needAliment = true;
}


void Camera::AlimentDrawCall()
{
    //描画コールを初期化
    if (_needResize)
        _renderOrders.resize(_renderModels._objects.size());
//    else
//        _renderOrders(nullptr);
    
    for (size_t i=0; i<_priorityTable.size(); ++i)
        _priorityTable[i]._count = 0;
    
    std::sort(_priorityTable.begin(), _priorityTable.end(),
        [&](const PriorityInfo &lhs, const PriorityInfo &rhs)
    {
        return (lhs._priority < rhs._priority);
    });

    for (auto image : _renderModels._objects)
    {
        size_t index = 0;
        for (size_t i = 0; i<_priorityTable.size(); ++i)
        {
            PriorityInfo* pInfo = &_priorityTable[i];
            
            //所属するpriority値が出たら
            //そのpriority値を何番目に使ったかを加算して終了
            if (image.lock()->GetPriority() == pInfo->_priority)
            {
                index += pInfo->_count;
                pInfo->_count++;
                break;
            }
            
            //所属するpriority値が出るまで、各priority値を使ってる数だけ加算
            index += pInfo->_size;
        }
        
        _renderOrders[index] = image;
    }
}


void Camera::Render()
{
    _renderModels.Update();

    if (_needAliment)
        AlimentDrawCall();

    for (auto image : _renderOrders)
    {
        if (!image.expired())
            image.lock()->Render(*this);
    }
}


bool Camera::IsDisplay(Vector2D point)
{
    auto lowerLeft = _position;
    auto upperRight = _position + _viewPortSize;
    
    return (lowerLeft._y < point._y
            && lowerLeft._x < point._x
            && point._y < upperRight._y
            && point._x < upperRight._x);
}
