#include "ofApp.h"

void ofApp::setupExample1(){
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

void ofApp::setupExample2(){
    mesh.setMode(OF_PRIMITIVE_LINES);
    mesh.enableColors();
    mesh.enableIndices();
    
    ofVec3f eyeLeftTop(50.0, 25.0, 0.0);
    ofVec3f eyeLeftBottom(50.0, 50.0, 0.0);
    ofVec3f eyeRightTop(100.0, 25.0, 0.0);
    ofVec3f eyeRightBottom(100.0, 50.0, 0.0);
    ofVec3f mouthLeft(50.0, 75.0, 0.0);
    ofVec3f mouthMiddle(75.0, 100.0, 0.0);
    ofVec3f mouthRight(100.0, 75.0, 0.0);
    
    mesh.addVertex(eyeLeftTop);
    mesh.addVertex(eyeLeftBottom);
    mesh.addIndex(0);
    mesh.addIndex(1);
    mesh.addColor(ofFloatColor(0.0, 1.0, 1.0));
    mesh.addColor(ofFloatColor(0.0, 1.0, 1.0));
    
    mesh.addVertex(eyeRightTop);
    mesh.addVertex(eyeRightBottom);
    mesh.addIndex(2);
    mesh.addIndex(3);
    mesh.addColor(ofFloatColor(0.0, 1.0, 1.0));
    mesh.addColor(ofFloatColor(0.0, 1.0, 1.0));
    
    mesh.addVertex(mouthLeft);
    mesh.addVertex(mouthMiddle);
    mesh.addVertex(mouthRight);
    mesh.addIndex(4);
    mesh.addIndex(5);
    mesh.addIndex(5);
    mesh.addIndex(6);
    mesh.addColor(ofFloatColor(0.0, 1.0, 0.0));
    mesh.addColor(ofFloatColor(0.0, 1.0, 0.0));
    mesh.addColor(ofFloatColor(0.0, 1.0, 0.0));

}

//--------------------------------------------------------------
void ofApp::setup(){

    //setupExample1();
    //setupExample2();
    
    ofSetFrameRate(60);
    
    bool bLoadImageSuccess = true;
    bLoadImageSuccess = image.load("stars.png");
    if (!bLoadImageSuccess) {
    cerr << "loading image failed ..." << endl;
    }
//    ofSetWindowShape(image.getWidth(), image.getHeight());
    float scale = 3;
    image.resize(image.getWidth()/scale, image.getHeight()/scale);
//    mesh.setMode(OF_PRIMITIVE_POINTS);
    
    mesh.setMode(OF_PRIMITIVE_LINES);
    
    float intensityThreshold = 150.0;
    int w = image.getWidth();
    int h = image.getHeight();
    for (int x=0; x<w; ++x) {
        for (int y=0; y<h; ++y) {
            ofColor c = image.getColor(x, y);
            float intensity = c.getLightness();
//            if (intensity >= intensityThreshold) {
//                ofVec3f pos(x*scale, y*scale, 0.0);
//                mesh.addVertex(pos);
//                mesh.addColor(c);
//            }
            if (intensity >= intensityThreshold) {
                float saturation = c.getSaturation();
                float z = ofMap(saturation, 0, 255, -100, 100);
                ofVec3f pos(x*4, y*4, z);
                mesh.addVertex(pos);
                mesh.addColor(c);
                offsets.push_back(ofVec3f(ofRandom(0,100000), ofRandom(0,100000), ofRandom(0,100000)));
            }
        }
    }
    
    
    // Let's add some lines!
    float connectionDistance = 30;
    int numVerts = mesh.getNumVertices();
    for (int a=0; a<numVerts; ++a) {
        ofVec3f verta = mesh.getVertex(a);
        for (int b=a+1; b<numVerts; ++b) {
            ofVec3f vertb = mesh.getVertex(b);
            float distance = verta.distance(vertb);
            if (distance <= connectionDistance) {
                mesh.addIndex(a);
                mesh.addIndex(b);
            }
        }
    }
    
    // We need to calculate our center point for the mesh
    // ofMesh has a method called getCentroid() that will
    // find the average location over all of our vertices
    //    http://en.wikipedia.org/wiki/Centroid
    meshCentroid = mesh.getCentroid();
    
    // Now that we know our centroid, we need to know the polar coordinates (distance and angle)
    // of each vertex relative to that center point.
    // We've found the distance between points before, but what about the angle?
    // This is where atan2 comes in.  atan2(y, x) takes an x and y value and returns the angle relative
    //     to the origin (0,0).  If we want the angle between two points (x1, y1) and (x2, y2) then we
    //     just need to use atan2(y2-y1, x2-x1).
    for (int i=0; i<numVerts; ++i) {
        ofVec3f vert = mesh.getVertex(i);
        float distance = vert.distance(meshCentroid);
        float angle = atan2(vert.y-meshCentroid.y, vert.x-meshCentroid.x);
        distances.push_back(distance);
        angles.push_back(angle);
    }
    
    // These variables will allow us to toggle orbiting on and off
    orbiting = false;
    startOrbitTime = 0.0;
    meshCopy = mesh;        // Store a copy of the mesh, so that we can reload the original state
    
    
    // We want to start off without the effect turned on
    mouseDisplacement = false;
    
    
    //equimap
    em.setup(1024, this);
    ofSpherePrimitive p(1000, 24);
    m = p.getMesh();
    
    
    //syphon
    
    mainOutputSyphonServer.setName("Screen Output");
    individualTextureSyphonServer.setName("Texture Output");
    
    mClient.setup();
    
    //using Syphon app Simple Server, found at http://syphon.v002.info/
    mClient.set("","Simple Server");
    
    tex.allocate(200, 100, GL_RGBA);

    
}

//--------------------------------------------------------------
void ofApp::update(){
    int numVerts = mesh.getNumVertices();
    for (int i=0; i<numVerts; ++i) {
        ofVec3f vert = mesh.getVertex(i);
        
        float time = ofGetElapsedTimef();
        float timeScale = 5.0;
        float displacementScale = 0.75;
        ofVec3f timeOffsets = offsets[i];
        
        // A typical design pattern for using Perlin noise uses a couple parameters:
        // ofSignedNoise(time*timeScale+timeOffset)*displacementScale
        //     ofSignedNoise(time) gives us noise values that change smoothly over time
        //     ofSignedNoise(time*timeScale) allows us to control the smoothness of our noise (smaller timeScale, smoother values)
        //     ofSignedNoise(time+timeOffset) allows us to use the same Perlin noise function to control multiple things and have them look as if they are moving independently
        //     ofSignedNoise(time)*displacementScale allows us to change the bounds of the noise from [-1, 1] to whatever we want
        // Combine all of those parameters together, and you've got some nice control over your noise
        
        vert.x += (ofSignedNoise(time*timeScale+timeOffsets.x)) * displacementScale;
        vert.y += (ofSignedNoise(time*timeScale+timeOffsets.y)) * displacementScale;
        vert.z += (ofSignedNoise(time*timeScale+timeOffsets.z)) * displacementScale;
        mesh.setVertex(i, vert);
    }
    
    if (orbiting) {
        int numVerts = mesh.getNumVertices();
        for (int i=0; i<numVerts; ++i) {
            ofVec3f vert = mesh.getVertex(i);
            float distance = distances[i];
            float angle = angles[i];
            float elapsedTime = ofGetElapsedTimef() - startOrbitTime;
            
            // Lets adjust the speed of the orbits such that things that are closer to
            // the center rotate faster than things that are more distant
            float speed = ofMap(distance, 0, 400, 1, 0.25);
            
            // To find the angular rotation of our vertex, we use the current time and
            // the starting angular rotation
            float rotatedAngle = elapsedTime * speed + angle;
            
            // Remember that our distances are calculated relative to the centroid of the mesh, so
            // we need to shift everything back to screen coordinates by adding the x and y of the centroid
            vert.x = distance * cos(rotatedAngle) + meshCentroid.x;
            vert.y = distance * sin(rotatedAngle) + meshCentroid.y;
            
            mesh.setVertex(i, vert);
        }
    }
    
    
    if (mouseDisplacement) {
        // Get the mouse location - it must be relative to the center of our screen because of the ofTranslate() command in draw()
        ofVec3f mouse(mouseX, ofGetWidth()-mouseY, 0);
        
        // Loop through all the vertices in the mesh and move them away from the mouses
        for (int i=0; i<mesh.getNumVertices(); ++i) {
            ofVec3f vertex = meshCopy.getVertex(i);
            float distanceToMouse = mouse.distance(vertex);
            
            // Scale the displacement based on the distance to the mouse
            // Small distance to mouse should yield a small displacement
            float displacement = ofMap(distanceToMouse, 0, 400, 300.0, 0, true);
            
            // Calculate the direction from the mouse to the current vertex
            ofVec3f direction = vertex - mouse;
            
            // Normalize the direction so that it has a length of one
            // This lets us easily change the length of the vector later
            direction.normalize();
            
            // Push the vertex in the direction away from the mouse and push it
            // a distance equal to the value of the variable displacement
            ofVec3f displacedVertex = vertex + displacement*direction;
            mesh.setVertex(i, displacedVertex);
        }
    }
    
    em.render();
}



void ofApp::drawEquiScene()
{
//    ofPushStyle();
//    ofSetLineWidth(3);
//    ofSetColor(192);
//    m.drawWireframe();
//    ofPopStyle();
    
    
    ofColor centerColor = ofColor(85, 78, 68);
    ofColor edgeColor(0, 0, 0);
    ofBackgroundGradient(centerColor, edgeColor, OF_GRADIENT_CIRCULAR);
    
    easyCam.begin();
    ofPushMatrix();
    ofTranslate(-ofGetWidth()/2, -ofGetHeight()/2);
    mesh.draw();
    ofPopMatrix();
    easyCam.end();
}


//--------------------------------------------------------------
void ofApp::draw(){
//    ofBackground(ofColor::navy);
    
//    ofColor centerColor = ofColor(85, 78, 68);
//    ofColor edgeColor(0, 0, 0);
//    ofBackgroundGradient(centerColor, edgeColor, OF_GRADIENT_CIRCULAR);
//    mesh.draw();
//    cout << mesh.getNumVertices() << endl;
//    image.draw(0,0);
    
    
    /*
    ofColor centerColor = ofColor(85, 78, 68);
    ofColor edgeColor(0, 0, 0);
    ofBackgroundGradient(centerColor, edgeColor, OF_GRADIENT_CIRCULAR);
    
    easyCam.begin();
    ofPushMatrix();
    ofTranslate(-ofGetWidth()/2, -ofGetHeight()/2);
    mesh.draw();
    ofPopMatrix();
    easyCam.end();
*/
    
    
    
    // Clear with alpha, so we can capture via syphon and composite elsewhere should we want.
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    
    
    
    ofClear(0);
    em.draw(0, 0, ofGetWidth(), ofGetHeight());
    
    
    
    
    
    // draw static into our one texture.
    unsigned char pixels[200*100*4];
    
    for (int i = 0; i < 200*100*4; i++)
    {
        pixels[i] = (int)(255 * ofRandomuf());
    }
    tex.loadData(pixels, 200, 100, GL_RGBA);
    
    ofSetColor(255, 255, 255);
    
    ofEnableAlphaBlending();
    
//    tex.draw(50, 50);
    
    // Syphon Stuff
    
    mClient.draw(50, 50);
    
    mainOutputSyphonServer.publishScreen();
    
    individualTextureSyphonServer.publishTexture(&tex);
    
    ofDrawBitmapStringHighlight(ofToString(ofGetFrameRate()), 10, 20);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'o') {
        orbiting = !orbiting;           // This inverts the boolean
        startOrbitTime = ofGetElapsedTimef();
        mesh = meshCopy;            // This restores the mesh to its original values
    }
    if (key == 'm') {
        mouseDisplacement = !mouseDisplacement;  // Inverts the boolean
        mesh = meshCopy;  // Restore the original mesh
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
