//
//  AnalysisTriangle.cpp
//  legend
//
//  Created by 厳 巍 on 2014/05/25.
//
//

#include "AnalysisTriangle.h"



AnalysisShape AnalysisTriangle::recogize(CCArray *linkballs){

    AnalysisShape result = noresult;
    if(linkballs->count() == 3){
        return triangle;
    }
    return result;
}


void AnalysisTriangle::init(CCSize visibleSize){
    
    spritesContainer = CCArray::create();
    spritesContainer->retain();
    
    float width =visibleSize.width;
    float height =visibleSize.height;
    
    float x1,x2,x3,y1,y2,y3;
    
    x1 = width / 2.0;
    y1 = height *4.0/5.0;
    y2 = height /4;
    y3 = height /4;
    
    x2 = width / 2.0 - (y1-y2)/tan(60.0*M_PI/180.0);
    x3 = width / 2.0 + (y1-y2)/tan(60.0*M_PI/180.0);
    
    ballPos_1 = ccp(x1, y1);
    ballPos_2 = ccp(x2, y2);
    ballPos_3 = ccp(x3, y3);
    
    pSprite_1 = CCSprite::create("bll_01.png");
    pSprite_1->setPosition(ballPos_1);
    pSprite_1->setTag(ENUM_PST_1);
    parent->addChild(pSprite_1);
    
    pSprite_2 = CCSprite::create("bll_02.png");
    pSprite_2->setTag(ENUM_PST_2);
    pSprite_2->setPosition(ballPos_2);
    parent->addChild(pSprite_2);
    
    pSprite_3 = CCSprite::create("bll_03.png");
    pSprite_3->setTag(ENUM_PST_3);
    pSprite_3->setPosition(ballPos_3);
    parent->addChild(pSprite_3);
    
    spritesContainer->addObject(pSprite_1);
    spritesContainer->addObject(pSprite_2);
    spritesContainer->addObject(pSprite_3);
}