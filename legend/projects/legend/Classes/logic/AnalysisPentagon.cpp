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
            //5角形判断
            if(linkballs->count() == 6){
                if(abs(preTag-tag)== 1 || abs(preTag-tag)==4){
                    sameInterval++;
                }
                preTag = tag;
            }
        }
    }
    
    if(sameInterval == 5 && linkballs->count() == 6){
        return pentagon;
    }
    
    //    if(logic!= NULL){
    //        return logic->recogize(linkballs);
    //    }
    return result;
    
}