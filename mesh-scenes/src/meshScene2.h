//
//  meshScene2.hpp
//  meshScenes
//
//  Created by Reed Tothong on 1/27/16.
//
//

#pragma once

#include "ofMain.h"
#include "baseScene.h"

class meshScene2 : public baseScene {
    
public:
    
    void setup();
    void update();
    void draw();
    
    
    ofMesh mesh;
};