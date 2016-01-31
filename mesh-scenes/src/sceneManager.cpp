//
//  sceneManager.cpp
//  d4nSFPCRunner
//
//  Created by zach on 11/14/15.
//
//

#include "sceneManager.h"
#include "emptyScene.h"
#include "meshScene1.h"
#include "meshScene2.h"
#include "equiScene.h"

void sceneManager::setup(){
    
//    scenes.push_back(new emptyScene() );
    scenes.push_back(new meshScene1() );
    scenes.push_back(new meshScene2() );
    scenes.push_back(new equiScene() );
    
    sceneFbo.allocate(VISUALS_WIDTH, VISUALS_HEIGHT, GL_RGBA, 4);
    codeFbo.allocate(VISUALS_WIDTH, VISUALS_HEIGHT, GL_RGBA, 4);
    
    
    for (auto scene : scenes){
        scene->dimensions.set(0,0,VISUALS_WIDTH, VISUALS_HEIGHT);
        scene->setup();
    }
    
    currentScene = 0;
    scenes[currentScene]->reset();
    
    
    
}

void sceneManager::update(){
    scenes[currentScene]->update();
}

void sceneManager::draw(){
    
    sceneFbo.begin();
    ofClear(0,0,0,255);
    ofPushStyle();
    scenes[currentScene]->draw();
    ofPopStyle();
    ofClearAlpha();
    sceneFbo.end();
    
    sceneFbo.draw(0,0);
    
}

void sceneManager::nextScene(bool forward){
    if (forward){
        currentScene ++;
        currentScene %= scenes.size();
    } else {
        currentScene --;
        if (currentScene < 0){
            currentScene = scenes.size() - 1;
        }
    }
    
    scenes[currentScene]->reset();

};

void sceneManager::advanceScene(){
    nextScene(true);
};

void sceneManager::regressScene(){
    nextScene(false);
};
