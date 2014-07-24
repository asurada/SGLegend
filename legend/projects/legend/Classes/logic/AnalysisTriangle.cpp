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


void AnalysisTriangle::init(CCLayer *_parent,CCArray *container){
    if(container->count() != 3) return;
    parent = _parent;
    spritesContainer = container;
    spritesContainer->retain();
   
    CCSize visibleSize = parent->getContentSize();
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
    
    BallBase* pSprite_1 = (BallBase *)spritesContainer->objectAtIndex(0);   //BallBase::create("bll_01.png");
    pSprite_1->setPosition(ballPos_1);
    pSprite_1->setTag(ENUM_PST_1);
    parent->addChild(pSprite_1);
    
    BallBase* pSprite_2 = (BallBase *)spritesContainer->objectAtIndex(1);
    pSprite_2->setTag(ENUM_PST_2);
    pSprite_2->setPosition(ballPos_2);
    parent->addChild(pSprite_2);
    
    BallBase* pSprite_3 = (BallBase *)spritesContainer->objectAtIndex(2);
    pSprite_3->setTag(ENUM_PST_3);
    pSprite_3->setPosition(ballPos_3);
    parent->addChild(pSprite_3);
    

}