//
//  ballBase.h
//  legend
//
//  Created by Yan Wei on 2014/07/24.
//
//

#ifndef __legend__ballBase__
#define __legend__ballBase__
#include "cocos2d.h"
#include "BaseAnimation.h"

USING_NS_CC;


class BallBase :public cocos2d::CCSprite{
    private:
        BaseAnimation *animation;
        typedef CCSprite super;
    public:
        virtual void init(const char *pName) =0;
        virtual void animateWhenTap() =0;
        virtual void animateWhenAttack() =0;
        virtual void animateWhenDefend() =0;
        virtual void animateWhenSeal() =0;
        virtual void animateWhenUpgrade() =0;
        virtual void animateWhenRevolute() =0;
        static BallBase* create(const char *pszFileName);
    
    
};

#endif /* defined(__legend__ballBase__) */
