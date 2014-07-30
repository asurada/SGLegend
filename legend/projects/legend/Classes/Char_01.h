//
//  Char_01.h
//  legend
//
//  Created by Yan Wei on 2014/07/24.
//
//

#ifndef __legend__Char_01__
#define __legend__Char_01__
#include "BaseFighter.h"


class Char_01 : public BaseFighter{
private:
    typedef CCSprite super;
    
public:
    static Char_01* create(const char *pszFileName);

    void attack(const char *bulletName);
    
    
    
};

#endif /* defined(__legend__Char_01__) */
