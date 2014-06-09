//
//  AnalysisStar.h
//  legend
//
//  Created by 厳 巍 on 2014/05/25.
//
//

#ifndef __legend__AnalysisStar__
#define __legend__AnalysisStar__
#include "AnalysisLogic.h"

class AnalysisStar{
    public :
        AnalysisLogic *logic;
        AnalysisStar();
        ~AnalysisStar();
        AnalysisShape recogize(CCArray *linkballs);
};

#endif /* defined(__legend__AnalysisStar__) */
