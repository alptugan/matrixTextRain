#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofLogToConsole();
    
    // fullscreen enable
    ofToggleFullscreen();
    
    // setBackground color
    ofSetBackgroundColor(0);
    
    
    // Load global font and size that includes Katana characters
    ofTrueTypeFontSettings settings("Arial Unicode.ttf", 12);
    
    settings.antialiased = true;
    settings.dpi = 72;
    settings.addRange({0x0021, 0x0040});
    settings.addRange({0x30A1, 0x3147});
    font.load(settings);
    
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
