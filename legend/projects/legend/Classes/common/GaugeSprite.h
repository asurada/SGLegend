//
//  GaugeSprite.h
//  legend
//
//  Created by Yan Wei on 2014/09/12.
//
//

#ifndef __legend__GaugeSprite__
#define __legend__GaugeSprite__
#include "cocos2d.h"
#include "Utility.h"
#include "GaugeDelegate.h"

USING_NS_CC;

typedef enum
{
	BARDIR_UP = 0,	// 上に伸びていく
	BARDIR_DOWN,	// 下に伸びていく
	BARDIR_LEFT,	// 左に伸びていく
	BARDIR_RIGHT,	// 右に伸びていく
} GaugeDirection;


class GaugeSprite : public CCSprite{

private:
    CCSprite super;
    CCSprite *_bar;
    CCSprite *_bg;
    
    double_t val_;
    double_t get_val_() const { return val_; }
    double_t set_val_(double_t const& value) { return val_ = value; }

	double_t minVal_;
    double_t get_minVal_() const { return minVal_; }
    double_t set_minVal_(double_t const& value) { return minVal_ = value; }
    
    
	double_t maxVal_;
    double_t get_maxVal_() const { return maxVal_; }
    double_t set_maxVal_(double_t const& value) { return maxVal_ = value; }

    double_t tarVal_;
    double_t get_tarVal_() const { return tarVal_; }
    double_t set_tarVal_(double_t const& value) { return tarVal_ = value; }
    
    
	double_t diffVal_;
    double_t get_diffVal_() const { return diffVal_; }
    double_t set_diffVal_(double_t const& value) { return diffVal_ = value; }
    
    double_t duration_;
    double_t get_duration_() const { return duration_; }
    double_t set_duration_(double_t const& value) { return duration_ = value; }
    
    bool isMove_;
    float barLenMax_;
    int get_isMove_() const { return isMove_; }
    GaugeDirection barDir_;
    
public :
    
    GaugeSprite();
    GaugeSprite(double_t _val,double_t _maxVal);
    ~GaugeSprite();
    
    CC_SYNTHESIZE(GaugeDelegate*, gaugeDelegate, Delegate);
    
    static GaugeSprite* nodeWithBarFile(std::string _barFileName ,float _barLenMax, GaugeDirection _barDir);
    static GaugeSprite* nodeWithBarFile(std::string _barFileName ,float _barLenMax, GaugeDirection _barDir ,double_t _val , double_t _minVal,double_t _maxVal);
    static GaugeSprite* nodeWithBarTexture(CCTexture2D* _barTexture ,float _barLenMax ,GaugeDirection _barDir);
    static GaugeSprite* nodeWithBarTexture(CCTexture2D* _barTexture ,float _barLenMax ,GaugeDirection _barDir, double_t _val ,double_t _minVal ,double_t _maxVal);
    void initBarParam(float _barLenMax ,GaugeDirection _barDir,double_t _val ,double_t _minVal ,double_t _maxVal);
    
    void onSchedule(float dt);
    bool moveStart(double_t _tarVal,double_t _duration);
    float getBarFitScale(double_t _val);
    void updateBarLen(double_t _val);
    void updateBarLen(double_t _val ,double_t _minVal ,double_t _maxVal);
    void moveFinish();
    void cancelFinishSelector();
    void moveForceFinish();
    void moveStop();
    CCSprite *getBar();
    
    
    
//    virtual void onMoveStart() = 0;
//    virtual void onMoveCancel() = 0;
//    virtual void onMoveForceFinish() = 0;
//    virtual void onMoveFinish() = 0;
    
};

#endif /* defined(__legend__GaugeSprite__) */
