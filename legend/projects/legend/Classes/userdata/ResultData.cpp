//
//  ResultData.cpp
//  legend
//
//  Created by Yan Wei on 2014/09/11.
//
//

#include "ResultData.h"

AnalysisShape ResultData::getShape(){
    return shape;
}

int ResultData::getOrder(){
    return order;
}

int ResultData::getValue(){
    return value;
}

void ResultData::setShape(AnalysisShape _shape){
    shape = _shape;
}

void ResultData::setOrder(int _order){
    order = _order;
}

void ResultData::setValue(int _value){
    value = _value;
}