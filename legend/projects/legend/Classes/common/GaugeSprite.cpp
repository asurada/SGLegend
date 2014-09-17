//
//  GaugeSprite.cpp
//  legend
//
//  Created by Yan Wei on 2014/09/12.
//
//

#include "GaugeSprite.h"


GaugeSprite*  GaugeSprite::nodeWithBarFile(std::string _barFileName ,float _barLenMax, GaugeDirection _barDir){
    return GaugeSprite::nodeWithBarFile(_barFileName,_barLenMax,_barDir,0.0,0.0,0.0f);
}

GaugeSprite*  GaugeSprite::nodeWithBarFile(std::string  _barFileName , float _barLenMax,GaugeDirection _barDir, double_t _val,double_t _minVal ,double_t _maxVal){
	CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage(_barFileName.c_str());
	return GaugeSprite::nodeWithBarTexture(texture,_barLenMax,_barDir,_val,_minVal,_maxVal);
}

GaugeSprite*  GaugeSprite::nodeWithBarTexture(CCTexture2D* _barTexture ,float _barLenMax ,GaugeDirection _barDir)
{
	return GaugeSprite::nodeWithBarTexture(_barTexture,_barLenMax,_barDir,0.0f,0.0f,0.0f);
}

GaugeSprite*  GaugeSprite::nodeWithBarTexture(CCTexture2D* _barTexture ,float _barLenMax ,GaugeDirection _barDir ,double_t _val ,double_t _minVal ,double_t _maxVal)
{
	GaugeSprite  *obj =(GaugeSprite*)CCSprite::createWithTexture(_barTexture);
	obj->initBarParam(_barLenMax,_barDir,_val,_minVal,_maxVal);
	return obj;
}

GaugeSprite::GaugeSprite(){
    val_		= 0.0f;
    minVal_		= 0.0f;
    maxVal_		= 0.0f;
    barDir_		= BARDIR_RIGHT;
    isMove_		= false;
    tarVal_		= 0.0f;
    diffVal_	= 0.0f;

}


GaugeSprite::GaugeSprite(double_t _val,double_t _maxVal){
    val_		= _val;
    minVal_		= 0.0f;
    maxVal_		= _maxVal;
    barDir_		= BARDIR_RIGHT;
    isMove_		= false;
    tarVal_		= 0.0f;
    diffVal_	= 0.0f;
    
//    _bar = GaugeSprite::nodeWithBarFile("ips_co_gg_gr@2x.png",100.0f,BARDIR_RIGHT, val_ ,0 , maxVal_);
//    _bg  = GaugeSprite::nodeWithBarFile("ips_co_gg_bt@2x.png",100.0f,BARDIR_RIGHT, val_ ,0 , maxVal_);
   // _bg->addChild(_bar,1);
}


GaugeSprite::~GaugeSprite(){
   //
}


void GaugeSprite::initBarParam(float _barLenMax,GaugeDirection _barDir ,double_t _val ,double_t _minVal , double_t _maxVal)
{
	val_		= _val;
	minVal_		= _minVal;
	maxVal_		= _maxVal;
	barLenMax_	= _barLenMax;
	barDir_		= _barDir;
	// 自分のアンカーを決める
	if( barDir_ == BARDIR_UP ){
		// 上に伸びていく
        this->setAnchorPoint(ccp(0.5f, 0.0f));
	} else if( barDir_ == BARDIR_DOWN ) {
		// 下に伸びていく
         this->setAnchorPoint(ccp(0.5f, 1.0f));

	} else if( barDir_ == BARDIR_LEFT ) {
		// 左に伸びていく
        this->setAnchorPoint(ccp(1.0f, 0.5f));

	} else if( barDir_ == BARDIR_RIGHT ) {
		// 右に伸びていく
        this->setAnchorPoint(ccp(0.0f, 0.5f));

	}
	isMove_		= false;
	tarVal_		= 0.0f;
	diffVal_    = 0.0f;
//	duration_	= 0.0f;
    this->updateBarLen(_val);
}

//
//void GaugeSprite::onExit()
//{
//	[self moveStop];
//	[super onExit];
//}

// 引数の値の時のバーのスケールを取得
float GaugeSprite::getBarFitScale(double_t _val)
{
	float per = Utility::calcPercentD(_val,minVal_,maxVal_);
	return Utility::getBarScale(per,_bar->getContentSize().width,barLenMax_);
}


// バーの長さを更新
void GaugeSprite::updateBarLen(double_t _val)
{
	this->updateBarLen(_val,minVal_,maxVal_);
}
// バーの長さを更新
void GaugeSprite::updateBarLen(double_t _val,double_t _minVal,double_t _maxVal)
{
	float per = Utility::calcPercentD(_val,_minVal,_maxVal);
	float scale = Utility::getBarScale(per,this->getContentSize().width,barLenMax_);
	if( barDir_ == BARDIR_UP || barDir_ == BARDIR_DOWN ){	// 上下に伸びていく
		this->setScaleY(scale);
	} else {	// 左右に伸びていく
        this->setScaleX(scale);
	}
	val_		= _val;
	minVal_		= _minVal;
	maxVal_		= _maxVal;
}

// 移動開始
bool GaugeSprite::moveStart(double_t _tarVal,double_t _duration)
{
	if( isMove_ ){ return false;}

	isMove_			= true;
	tarVal_			= _tarVal;
	diffVal_		= tarVal_ - val_;
	duration_		= _duration;
    this->schedule(schedule_selector(GaugeSprite::onSchedule));
	return true;
}


void GaugeSprite::onSchedule(float dt)
{
	//NSTimeInterval diffTime	= [NSDate timeIntervalSinceReferenceDate] - moveStartTime;
	//double_t addVal	= (diffVal * diffTime) / duration;
	double_t addVal	= (diffVal_ * dt) / duration_;
	if( diffVal_ < 0.0f && addVal > -0.1f ){
		addVal		= -0.1f;
	} else if( diffVal_ >= 0.0f && addVal < 0.1f ){
		addVal		= 0.1f;
	}
	double_t nextVal	= val_ + addVal;
	//double_t nextVal	= startVal + addVal;
	bool isEnd		= false;
	if( diffVal_ < 0.0f && nextVal <= tarVal_ ){
		isEnd		= true;
		nextVal		= tarVal_;
	} else if( diffVal_ >= 0.0f && nextVal >= tarVal_ ){
		isEnd		= true;
		nextVal		= tarVal_;
	}
	this->updateBarLen(nextVal);
	if( isEnd ){
		this->moveFinish();
	}
}


CCSprite* GaugeSprite::getBar(){
    return _bg;
}


// 移動終了
void GaugeSprite::moveFinish()
{
	if( !isMove_ ){ return; }
	this->moveStop();
	if( gaugeDelegate != NULL){
		gaugeDelegate->onMoveFinish();
	}
}

// 終了処理のキャンセル
void GaugeSprite::cancelFinishSelector()
{
	if( gaugeDelegate != NULL){
		gaugeDelegate->onMoveCancel();
	}
}

// 強制終了
void GaugeSprite::moveForceFinish()
{
	if( !isMove_ ){ return; }
	this->updateBarLen(tarVal_);
	this->moveFinish();
}

// 移動停止
void GaugeSprite::moveStop()
{
	if( !isMove_ ){ return; }
	isMove_			= false;
	this->unschedule(schedule_selector(GaugeSprite::onSchedule));
}