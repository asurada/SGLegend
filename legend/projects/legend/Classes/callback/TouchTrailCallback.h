//
//  TouchTrailCallback.h
//  legend
//
//  Created by Yan Wei on 2014/07/09.
//
//

#ifndef __legend__TouchTrailCallback__
#define __legend__TouchTrailCallback__

class TouchTrailCallback{
    
public:
    virtual void touchBegin_TouchTrail(cocos2d::CCPoint point) = 0;
    virtual void touchMove_TouchTrail(cocos2d::CCPoint point) = 0;
    virtual void touchEnd_TouchTrail(cocos2d::CCPoint point) = 0;
};

#endif /* defined(__legend__TouchTrailCallback__) */
