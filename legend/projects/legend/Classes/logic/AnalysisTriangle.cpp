//
//  AnalysisTriangle.cpp
//  legend
//
//  Created by 厳 巍 on 2014/05/25.
//
//

#include "AnalysisTriangle.h"



AnalysisShape AnalysisTriangle::recogize(CCArray *linkballs){

    AnalysisShape result = noresult;
    if(linkballs->count() == 4){
        return triangle;
    }
    return result;
}