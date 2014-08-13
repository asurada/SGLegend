//
//  Char_01.cpp
//  legend
//
//  Created by Yan Wei on 2014/07/24.
//
//

#include "Char_01.h"


Char_01::Char_01(const char *pszFileName){
    _char = CCSprite::create(pszFileName);
}



const char* Char_01::getBulletName(bulletType _type){
    string result;
    switch (_type) {
        case fire:
            result = "fire_1.png";
            radius= 50.0,
            density = 0.4,
            friction = 0.5,
            restitution = 0.6;
            break;
        case water:
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

