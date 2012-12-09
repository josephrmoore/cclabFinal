#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofBackground(255, 255, 255);
    ofEnableAlphaBlending();
	ofSetVerticalSync(true);
//    ofSetLogLevel(OF_LOG_VERBOSE);
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
    
    box2d.init();
	box2d.setGravity(0, 0);
	box2d.createBounds(0,0,ofGetWidth(),ofGetHeight());
	box2d.setFPS(30.0);
	box2d.registerGrabbing();
    
    // register the listener so that we get the events
	ofAddListener(box2d.contactStartEvents, this, &testApp::contactStart);
	ofAddListener(box2d.contactEndEvents, this, &testApp::contactEnd);
    
    rev = false;
    millis = ofGetElapsedTimeMillis();
    
//	
//    // register the listener so that we get the events
//	ofAddListener(box2d.contactStartEvents, this, &testApp::contactStart);
//	ofAddListener(box2d.contactEndEvents, this, &testApp::contactEnd);
    
}

//--------------------------------------------------------------
void testApp::contactStart(ofxBox2dContactArgs &e) {
	if(e.a != NULL && e.b != NULL) { 
		
		// if we collide with the ground we do not
		// want to play a sound. this is how you do that
		if(e.a->GetType() == b2Shape::e_circle && e.b->GetType() == b2Shape::e_circle) {
//            cout << e.a->GetBody()->GetUserData() << endl;
//			cout << e.b->GetBody()->GetUserData() << endl;
//            ofxBox2dCircle collided;
//            for (int i=0; i<creatures.size();i++){
//                if(creatures[i].collided = ?????){
//                    GET COLLISION PARTNER
//                    DO BREEDING FXInfo
//                }
//            }
			
//			if() {
//
//			}
//			
//			if() {
//
//			}
		}
	}
}

//--------------------------------------------------------------
void testApp::contactEnd(ofxBox2dContactArgs &e) {
	if(e.a != NULL && e.b != NULL) { 
		
//        cout << e.a->GetBody()->GetUserData() << endl;
//        cout << e.b->GetBody()->GetUserData() << endl;


//		if() {
//			
//		}
//		
//		if() {
//			
//		}
	}
}

//--------------------------------------------------------------
void testApp::update(){
    for(int i=0; i<creatures.size();i++){
        creatures[i].update();
    }
    openNIDevice.update();
    box2d.update();
    if(timer<=1000){
        timer = ofGetElapsedTimeMillis()-millis;
        rev = false;
    } else {
        millis = ofGetElapsedTimeMillis();
        timer = ofGetElapsedTimeMillis()-millis;
        rev = true;
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    
    // get number of current users
    int numUsers = openNIDevice.getNumTrackedUsers();
        
//    if(numUsers<creatures.size()){
//        for(int i=0;i<creatures.size();i++){
//            creatures.erase(creatures.begin());
//            i = 0;
//        }
//        for(int i=numUsers;i<maxUsers;i++){
//            ps[i] = false;
//        }
//        
//        if(numUsers == 1){
//            p2 = false;
//        } else if (numUsers == 0){
//            p1 = false;
//            p2 = false;
//        }
//    }
    
    for(int i=0;i<numUsers;i++){
        ofxOpenNIUser & user = openNIDevice.getTrackedUser(i);
            bool thisuser = false;
            for(int j=0;j<creatures.size();j++){
                for(int k=0;k<numUsers;k++){
                    ofxOpenNIUser & user = openNIDevice.getTrackedUser(k);
                }
                if(user.getXnID() == creatures[j].userId){
                    ofPoint & center = user.getCenter();
                    creatures[j].user_x = center.x;
                    creatures[j].user_y = center.z;
                    
                    cout << center.x << endl;
                    cout << center.z << endl;
                    if(rev == true && center.x>0){
                        cout << "Rev" << endl;
                        ofVec2f loc, amt;
                        int x1, y1, x2, y2;
                        if(creatures[j].user_x-creatures[j].user_last_x<0){
                            // force to the left
                            x1 = creatures[j].xpos+50;
                            x2 = ofMap(creatures[j].xpos-50, 0, ofGetWidth()+100, 0, 1);
                        } else if (creatures[j].user_x-creatures[j].user_last_x>0){
                            // force to the right
                            x1 = creatures[j].xpos-50;
                            x2 = ofMap(creatures[j].xpos-50, 0, ofGetWidth()+100, 0, 1);
                        }
                        if(creatures[j].user_y-creatures[j].user_last_y<0){
                            // force toward up
                            y1 = creatures[j].ypos+50;
                            y2 = ofMap(creatures[j].ypos-50, 0, ofGetHeight()+100, 0, 1);
                        } else if (creatures[j].user_y-creatures[j].user_last_y>0){
                            // force toward down
                            y1 = creatures[j].ypos-50;
                            y2 = ofMap(creatures[j].ypos+50, 0, ofGetHeight()+100, 0, 1);
                        }
                        loc = ofVec2f(x1, y1);
                        amt = ofVec2f(x2, y2);
                        creatures[j].circle.addImpulseForce(amt, loc);
                        creatures[j].user_last_x = user.getCenter().x;
                        creatures[j].user_last_y = user.getCenter().y;  
                    }
                    thisuser = true;
                    if(user.isSkeleton()){
                        creatures[j].draw();
                    } else {
                        creatures.erase(creatures.begin()+j);
                    }
                }
            }
            if(!thisuser){
                creature baby;
                baby.immaculate(box2d.getWorld(), user.getXnID());
                creatures.push_back(baby);
            }

//        cout << "Found:" << endl;
//        cout << user.isFound() << endl;
//        cout << "Tracking:" << endl;
//        cout << user.isTracking() << endl;
//        cout << "Skeleton:" << endl;
//        cout << user.isSkeleton() << endl;
//        cout << "Calibrating:" << endl;
//        cout << user.isCalibrating() << endl;

//        if(numUsers == (i+1) && ps[i] == false){
//            creature baby;
//            baby.immaculate(box2d.getWorld());
//            creatures.push_back(baby);
//            ps[i] = true;
//        }
    }
    bool extracreature = false;
    for(int i=0;i<creatures.size();i++){
        for(int j=0;j<numUsers;j++){
            ofxOpenNIUser & user = openNIDevice.getTrackedUser(j);
            if(user.getXnID() == creatures[j].userId){
                extracreature = true;
            }
        }
        if(!extracreature){
            creatures.erase(creatures.begin()+i);
        }
    }
    
//    for(int i=0; i<circles.size(); i++) {
//		ofFill();
//		ofSetHexColor(0x90d4e3);
//		circles[i].draw();
//	}
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
//        creature baby;
//        baby.immaculate(box2d.getWorld());
//        creatures.push_back(baby);
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