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
    if(starCount == 2 && linkballs->count() == 6){
        return star;
    }
    
    return result;

}