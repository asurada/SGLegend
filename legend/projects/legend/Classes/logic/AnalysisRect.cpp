//
//  AnalysisRect.cpp
//  legend
//
//  Created by 厳 巍 on 2014/05/25.
//
//

#include "AnalysisRect.h"

AnalysisShape AnalysisRect::recogize(CCArray *linkballs){
    int preTag = -1;
    int starCount = 0;
    AnalysisShape result = noresult;
    
    if(linkballs->count() != 5){
        return result;
    }
    
    for(int i=0; i < linkballs->count(); i++)
    {
        CCSprite *sprite = (CCSprite *)linkballs->objectAtIndex(i);
        int tag = sprite->getTag();
        CCLOG("tag = %d", tag);
        tag = tag%3;
        if(preTag == -1){
            preTag = tag;
        }else{
            //星形判断
            if(linkballs->count() == 5){
                result = star;
                if(preTag == tag ){
                    starCount++;
                    preTag = tag;
                }else{
                    preTag = tag;
                }
            }
        }
        
    }
    if(starCount == 2 && linkballs->count() == 5){
        return star;
    }
    
    return result;

}

void AnalysisRect::init(CCLayer *_parent,CCArray *container){
    if(container->count() != 4)return;
    parent =_parent;
    spritesContainer = container;
    spritesContainer->retain();
    
    CCSize visibleSize = parent->getContentSize();
    float width =visibleSize.width;
    float height =visibleSize.height;
    float x1,x2,x3,x4,y1,y2,y3,y4;
    
    x1  = width * 3.0 / 4.0;
    x2 = x1;
    y1 = height * 3.0 / 4.0;
    y4 = y1;
    y2 = height * 1.0 / 4.0;
    y3 = y2;
    x3 = width  * 1.0 / 4.0;
    x4 = x3;
    
    CCPoint ballPos_1 = ccp(x1, y1);
    CCPoint ballPos_2 = ccp(x2, y2);
    CCPoint ballPos_3 = ccp(x3, y3);
    CCPoint ballPos_4 = ccp(x4, y4);
    
   
    BallBase* pSprite_1 =  (BallBase *)spritesContainer->objectAtIndex(0);
    pSprite_1->setPosition(ballPos_1);
    pSprite_1->setTag(ENUM_PST_1);
    parent->addChild(pSprite_1);
        
    BallBase* pSprite_2 =  (BallBase *)spritesContainer->objectAtIndex(1);
    pSprite_2->setTag(ENUM_PST_2);
    pSprite_2->setPosition(ballPos_2);
    parent->addChild(pSprite_2);
        
    BallBase* pSprite_3 = (BallBase *)spritesContainer->objectAtIndex(2);
    pSprite_3->setTag(ENUM_PST_3);
    pSprite_3->setPosition(ballPos_3);
    parent->addChild(pSprite_3);
    
    BallBase* pSprite_4 = (BallBase *)spritesContainer->objectAtIndex(3);
    pSprite_4->setTag(ENUM_PST_4);
    pSprite_4->setPosition(ballPos_4);
    parent->addChild(pSprite_4);
    


    
}