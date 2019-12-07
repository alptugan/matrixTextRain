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
    ofParameterGroup guiTrailSetup;
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
            }
        }
        
    }
    
    void draw() {
        fps.setup("FPS ", ofToString(ofGetFrameRate()));
        
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
        
    }
};

#endif /* matrixTextRain_h */
