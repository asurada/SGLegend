//
//  GaugeDelegate.h
//  legend
//
//  Created by Yan Wei on 2014/09/14.
//
//

#ifndef legend_GaugeDelegate_h
#define legend_GaugeDelegate_h

class GaugeDelegate{
public:
    virtual void onMoveStart() = 0;
    virtual void onMoveCancel() = 0;
    virtual void onMoveForceFinish() = 0;
    virtual void onMoveFinish() = 0;
};


#endif
