//
//  AnimationTool.cpp
//  legend
//
//  Created by Yan Wei on 2014/08/11.
//
//

#include "AnimationTool.h"
#define PTM_RATIO (32)

CCSprite* AnimationTool::startFireAnm(CCPoint &pos,const char * image,const char * plist,const char * imgSplit,int count,const char *format,CCObject* pSelectorTarget,SEL_CallFuncND selector){
    
    CCTextureCache::sharedTextureCache()->addImage(image);
    CCTextureCache *cache = CCTextureCache::sharedTextureCache();
    CCTexture2D *texture2D = cache->textureForKey(image);
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(plist, texture2D);
    CCArray *normalAnimFrames = CCArray::create();
    for (int i=1; i<count; i++) {
        char* tempString = new char;
        sprintf(tempString, format, imgSplit,i);
        CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(tempString);
        normalAnimFrames->addObject(frame);
    }
    CCAnimation *animation = CCAnimation::createWithSpriteFrames(normalAnimFrames,0.1f);
    animation->setLoops(1);
    
    CCAnimate *animate = CCAnimate::create(animation);
    
    CCSprite* animationSprite = CCSprite::create();
    animationSprite->setScale(1.0f);
    animationSprite->setPosition(pos);
    
    CCCallFuncND *cleanupAction = CCCallFuncND::create(pSelectorTarget,selector,animationSprite);
    CCSequence *seq = CCSequence::create(animate, cleanupAction,NULL);
    animationSprite->runAction(seq);

    return animationSprite;
    
}



void AnimationTool::setBullet(CCSprite* bullet,float radius, float density,float friction,float restitution,b2World* world){
    b2BodyDef bodyDef; //b2BodyDef構造体
    b2Body *body;
    b2FixtureDef fixtureDef;//Fixtureの定義を入れる構造体
    b2CircleShape circle;
    bodyDef.type = b2_dynamicBody;    //動的な物体に
    bodyDef.position.Set(bullet->getPosition().x/PTM_RATIO, bullet->getPosition().y/PTM_RATIO);   //位置を設定
    bodyDef.userData = bullet;
    body = world->CreateBody(&bodyDef);
    //b2CircleShape circle;//形を定義するクラス
    circle.m_radius = radius/PTM_RATIO;    //半径を50pxに
    // b2FixtureDef fixtureDef;    //Fixtureの定義を入れる構造体
    fixtureDef.shape = &circle;    //形
    fixtureDef.density = density;      //密度
    fixtureDef.friction = friction;     //摩擦率
    fixtureDef.restitution = restitution;  //反発係数
    body->CreateFixture(&fixtureDef);  //
    body->SetBullet(true);
    b2Vec2 force = b2Vec2(0, 30);
    body->ApplyLinearImpulse(force, body->GetPosition());
}
