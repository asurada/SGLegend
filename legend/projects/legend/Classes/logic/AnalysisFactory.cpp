//
//  AnalysisFactory.cpp
//  legend
//
//  Created by 厳 巍 on 2014/05/27.
//
//

#include "AnalysisFactory.h"
#include "ShapeConst.h"
#include "AnalysisTriangle.h"
#include "AnalysisRect.h"
#include "AnalysisRhombus.h"
#include "AnalysisPentagon.h"
#include "AnalysisHexagon.h"

ResultData* AnalysisFactory::analysis(int &formation,CCArray* linkballs){

    AnalysisShape result = noresult;
    CCLog("formation = %d",formation);
    switch (formation) {
        case TRIANGLE:
            logic = new AnalysisTriangle();
            break;
        case RECT:
            logic = new AnalysisRect();
            break;
        case RHOMBUS:
            logic = new AnalysisRhombus();
            break;
        case PENTAGON:
            logic = new AnalysisPentagon();
            break;
        case HEXAGON:
            logic = new AnalysisHexagon();
            break;
        default:
            break;
    }

    if(logic != NULL){
        return  logic->recogize(linkballs);
    }
    
    return NULL;


}