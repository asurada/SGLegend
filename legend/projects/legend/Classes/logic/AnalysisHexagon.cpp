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
    
    
    
    //    if(logic!= NULL){
    //        return logic->recogize(linkballs);
    //    }
    return result;
    
}