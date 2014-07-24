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
    delete world;        //Worldを解放
    world = NULL;
}

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
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    this->initPhysics();
    
    touchBallArray = CCArray::create();
    touchBallArray->retain();
    
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
    
    return true;
}



void GameScene::ccTouchesBegan(CCSet* touches, CCEvent* event)
{

    CCSetIterator it;
    CCTouch* touch;
    
    for( it = touches->begin(); it != touches->end(); it++)
    {
        touch = (CCTouch*)(*it);
        
        if(!touch)
            break;

        CCPoint location = touch->getLocationInView();
        location = CCDirector::sharedDirector()->convertToGL(location);
        if (pSprite_char->boundingBox().containsPoint(location))
        {
            fire("fire_1.png");
        }
    }

}


void GameScene::ccTouchesCancelled(CCSet* touches, CCEvent* event)
{
    
}


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

void GameScene::ccTouchesMoved(CCSet* touches, CCEvent* event)
{
   
}


void GameScene::explode(){
    bullet->setVisible(false);
    operationlayer->removeAllMagicSquare();
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




//背景
void GameScene::update(float dt)
{
    world->Step(dt, 10, 10);
    
    backgroundRun();
    CCSize s = CCDirector::sharedDirector()->getWinSize();
	// simple collision test
	pSprite_monster->setColor(ccWHITE);
	//pSprite_monster->setFlipY(false);
   
    
   

    for(b2Body *b = world->GetBodyList(); b; b=b->GetNext()) {
        if (b->GetUserData() != NULL) {
            CCSprite *sprite = (CCSprite *)b->GetUserData();
            sprite->setPosition(ccp(b->GetPosition().x * PTM_RATIO_WIN,
                                  b->GetPosition().y * PTM_RATIO_WIN));
            sprite->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
            
            

            if (sprite != NULL && pSprite_monster->boundingBox().intersectsRect(sprite->boundingBox()))
            {
                pSprite_monster->setColor(ccc3(CCRANDOM_0_1() * 255, CCRANDOM_0_1() * 255, CCRANDOM_0_1() * 255));
                this->startFireAnm(monster,"fire2.png","fire2.plist","fire",40);
                b->GetWorld()->DestroyBody(b);
                sprite->removeFromParentAndCleanup(true);
            }else if(sprite != NULL && sprite->getPosition().y > s.height){
                b->GetWorld()->DestroyBody(b);
                sprite->removeFromParentAndCleanup(true);
                //delete sprite;
            }
        }
    }
	
//	CCLabelAtlas* posLabel = (CCLabelAtlas*)[_player getChildByTag:1];
//	posLabel.string = [NSString stringWithFormat:@"%.0f/%.0f", _player.position.x, _player.position.y];
}

void GameScene::backgroundRun(){
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

}

void GameScene::beginFire(AnalysisShape shape){
    switch (shape) {
        case star:
            fire("fire_1.png");
            break;
        case hexagon:
            fire("fire_2.png");
            break;
        default:
            break;
    }
}

void GameScene::endFire(AnalysisShape shape){
    
}



void GameScene::cleanupSprite(CCSprite* inSprite)
{
   // bullet->setPosition(center);
    inSprite->removeFromParentAndCleanup(true);
}


void GameScene::initPhysics()
{
    
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    b2Vec2 gravity;
    gravity.Set(0.0f, 0.0f);
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
//    groundBox.Set(b2Vec2(0,s.height/PTM_RATIO_WIN), b2Vec2(s.width/PTM_RATIO_WIN,s.height/PTM_RATIO_WIN));
//    groundBody->CreateFixture(&groundBox,0);
    // left
    groundBox.Set(b2Vec2(0,s.height/PTM_RATIO_WIN), b2Vec2(0,0));
    groundBody->CreateFixture(&groundBox,0);
    // right
    groundBox.Set(b2Vec2(s.width/PTM_RATIO_WIN,s.height/PTM_RATIO_WIN), b2Vec2(s.width/PTM_RATIO_WIN,0));
    groundBody->CreateFixture(&groundBox,0);
}



void GameScene::fire(const char *pszFileName){
    b2BodyDef bodyDef;    //b2BodyDef構造体
    bodyDef.type = b2_dynamicBody;    //動的な物体に
    bodyDef.position.Set(pSprite_char->getPosition().x/PTM_RATIO_WIN, pSprite_char->getPosition().y/PTM_RATIO_WIN);   //位置を設定
    CCSprite *bullet = CCSprite::create(pszFileName);
    bullet->setScale(2.0);
//    bullet->setVisible(true);
    bullet->setPosition(pSprite_char->getPosition());
    this->addChild(bullet,3);
    bodyDef.userData = bullet;
    
    b2Body *body = world->CreateBody(&bodyDef);    //WorldからBodyを作成
    b2CircleShape circle;    //形を定義するクラス
    circle.m_radius = 50/PTM_RATIO;    //半径を50pxに
    b2FixtureDef fixtureDef;    //Fixtureの定義を入れる構造体
    fixtureDef.shape = &circle;    //形
    fixtureDef.density = 0.4;      //密度
    fixtureDef.friction = 0.5;     //摩擦率
    fixtureDef.restitution = 0.6;  //反発係数
    body->CreateFixture(&fixtureDef);  //
    body->SetBullet(true);
    b2Vec2 force = b2Vec2(0, 30);
    body->ApplyLinearImpulse(force, body->GetPosition());
}


void GameScene::BeginContact(b2Contact* contact)
{
    // We need to copy out the data because the b2Contact passed in
    // is reused.
//    MyContact myContact = { contact->GetFixtureA(), contact->GetFixtureB() };
//    _contacts.push_back(myContact);
}

void GameScene::EndContact(b2Contact* contact)
{
//    MyContact myContact = { contact->GetFixtureA(), contact->GetFixtureB() };
//    std::vector::iterator pos;
//    pos = std::find(_contacts.begin(), _contacts.end(), myContact);
//    if (pos != _contacts.end())
//    {
//        _contacts.erase(pos);
//    }
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