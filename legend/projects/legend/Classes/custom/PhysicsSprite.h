//
//  PhysicsSprite.h
//  legend
//
//  Created by 厳 巍 on 2014/06/04.
//
//

#ifndef __legend__PhysicsSprite__
#define __legend__PhysicsSprite__

#include "cocos2d.h"
#include "Box2D.h"
class PhysicsSprite : public cocos2d::CCSprite
{
public:
    PhysicsSprite();
    void setPhysicsBody(b2Body * body);
    virtual bool isDirty(void);
    virtual cocos2d::CCAffineTransform nodeToParentTransform(void);
private:
    b2Body* m_pBody;    // strong ref
};

#endif 