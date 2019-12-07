#pragma once

#include "ofMain.h"
static ofTrueTypeFont font;

#include "ofxGui.h"
//#include "ofxFilikaUtils.h"
#include "matrixTextRain.h"



class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(ofKeyEventArgs & key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
    ofxPanel gui;
    bool isShowGui;
    
    //ofxFilikaUtils utils;
    
    matrixTextRain textRain;
};