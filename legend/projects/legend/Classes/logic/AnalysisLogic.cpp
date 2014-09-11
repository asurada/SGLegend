//
//  AnalysisLogic.cpp
//  legend
//
//  Created by 厳 巍 on 2014/05/25.
//
//

#include "AnalysisLogic.h"




AnalysisLogic::AnalysisLogic(){

}


AnalysisLogic::AnalysisLogic(int formate){
   
}


ResultData* AnalysisLogic::recogize(CCArray *linkballs){
    ResultData *result = new ResultData();
    result->setShape(noresult);
    return result;
}

CCArray *AnalysisLogic::getContainer(){
    return spritesContainer;
}