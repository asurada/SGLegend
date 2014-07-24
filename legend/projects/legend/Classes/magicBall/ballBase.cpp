//
//  ballBase.cpp
//  legend
//
//  Created by Yan Wei on 2014/07/24.
//
//

#include "BallBase.h"


BallBase* BallBase::create(const char *pszFileName){
    return (BallBase*)super::create(pszFileName);
}