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
#include "ballBase.h"

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


enum Position{
    ENUM_PST_1=1,
    ENUM_PST_2=2,
    ENUM_PST_3=3,
    ENUM_PST_4=4,
    ENUM_PST_5=5,
    ENUM_PST_6=6,
};

class AnalysisLogic{

    protected:
        CCArray *spritesContainer;
        CCLayer* parent;
    public:
        AnalysisLogic *logic;
        AnalysisLogic(int formate);
        AnalysisLogic();
        ~AnalysisLogic();
        CCArray *getContainer();
        virtual void init(CCLayer *_parent,CCArray *container) = 0;
        virtual AnalysisShape recogize(CCArray *linkballs) = 0;

    
};

#endif /* defined(__legend__AnalysisLogic__) */
