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
#include "ballBase.h"


class AnalysisRect:public AnalysisLogic{
    public:
        ResultData* recogize(CCArray *linkballs);
        void init(CCLayer *_parent,CCArray *container);

};

#endif /* defined(__legend__AnalysisRect__) */
