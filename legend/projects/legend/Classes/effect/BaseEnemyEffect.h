//
//  BaseEnemyEffect.h
//  legend
//
//  Created by Yan Wei on 2014/07/24.
//
//

#ifndef __legend__BaseEnemyEffect__
#define __legend__BaseEnemyEffect__
#include "BaseEffect.h"

class BaseEnemyEffect : public BaseEffect{
    public:
        virtual void attack() = 0;
        virtual void defend() = 0;
        virtual void action() = 0;


};

#endif /* defined(__legend__BaseEnemyEffect__) */
