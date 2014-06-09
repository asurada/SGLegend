//
//  GameScene.cpp
//  legend
//
//  Created by 厳 巍 on 2014/05/17.
//
//

#include "GameScene.h"
#include "CCBlade.h"
#include "TouchTrailLayer.h"
#include "OperationLayer.h"
#include "PhysicsSprite.h"
#include "ShapeConst.h"
using namespace cocos2d;

USING_NS_CC;

static const int PTM_RATIO_WIN = PTM_RATIO;
static const int kScrollSpeed = 2;

enum {
    kTagParentNode = 1,
};

GameScene::GameScene(){
    
   
}


GameScene::~GameScene(){
    
}

//void GameScene::registerWithTouchDispatcher()
//{
//    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, this->getTouchPriority(), true);
//}

CCScene* GameScene::scene()
{
    
   
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GameScene *layer = GameScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    
 
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    setTouchEnabled( true );
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    this->initPhysics();
    
    ballArray = CCArray::create();
    ballArray->retain();
    touchBallArray = CCArray::create();
    touchBallArray->retain();
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
    
    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                                          "CloseNormal.png",
                                                          "CloseSelected.png",
                                                          this,
                                                          menu_selector(GameScene::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));
    
    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);
    
    
//    TouchTrailLayer *layer = TouchTrailLayer::create();
//    this->addChild(layer,12);
    
    
    operationlayer = OperationLayer::create();
    operationlayer->setDelegate(this);
    operationlayer->init();
    operationlayer->setPosition(ccp(0,0));
    this->addChild(operationlayer,1);

   
    
    
   //this->initBallInRect();
   // this->initBallInTriangle();
   // this->initBallInRhombus();
   // this->initBallInPentagon();
    
    
    pSprite_bg_1 = CCSprite::create("bg@2x.png");
    pSprite_bg_1->setPosition(ccp(0 , visibleSize.height/2));
    pSprite_bg_1->setAnchorPoint(ccp(0,0.5f));
    this->addChild(pSprite_bg_1, 0);
    
    
    pSprite_bg_2 = CCSprite::create("bg@2x.png");
    pSprite_bg_2->setPosition(ccp(0 , visibleSize.height*3/2));
    pSprite_bg_2->setAnchorPoint(ccp(0,0.5f));
    this->addChild(pSprite_bg_2, 0);
    
    
    pSprite_round = CCSprite::create("round.png");
    pSprite_round->setPosition(ccp(visibleSize.width/2 , visibleSize.height/4));
    pSprite_round->setScale(1);
    this->addChild(pSprite_round, 0);
    

    center = ccp(visibleSize.width/2 , visibleSize.height/4);
    pSprite_char = CCSprite::create("char.png");
    pSprite_char->setPosition(center);
    this->addChild(pSprite_char, 2);
    

    
    
    monster = ccp(visibleSize.width/2 , visibleSize.height/2 + visibleSize.height/4);
    pSprite_monster = CCSprite::create("monster.png");
    pSprite_monster->setPosition(monster);
    pSprite_monster->setScale(1.5);
    this->addChild(pSprite_monster, 0);
    
    
    

    
    this->scheduleUpdate();
    
    target = CCRenderTexture::create(s.width, s.height, kCCTexture2DPixelFormat_RGBA8888);
    target->retain();
    target->setPosition(ccp(s.width / 2, s.height / 2));
    
    this->addChild(target);

    

  

    brush = CCSprite::create("largeBrush.png");
    brush->retain();
    return true;
}



void GameScene::ccTouchesBegan(CCSet* touches, CCEvent* event)
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    CCSetIterator it;
    CCTouch* touch;
    
    for( it = touches->begin(); it != touches->end(); it++)
    {
        touch = (CCTouch*)(*it);
        
        if(!touch)
            break;

        
        
        CCPoint location = touch->getLocationInView();
        location = CCDirector::sharedDirector()->convertToGL(location);
        

        
        previousLocation = location;
        
        b2BodyDef myBodyDef;
        myBodyDef.type = b2_staticBody;
        myBodyDef.position.Set(location.x/PTM_RATIO_WIN,location.y/PTM_RATIO_WIN);
        currentPlatformBody = world->CreateBody(&myBodyDef);
        
    }

}


