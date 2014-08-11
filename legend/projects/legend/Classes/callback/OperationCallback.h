//
//  OperationCallback.h
//  legend
//
//  Created by 厳 巍 on 2014/05/24.
//
//

#ifndef legend_OperationCallback_h
#define legend_OperationCallback_h
#include "AnalysisLogic.h"
class OperationCallback{
    
public:
    virtual void beginFire(AnalysisShape shape) = 0;
    virtual void endFire(AnalysisShape shape) = 0;


};


#endif
