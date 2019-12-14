#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofLogToConsole();
    
    // fullscreen enable
    ofToggleFullscreen();
    
    // setBackground color
    ofSetBackgroundColor(0);
    
    
    
    
    // Setup textrain object
    textRain.setup();
    
    // Init GUI
    gui.setup("OPTIONS");
    
    gui.add(textRain.gui);
    
    gui.loadFromFile("settings.xml");
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    textRain.draw();
    // Draw gui
    if(isShowGui)
        gui.draw();
    
    // Draw fps
    //utils.drawFPS(ofxFilikaAlignment::TOP_RIGHT);
}

//--------------------------------------------------------------
void ofApp::keyPressed(ofKeyEventArgs & key){
    // 343 CMD
    //ofLog() << key.key << " :: " << key.keycode;
    if(key.key == 'g') {
        isShowGui = !isShowGui;
    }else if(key.key == 'f') {
        ofToggleFullscreen();
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
