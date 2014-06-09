//
//  AnalysisStar.cpp
//  legend
//
//  Created by 厳 巍 on 2014/05/25.
//
//

#include "AnalysisStar.h"


AnalysisStar::AnalysisStar(){
    
}

AnalysisShape AnalysisStar::recogize(CCArray *linkballs){
    int preTag = -1;
    int starCount = 0;
    int sameInterval = 0;
    AnalysisShape result = noresult;
    

    if(linkballs->count() != 6){
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
            //星形判断
            if(linkballs->count() == 6){
                if(abs(preTag-tag) < 2){
                    return noresult;
                }
                if(abs(preTag-tag) > 1 && (preTag%3 == tag%3) ){
                    starCount++;
                }else if(abs(preTag-tag)==3 || abs(preTag-tag)==2){
                    sameInterval++;
                }
                preTag = tag;
            }
            
        }
    }
    if(starCount == 2 && linkballs->count() == 6){
        return star;
    }
    
    if(sameInterval == 5 && linkballs->count() == 6){
        return star;
    }

//    if(logic!= NULL){
//        return logic->recogize(linkballs);
//    }
    return result;

}