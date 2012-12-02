#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofBackground(255, 255, 255);
    ofEnableAlphaBlending();
	ofSetVerticalSync(true);
    ofSetLogLevel(OF_LOG_VERBOSE);
    maxUsers = 2;
    for(int i=0;i<maxUsers;i++){
        ps.push_back(false);
    }
    openNIDevice.setup();
    openNIDevice.addImageGenerator();
    openNIDevice.addDepthGenerator();
    openNIDevice.setRegister(true);
    openNIDevice.setMirror(true);
    openNIDevice.addUserGenerator();
    openNIDevice.setMaxNumUsers(2);
    openNIDevice.start();
}

//--------------------------------------------------------------
void testApp::update(){
    for(int i=0; i<creatures.size();i++){
        creatures[i].update();
    }
    openNIDevice.update();
}

//--------------------------------------------------------------
void testApp::draw(){
    
    for(int i=0; i<creatures.size();i++){
        creatures[i].draw();
    }
    // get number of current users
    int numUsers = openNIDevice.getNumTrackedUsers();
    
    if(numUsers<creatures.size()){
        for(int i=0;i<creatures.size();i++){
            creatures.erase(creatures.begin());
            i = 0;
        }
        
        for(int i=numUsers;i<maxUsers;i++){
            ps[i] = false;
        }
//        
//        if(numUsers == 1){
//            p2 = false;
//        } else if (numUsers == 0){
//            p1 = false;
//            p2 = false;
//        }
    }
    
    for(int i=0;i<numUsers;i++){
        if(numUsers == (i+1) && ps[i] == false){
            creature baby;
            baby.immaculate();
            creatures.push_back(baby);
            ps[i] = true;
        }
    }
}

//--------------------------------------------------------------
void testApp::userEvent(ofxOpenNIUserEvent & event){
    // show user event messages in the console
    ofLogNotice() << getUserStatusAsString(event.userStatus) << "for user" << event.id << "from device" << event.deviceID;
}

//--------------------------------------------------------------
void testApp::exit(){
    openNIDevice.stop();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if(key == 'b'){
        cout << "ba" << endl;
    }
    
    if(key == 'c'){
        creature baby;
        baby.immaculate();
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