
#pragma once

#include "ofMain.h"

class baseScene {
    
public:
    
    virtual void setup(){}
    virtual void update(){}
    virtual void draw(){}
    virtual void keyPressed(){}
    
    virtual void reset(){}
    
    baseScene(){};
    ~baseScene(){}

    
    ofRectangle dimensions;     // this is the dimensions of
    // the surface you are drawing into.
    
};