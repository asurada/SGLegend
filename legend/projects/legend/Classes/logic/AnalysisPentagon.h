//
//  AnalysisPentagon.h
//  legend
//
//  Created by 厳 巍 on 2014/05/25.
//
//

#ifndef __legend__AnalysisPentagon__
#define __legend__AnalysisPentagon__
#include "AnalysisLogic.h"
#include "ballBase.h"

class AnalysisPentagon:public AnalysisLogic{
public :
    AnalysisPentagon *logic;
    AnalysisPentagon();
    ~AnalysisPentagon();
    ResultData* recogize(CCArray *linkballs);
    void init(CCLayer *_parent,CCArray *container);
};


#endif /* defined(__legend__AnalysisPentagon__) */
