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


AnalysisShape AnalysisHexagon::recogize(CCArray *linkballs){
    int preTag = -1;
    int sameInterval = 0;
    int starCount = 0;
    int triangleCount = 0;
    int reverseTriangel = 0;
    AnalysisShape result = noresult;
    for(int i=0; i < linkballs->count(); i++)
    {
        CCSprite *sprite = (CCSprite *)linkballs->objectAtIndex(i);
        int tag = sprite->getTag();
        //        CCLOG("tag = %d", tag);
        //        CCLOG("preTag = %d", preTag);
        if(preTag == -1){
            preTag = tag;
        }else{
            //6角形判断
            if(linkballs->count() == 6){
                if(abs(preTag-tag)==1 || abs(preTag-tag)==5){
                    sameInterval++;
                }
                preTag = tag;
            }else if(linkballs->count() == 5){//星形
                if(abs(preTag-tag) < 2){
                    return noresult;
                }
                if(abs(preTag-tag) > 1 && (preTag%3 == tag%3) ){
                    starCount++;
                }else if(abs(preTag-tag)==3 || abs(preTag-tag)==2){
                    sameInterval++;
                }
                preTag = tag;
            }else if(linkballs->count() == 4){//四角
                if(tag == 1 || tag == 4)
                    return noresult;
                if(abs(preTag-tag) == 3){
                    return cross;
                }else{
                    return rect;
                }
                preTag = tag;
            }else if(linkballs->count() == 3){//三角
                if(tag == 1 || tag == 3 || tag == 5){
                    triangleCount++;
                }
                if(tag == 2 || tag == 4 || tag == 6){
                    reverseTriangel++;
                }
                if(triangleCount == 3){
                    return equaltriangle;
                }
                if(reverseTriangel == 3){
                    return reverse_equaltriangle;
                }
                return triangle;
            }
        }
    }

    if(sameInterval == 6 && linkballs->count() == 6){
        return hexagon;
    }
    
    if(starCount == 2 && linkballs->count() == 5){
        return star;
    }
    
    if(sameInterval == 5 && linkballs->count() == 6){
        return star;
    }
    return result;
    
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
    
    ballPos_1 = ccp(x1, y1);
    ballPos_2 = ccp(x2, y2);
    ballPos_3 = ccp(x3, y3);
    ballPos_4 = ccp(x4, y4);
    ballPos_5 = ccp(x5, y5);
    ballPos_6 = ccp(x6, y6);


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

    BallBase* pSprite_6 =(BallBase *)spritesContainer->objectAtIndex(5);
    pSprite_6->setTag(ENUM_PST_6);
    pSprite_6->setPosition(ballPos_6);
    parent->addChild(pSprite_6);

}