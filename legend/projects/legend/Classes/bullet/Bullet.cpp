//
//  BaseBullet.cpp
//  legend
//
//  Created by Yan Wei on 2014/07/24.
//
//

#include "Bullet.h"
#include "ShapeConst.h"

Bullet* Bullet::create(const char *pszFileName){
    return (Bullet*)super::create(pszFileName);
}


void Bullet::cleanupSprite()
{
    animationSprite->removeFromParentAndCleanup(true);
}


void Bullet::setExplode(bulletType _type){
    switch (_type) {
        case attack_1:
            _strImage = "attack_1.png";
            _strPlist = "attack_1.plist";
            _strImgSplit = "attack_1";
            _frameCount = 10;
            _format = "%s_%d.png";
            wound_r = 255;
            wound_g = 0;
            wound_b = 0;
            break;
        case attack_2:
            _strImage = "attack_2.png";
            _strPlist = "attack_2.plist";
            _strImgSplit = "attack_2";
            _format = "%s_%d.png";
            _frameCount = 9;
            wound_r = 0;
            wound_g = 255;
            wound_b = 0;
            break;
        case attack_3:
            _strImage = "attack_3.png";
            _strPlist = "attack_3.plist";
            _strImgSplit = "attack_3";
            _format = "%s_%d.png";
            _frameCount = 10;
            wound_r = 0;
            wound_g = 0;
            wound_b = 255;
            break;
        case attack_4:
            _strImage = "attack_4.png";
            _strPlist = "attack_4.plist";
            _strImgSplit = "attack_4";
            _format = "%s_%d.png";
            _frameCount = 10;
            wound_r = 0;
            wound_g = 255;
            wound_b = 255;
            break;
        case attack_5:
            _strImage = "attack_5.png";
            _strPlist = "attack_5.plist";
            _strImgSplit = "attack_5";
            _format = "%s_%d.png";
            _frameCount = 10;
            wound_r = 255;
            wound_g = 0;
            wound_b = 255;
            break;
        case attack_6:
            _strImage = "attack_6.png";
            _strPlist = "attack_6.plist";
            _strImgSplit = "attack_6";
            _format = "%s_%d.png";
            _frameCount = 15;
            wound_r = 255;
            wound_g = 255;
            wound_b = 0;
            break;
        case effect_1:
            _strImage = "fire2.png";
            _strPlist = "fire2.plist";
            _strImgSplit = "fire";
            _format = "%s%d.png";
            _frameCount = 40;
        default:
            break;
    }
}


const char* Bullet::getPlist(){
   return _strPlist.c_str();
}


const char* Bullet::getImage(){
    return _strImage.c_str();
}


const char* Bullet::getImageSplit(){
    return _strImgSplit.c_str();
}

const char* Bullet::getFormat(){
    return _format.c_str();
}




int Bullet::getFrameCount(){
    return _frameCount;
}

int Bullet::getWound_r(){
    return wound_r;
}

int Bullet::getWound_g(){
    return wound_g;
}

int Bullet::getWound_b(){
    return wound_b;
}



