//
//  FireBullet.cpp
//  legend
//
//  Created by Yan Wei on 2014/07/24.
//
//

#include "FireBullet.h"
#include "cocos2d.h"

USING_NS_CC;

FireBullet* FireBullet::create(const char *pszFileName){
    return (FireBullet*)super::create(pszFileName);
}


void FireBullet::explode(){
    const char * image = "fire2.png";
    const char *plist = "fire2.plist";
    const char *imgSplit = "fire";
    CCTextureCache::sharedTextureCache()->addImage(image);
    CCTextureCache *cache = CCTextureCache::sharedTextureCache();
    CCTexture2D *texture2D = cache->textureForKey(image);
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(plist, texture2D);
    CCArray *normalAnimFrames = CCArray::create();
    int count = 7;
    for (int i=1; i<count; i++) {
        char* tempString = new char;
        sprintf(tempString, "%s%d.png", imgSplit,i);
        CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(tempString);
        normalAnimFrames->addObject(frame);
    }
    CCAnimation *animation = CCAnimation::createWithSpriteFrames(normalAnimFrames,0.016f);
    animation->setLoops(1);
    
    CCAnimate *animate = CCAnimate::create(animation);
    animationSprite = CCSprite::create("fire1.png");
    animationSprite->setScale(2.0f);
    animationSprite->setPosition(this->getPosition());
    this->addChild(animationSprite, 1);
    
    CCCallFuncND *cleanupAction = CCCallFuncND::create(this,callfuncND_selector(super::cleanupSprite),NULL);
    CCSequence *seq = CCSequence::create(animate, cleanupAction,NULL);
    animationSprite->runAction(seq);

}