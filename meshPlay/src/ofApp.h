#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    void setupExample1();
    void setupExample2();
    
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
};
