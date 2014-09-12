//
//  GaugeSprite.cpp
//  legend
//
//  Created by Yan Wei on 2014/09/12.
//
//

#include "GaugeSprite.h"


static GaugeSprite::CCSprite* nodeWithBarFile(std::string _barFileName ,float _barLenMax, GaugeDirection _barDir){
    return this->nodeWithBarFile(_barFileName,_barLenMax,_barDir,0.0,0.0,0.0f);
}


static GaugeSprite::CCSprite* nodeWithBarFile(std::string  _barFileName , float _barLenMax,BarDir _barDir, double_t _val,double_t _minVal ,double_t _maxVal){
	CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage(_barFileName->char);
	return this->nodeWithBarTexture:texture:_barLenMax:_barDir:_val:_minVal:_maxVal];
}
static GaugeSprite::CCSprite* nodeWithBarTexture:(CCTexture2D*)_barTexture :(float)_barLenMax :(BarDir)_barDir
{
	return [self nodeWithBarTexture:_barTexture:_barLenMax:_barDir:0.0f:0.0f:0.0f];
}
static GaugeSprite::CCSprite* nodeWithBarTexture:(CCTexture2D*)_barTexture :(float)_barLenMax :(BarDir)_barDir :(double_t)_val :(double_t)_minVal :(double_t)_maxVal
{
	id obj = [self spriteWithTexture:_barTexture];
	[obj initBarParam:_barLenMax:_barDir:_val :_minVal :_maxVal];
	return obj;
}




// Override
-(id) init
{
	if((self = [super init])){
		val_		= 0.0f;
		minVal_		= 0.0f;
		maxVal_		= 0.0f;
		barDir_		= BARDIR_RIGHT;
		moveEndTarget	= nil;
		moveEndSelector	= nil;
		isMove_		= FALSE;
		tarVal		= 0.0f;
		diffVal		= 0.0f;
		duration	= 0.0f;
	}
	return self;
}

- (void) initBarParam:(float)_barLenMax :(BarDir)_barDir :(double_t)_val :(double_t)_minVal :(double_t)_maxVal
{
	val_		= _val;
	minVal_		= _minVal;
	maxVal_		= _maxVal;
	barLenMax_	=_barLenMax;
	barDir_		= _barDir;
	// 自分のアンカーを決める
	if( barDir_ == BARDIR_UP ){
		// 上に伸びていく
		self.anchorPoint = ccp(0.5f, 0.0f);
	} else if( barDir_ == BARDIR_DOWN ) {
		// 下に伸びていく
		self.anchorPoint = ccp(0.5f, 1.0f);
	} else if( barDir_ == BARDIR_LEFT ) {
		// 左に伸びていく
		self.anchorPoint = ccp(1.0f, 0.5f);
	} else if( barDir_ == BARDIR_RIGHT ) {
		// 右に伸びていく
		self.anchorPoint = ccp(0.0f, 0.5f);
	}
	moveEndTarget	= nil;
	moveEndSelector	= nil;
	isMove_		= FALSE;
	tarVal		= 0.0f;
	diffVal		= 0.0f;
	duration	= 0.0f;
	[self updateBarLen:_val];
}

- (void)dealloc
{
	[super dealloc];
}

-(void) onExit
{
	[self moveStop];
	[super onExit];
}

// 引数の値の時のバーのスケールを取得
- (float) getBarFitScale:(double_t)_val
{
	float per = [SNGUtil calcPercentD:_val:minVal_:maxVal_];
	return [GameManager getBarScale:per	:self.width	:barLenMax_];
}
// バーの長さを更新
- (void) updateBarLen:(double_t)_val
{
	[self updateBarLen:_val:minVal_ :maxVal_];
}
// バーの長さを更新
- (void) updateBarLen:(double_t)_val :(double_t)_minVal :(double_t)_maxVal
{
	float per = [SNGUtil calcPercentD:_val:_minVal:_maxVal];
	float scale = [GameManager getBarScale:per	:self.width	:barLenMax_];
	if( barDir_ == BARDIR_UP || barDir_ == BARDIR_DOWN ){	// 上下に伸びていく
		self.scaleY = scale;
	} else {	// 左右に伸びていく
		self.scaleX = scale;
	}
	val_		= _val;
	minVal_		= _minVal;
	maxVal_		= _maxVal;
}

// 移動開始
- (BOOL) moveStart:(double_t)_tarVal duration:(ccTime)_duration target:(id)_target selector:(SEL)_selector
{
	if( isMove_ ){ return FALSE; }
	moveEndTarget	= _target;
	moveEndSelector	= _selector;
	isMove_			= TRUE;
	tarVal			= _tarVal;
	diffVal			= tarVal - val_;
	duration		= _duration;
	[self schedule:@selector(onSchedule:)];
	return TRUE;
}
-(void) onSchedule:(ccTime)dt
{
	//NSTimeInterval diffTime	= [NSDate timeIntervalSinceReferenceDate] - moveStartTime;
	//double_t addVal	= (diffVal * diffTime) / duration;
	double_t addVal	= (diffVal * dt) / duration;
	if( diffVal < 0.0f && addVal > -0.1f ){
		addVal		= -0.1f;
	} else if( diffVal >= 0.0f && addVal < 0.1f ){
		addVal		= 0.1f;
	}
	double_t nextVal	= val_ + addVal;
	//double_t nextVal	= startVal + addVal;
	BOOL isEnd		= FALSE;
	if( diffVal < 0.0f && nextVal <= tarVal ){
		isEnd		= TRUE;
		nextVal		= tarVal;
	} else if( diffVal >= 0.0f && nextVal >= tarVal ){
		isEnd		= TRUE;
		nextVal		= tarVal;
	}
	[self updateBarLen:nextVal];
	if( isEnd ){
		[self moveFinish];
	}
}
// 移動終了
- (void) moveFinish
{
	if( !isMove_ ){ return; }
	[self moveStop];
	if( moveEndTarget != nil && moveEndSelector != nil ){
		[moveEndTarget performSelector:moveEndSelector withObject:self];
	}
}

// 終了処理のキャンセル
- (void) cancelFinishSelector
{
	moveEndTarget	= nil;
	moveEndSelector	= nil;
}
// 強制終了
- (void) moveForceFinish
{
	if( !isMove_ ){ return; }
	[self updateBarLen:tarVal];
	[self moveFinish];
}
// 移動停止
- (void) moveStop
{
	if( !isMove_ ){ return; }
	isMove_			= FALSE;
	[self unschedule:@selector(onSchedule:)];
}