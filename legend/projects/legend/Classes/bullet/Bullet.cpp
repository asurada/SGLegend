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
        case fire:
            _strImage = "fire2.png";
            _strPlist = "fire2.plist";
            _strImgSplit = "fire";
            _frameCount = 40;
            break;
        case water:
            _strImage = "fire.png";
            _strPlist = "fire.plist";
            _strImgSplit = "fire_";
            _frameCount = 20;
            break;
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


int Bullet::getFrameCount(){
    return _frameCount;
}