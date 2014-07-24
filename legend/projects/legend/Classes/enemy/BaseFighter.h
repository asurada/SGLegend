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
#include "Box2D.h"
#include "BaseEnemyEffect.h"
#include "BaseBullet.h"
#include "ShapeConst.h"

class BaseFighter : public cocos2d::CCSprite{
private:
    BaseEnemyEffect* _effect;
    BaseFighter* _target;
    typedef CCSprite super;
    cocos2d::CCLayer* _parent;
    int hp;
    int magic;
    int exp;
public:
    virtual void init(int hp,int magic,int exp) =0;
    static BaseFighter* create(const char *pszFileName);
    virtual void explode() = 0;
    virtual void attack(const char *bulletName,b2World &world);
    virtual void enemyExplode() = 0;
    virtual void defend() = 0;
    virtual void die() = 0;
    virtual void refreshHp(int hp) = 0;
    virtual void powerUp() = 0;
    virtual void speedUp() = 0;
    virtual void magicUp() = 0;
    virtual void levelUp() = 0;
    virtual BaseFighter* transform() = 0;
    virtual BaseFighter* evolve() = 0;
    void setTarget(BaseFighter* target);
    
};

#endif /* defined(__legend__BaseEnemy__) */
