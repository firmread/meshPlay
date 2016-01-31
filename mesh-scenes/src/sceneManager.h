

#pragma once

#include "ofMain.h"
#include "baseScene.h"
#include "appConstants.h"



class sceneManager {
    
private:
    
    void nextScene(bool forward);
    
public:
    
    
    vector < baseScene * > scenes;
    int currentScene;
    
    void setup();
    void update();
    void draw();
    
    void advanceScene();
    void regressScene();
    
    ofFbo sceneFbo;
    ofFbo codeFbo;
    
};
