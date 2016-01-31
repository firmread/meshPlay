//
//  equiScene.hpp
//  meshScenes
//
//  Created by Reed Tothong on 1/27/16.
//
//
#pragma once

#include "ofMain.h"
#include "baseScene.h"
#include "ofxEquiMap.h"

class equiScene : public baseScene, public ofxEquiMap::Scene {
    
public:
    
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    
    void drawEquiScene();

    ofMesh mesh;
    ofImage image;
    
    ofEasyCam easyCam;
    
    vector<ofVec3f> offsets;
    
    // We are going to use these to allow us to toggle orbiting on and off
    ofMesh meshCopy;
    bool orbiting;
    float startOrbitTime;
    
    // These variables will let us store the polar coordinates of each vertex
    vector<float> distances;
    vector<float> angles;
    ofVec3f meshCentroid;
    
    
    // Like with the orbiting tweak, this gives us a way to toggle on and off our magnifying effect
    bool mouseDisplacement;
    
    ofxEquiMap::Renderer em;
    ofVboMesh m;

};