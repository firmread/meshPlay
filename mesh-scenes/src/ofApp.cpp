#include "ofApp.h"

void ofApp::setup(){
    
    ofSetFrameRate(60);
    
    //syphon
    mainOutput.setName("Screen Output");
    texOutput.setName("Texture Output");
    mClient.setup();
    //using Syphon app Simple Server, found at http://syphon.v002.info/
    mClient.set("","Simple Server");
    tex.allocate(200, 100, GL_RGBA);
    
    SM.setup();
}

void ofApp::update(){
    SM.update();
}
void ofApp::draw(){    
    
    // draw static into our one texture.
    ofPushStyle();
    unsigned char pixels[200*100*4];
    for (int i = 0; i < 200*100*4; i++){
        pixels[i] = (int)(255 * ofRandomuf());
    }
    tex.loadData(pixels, 200, 100, GL_RGBA);
    ofPopStyle();
//    ofSetColor(255, 255, 255);
    ofEnableAlphaBlending();
//    tex.draw(50, 50);
    
    
    SM.draw();
    
    
    // Syphon Stuff
    mClient.draw(50, 50);
    mainOutput.publishScreen();
    texOutput.publishTexture(&tex);
    ofDrawBitmapStringHighlight(ofToString(ofGetFrameRate()), 10, 20);

}
void ofApp::keyPressed(int key){
    if (key == ' '){
        SM.advanceScene();
    } else if (key == '.'){
        SM.regressScene();
    }
}
void ofApp::keyReleased(int key){ }
void ofApp::mouseMoved(int x, int y ){ }
void ofApp::mouseDragged(int x, int y, int button){ }
void ofApp::mousePressed(int x, int y, int button){ }
void ofApp::mouseReleased(int x, int y, int button){ }
void ofApp::mouseEntered(int x, int y){ }
void ofApp::mouseExited(int x, int y){ }
void ofApp::windowResized(int w, int h){
    fixScreenSize();
}
void ofApp::gotMessage(ofMessage msg){ }
void ofApp::dragEvent(ofDragInfo dragInfo){ }
void ofApp::fixScreenSize(){
    float width = VISUALS_WIDTH;
    float height = VISUALS_HEIGHT;
    ofSetWindowShape(width, height);
}

