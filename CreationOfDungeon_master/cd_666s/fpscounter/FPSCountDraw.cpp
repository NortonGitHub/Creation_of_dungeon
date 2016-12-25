#include "FPSCountDraw.h"
#include "../DebugDraw.h"

FPSDrawer::FPSDrawer(FPSCounter& fpsCounter)
    : _fpsCounter(fpsCounter)
{
}


FPSDrawer::~FPSDrawer()
{
}


void FPSDrawer::Draw()
{
    Debug::DrawString(Vector2D::zero, std::to_string(_fpsCounter.GetFPS()));
    Debug::DrawString(Vector2D(0, 568), std::to_string(_fpsCounter.GetDeltaTime()));
}