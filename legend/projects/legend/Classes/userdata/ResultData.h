//
//  ResultData.h
//  legend
//
//  Created by Yan Wei on 2014/09/11.
//
//

#ifndef __legend__ResultData__
#define __legend__ResultData__



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


class ResultData{
private:
    AnalysisShape shape;
    int order;
    int value;
public:
    AnalysisShape getShape();
    int getOrder();
    int getValue();
    void setShape(AnalysisShape _shape);
    void setOrder(int _order);
    void setValue(int _value);
};

#endif /* defined(__legend__ResultData__) */
