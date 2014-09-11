//
//  AnalysisRhombus.cpp
//  legend
//
//  Created by 厳 巍 on 2014/05/25.
//
//

#include "AnalysisRhombus.h"

AnalysisRhombus::AnalysisRhombus(){
    
}


ResultData* AnalysisRhombus::recogize(CCArray *linkballs){
//    int preTag = -1;
//    int sameInterval = 0;
    AnalysisShape result = noresult;
    ResultData *resultData = new ResultData();
    
//    if(linkballs->count() != 6){
//        //        if(logic! = NULL ){
//        //            return logic->recogize(linkballs);
//        //        }
//        return result;
//    }
//    
//    for(int i=0; i < linkballs->count(); i++)
//    {
//        CCSprite *sprite = (CCSprite *)linkballs->objectAtIndex(i);
//        int tag = sprite->getTag();
//        //        CCLOG("tag = %d", tag);
//        //        CCLOG("preTag = %d", preTag);
//        if(preTag == -1){
//            preTag = tag;
//        }else{
//            //5角形判断
//            if(linkballs->count() == 6){
//                if(abs(preTag-tag)== 1 || abs(preTag-tag)==4){
//                    sameInterval++;
//                }
//                preTag = tag;
//            }
//        }
//    }
//    
//    if(sameInterval == 5 && linkballs->count() == 6){
//        return pentagon;
//    }
//    
//    //    if(logic!= NULL){
//    //        return logic->recogize(linkballs);
//    //    }
    resultData->setShape(result);
    return resultData;
    
}


void AnalysisRhombus::init(CCLayer *_parent,CCArray *container){
    if(container->count() != 4)return;
    parent =_parent;
    spritesContainer = container;
    spritesContainer->retain();

    CCSize visibleSize = parent->getContentSize();
    float width =visibleSize.width;
    float height =visibleSize.height;
    float x1,x2,x3,x4,y1,y2,y3,y4;
    x1 = width  * 1.0 / 2.0;
    x3 = x1;
    y1 = height * 4.0 / 5.0;
    y3 = height * 1.0 / 5.0;
    y2 = height * 1.0 / 2.0;
    y4 = y2;
    x2 = width  * 4.0 / 5.0;
    x4 = width  * 1.0 / 5.0;
    CCPoint ballPos_1 = ccp(x1, y1);
    CCPoint ballPos_2 = ccp(x2, y2);
    CCPoint ballPos_3 = ccp(x3, y3);
    CCPoint ballPos_4 = ccp(x4, y4);

    StoneData* pSprite_1 = (StoneData *)spritesContainer->objectAtIndex(0);
    pSprite_1->setPosition(ballPos_1);
    pSprite_1->setTag(ENUM_PST_1);
    parent->addChild(pSprite_1);
        
    StoneData* pSprite_2 =  (StoneData *)spritesContainer->objectAtIndex(1);
    pSprite_2->setTag(ENUM_PST_2);
    pSprite_2->setPosition(ballPos_2);
    parent->addChild(pSprite_2);
        
    StoneData* pSprite_3 =  (StoneData *)spritesContainer->objectAtIndex(2);
    pSprite_3->setTag(ENUM_PST_3);
    pSprite_3->setPosition(ballPos_3);
    parent->addChild(pSprite_3);
        
    StoneData* pSprite_4 =  (StoneData *)spritesContainer->objectAtIndex(3);
    pSprite_4->setTag(ENUM_PST_4);
    pSprite_4->setPosition(ballPos_4);
    parent->addChild(pSprite_4);
    

}