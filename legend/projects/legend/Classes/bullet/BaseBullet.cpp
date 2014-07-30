//
//  BaseBullet.cpp
//  legend
//
//  Created by Yan Wei on 2014/07/24.
//
//

#include "BaseBullet.h"
#include "ShapeConst.h"

static const int PTM_RATIO_WIN = PTM_RATIO;

BaseBullet* BaseBullet::create(const char *pszFileName){
    return (BaseBullet*)super::create(pszFileName);
}


void BaseBullet::cleanupSprite()
{
    animationSprite->removeFromParentAndCleanup(true);
}


