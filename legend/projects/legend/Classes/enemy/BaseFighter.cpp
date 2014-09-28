//
//  BaseEnemy.cpp
//  legend
//
//  Created by Yan Wei on 2014/07/24.
//
//

#include "BaseFighter.h"
#define HEIGHT 350



void BaseFighter::setPosition(CCLayer* _layer,CCPoint _position,int zOrder){
    _parent = _layer;
    _char->setPosition(_position);
    _char->setAnchorPoint(ccp(0.5, 0.5));
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
    _bg->setPosition(ccp(pos.x, pos.y-180));
    _parent->addChild(_bg,0);
    
    _hpGauge = CCSprite::create("ips_co_gg_bt@2x.png");
    
    bgHpPer = (float)_bg->getContentSize().width/(float)_hpGauge->getContentSize().width;
    _hpGauge->setAnchorPoint(ccp(0.0f, 0.5f));
    _hpGauge->setScaleX(bgHpPer*this->getPercent());
    _hpGauge->setPosition(ccp(pos.x - _bg->getContentSize().width/2, pos.y-180));
    _parent->addChild(_hpGauge,1);
    
    
    _mgGauge = CCSprite::create("ips_co_bl_bt@2x.png");
    
    bgHpPer = (float)_bg->getContentSize().width/(float)_mgGauge->getContentSize().width;
    _mgGauge->setAnchorPoint(ccp(0.0f, 0.5f));
    _mgGauge->setScaleX(bgHpPer*this->getPercent());
    _mgGauge->setPosition(ccp(pos.x - _bg->getContentSize().width/2, pos.y-189));
    _parent->addChild(_mgGauge,1);
}


double_t BaseFighter::getPercent(){
    float per =  _hp / _maxHp;
    return per;
}

void BaseFighter::changeSize(CCSize &size){
    _char->setContentSize(size);
}

void BaseFighter::changeRect(CCRect &rect){
    _char->setTextureRect(rect);
}

bool BaseFighter::appear(){
    CCSize size = _char->boundingBox().size;
    _char->setVisible(true);
    if(height < HEIGHT){
        y = (0-height)/2;
        height = height + 8;
        CCRect rect = CCRectMake(0,y,size.width, height);
        _char->setTextureRect(rect);
        return true;
    }
    return false;
}

bool BaseFighter::disappear(){
    CCSize size = _char->boundingBox().size;
    if(height > 0){
        y = (0-height)/2;
        height = height - 8;
        CCRect rect = CCRectMake(0,y,size.width, height);
        _char->setTextureRect(rect);
        return true;
    }
    return false;
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


void BaseFighter::setVisible(bool isVisible){
    _char->setVisible(isVisible);
}

