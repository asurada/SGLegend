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



class BaseBullet : public cocos2d::CCSprite{
private:
    typedef CCSprite super;
    b2BodyDef bodyDef; //b2BodyDef構造体
    b2Body *body;
    b2FixtureDef fixtureDef;//Fixtureの定義を入れる構造体
    b2CircleShape circle;
    float density;
    float friction;     //摩擦率
    float restitution = 0.6;  //反発係数
public:
    static BaseBullet* create(const char *pszFileName);
    void init(b2World* world);
    void fire();

};

#endif /* defined(__legend__BaseBullet__) */
