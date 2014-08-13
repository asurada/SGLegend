//
//  Enm_01.h
//  legend
//
//  Created by Yan Wei on 2014/07/24.
//
//

#ifndef __legend__Enm_01__
#define __legend__Enm_01__
#include "BaseFighter.h"

class Enm_01 :public BaseFighter{
private:
    typedef CCSprite super;
public:
    Enm_01(const char *pszFileName);
   // ~Enm_01();
   // virtual CCSprite *attack(bulletType _type);
    const char* getBulletName(bulletType _type);
    
    
};

#endif /* defined(__legend__Enm_01__) */
