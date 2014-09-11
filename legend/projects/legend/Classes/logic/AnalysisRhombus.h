//
//  AnalysisRhombus.h
//  legend
//
//  Created by 厳 巍 on 2014/05/25.
//
//

#ifndef __legend__AnalysisRhombus__
#define __legend__AnalysisRhombus__
#include "AnalysisLogic.h"
#include "ballBase.h"

class AnalysisRhombus:public AnalysisLogic{
public :
    AnalysisRhombus *logic;
    AnalysisRhombus();
    ~AnalysisRhombus();
    void init(CCLayer *_parent,CCArray *container);
    ResultData* recogize(CCArray *linkballs);
};

#endif /* defined(__legend__AnalysisRhombus__) */
