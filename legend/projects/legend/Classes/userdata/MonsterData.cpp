//
//  MonsterData.cpp
//  legend
//
//  Created by Yan Wei on 2014/09/03.
//
//

#include "MonsterData.h"


void MonsterData::setMonster(CCSprite *monst){
    this->monster_ = monst;
}


CCSprite* MonsterData::getMonster(){
    return monster_;
}
