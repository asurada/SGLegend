//
//  AnalysisFactory.h
//  legend
//
//  Created by 厳 巍 on 2014/05/27.
//
//

#ifndef __legend__AnalysisFactory__
#define __legend__AnalysisFactory__
#include "AnalysisLogic.h"

class AnalysisFactory{
    private:
    
    public:
        AnalysisLogic *logic;
        AnalysisShape analysis(int &formation,CCArray* linkballs);
};

#endif /* defined(__legend__AnalysisFactory__) */
