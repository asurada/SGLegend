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

class AnalysisPentagon:public AnalysisLogic{
public :
    AnalysisPentagon *logic;
    AnalysisPentagon();
    ~AnalysisPentagon();
    AnalysisShape recogize(CCArray *linkballs);
    void init(CCLayer *_parent);
};


#endif /* defined(__legend__AnalysisPentagon__) */
