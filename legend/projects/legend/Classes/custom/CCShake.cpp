//
//  CCShake.cpp
//  legend
//
//  Created by Yan Wei on 2014/07/16.
//
//

#include "CCShake.h"
USING_NS_CC;

// not really useful, but I like clean default constructors
CCShake::CCShake() : _strength_x(0), _strength_y(0), _initial_x(0), _initial_y(0)
{
    
}

CCShake* CCShake::actionWithDuration(float duration, float strength )
{
    // call other construction method with twice the same strength
    return actionWithDuration(duration, strength, strength );
}

CCShake* CCShake::actionWithDuration(float duration, float strength_x, float strength_y)
{
    CCShake *p_action = new CCShake();
    p_action->initWithDuration(duration, strength_x, strength_y);
    p_action->autorelease();
    
    return p_action;
}

bool CCShake::initWithDuration(float duration, float strength_x, float strength_y)
{
    if (CCActionInterval::create(duration))
    {
        _strength_x = strength_x;
        _strength_y = strength_y;
        return true;
    }
    
    return false;
}

// Helper function. I included it here so that you can compile the whole file
// it returns a random value between min and max included
float fgRangeRand( float min, float max )
{
    float rnd = ((float)rand()/(float)RAND_MAX);
    return rnd*(max-min)+min;
}

void CCShake::update(float time)
{
    float randx = fgRangeRand( -_strength_x, _strength_x );
    float randy = fgRangeRand( -_strength_y, _strength_y );
    
    // move the target to a shaked position
    m_pTarget->setPosition( ccp( randx, randy) );
}

void CCShake::startWithTarget(CCNode *pTarget)
{
    CCActionInterval::startWithTarget( pTarget );
    
    // save the initial position
    _initial_x = pTarget->getPosition().x;
    _initial_y = pTarget->getPosition().y;
}

void CCShake::stop(void)
{
    // Action is done, reset clip position
    m_pTarget->setPosition( ccp( _initial_x, _initial_y ) );
    
    CCActionInterval::stop();
}
}