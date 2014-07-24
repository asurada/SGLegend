//
//  BaseEnemy.cpp
//  legend
//
//  Created by Yan Wei on 2014/07/24.
//
//

#include "BaseFighter.h"

BaseFighter* BaseFighter::create(const char *pszFileName){
    return (BaseFighter*)super::create(pszFileName);
}