void GameScene::ccTouchesCancelled(CCSet* touches, CCEvent* event)
{
//    drawNode->removeFromParentAndCleanup(true);
//    //    if (_mouseJoint)
//    //    {
//    //        _world->DestroyJoint(_mouseJoint);
//    //        _mouseJoint = NULL;
//    //    }
//    
}
//
void GameScene::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
    //Add a new body/atlas sprite at the touched location
    CCSetIterator it;
    CCTouch* touch;
    
    for( it = touches->begin(); it != touches->end(); it++)
    {
        touch = (CCTouch*)(*it);
    }
    
    
  
}
//
void GameScene::ccTouchesMoved(CCSet* touches, CCEvent* event)
{
//    //CCTouch *touch = (CCTouch *)touches->anyObject();
//    
//	CCSetIterator it;
//	for( it = touches->begin(); it != touches->end(); it++)
//    {
//        CCTouch* touch = (CCTouch*)(*it);
//        if(!touch)
//            break;
//
//        CCPoint location = touch->getLocationInView();
//        location = CCDirector::sharedDirector()->convertToGL(location);
//        CCObject *obj;
//        
//  
////todo
////        if(startSprite != NULL){
////            float distance = sqrt( pow(location.x - startSprite->getPosition().x, 2) + pow(location.y - startSprite->getPosition().y, 2));
////            
////            CCPoint start = startSprite->getPosition();
////            if(distance > 15)
////            {
////                this->drawLineByPoint(start , location);
////                
////            }
////
////        }
//
//            }
//        }
//    }
}




void GameScene::attack(){
    

//    CCRotateBy *rotate = CCRotateBy::create(0.8f, 360.0f);
//    drawNode->runAction(CCRepeatForever::create(rotate));
    bullet->setPosition(ccp(320,284));
    bullet->setVisible(true);
    bullet->stopAllActions();
    CCLOG("position = (%f,%f)",pSprite_char->getPosition().x,pSprite_char->getPosition().y);
    CCLOG("position = (%f,%f)",pSprite_monster->getPosition().x,pSprite_monster->getPosition().y);
    bullet->runAction(CCSequence::create(CCMoveTo::create(0.6, ccp(320,pSprite_monster->getPosition().y)), CCCallFuncN::create(this, callfuncN_selector(GameScene::explode)), NULL  // DO NOT FORGET TO TERMINATE WITH NULL
                                            ));
}


void GameScene::explode(){
    bullet->setVisible(false);
    operationlayer->clearMagicSquare();
    
    
}

void GameScene::startFireAnm(CCPoint &pos,const char * image,const char * plist,const char * imgSplit,int count){
    
    CCTextureCache::sharedTextureCache()->addImage(image);
    CCTextureCache *cache = CCTextureCache::sharedTextureCache();
    CCTexture2D *texture2D = cache->textureForKey(image);
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(plist, texture2D);
    CCArray *normalAnimFrames = CCArray::create();
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
    animationSprite->setPosition(pos);
    this->addChild(animationSprite, 1);
    
    CCCallFuncND *cleanupAction = CCCallFuncND::create(this,callfuncND_selector(GameScene::cleanupSprite),animationSprite);
    CCSequence *seq = CCSequence::create(animate, cleanupAction,NULL);

    
    animationSprite->runAction(seq);

}




int GameScene::anlysisWriteHanding(CCArray *spriteList){
    int preTag = -1;
    int result = -1;
    int starCount = 0;
    for(int i=0; i < spriteList->count(); i++)
    {
        CCSprite *sprite = (CCSprite *)spriteList->objectAtIndex(i);
        int tag = sprite->getTag();
        CCLOG("tag = %d", tag);
        tag = tag%3;
        if(preTag == -1){
            preTag = tag;
        }else{
            //星形判断
            if(spriteList->count() == 6){
                result = SHARP_PENTAGON;
                if(preTag == tag ){
                    starCount++;
                    preTag = tag;
                }else{
                    preTag = tag;
                }
            }
            if(spriteList->count() == 5){
                if(preTag == tag){
                    return 0;
                }else{
                    preTag = tag;
                }
            }
            if(spriteList->count() == 4){
                if(preTag == tag){
                    return 0;
                }else{
                    preTag = tag;
                }
            }
        }
    }
    
    if(starCount == 2 && spriteList->count() == 6){
        return SHARP_STAR;
    }
    return result;

}



