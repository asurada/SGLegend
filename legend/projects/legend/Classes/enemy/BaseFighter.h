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
#include "Bullet.h"
#include "ShapeConst.h"
#include "Box2D.h"
#include "FighterCallback.h"
#include "GaugeSprite.h"

class BaseFighter : public CCSprite{
private:
   

    
protected:
     CCSprite* _char;
     CCSprite* _hpGauge;
     CCSprite* _magicGauge;
     CCLayer* _parent;
     int hp;
     int magic;
     int exp;
     float radius, density, friction, restitution;
     BaseEnemyEffect* _effect;
     BaseFighter* _target;
     b2World* world;
public:
//    virtual void init(int hp,int magic,int exp) =0;
    CCSprite* getChar();
    static BaseFighter* create(const char *pszFileName);
    CCSprite* attack(bulletType _type);
//    virtual void explode() = 0;
//    virtual void enemyExplode() = 0;
//    virtual void defend() = 0;
//    virtual void die() = 0;
//    virtual void refreshHp(int hp) = 0;
//    virtual void powerUp() = 0;
//    virtual void speedUp() = 0;
//    virtual void magicUp() = 0;
//    virtual void levelUp() = 0;
//    virtual BaseFighter* transform() = 0;
//    virtual BaseFighter* evolve() = 0;
    void setPosition(CCLayer* _layer,CCPoint _position,int zOrder);
    virtual const char* getBulletName(bulletType _type) =0;
    float getRadius();
    float getDensity();
    float getFriction();
    float getRestitution();
    
//    void setTarget(BaseFighter* target);
    CC_SYNTHESIZE(FighterCallback*, fighterCallback, Delegate);
};

#endif /* defined(__legend__BaseEnemy__) */
