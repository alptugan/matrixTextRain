//
//  matrixTextRain.h
//  matrixTextRain
//
//  Created by alp tugan on 30.11.2019.
//

#ifndef matrixTextRain_h
#define matrixTextRain_h

#include "ofMain.h"
#include "matrixCharStream.h"

class matrixTextRain {
private:
    int numStream;  // Number of vertical stream objects
    int fontW, fontH; // global font width and height
    vector<matrixCharStream> stream;
    
    // GUI
    ofParameter<bool> gShowTexture;
    ofParameter<bool> gEnableDepth;
    ofParameter<bool> gEnableDebug;
    ofParameter<ofColor> gColor;
    ofParameter<ofColor> gGlowColor;
    ofParameterGroup guiTrailSetup;
    ofParameterGroup guiChar;
    ofParameter<bool> gEnableTrail;
    ofParameter<int> gTrailAmount;
    ofParameter<glm::vec2> gSpeed;
    ofxLabel fps;
    
    ofEasyCam cam;
    ofFbo fbo;
    
    ofBoxPrimitive box;

public:
    ofParameterGroup gui;
    
    void setup() {
        fontW = font.stringWidth("サ"); // get width from a random char from unicode range
        fontH = font.stringHeight("サ"); // get height from a random char from unicode range
        
        numStream = round(ofGetWidth() / fontW);
        stream.resize(numStream);
        
        for(int i = 0; i < numStream; i++) {
            stream[i].setup(i * fontW, fontW, fontH);
        }
        
        
        // Fbo allocation to display more trails
        fbo.allocate(ofGetWidth(), ofGetHeight(),GL_RGBA,4);
        fbo.begin();
        ofClear(0, 0, 0, 0);
        fbo.end();
        
            // GL_REPEAT for texture wrap only works with NON-ARB textures //
        ofDisableArbTex();
        
        float width     = ofGetWidth() * 1.2;
        float height    = ofGetHeight() * 1.2;
        box.set( width, height, width );
        
        // Map texture coordinates to generated cube sizes
        box.mapTexCoordsFromTexture( fbo.getTexture() );
        
        // Init GUI
        ofAddListener(gui.parameterChangedE(), this, &matrixTextRain::guiChanged);
        
        gui.setName("Matrix Room");
        gui.add(gShowTexture.set("Show Only Texture", true));
        gui.add(gEnableDepth.set("Enable Depth Sorting", true));
        
        gui.add(gSpeed.set("Set Speed Min and Max", glm::vec2(2,10), glm::vec2(1, 1), glm::vec2(12, 12)));
        
        // CHAR GUI : Every single letter
        guiChar.setName("Char Properties");
        guiChar.add(gEnableDebug.set("Show font bounding box", false));
        guiChar.add(gColor.set("Char Color", ofColor(0, 250, 70, 255), ofColor(0), ofColor(255)));
        guiChar.add(gGlowColor.set("First Char Glow Color", ofColor(200, 255, 200, 255), ofColor(0), ofColor(255)));
        gui.add(guiChar);
        
        // CHAR STREAM GUI : Every single column consisting random instances of matrixChar
        guiTrailSetup.setName("Trail setup");
        guiTrailSetup.add(gEnableTrail.set("Enable Trail Effect", true));
        guiTrailSetup.add(gTrailAmount.set("Trail Amount", 100, 0, 255));
        gui.add(guiTrailSetup);
        
        fps.setup("FPS","");
        gui.add(fps.getParameter());
        
        
    }
    
    void guiChanged(ofAbstractParameter & param) {
        if(param.getName() != "FPS ") {
            if(param.getName() == "Set Speed Min and Max") {
                for(int i = 0; i < numStream; i++) {
                    stream[i].setRandomSpeedRange(round(gSpeed->x), round(gSpeed->y));
                }
            } else if(param.getName() == "Show font bounding box") {
                for(int i = 0; i < numStream; i++) {
                    stream[i].setDebugView(gEnableDebug);
                }
            } else if(param.getName() == "Char Color") {
                for(int i = 0; i < numStream; i++) {
                    stream[i].setStreamColor(gColor);
                }
            }else if(param.getName() == "First Char Glow Color") {
                for(int i = 0; i < numStream; i++) {
                    stream[i].setGlowingCharColor(gGlowColor);
                }
            }
        }
        
    }
    
    void draw() {
        fps.setup("FPS ", ofToString(ofGetFrameRate()));
        ofPushStyle();
        // Begin fbo to create texture
        fbo.begin();
            if(gEnableTrail) {
                ofSetColor(ofColor(0, gTrailAmount));
                ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
            }else{
                ofClear(0, 0, 0, 0);
            }
        
            // Draw text rain
            for(int i = 0; i < numStream; i++) {
                stream[i].draw();
            }
        fbo.end();
        
        
        //glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);
        
        // Enable mesh depth sorting
        if(gEnableDepth) ofEnableDepthTest();
        
        if(!gShowTexture)
        {
            cam.begin();
            fbo.getTexture().bind();
            box.draw();
            fbo.getTexture().unbind();
            cam.end();
            }else{
                fbo.draw(0, 0);
        }
        
        // Disable mesh depth sorting
        if(gEnableDepth) ofDisableDepthTest();
        
        //glDisable(GL_BLEND);
        ofPopStyle();
    }
};

#endif /* matrixTextRain_h */
