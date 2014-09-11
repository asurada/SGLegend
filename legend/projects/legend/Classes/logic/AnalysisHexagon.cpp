//
//  AnalysisHexagon.cpp
//  legend
//
//  Created by 厳 巍 on 2014/05/25.
//
//

#include "AnalysisHexagon.h"

AnalysisHexagon::AnalysisHexagon(){
    
}


ResultData* AnalysisHexagon::recogize(CCArray *linkballs){
    int preTag = -1;
    int sameInterval = 0;
    int starCount = 0;
    int triangleCount = 0;
    int reverseTriangel = 0;
    int value = 0;
    int order = 0;
    AnalysisShape shape = noresult;
    ResultData *resultData = new ResultData();
    for(int i=0; i < linkballs->count(); i++)
    {
        StoneData *sprite = (StoneData *)linkballs->objectAtIndex(i);
        int tag = sprite->getTag();
        
        if(preTag != -1){
            order = preTag-tag;
        }
        value += tag;
        
        
        CCLOG("tag : %d",tag);
        if(preTag == -1){
            preTag = tag;
        }else{
            //6角形判断
            if(linkballs->count() == 6){//6角形判断
                CCLOG("6角形判断");
                if(abs(preTag-tag)==1 || abs(preTag-tag)==5){
                    sameInterval++;
                }
                preTag = tag;
            }else if(linkballs->count() == 5){//星形
                CCLOG("星形判断");
                if(abs(preTag-tag) < 2){
                    shape = noresult;
                }
                if(abs(preTag-tag) > 1 && (preTag%3 == tag%3) ){
                    starCount++;
                }else if(abs(preTag-tag)==3 || abs(preTag-tag)==2){
                    sameInterval++;
                }
                preTag = tag;
            }else if(linkballs->count() == 4){//四角
                 CCLOG("四角判断");
                if(tag == 1 || tag == 4)
                    shape =  noresult;
                if(abs(preTag-tag) == 3){
                    shape =  cross;
                }else{
                    shape =  rect;
                }
                preTag = tag;
            }else if(linkballs->count() == 3){//三角
                CCLOG("三角判断");
                if(tag == 1 || tag == 3 || tag == 5){
                    triangleCount++;
                }
                if(tag == 2 || tag == 4 || tag == 6){
                    reverseTriangel++;
                }
                if(triangleCount == 3){
                    shape =  equaltriangle;
                }
                if(reverseTriangel == 3){
                    shape =  reverse_equaltriangle;
                }
                shape =  triangle;
            }
        }
    }

    if(sameInterval == 5 && linkballs->count() == 6){
        shape =  hexagon;
    }
    
    if(starCount == 2 && linkballs->count() == 5){
        shape =  star;
    }
    
    if(sameInterval == 5 && linkballs->count() == 5){
        shape =  star;
    }
    resultData->setShape(shape);
    resultData->setValue(value);
    return resultData;
    
}


void AnalysisHexagon::init(CCLayer *_parent,CCArray *container){
    parent = _parent;
    if(container->count() != 6)return;
    spritesContainer = container;
    spritesContainer->retain();
    
    CCSize visibleSize = parent->getContentSize();
    float width = visibleSize.width;
    float height = visibleSize.height;
    float x1,x2,x3,x4,x5,x6,y1,y2,y3,y4,y5,y6;
    float centerX,centerY;
    float distance;
    
    centerX = width / 2.0;
    centerY = height / 2.0;
    x1 = width  * 1.0 / 2.0;
    y1 = height * 7.0 / 8.0;
    
    distance = y1 - centerY;
    
    x2 = centerX + distance * sin(60 * M_PI /180);
    y2 = centerY + distance * cos(60 * M_PI /180);
    
    x3 = centerX + distance * sin(60 * M_PI /180);
    y3 = centerY - distance * cos(60 * M_PI /180);
    
    
    x4 = width  * 1.0 / 2.0;
    y4 = height * 1.0 / 8.0;
    
    x5 = centerX -(x3 - centerX);
    y5 = y3;
    
    x6 = centerX -(x2 - centerX);
    y6 = y2;
    
    CCPoint ballPos_1 = ccp(x1, y1);
    CCPoint ballPos_2 = ccp(x2, y2);
    CCPoint ballPos_3 = ccp(x3, y3);
    CCPoint ballPos_4 = ccp(x4, y4);
    CCPoint ballPos_5 = ccp(x5, y5);
    CCPoint ballPos_6 = ccp(x6, y6);


    StoneData* pSprite_1 = (StoneData *)spritesContainer->objectAtIndex(0);
    pSprite_1->setPosition(ballPos_1);
    pSprite_1->setTag(ENUM_PST_1);
    parent->addChild(pSprite_1);
        
    StoneData* pSprite_2 = (StoneData *)spritesContainer->objectAtIndex(1);
    pSprite_2->setTag(ENUM_PST_2);
    pSprite_2->setPosition(ballPos_2);
    parent->addChild(pSprite_2);
        
    StoneData* pSprite_3 = (StoneData *)spritesContainer->objectAtIndex(2);
    pSprite_3->setTag(ENUM_PST_3);
    pSprite_3->setPosition(ballPos_3);
    parent->addChild(pSprite_3);
    
    StoneData* pSprite_4 = (StoneData *)spritesContainer->objectAtIndex(3);
    pSprite_4->setTag(ENUM_PST_4);
    pSprite_4->setPosition(ballPos_4);
    parent->addChild(pSprite_4);

    StoneData* pSprite_5 = (StoneData *)spritesContainer->objectAtIndex(4);
    pSprite_5->setTag(ENUM_PST_5);
    pSprite_5->setPosition(ballPos_5);
    parent->addChild(pSprite_5);

    StoneData* pSprite_6 =(StoneData *)spritesContainer->objectAtIndex(5);
    pSprite_6->setTag(ENUM_PST_6);
    pSprite_6->setPosition(ballPos_6);
    parent->addChild(pSprite_6);

}