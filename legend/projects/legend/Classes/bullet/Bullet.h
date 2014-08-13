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

enum bulletType{
    fire = 0,
    water,
};

class Bullet : public cocos2d::CCSprite{
private:
    typedef CCSprite super;
    string _strImage;
    string _strPlist;
    string _strImgSplit;
    int    _frameCount;
public:
    void setExplode(bulletType _type);
    const char* getImage();
    const char* getPlist();
    const char* getImageSplit();
    int getFrameCount();
    
    CCSprite* animationSprite;
    void cleanupSprite();
    static Bullet* create(const char *pszFileName);
   // virtual void explode() = 0;

};

#endif /* defined(__legend__BaseBullet__) */
