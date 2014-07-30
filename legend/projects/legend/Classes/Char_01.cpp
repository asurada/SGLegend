//
//  Char_01.cpp
//  legend
//
//  Created by Yan Wei on 2014/07/24.
//
//

#include "Char_01.h"
#include "FireBullet.h"


Char_01* Char_01::create(const char *pszFileName){
    return (Char_01*)super::create(pszFileName);
}

void Char_01::attack(const char *bulletName){
    BaseBullet *bullet = FireBullet::create(bulletName);
    bullet->setPosition(this->getPosition());
    this->getParent()->addChild(bullet,5);
 
    if(fighterCallback){
        fighterCallback->onInitBullet(bullet);
    }
    
 //   bullet->init(getWorld());
//    bullet->fire();
}