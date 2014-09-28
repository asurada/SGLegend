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
    attack_1 = 1,
    attack_2 = 2,
    attack_3 = 3,
    attack_4 = 4,
    attack_5 = 5,
    attack_6 = 6,
    attack_7 = 7,
    attack_8 = 8,
    effect_1 = 101,

    
};

class Bullet : public cocos2d::CCSprite{
private:
    typedef CCSprite super;
    string _strImage;
    string _strPlist;
    string _strImgSplit;
    string _format;
    int    _frameCount;
    int    wound_r;
    int    wound_g;
    int    wound_b;
public:
    void setExplode(bulletType _type);
    const char* getImage();
    const char* getPlist();
    const char* getImageSplit();
    const char* getFormat();
    int getWound_r();
    int getWound_g();
    int getWound_b();
    int getFrameCount();

    
    CCSprite* animationSprite;
    void cleanupSprite();
    static Bullet* create(const char *pszFileName);
   // virtual void explode() = 0;

};

#endif /* defined(__legend__BaseBullet__) */
