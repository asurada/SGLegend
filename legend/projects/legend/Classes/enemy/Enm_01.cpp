//
//  Enm_01.cpp
//  legend
//
//  Created by Yan Wei on 2014/07/24.
//
//

#include "Enm_01.h"


Enm_01* Enm_01::create(const char *pszFileName){
    return (Enm_01*)CCSprite::create(pszFileName);
}


Enm_01::Enm_01(const char *pszFileName){
    _char = Enm_01::create(pszFileName);
    _hpGauge = GaugeSprite::nodeWithBarFile("ips_co_gg_gr@2x.png",100.0f,BARDIR_LEFT);
    this->addChild(_hpGauge,2);
}

Enm_01::~Enm_01(){
   
}


bool Enm_01::init(){
    
    return true;
}


const char* Enm_01::getBulletName(bulletType _type){
    string result;
    switch (_type) {
        case fire:
            result = "fire_1.png";
            radius= 50.0,
            density = 0.4,
            friction = 0.5,
            restitution = 0.6;
            break;
        default:
            break;
    }
    return result.c_str();
}
