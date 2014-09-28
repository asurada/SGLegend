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
#include "AnimationTool.h"
#include "Enm_01.h"
#include "DrawUtils.h"
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
  //  operationlayer->setPosition(ccp(0,0));
   // this->addChild(operationlayer,1);
    
    
    

   //this->initBallInRect();
   // this->initBallInTriangle();
   // this->initBallInRhombus();
   // this->initBallInPentagon();
    
    pSprite_bg_1 = CCSprite::create("bg@2x.png");
    pSprite_bg_1->setPosition(ccp(0 , visibleSize.height/2));
    pSprite_bg_1->setAnchorPoint(ccp(0,0.5f));
    this->addChild(pSprite_bg_1, 0);
    
    //DrawUtils::drawSolidCircle(ccp(0,0),20,30,ccc4f(0,255,0,0.5));
    
    pSprite_bg_2 = CCSprite::create("bg@2x.png");
    pSprite_bg_2->setPosition(ccp(0 , visibleSize.height*3/2));
    pSprite_bg_2->setAnchorPoint(ccp(0,0.5f));
    this->addChild(pSprite_bg_2, 0);
    
    
    
    
    
    pSprite_round = CCSprite::create("round.png");
    pSprite_round->setAnchorPoint(ccp(0.5,0.5));
    emptyNode = CCSprite::create();
    pSprite_round->addChild(operationlayer);
    emptyNode->addChild(pSprite_round);
    emptyNode->setPosition(ccp(visibleSize.width/2 , visibleSize.height/4 +135));
    emptyNode->setAnchorPoint(ccp(0.5,0.5));
    emptyNode->cocos2d::CCNode::setScale(1.0, 1.0);
    
    
    this->addChild(emptyNode);
    
    center = ccp(visibleSize.width/2 , visibleSize.height/4+100);
    pSprite_char = new Char_01("char.png");
    pSprite_char->setVisible(false);
    CCSize rect = CCSize(150, 0);
    
    
    if(pSprite_char->init()){
        pSprite_char->changeSize(rect);
        pSprite_char->setPosition(this,center,0);
        pSprite_char->initGauge(center);
    }
    
    
    
    
    monster = ccp(visibleSize.width/2 , visibleSize.height/2 + visibleSize.height/4);
    pSprite_monster = new Enm_01("monster.png");
    if(pSprite_monster->init()){
        pSprite_monster->setPosition(this,monster,0);
        pSprite_monster->initGauge(monster);
    }

    this->scheduleUpdate();
        
    bullets = new Bullet();

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
        if (pSprite_char->getChar()->boundingBox().containsPoint(location))
        {
            CCLOG("ccTouchesBegan");
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

float rotation = 0;
float scaleY = 1;
bool canPerform = true;
bool disappear = false;
bool isAnimationRun = false;

//背景
void GameScene::update(float dt)
{
    world->Step(dt, 10, 10);
    backgroundRun();
    
    
    
    //出現
    if(canPerform){
        if(emptyNode->getScaleY() > 0.3){
            emptyNode->cocos2d::CCNode::setScale(1.0, emptyNode->getScaleY()-0.02);
        }else{
        
            if(pSprite_char != NULL){
                rotation = rotation + 8;
                pSprite_round->setRotation(rotation);
                if(pSprite_char->appear()){
                    emptyNode->setPosition(ccp(emptyNode->getPosition().x,emptyNode->getPosition().y-4));
                }else{
                    canPerform = false;
                }
            }
        }
    }else{
        if(emptyNode->getScaleY()  < 1){
            emptyNode->cocos2d::CCNode::setScale(1.0, emptyNode->getScaleY()+0.02);
        }else{
            
            rotation = 0;
            CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
            
            if(emptyNode->getPosition().y < visibleSize.height/4){
                emptyNode->setPosition(ccp(emptyNode->getPosition().x,emptyNode->getPosition().y+4));
                pSprite_round->setRotation(rotation);
            }
        }
        
    }
    
    //消える
    if(disappear){
        if(pSprite_char->disappear()){
            
        }else{
            disappear = false;
            canPerform = true;
        }
    }
    
    
    
    CCSize s = CCDirector::sharedDirector()->getWinSize();
	// simple collision test
	pSprite_monster->getChar()->setColor(ccWHITE);
    
    
    for(b2Body *b = world->GetBodyList(); b; b=b->GetNext()) {
        if (b->GetUserData() != NULL) {
            CCSprite *sprite  = (CCSprite *)(b->GetUserData());
            sprite->setPosition(ccp(b->GetPosition().x * PTM_RATIO_WIN,
                                  b->GetPosition().y * PTM_RATIO_WIN));
            sprite->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
            
            if (sprite != NULL && pSprite_monster->getChar()->boundingBox().intersectsRect(sprite->boundingBox()))
            {
                
                
                pSprite_monster->updateHpBar((double_t)10.0);
                bulletType type = (bulletType)sprite->getTag();
                bullets->setExplode(type);
                
                animationSprite = AnimationTool::startFireAnm(monster,bullets->getImage(),bullets->getPlist(),bullets->getImageSplit(),bullets->getFrameCount(),bullets->getFormat(),this,callfuncND_selector(GameScene::cleanupSprite));
                isAnimationRun = true;
                this->addChild(animationSprite, 1);
                b->GetWorld()->DestroyBody(b);
                sprite->removeFromParentAndCleanup(true);
            }else if(sprite != NULL && (sprite->getPosition().y > s.height || sprite->getPosition().y < 0 || sprite->getPosition().x > s.width || sprite->getPosition().x < 0)){
                b->GetWorld()->DestroyBody(b);
                sprite->removeFromParentAndCleanup(true);
                //delete sprite;
            }
        }
    }
    
    if(isAnimationRun && bullets != NULL){
        pSprite_monster->getChar()->setColor(ccc3(CCRANDOM_0_1() * bullets->getWound_r(), CCRANDOM_0_1()  * bullets->getWound_g(), CCRANDOM_0_1() * bullets->getWound_b()));
    }
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
	bg1Pos.x = (int)bg1Pos.x;
	bg2Pos.x = (int)bg2Pos.x;
	pSprite_bg_1->setPosition(bg1Pos);
	pSprite_bg_2->setPosition(bg2Pos);

}

void GameScene::beginFire(AnalysisShape shape){
    switch (shape) {
        case star:
            CCLOG("star:星");
            disappear = true;
            break;
        case hexagon:
            CCLOG("star：六角");
            onFire(attack_2);
            break;
        case noresult:
            CCLOG("noresult：no");
            break;
        case triangle:
            CCLOG("triangle：三角");
             onFire(attack_3);
            break;
        case rect:
            CCLOG("triangle：四角");
            onFire(attack_4);
            break;
        case pentagon:
            CCLOG("triangle：五角");
            onFire(attack_5);
            break;
        case cross:
            CCLOG("triangle：十字");
            onFire(effect_1);
            break;
        case equaltriangle:
           
             onFire(attack_1);
            CCLOG("triangle：等辺三角");
            break;
        case reverse_equaltriangle:
            CCLOG("reverse_equaltriangle");
            break;
            
        default:
            break;
    }
}

void GameScene::endFire(AnalysisShape shape){
    
}



void GameScene::onFire(bulletType _type){
    CCSprite *bullet = pSprite_char->attack(_type);
    AnimationTool::setBullet(bullet,pSprite_char->getRadius(),
                             pSprite_char->getDensity(),
                             pSprite_char->getFriction(),
                             pSprite_char->getRestitution(),
                             this->world);
}


void GameScene::cleanupSprite(CCSprite* inSprite)
{
    isAnimationRun = false;
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
    if(false){
        groundBox.Set(b2Vec2(0,0), b2Vec2(s.width/PTM_RATIO_WIN,0));
        groundBody->CreateFixture(&groundBox,0);
    // top
        groundBox.Set(b2Vec2(0,s.height/(PTM_RATIO_WIN*2)), b2Vec2(s.width/PTM_RATIO_WIN,s.height/(PTM_RATIO_WIN*2)));
        groundBody->CreateFixture(&groundBox,0);
    // left
        groundBox.Set(b2Vec2(0,s.height/PTM_RATIO_WIN), b2Vec2(0,0));
        groundBody->CreateFixture(&groundBox,0);
    // right
        groundBox.Set(b2Vec2(s.width/PTM_RATIO_WIN,s.height/PTM_RATIO_WIN), b2Vec2(s.width/PTM_RATIO_WIN,0));
        groundBody->CreateFixture(&groundBox,0);
    }
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


void GameScene::draw(){
    DrawUtils::drawSolidCircle(ccp(100,100),30,30,ccc4f(0,255,0,0.5));
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