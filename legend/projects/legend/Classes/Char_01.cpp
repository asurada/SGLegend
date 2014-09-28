//
//  Char_01.cpp
//  legend
//
//  Created by Yan Wei on 2014/07/24.
//
//

#include "Char_01.h"




Char_01* Char_01::create(const char *pszFileName){
    return (Char_01*)CCSprite::create(pszFileName);
}


Char_01::Char_01(const char *pszFileName){
    _hp  =   100;
    _maxHp = 100;
    x= 0;
    y =0;
    height = -80;
    _char = Char_01::create(pszFileName);
}

Char_01::~Char_01(){
    
}
const char* Char_01::getBulletName(bulletType _type){
    string result;
    switch (_type) {
        case attack_1:
            result = "fire_1.png";
            radius= 50.0,
            density = 0.4,
            friction = 0.5,
            restitution = 0.6;
            break;
        case attack_2:
            result = "fire_2.png";
            radius= 50.0,
            density = 0.4,
            friction = 0.5,
            restitution = 0.6;
        case attack_3:
            result = "fire_1.png";
            radius= 50.0,
            density = 0.4,
            friction = 0.5,
            restitution = 0.6;
            break;
        case attack_4:
            result = "fire_2.png";
            radius= 50.0,
            density = 0.4,
            friction = 0.5,
            restitution = 0.6;
        case attack_5:
            result = "fire_1.png";
            radius= 50.0,
            density = 0.4,
            friction = 0.5,
            restitution = 0.6;
            break;
        case attack_6:
            result = "fire_2.png";
            radius= 50.0,
            density = 0.4,
            friction = 0.5,
            restitution = 0.6;
        case effect_1:
            result = "fire_2.png";
            radius= 50.0,
            density = 0.4,
            friction = 0.5,
            restitution = 0.6;
        default:
            break;
    }
    return result.c_str();
}

