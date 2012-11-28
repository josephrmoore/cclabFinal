#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofBackground(255, 255, 255);
    ofEnableAlphaBlending();
	ofSetVerticalSync(true);
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
    if(myswitch){

    }
    
    for(int i=0; i<creatures.size();i++){
        creatures[i].draw();
    }
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if(key == 'b'){
        if(myswitch){
            myswitch = false;
        } else {
            myswitch = true;
        }
        cout << "ba" << endl;
    }
    
    if(key == 'c'){
        creature baby;
        baby.immaculate();
        cout << "age: " << baby.adult_age << endl;
        cout << "color: " << baby.adult_color << endl;
        cout << "sides: " << baby.adult_sides << endl;
        cout << "size: " << baby.adult_size << endl;
        creatures.push_back(baby);
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}