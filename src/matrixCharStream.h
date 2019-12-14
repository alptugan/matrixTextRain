//
//  matrixCharStream.h
//  matrixTextRain
//
//  Created by alp tugan on 5.12.2019.
//

#ifndef matrixCharStream_h
#define matrixCharStream_h

#include "ofMain.h"
#include "matrixChar.h"

class matrixCharStream {
private:
    
    ofColor blockColor;
    int minimum, maximum;
    int numLetters, tempX;
    int currentStreamH;
    int speed;
    int fontW, fontH;
    ofVboMesh vboMesh;
public:
    vector<matrixChar> letters;
    int getStreamWidth() {
        return letters[0].fontW;
    }
    
    void setRandomSpeedRange(int minimum, int maximum) {
        this->minimum = minimum;
        this->maximum = maximum;
        speed = (ofRandom(this->minimum, this->maximum));
    }
    
    void setDebugView(bool isDebug) {
        for (int i = 0; i < numLetters; i++) {
            letters[i].isDebug = isDebug;
        }
    }
    
    void setStreamColor(ofColor color) {
        for (int i = 0; i < numLetters; i++) {
            if( i != numLetters - 1)
            {
                float alpha = ofMap(i, 0, numLetters - 1, 0, 255);
                letters[i].color = ofColor(color.r, color.g, color.b, alpha);
            }
        }
    }
    
    void setGlowingCharColor(ofColor color) {
        blockColor = color;
        letters[numLetters - 1].color = blockColor;
    }
    
    void setup(int tempX, int fontW, int fontH) {
        this->tempX = tempX;
        this->fontW = fontW;
        this->fontH = fontH;
        this->minimum = 2;
        this->maximum = 10;
        
        blockColor     = ofColor(200, 255, 200, 255);
        currentStreamH = 0;
        
        // Generate random speed for each stream block
        setRandomSpeedRange(this->minimum, this->maximum);
        
        // Generate random number for characters array for each block
        numLetters = round(ofRandom(8, 60));
        
        letters.clear();
        letters.resize(numLetters);
        
        for (int i = 0; i < numLetters; i++) {
            letters[i].setup(this->tempX, i, this->fontW, this->fontH);
            letters[i].y = currentStreamH;
            currentStreamH += letters[i].fontH;
            
                // calculate color Alpha
            if( i != numLetters - 1)
            {
                float alpha = ofMap(i, 0, numLetters - 1, 0, 255);
                letters[i].color = ofColor(letters[i].color.r, letters[i].color.g, letters[i].color.b, alpha);
            }
        }
        
        // set the last letter to white to create shine effect
        letters[numLetters - 1].color = blockColor;
    }
    
    
    void draw() {
        
        
        for (int i = 0; i < numLetters; i++) {
            letters[i].draw();
        }
        
        /* */
        if( ofGetFrameNum() % speed == 0) {
            for (int i = 0; i < numLetters; i++) {
                letters[i].y += this->fontH;
                
                if(i == numLetters - 1)
                    letters[i].generateRandomChar();
                else
                    letters[i].letter = letters[i + 1].letter;
            }
        }
        
        if(letters[0].y >= ofGetHeight()) {
            setRandomSpeedRange(this->minimum, this->maximum);
            for (int i = 0; i < numLetters; i++) {
                letters[i].y = ((numLetters - 1) - i) * -this->fontH;
            }
        }
    }
    
};
#endif /* matrixCharStream_h */
