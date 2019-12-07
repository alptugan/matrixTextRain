//
//  matrixChar.h
//  matrixTextRain
//
//  Created by alp tugan on 5.12.2019.
//

#ifndef matrixChar_h
#define matrixChar_h

class matrixChar {
private:
    uint32_t theChar;
    
    float lastTriggerTime;
public:
    string alignment;
    int fontH,fontW;
    ofColor color;
    string letter;
    int x,y,z;
    int index;
    bool isDebug;
    
    void setup(int tempX, int index, int fontW, int fontH) {
        
        this->index = index;
        this->fontW = fontW;
        this->fontH = fontH;
        
        generateRandomChar();
        
        x = tempX;
        y = 0;
        z = 0;
        
        alignment = "left";
        
        color = ofColor(0, 250, 70, 255);
    }
    
    void draw() {
        ofPushMatrix();
        ofTranslate(x, y, z);
        ofPushStyle();
        ofFill();
        ofSetColor(color);
        
        if(alignment == "center") {
            font.drawString(letter, -fontW * 0.5, fontH * 0.5);
        } else if(alignment == "left") {
            font.drawString(letter, 0, fontH - 2);
        }
        
        if(isDebug) {
            ofNoFill();
            ofSetColor(255,0,0);
            ofDrawRectangle(0,0,fontW,fontH);
        }
        
        ofPopStyle();
        ofPopMatrix();
        
        /*if(ofGetElapsedTimef() - lastTriggerTime > 0.05) {
         generateRandomChar();
         lastTriggerTime = ofGetElapsedTimef();
         }*/
        
    }
    
    void generateRandomChar() {
            // 65 - 90
        int rangeSelector = round(ofRandom(0,1));
        
        if(rangeSelector == 1) {
                // Decimal range for matrix code nfi.ttf
                //theChar = round(ofRandom(96, 126));
            
                // Decimal range for Arial Unicode.ttf
            theChar = round(ofRandom(33, 64));
        }else{
                // Decimal range for matrix code nfi.ttf
                //theChar = round(ofRandom(33, 63));
            
                // Decimal range for Arial Unicode.ttf
            theChar = round(ofRandom(12449, 12615));
        }
        
        
            //ofLog() << theChar;
        letter.clear();
        
        ofUTF8Append(letter, theChar);
            //letter= ofToString(theChar);
            //letter = "サッカ";
        
    }
};
#endif /* matrixChar_h */
