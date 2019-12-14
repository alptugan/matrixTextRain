#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
	//ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context
    
    ofGLFWWindowSettings s;
    s.setSize(1400, 700);
    //s.setGLVersion(3, 2);
    
    ofCreateWindow(s);
    
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}
