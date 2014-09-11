//
//  MonsterData.h
//  legend
//
//  Created by Yan Wei on 2014/09/03.
//
//

#ifndef __legend__MonsterData__
#define __legend__MonsterData__

#include "cocos2d.h"
USING_NS_CC;

class MonsterData{
    
    private:
        CCSprite *monster_;
    
public:
    void setMonster(CCSprite *monst);
    CCSprite* getMonster();
    
};
#endif
