//
//  BaseBullet.h
//  legend
//
//  Created by Yan Wei on 2014/07/24.
//
//

#ifndef __legend__BaseBullet__
#define __legend__BaseBullet__

#include "cocos2d.h"
#include "Box2D.h"
USING_NS_CC;


class BaseBullet : public cocos2d::CCSprite{
private:
    typedef CCSprite super;
   
public:
    CCSprite* animationSprite;
    void cleanupSprite();
    static BaseBullet* create(const char *pszFileName);
   // virtual void explode() = 0;

};

#endif /* defined(__legend__BaseBullet__) */
