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

bool BaseFighter::init(){
    super.init();
    return true;
}


void BaseFighter::initGauge(CCPoint pos){
    _bg = CCSprite::create("ips_co_gg_gr@2x.png");
    _bg->setPosition(ccp(pos.x, pos.y-100));
    _parent->addChild(_bg,0);
    
    _hpGauge = CCSprite::create("ips_co_gg_bt@2x.png");
    
    bgHpPer = (float)_bg->getContentSize().width/(float)_hpGauge->getContentSize().width;
    _hpGauge->setAnchorPoint(ccp(0.0f, 0.5f));
    _hpGauge->setScaleX(bgHpPer*this->getPercent());
    _hpGauge->setPosition(ccp(pos.x - _bg->getContentSize().width/2, pos.y-100));
    _parent->addChild(_hpGauge,1);
}


double_t BaseFighter::getPercent(){
    float per =  _hp / _maxHp;
    return per;
}


void BaseFighter::updateHpBar(double_t hp){
    if(_hpGauge != NULL){
        if(_hp>  hp){
            _hp -= hp;
            _hpGauge->setScaleX(bgHpPer *this->getPercent());
        }else{
            _hp = 0;
        }
    }
}


