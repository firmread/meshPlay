//
//  meshScene1.cpp
//  meshScenes
//
//  Created by Reed Tothong on 1/27/16.
//
//

#include "meshScene1.h"


void meshScene1::setup(){
    
    //    mesh.setMode(OF_PRIMITIVE_POINTS);
    //    mesh.setMode(OF_PRIMITIVE_LINES);
    //    mesh.setMode(OF_PRIMITIVE_LINE_STRIP);
    //    mesh.setMode(OF_PRIMITIVE_LINE_LOOP);
    mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    mesh.enableColors();
    
    ofVec3f top(100.0, 50.0, 0.0);
    ofVec3f left(50.0, 150.0, 0.0);
    ofVec3f right(150.0, 150.0, 0.0);
    
    mesh.addVertex(top);
    mesh.addColor(ofFloatColor(1.0, 0.0, 0.0));
    
    mesh.addVertex(left);
    mesh.addColor(ofFloatColor(0.0, 1.0, 0.0));
    
    mesh.addVertex(right);
    mesh.addColor(ofFloatColor(1.0, 1.0, 0.0));
}

void meshScene1::update(){
    
}

void meshScene1::draw(){
    mesh.draw();
}