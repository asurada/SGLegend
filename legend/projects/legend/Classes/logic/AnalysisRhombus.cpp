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


AnalysisShape AnalysisRhombus::recogize(CCArray *linkballs){
//    int preTag = -1;
//    int sameInterval = 0;
    AnalysisShape result = noresult;
    
    
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
    return result;
    
}


void AnalysisRhombus::init(CCSize visibleSize){
    spritesContainer->removeAllObjects();

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
    
    
    pSprite_4 = CCSprite::create("bll_04.png");
    pSprite_4->setTag(ENUM_PST_4);
    pSprite_4->setPosition(ballPos_4);
    parent->addChild(pSprite_4);
    spritesContainer->addObject(pSprite_4);
    
}