void GameScene::update(float dt)
{
	CCPoint bg1Pos = pSprite_bg_1->getPosition();
	CCPoint bg2Pos = pSprite_bg_2->getPosition();
	bg1Pos.y -= kScrollSpeed;
	bg2Pos.y -= kScrollSpeed;
	
	// move scrolling background back from left to right end to achieve "endless" scrolling
	if (bg1Pos.y < -pSprite_bg_1->getContentSize().height/2)
	{
		bg1Pos.y = pSprite_bg_1->getContentSize().height * 3 / 2;
		
	}
    if(bg2Pos.y < -pSprite_bg_1->getContentSize().height/2){
        bg2Pos.y = pSprite_bg_2->getContentSize().height * 3 / 2;
    }
	
	// remove any inaccuracies by assigning only int values (this prevents floating point rounding errors accumulating over time)
	bg1Pos.x = (int)bg1Pos.x;
	bg2Pos.x = (int)bg2Pos.x;
	pSprite_bg_1->setPosition(bg1Pos);
	pSprite_bg_2->setPosition(bg2Pos);
	
	// simple collision test
	pSprite_monster->setColor(ccWHITE);
	//pSprite_monster->setFlipY(false);

    
    if (bullet != NULL && pSprite_monster->boundingBox().intersectsRect(bullet->boundingBox()))
    {
        bullet->setVisible(false);
        pSprite_monster->setColor(ccc3(CCRANDOM_0_1() * 255, CCRANDOM_0_1() * 255, CCRANDOM_0_1() * 255));
        this->startFireAnm(monster,"fire2.png","fire2.plist","fire",40);
       
    }

	
//	CCLabelAtlas* posLabel = (CCLabelAtlas*)[_player getChildByTag:1];
//	posLabel.string = [NSString stringWithFormat:@"%.0f/%.0f", _player.position.x, _player.position.y];
}



void GameScene::beginFire(AnalysisShape shape){
    switch (shape) {
        case star:
            bullet = CCSprite::create("fire_1.png");
            bullet->setScale(2.0);
            bullet->setVisible(false);
            this->addChild(bullet,3);
            this->attack();
            //this->startFireAnm(monster,"fire2.png","fire2.plist","fire",40);
            break;
        case hexagon:
            bullet = CCSprite::create("fire_2.png");
            bullet->setScale(2.0);
            bullet->setVisible(false);
            this->addChild(bullet,3);
            this->attack();
            
            // this->startFireAnm(monster,"fire.png","fire.plist","fire_",20);
            break;
        default:
            break;
    }

}

void GameScene::endFire(AnalysisShape shape){
    
}


void GameScene::addPhysics(std::vector<cocos2d::CCPoint> autoPoints){
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    b2BodyDef myBodyDef;
    myBodyDef.type = b2_dynamicBody; //this will be a dynamic body
    myBodyDef.position.Set(currentPlatformBody->GetPosition().x, currentPlatformBody->GetPosition().y); //set the starting position
    b2Body* newBody = world->CreateBody(&myBodyDef);
    
    for(int i=0; i < autoPoints.size()-1; i++)
    {
        CCPoint start = autoPoints[i];
        CCPoint end = autoPoints[i+1];
        addRectangleBetweenPointsToBody(newBody,start,end);
        
    }
    world->DestroyBody(currentPlatformBody);
    CCRect bodyRectangle = getBodyRectangle(newBody);
    CCImage *pImage = target->newCCImage();
    CCTexture2D *tex = CCTextureCache::sharedTextureCache()->addUIImage(pImage,NULL);
    CC_SAFE_DELETE(pImage);

    //CCSprite *sprite = CCSprite::create(tex, bodyRectangle);
    
    CCSprite *sprite = new CCSprite();
    sprite->initWithTexture(tex, bodyRectangle);

    float anchorX = newBody->GetPosition().x * PTM_RATIO_WIN - bodyRectangle.origin.x;
    float anchorY = bodyRectangle.size.height - (s.height - bodyRectangle.origin.y - newBody->GetPosition().y * PTM_RATIO_WIN);
    
    sprite->setAnchorPoint(ccp(anchorX / bodyRectangle.size.width,  anchorY / bodyRectangle.size.height));
    newBody->SetUserData(sprite);
    addChild(sprite,6);
    
    removeChild(target,true);
    target->release();
    
    target = CCRenderTexture::create(s.width, s.height, kCCTexture2DPixelFormat_RGBA8888);
    target->retain();
    target->setPosition(ccp(s.width / 2, s.height / 2));
    
    this->addChild(target, 4);


}


void GameScene::cleanupSprite(CCSprite* inSprite)
{
    bullet->setPosition(center);
    inSprite->removeFromParentAndCleanup(true);
    //this->removeDrawNode();
}


