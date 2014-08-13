//
//  BaseEnemy.cpp
//  legend
//
//  Created by Yan Wei on 2014/07/24.
//
//

#include "BaseFighter.h"


void BaseFighter::setPosition(CCLayer* _layer,CCPoint _position,int zOrder){
    _parent = _layer;
    _char->setPosition(_position);
    _parent->addChild(_char,zOrder);
}


CCSprite* BaseFighter::getChar(){
    return _char;
}


CCSprite* BaseFighter::attack(bulletType _type){
    CCSprite* bullet = CCSprite::create(getBulletName(_type));
    bullet->setTag(_type);
    bullet->setPosition(_char->getPosition());
    _parent->addChild(bullet,4);
    return bullet;
}


float BaseFighter::getRadius(){
    return radius;
}
float BaseFighter::getDensity(){
    return density;
}
float BaseFighter::getFriction(){
    return friction;
}
float BaseFighter::getRestitution(){
    return restitution;
}