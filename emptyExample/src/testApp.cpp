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
    
    rev = true;
    millis = ofGetElapsedTimeMillis();
    timer = 0;
    
    if(!my_img.loadImage("http://www.greenfoot.org/images/calibration-pose.png?1345204192")){
        ofLog(OF_LOG_ERROR,"Errorwhileloadingimage");
    }
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
    int numUsers = openNIDevice.getNumTrackedUsers();
    for(int i=0;i<numUsers;i++){
        ofxOpenNIUser & user = openNIDevice.getTrackedUser(i);
        bool thisuser = false;
        for(int j=0;j<creatures.size();j++){
            if(creatures[j].justPushed == true){
                cout<<"timeron"<<endl;
                if(timer == 150){
                    creatures[j].justPushed = false;
                }
                if(timer>=150){
                    millis = ofGetElapsedTimeMillis();
                    timer = 0;
                }
                if(ofGetElapsedTimeMillis()-millis>150){
                    timer = 150;
                } else {
                    timer = ofGetElapsedTimeMillis()-millis;
                }
//                cout<<timer<<endl;
            }
            if(user.getXnID() == creatures[j].userId){
                ofPoint & center = user.getCenter();
                ofPoint userPt = openNIDevice.worldToProjective(center);
                creatures[j].user_x = userPt.x;
                creatures[j].user_y = userPt.y;
                if(!creatures[j].user_last_x){
                    creatures[j].user_last_x = creatures[j].user_x;
                }
                if(!creatures[j].user_last_y){
                    creatures[j].user_last_y = creatures[j].user_y;
                }
                if(userPt.x){
                    ofVec2f loc, amt;
                    int x1, y1, x2, y2, diffX, diffY;
                    diffX = creatures[j].user_x-creatures[j].user_last_x;
                    diffY = creatures[j].user_y-creatures[j].user_last_y;
                    x1 = creatures[j].circle.getPosition().x;
                    x2 = diffX;
                    y1 = creatures[j].circle.getPosition().y;
                    y2 = diffY;
//                    cout << x1 << endl;
//                    cout << x2 << endl;
//                    cout << " " << endl;
//                    cout << y1 << endl;
//                    cout << y2 << endl;
//                    cout << " " << endl;
//                    cout << "END" << endl;
//                    cout << " " << endl;
                    amt = ofVec2f(x2, y2);
                    loc = ofVec2f(x1, y1);
                    if((diffX > 3 || diffY > 3) && creatures[j].justPushed == false){
                        creatures[j].circle.addImpulseForce(amt, loc);
                        creatures[j].justPushed = true;
                        creatures[j].user_last_x = userPt.x;
                        creatures[j].user_last_y = userPt.y;
                    }  
                }
                thisuser = true;
            }
        }
        if(!thisuser){
            creature baby;
            baby.immaculate(box2d.getWorld(), user.getXnID());
            creatures.push_back(baby);
        }
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
}

//--------------------------------------------------------------
void testApp::draw(){
    int numUsers = openNIDevice.getNumTrackedUsers();
    for(int i=0;i<numUsers;i++){
        ofxOpenNIUser & user = openNIDevice.getTrackedUser(i);
        for(int j=0;j<creatures.size();j++){
            if(user.getXnID() == creatures[j].userId){
                if(user.isSkeleton()){
                    creatures[j].draw();
                } else if (user.isFound()){
                    creatures.erase(creatures.begin()+j);
                    my_img.draw(200,0,ofGetWidth()-400,ofGetHeight());

                    cout << "Calibrate please." << endl;
                } else {
                    creatures.erase(creatures.begin()+j);
                }
            }
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