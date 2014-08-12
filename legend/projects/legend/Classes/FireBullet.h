//
//  FireBullet.h
//  legend
//
//  Created by Yan Wei on 2014/07/24.
//
//

#ifndef __legend__FireBullet__
#define __legend__FireBullet__

#include "BaseBullet.h"
#include "cocos2d.h"

class FireBullet : public BaseBullet{
    public:
        const char * image = "fire2.png";
        const char *plist = "fire2.plist";
        const char *imgSplit = "fire";
        void explode();
        static FireBullet* create(const char *pszFileName);
    
    private:
        typedef BaseBullet super;
    
};

#endif /* defined(__legend__FireBullet__) */
