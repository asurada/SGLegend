//
//  CCPath.h
//  legend
//
//  Created by 厳 巍 on 2014/06/10.
//
//

#ifndef __legend__CCPath__
#define __legend__CCPath__

#include "cocos2d.h"

typedef cocos2d::ccVertex2F CGPoint_x;
#define cgp(__X__, __Y__) vertex2(__X__, __Y__)

class CCPath : public cocos2d::CCNodeRGBA {
private:
    CC_SYNTHESIZE_RETAIN(cocos2d::CCTexture2D *, _texture, Texture);
    int _pointLimit;
    std::vector<CGPoint_x> _path;
    CGPoint_x *_vertices;
    CGPoint_x *_texCoords;
    bool _autoCleanup;
    // shader stuff
    GLint _uniformColor;
private:
    CCPath(const char *filePath, float stroke, int pointLimit);
    virtual ~CCPath();
    void populateVertices();
    void pop(int count);
    void popLastOne(float delta);
    void draw();
public:
    CC_PROPERTY(float, _stroke, Stroke);
    CC_PROPERTY(float, _drainInterval, DrainInterval);
public:
    static CCPath* create(const char *filePath, float stroke, int pointLimit);
    void push(const cocos2d::CCPoint &point);
    void autoCleanup();
};

#endif