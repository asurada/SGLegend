//
//  AnalysisTriangle.h
//  legend
//
//  Created by 厳 巍 on 2014/05/25.
//
//

#ifndef __legend__AnalysisTriangle__
#define __legend__AnalysisTriangle__


#include "AnalysisLogic.h"

class AnalysisTriangle:public AnalysisLogic{
    public:
        AnalysisShape recogize(cocos2d::CCArray *linkballs);
        void init(CCLayer *_parent);

};

#endif /* defined(__legend__AnalysisTriangle__) */
