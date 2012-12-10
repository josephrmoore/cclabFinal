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
    timerInterval = 1000;
    totalNpcs = 5;
    newCircle = false;
    p1 = 0;
    p2= 0;
    state = 0;
    if(!my_img.loadImage("bk.png")){
        ofLog(OF_LOG_ERROR,"Errorwhileloadingimage");
    }
    for(int i=0;i<totalNpcs;i++){
        creature baby;
        baby.immaculate(box2d.getWorld(), 0);
        npc.push_back(baby);
    }
    
}

//--------------------------------------------------------------
void testApp::contactStart(ofxBox2dContactArgs &e) {
    b2Body * c = e.a->GetBody();
    b2Body * d = e.b->GetBody();
    int a,b;
//    cout<<c->GetPosition().x<<endl;
//    cout<<d->GetPosition().x<<endl;
    for(int i=0;i<npc.size();i++){
        if(npc[i].circle.body->GetPosition().x == c->GetPosition().x){
            a=i;
//            cout<<npc[i].adult_size<<endl;
        }
        if(npc[i].circle.body->GetPosition().x == d->GetPosition().x){
            b=i;
//            cout<<npc[i].adult_size<<endl;
        }
    }
    if((a >=0 && b >=0) && (a<npc.size() && b<npc.size())){
        if(npc[a].curr_size==npc[a].adult_size && npc[b].curr_size==npc[b].adult_size){
//            newCircle = true;
        }
//        cout<<a<<endl;
//        cout<<b<<endl;
        
//        npc[a].livebirth(npc[a], npc[b], box2d.getWorld(), 0);
    }
	
    if(e.a != NULL && e.b != NULL) { 
		// if we collide with the ground we do not
		// want to play a sound. this is how you do that
//        cout<<(e.a->GetBody()->GetUserData())<<endl;
//        cout<<(e.b->GetBody()->GetUserData())<<endl;
		if(e.a->GetType() == b2Shape::e_circle && e.b->GetType() == b2Shape::e_circle) {
            ofxBox2dCircle * me = (ofxBox2dCircle*)e.a->GetBody()->GetUserData();
            ofxBox2dCircle * partner = (ofxBox2dCircle*)e.b->GetBody()->GetUserData();
//            if(me){
//                int x = me->getPosition().x;
//                int y = me->getPosition().y;
//                cout<<x<<endl;
//                cout<<y<<endl;
//                
//            }
//            cout<<me->getRadius()<<endl;
//            cout<<me<<endl;
//            cout<<partner<<endl;
//            me->livebirth(partner, box2d.getWorld(), 0);
//            cout << e.a << endl;
//            cout << e.b << endl;
            
//            cout<<"contactstart"<<endl;
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
        if(e.a->GetType() == b2Shape::e_circle && e.b->GetType() == b2Shape::e_circle) {
//            cout<<"contactend"<<endl;
        }


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
    if(state == 0){
    numUsers = openNIDevice.getNumTrackedUsers();
    for(int i=0;i<numUsers;i++){
        ofxOpenNIUser & user = openNIDevice.getTrackedUser(i);
        ofPoint & center = user.getCenter();
        ofPoint userPt = openNIDevice.worldToProjective(center);
        if(i==0){
            p1 = ofMap(userPt.x, 0, 640, 0, 1400);
        } 
        if(i==1){
            p2 = ofMap(userPt.x, 0, 640, 0, 1400);
        }
    }
    if(npc.size()<totalNpcs){
        for(int i=0; i<(totalNpcs-npc.size());i++){
            creature baby;
            baby.immaculate(box2d.getWorld(), 0);
            npc.push_back(baby);
        }
    }
    if(newCircle == true){
        creature baby;
        baby.immaculate(box2d.getWorld(), 0);
        npc.push_back(baby);
        newCircle = false;
    }
    for(int i=0; i<npc.size();i++){
        npc[i].update();
        if(p1 != 0 && p2 != 0){
            if((npc.size()<300) && ((npc[i].circle.getPosition().x > p1 && npc[i].circle.getPosition().x < p1+100) && (npc[i].curr_size == npc[i].adult_size))){
                creature baby;
                baby.immaculate(box2d.getWorld(), 0);
                npc.push_back(baby);
            }
            if((npc.size()>0) && (npc[i].circle.getPosition().x > p2 && npc[i].circle.getPosition().x < p2+100)){
                npc.erase(npc.begin()+i);
            }
        }
        if(npc[i].curr_size == 0){
            npc.erase(npc.begin()+i);
        }
        if(npc.size()>=300){
            state = 1;
        }
        if(npc.size() == 0){
            state = 2;
        }
    }
    openNIDevice.update();
    box2d.update();
    
    if(timer>=timerInterval){
        millis = ofGetElapsedTimeMillis();
        timer = 0;
    }
    if(ofGetElapsedTimeMillis()-millis>timerInterval){
        timer = timerInterval;
    } else {
        timer = ofGetElapsedTimeMillis()-millis;
    }
    cout<<timer<<endl;
    
//        ofxOpenNIUser & user = openNIDevice.getTrackedUser(i);
//        thisuser = false;
        
//        for(int j=0;j<creatures.size();j++){
//            if(creatures[j].justPushed == true){
//
//                if(timer == timerInterval){
//                    creatures[j].justPushed = false;
//                }
//                if(timer>=timerInterval){
//                    millis = ofGetElapsedTimeMillis();
//                    timer = 0;
//                }
//                if(ofGetElapsedTimeMillis()-millis>timerInterval){
//                    timer = timerInterval;
//                } else {
//                    timer = ofGetElapsedTimeMillis()-millis;
//                }
////                cout<<timer<<endl;
//            }
//            if(user.getXnID() == creatures[j].userId){
//                ofPoint & center = user.getCenter();
//                ofPoint userPt = openNIDevice.worldToProjective(center);
//                creatures[j].user_x = userPt.x;
//                creatures[j].user_y = userPt.y;
//                if(!creatures[j].user_last_x){
//                    creatures[j].user_last_x = creatures[j].user_x;
//                }
//                if(!creatures[j].user_last_y){
//                    creatures[j].user_last_y = creatures[j].user_y;
//                }
//                if(userPt.x){
//                    ofVec2f loc, amt;
//                    int x1, y1, x2, y2, diffX, diffY;
//                    diffX = creatures[j].user_x-creatures[j].user_last_x;
//                    diffY = creatures[j].user_y-creatures[j].user_last_y;
//                    x1 = creatures[j].circle.getPosition().x;
//                    x2 = diffX;
//                    y1 = creatures[j].circle.getPosition().y;
//                    y2 = diffY;
////                    cout << x1 << endl;
////                    cout << x2 << endl;
////                    cout << " " << endl;
////                    cout << y1 << endl;
////                    cout << y2 << endl;
////                    cout << " " << endl;
////                    cout << "END" << endl;
////                    cout << " " << endl;
//                    amt = ofVec2f(x2, y2);
//                    loc = ofVec2f(x1, y1);
//                    if((diffX > 3 || diffY > 3) && creatures[j].justPushed == false){
//                        creatures[j].circle.addImpulseForce(amt, loc);
//                        creatures[j].justPushed = true;
//                        creatures[j].user_last_x = userPt.x;
//                        creatures[j].user_last_y = userPt.y;
//                    }  
//                }
//                thisuser = true;
//                creatures[j].update();
//            }
//            
//        }
//        if(!thisuser){
//            creature baby;
//            baby.immaculate(box2d.getWorld(), user.getXnID());
//            creatures.push_back(baby);
//        }
//        
//    }
//    extracreature = false;
//    for(int i=0;i<creatures.size();i++){
//        for(int j=0;j<numUsers;j++){
//            ofxOpenNIUser & user = openNIDevice.getTrackedUser(j);
//            if(user.getXnID() == creatures[j].userId){
//                extracreature = true;
//            }
//        }
//        if(!extracreature){
//            creatures.erase(creatures.begin()+i);
//        }
//    }
//    cout<<creatures.size()<<endl;
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    ofSetHexColor(0xffffff);
    my_img.draw(0,20,ofGetWidth(),ofGetHeight());

    if(state == 0){
//    ofBackground(0,0,0);

//    cout<<ofGetLightingEnabled()<<endl;
    if(p1>0){
        ofSetHexColor(0xA0A0A0);
    } else {
        ofSetHexColor(0xffffff);
    }
    ofFill();
    ofRect(p1, 0, 100, 20);
    if(p2>0){
        ofSetHexColor(0x476776);
    } else {
        ofSetHexColor(0xffffff);
    }
    ofFill();
    ofRect(p2, 0, 100, 20);
//    openNIDevice.drawDebug();
    for(int j=0;j<npc.size();j++){
        npc[j].draw();
    }
    for(int j=0;j<creatures.size();j++){
        ofxOpenNIUser & user = openNIDevice.getTrackedUser(j);
        if(creatures[j].curr_size == 0){
            creatures.erase(creatures.begin()+j);
            j=0;
        } else {
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
    } else if (state == 1){
        cout<<"Creation wins"<<endl;
    } else if (state == 2){
        cout<<"Destruction wins."<<endl;
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