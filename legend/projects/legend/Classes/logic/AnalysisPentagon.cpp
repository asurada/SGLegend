//
//  AnalysisPentagon.cpp
//  legend
//
//  Created by 厳 巍 on 2014/05/25.
//
//

#include "AnalysisPentagon.h"

AnalysisPentagon::AnalysisPentagon(){
    
}


AnalysisShape AnalysisPentagon::recogize(CCArray *linkballs){
    int preTag = -1;
    int sameInterval = 0;
    AnalysisShape result = noresult;
    
    
    if(linkballs->count() != 5){
        //        if(logic! = NULL ){
        //            return logic->recogize(linkballs);
        //        }
        return result;
    }
    
    for(int i=0; i < linkballs->count(); i++)
    {
        CCSprite *sprite = (CCSprite *)linkballs->objectAtIndex(i);
        int tag = sprite->getTag();
        //        CCLOG("tag = %d", tag);
        //        CCLOG("preTag = %d", preTag);
        if(preTag == -1){
            preTag = tag;
        }else{
            //5角形判断
            if(linkballs->count() == 5){
                if(abs(preTag-tag)== 1 || abs(preTag-tag)==4){
                    sameInterval++;
                }
                preTag = tag;
            }
        }
    }
    
    if(sameInterval == 5 && linkballs->count() == 5){
        return pentagon;
    }
    
    //    if(logic!= NULL){
    //        return logic->recogize(linkballs);
    //    }
    return result;
    
}


void AnalysisPentagon::init(CCLayer *_parent,CCArray *container){
    if(container->count() != 5)return;
    parent =_parent;
    spritesContainer = container;
    spritesContainer->retain();
    CCSize visibleSize = parent->getContentSize();
    float width = visibleSize.width;
    float height = visibleSize.height;
    float x1,x2,x3,x4,x5,y1,y2,y3,y4,y5;
    float centerX,centerY;
    float distance;
    
    centerX = width / 2.0;
    centerY = height / 2.0;
    
    x1 = width  * 1.0 / 2.0;
    y1 = height * 6.0 / 7.0;
    distance = y1 - centerY;
    x2 = centerX + cos(18.0*M_PI/180.0)*(distance);
    y2 = centerY + sin(18.0*M_PI/180.0)*(distance);
    
    x3 = centerX + cos(54.0*M_PI/180.0)*(distance);
    y3 = centerY - sin(54.0*M_PI/180.0)*(distance);
    
    x4 = centerX - (x3 - centerX);
    y4 = y3;
    
    x5 = centerX -(x2 - centerX);
    y5 = y2;
    
    ballPos_1 = ccp(x1, y1);
    ballPos_2 = ccp(x2, y2);
    ballPos_3 = ccp(x3, y3);
    ballPos_4 = ccp(x4, y4);
    ballPos_5 = ccp(x5, y5);
 

    BallBase* pSprite_1 = (BallBase *)spritesContainer->objectAtIndex(0);
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
        
   
    BallBase* pSprite_4 = (BallBase *)spritesContainer->objectAtIndex(3);
    pSprite_4->setTag(ENUM_PST_4);
    pSprite_4->setPosition(ballPos_4);
    parent->addChild(pSprite_4);
    

    BallBase* pSprite_5 = (BallBase *)spritesContainer->objectAtIndex(4);
    pSprite_5->setTag(ENUM_PST_5);
    pSprite_5->setPosition(ballPos_5);
    parent->addChild(pSprite_5);
    
    
    

    
}