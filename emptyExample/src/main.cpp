#include "ofMain.h"
#include "testApp.h"
#include "ofAppGlutWindow.h"

//--------------------------------------------------------------
int main(){
	ofAppGlutWindow window; // create a window
	// set width, height, mode (OF_WINDOW or OF_FULLSCREEN)
	ofSetupOpenGL(&window, 1400, 900, OF_WINDOW);
	ofRunApp(new testApp()); // start the app
}
