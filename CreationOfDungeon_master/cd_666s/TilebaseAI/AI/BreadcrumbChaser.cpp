#include "BreadcrumbChaser.h"
#include "Breadcrumb.h"
#include "../Character.h"
#include "../TileField.h"
#include <algorithm>

BreadcrumbChaser::BreadcrumbChaser(std::vector<TiledVector> &pathRef
                                   , Character &owner
                                   , int searchRange
                                   , bool diagonal)
: PathFindingAIBase(owner, pathRef)
, _searchRange(searchRange)
, _diagonal(diagonal)
, _currentID(0)
{
}


BreadcrumbChaser::~BreadcrumbChaser()
{
}


void BreadcrumbChaser::Reset()
{
    _currentID = 0;
}


void BreadcrumbChaser::Update()
{
    SearchBreadcrumbs();
}


void BreadcrumbChaser::SearchBreadcrumbs()
{
    TiledVector ownerPos = _owner.GetTilePos();
    std::vector<const Breadcrumb *> breadcrumbs;
    
    //周囲の8マスにBreadcrumbがあるか調べる
    if (_diagonal)
    {
        for (size_t i=0; i<8; ++i)
        {
            TiledVector pos = ownerPos + TiledVector::eightDirecton[i];
            auto breadcrumb = FIELD->GetBreadcrumb(pos);
            
            if ( breadcrumb != nullptr )
                breadcrumbs.push_back(breadcrumb);
        }
    }
    //周囲の4マスにBreadcrumbがあるか調べる
    else
    {
        for (size_t i=0; i<4; ++i)
        {
            TiledVector pos = ownerPos + TiledVector::fourDirecton[i];
            auto breadcrumb = FIELD->GetBreadcrumb(pos);
            
            if ( breadcrumb != nullptr )
                breadcrumbs.push_back(breadcrumb);
        }
    }
    
    //何もなければ終了
    if (breadcrumbs.size() == 0)
        return;
    
    //取得したbreadcrumbをIDでソート
    sort(breadcrumbs.begin(), breadcrumbs.end(),
         [](const Breadcrumb* lhs, const Breadcrumb* rhs)
         {
             return (rhs->GetID() < lhs->GetID());
         });
    
    auto breadcrumb = breadcrumbs[0];
    
    //今いる自分のノードのIDの方が大きければ終了
    if (breadcrumb->GetID() <= _currentID)
        return;
    
    //最終的に決定したbreadcrumbの位置を目的地とする
    _pathRef.push_back( breadcrumb->GetTilePos() );
    _currentID = breadcrumb->GetID();
}