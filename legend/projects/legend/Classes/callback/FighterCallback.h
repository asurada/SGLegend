//
//  FighterCallback.h
//  legend
//
//  Created by Yan Wei on 2014/07/28.
//
//

#ifndef legend_FighterCallback_h
#define legend_FighterCallback_h

#include "Bullet.h"

class FighterCallback{
    
public:
    virtual void onInitBullet(Bullet* bullet) = 0;
    virtual void onFire(Bullet* bullet) = 0;
};

#endif
