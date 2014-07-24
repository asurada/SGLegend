//
//  AnalysisHexagon.h
//  legend
//
//  Created by 厳 巍 on 2014/05/25.
//
//

#ifndef __legend__AnalysisHexagon__
#define __legend__AnalysisHexagon__
#include "AnalysisLogic.h"

class AnalysisHexagon:public AnalysisLogic{
public :
    AnalysisHexagon *logic;
    AnalysisHexagon();
    ~AnalysisHexagon();
    AnalysisShape recogize(CCArray *linkballs);
    void init(CCLayer *_parent,CCArray *container);
};

#endif /* defined(__legend__AnalysisHexagon__) */
