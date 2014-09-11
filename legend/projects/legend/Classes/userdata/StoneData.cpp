//
//  StoneData.cpp
//  legend
//
//  Created by Yan Wei on 2014/09/03.
//
//

#include "StoneData.h"


void StoneData:: setPower(int _power){
    this->power = _power;
}

void StoneData::setSpeed(int _speed){
    this->speed = _speed;
}

void StoneData :: setHp(int _hp){
    this->hp = _hp;
}

void StoneData :: setMagic(int _magic){
    this->magic = _magic;
}


void StoneData :: setFire(int _fire){
    this->fire = _fire;
}
void StoneData :: setWater(int _water){
    this->water = _water;
    
}
void StoneData ::  setSoil(int _soil){
    this->soil = _soil;
}
void StoneData ::  setMetal(int _metal){
    this->metal = _metal;
}
void StoneData :: setWood(int _wood){
    this->wood = _wood;
}
int StoneData :: getFire(){
    return fire;
}
int StoneData :: getWater(){
    return water;
}
int StoneData :: getSoil(){
    return soil;
}
int StoneData :: getMetal(){
    return metal;
}
int StoneData :: getWood(){
    return wood;
}