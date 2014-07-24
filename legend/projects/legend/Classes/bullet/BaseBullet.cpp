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


void BaseBullet::init(b2World* world){
   
    bodyDef.type = b2_dynamicBody;    //動的な物体に
    bodyDef.position.Set(this->getPosition().x/PTM_RATIO_WIN, this->getPosition().y/PTM_RATIO_WIN);   //位置を設定
    bodyDef.userData = this;
    body = world->CreateBody(&bodyDef);
    //b2CircleShape circle;//形を定義するクラス
    circle.m_radius = 50/PTM_RATIO;    //半径を50pxに
   // b2FixtureDef fixtureDef;    //Fixtureの定義を入れる構造体
    fixtureDef.shape = &circle;    //形
    fixtureDef.density = 0.4;      //密度
    fixtureDef.friction = 0.5;     //摩擦率
    fixtureDef.restitution = 0.6;  //反発係数
    body->CreateFixture(&fixtureDef);  //
    body->SetBullet(true);
    
}

void BaseBullet::fire(){
//    b2Vec2 force = b2Vec2(0, 30);
//    body->ApplyLinearImpulse(force, body->GetPosition());
}

