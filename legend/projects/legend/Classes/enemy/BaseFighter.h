//
//  BaseEnemy.h
//  legend
//
//  Created by Yan Wei on 2014/07/24.
//
//

#ifndef __legend__BaseEnemy__
#define __legend__BaseEnemy__
#include "cocos2d.h"
#include "BaseEnemyEffect.h"

class BaseFighter : public cocos2d::CCSprite{
private:
    BaseEnemyEffect* effect;
    typedef CCSprite super;
public:
    virtual void init(const char *pName) =0;
    static BaseFighter* create(const char *pszFileName);
    virtual void explode() = 0;
    virtual void attack() = 0;
    virtual void defend() = 0;
    virtual void die() = 0;
    virtual void refreshHp(int hp) = 0;
    virtual void powerUp() = 0;
    virtual void speedUp() = 0;
    virtual void magicUp() = 0;
    virtual void levelUp() = 0;
    virtual BaseFighter* transform() = 0;
    virtual BaseFighter* evolve() = 0;
    
};

#endif /* defined(__legend__BaseEnemy__) */
