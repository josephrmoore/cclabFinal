#pragma once

#include "ofMain.h"
#include "creature.h"
#include "ofxBox2d.h"
#include "Polygon.h"
#include "ofxOpenNI.h"


class testApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
        void exit();
        
        vector <creature> creatures;
        vector <bool> ps;
		
        void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        int maxUsers;
        int timer;
        int millis;
        bool rev;
        void userEvent(ofxOpenNIUserEvent & event);
        // this is the function for contacts
        ofxOpenNI openNIDevice;
        ofxBox2d box2d;
        ofImage my_img;
        vector		<ofxBox2dCircle>	circles;
        void contactStart(ofxBox2dContactArgs &e);
        void contactEnd(ofxBox2dContactArgs &e);
};
