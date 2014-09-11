//
//  StoneData.h
//  legend
//
//  Created by Yan Wei on 2014/09/03.
//
//

#ifndef __legend__StoneData__
#define __legend__StoneData__

#include "cocos2d.h"
USING_NS_CC;

class StoneData : public CCSprite{
    protected:
        int power;
        int speed;
        int hp;
        int magic;
        int tag;
        int fire;
        int water;
        int soil;
        int metal;
        int wood;
    
    
    public:
        void setPower(int _power);
        int getPower();
        void setSpeed(int _speed);
        int getSpeed();
        void setHp(int _hp);
        int getHp();
        void setMagic(int _magic);
        int getMagic();
        void setFire(int _fire);
        void setWater(int _water);
        void setSoil(int _soil);
        void setMetal(int _metal);
        void setWood(int _wood);
        int getFire();
        int getWater();
        int getSoil();
        int getMetal();
        int getWood();
    
};

#endif