void GameScene::initPhysics()
{
    
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    b2Vec2 gravity;
    gravity.Set(0.0f, -10.0f);
    world = new b2World(gravity);
    
    // Do we want to let bodies sleep?
    world->SetAllowSleeping(true);
    
    world->SetContinuousPhysics(true);
    
    //     m_debugDraw = new GLESDebugDraw( PTM_RATIO );
    //     world->SetDebugDraw(m_debugDraw);
    
    uint32 flags = 0;
    flags += b2Draw::e_shapeBit;
    //        flags += b2Draw::e_jointBit;
    //        flags += b2Draw::e_aabbBit;
    //        flags += b2Draw::e_pairBit;
    //        flags += b2Draw::e_centerOfMassBit;
    //m_debugDraw->SetFlags(flags);
    
    
    // Define the ground body.
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0, 0); // bottom-left corner
    
    // Call the body factory which allocates memory for the ground body
    // from a pool and creates the ground box shape (also from a pool).
    // The body is also added to the world.
    b2Body* groundBody = world->CreateBody(&groundBodyDef);
    
    // Define the ground box shape.
    b2EdgeShape groundBox;
    
    // bottom
    
    groundBox.Set(b2Vec2(0,0), b2Vec2(s.width/PTM_RATIO_WIN,0));
    groundBody->CreateFixture(&groundBox,0);
    
    // top
    groundBox.Set(b2Vec2(0,s.height/PTM_RATIO_WIN), b2Vec2(s.width/PTM_RATIO_WIN,s.height/PTM_RATIO_WIN));
    groundBody->CreateFixture(&groundBox,0);
    
    // left
    groundBox.Set(b2Vec2(0,s.height/PTM_RATIO_WIN), b2Vec2(0,0));
    groundBody->CreateFixture(&groundBox,0);
    
    // right
    groundBox.Set(b2Vec2(s.width/PTM_RATIO_WIN,s.height/PTM_RATIO_WIN), b2Vec2(s.width/PTM_RATIO_WIN,0));
    groundBody->CreateFixture(&groundBox,0);
}

void GameScene::addRectangleBetweenPointsToBody(b2Body *body, CCPoint start, CCPoint end)
{
    
    float distance = sqrt( pow(end.x - start.x, 2) + pow(end.y - start.y, 2));
    
    float sx=start.x;
    float sy=start.y;
    float ex=end.x;
    float ey=end.y;
    float dist_x=sx-ex;
    float dist_y=sy-ey;
    float angle= atan2(dist_y,dist_x);
    
    float px= (sx+ex)/2/PTM_RATIO_WIN - body->GetPosition().x;
    float py = (sy+ey)/2/PTM_RATIO_WIN - body->GetPosition().y;
    
    float width = abs(distance)/PTM_RATIO;
    float height =  brush->boundingBox().size.height/PTM_RATIO;
    
    b2PolygonShape boxShape;
    boxShape.SetAsBox(width / 2, height / 2, b2Vec2(px,py),angle);
    
    b2FixtureDef boxFixtureDef;
    boxFixtureDef.shape = &boxShape;
    boxFixtureDef.density = 5;
    
    boxFixtureDef.filter.categoryBits = 2;
    
    body->CreateFixture(&boxFixtureDef);
}


CCRect GameScene::getBodyRectangle(b2Body* body)
{
    
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    float minX2 = s.width;
    float maxX2 = 0;
    float minY2 = s.height;
    float maxY2 = 0;
    
    const b2Transform& xf = body->GetTransform();
    for (b2Fixture* f = body->GetFixtureList(); f; f = f->GetNext())
    {
        
        b2PolygonShape* poly = (b2PolygonShape*)f->GetShape();
        int32 vertexCount = poly->m_vertexCount;
        b2Assert(vertexCount <= b2_maxPolygonVertices);
        
        for (int32 i = 0; i < vertexCount; ++i)
        {
            b2Vec2 vertex = b2Mul(xf, poly->m_vertices[i]);
            
            
            if(vertex.x < minX2)
            {
                minX2 = vertex.x;
            }
            
            if(vertex.x > maxX2)
            {
                maxX2 = vertex.x;
            }
            
            if(vertex.y < minY2)
            {
                minY2 = vertex.y;
            }
            
            if(vertex.y > maxY2)
            {
                maxY2 = vertex.y;
            }
        }
    }
    
    maxX2 *= PTM_RATIO;
    minX2 *= PTM_RATIO;
    maxY2 *= PTM_RATIO;
    minY2 *= PTM_RATIO;
    
    float width2 = maxX2 - minX2;
    float height2 = maxY2 - minY2;
    float remY2 = s.height - maxY2;
    return CCRectMake(minX2, remY2, width2, height2);
}



void GameScene::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}