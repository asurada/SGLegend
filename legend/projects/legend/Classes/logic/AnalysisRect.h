//
//  AnalysisRect.h
//  legend
//
//  Created by 厳 巍 on 2014/05/25.
//
//

#ifndef __legend__AnalysisRect__
#define __legend__AnalysisRect__
#include "AnalysisLogic.h"

class AnalysisRect:public AnalysisLogic{
    public:
        AnalysisShape recogize(CCArray *linkballs);

};

#endif /* defined(__legend__AnalysisRect__) */
