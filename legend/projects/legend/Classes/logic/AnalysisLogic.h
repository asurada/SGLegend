//
//  AnalysisLogic.h
//  legend
//
//  Created by 厳 巍 on 2014/05/25.
//
//

#ifndef __legend__AnalysisLogic__
#define __legend__AnalysisLogic__
#include "cocos2d.h"

USING_NS_CC;

enum AnalysisShape{
    noresult = 0,
    triangle = 1,
    rect = 2,
    star = 3,
    hexagon = 4,
    pentagon = 5,
    cross = 6,
    equaltriangle = 7,
    reverse_equaltriangle= 8,
};


class AnalysisLogic{

    private:
    
    
    public:
        AnalysisLogic *logic;
        AnalysisLogic(int formate);
        AnalysisLogic();
        ~AnalysisLogic();
        int pointCount;
        virtual AnalysisShape recogize(CCArray *linkballs);

    
};

#endif /* defined(__legend__AnalysisLogic__) */
