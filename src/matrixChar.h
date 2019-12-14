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
public:
    string alignment;
    int fontH,fontW;
    ofColor color;
    string letter;
    int x,y,z;
    int index;
    bool isDebug;
    ofVboMesh mesh;
    ofFbo fbo;
    
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
        //ofFill();
        ofSetColor(color);
        
        /*for(int i = 0; i < mesh.getVertices().size(); i++) {
         ofLog() << mesh.getVertices()[i];
         }*/
        
        if(alignment == "center") {
            font.drawString(letter, -fontW * 0.5, fontH * 0.5);
        } else if(alignment == "left") {
            font.drawString(letter, 0, fontH - 2);
        }
        
        //2- Fbo
        //fbo.draw(0,fontH - 2);
        
        //1- Vbo Mesh
        
        font.getFontTexture().bind();
        mesh.draw();
        font.getFontTexture().unbind();
        
        if(isDebug) {
            ofNoFill();
            ofSetColor(255,0,0);
            ofDrawRectangle(0,0,fontW,fontH);
        }
        
        ofPopStyle();
        ofPopMatrix();
    }
    
    void generateRandomChar() {
            // 65 - 90
        float rangeSelector = ofRandomf();
        
        if(rangeSelector < 0.3) {
                // Decimal range for matrix code nfi.ttf
                //theChar = round(ofRandom(96, 126));
            
                // Decimal range for Arial Unicode.ttf
            theChar = round(ofRandom(33, 64));
        }else if(rangeSelector < 0.4){
                // Decimal range for matrix code nfi.ttf
                //theChar = round(ofRandom(33, 63));
            
            // Decimal range for Arial Unicode.ttf
            /* Exclude dead char decimals
             12544: ㄀
             12545: ㄁
             12546: ㄂
             12547: ㄃
             12548: ㄄
             12589: ㄭ
             12590: ㄮ
             12591: ㄯ
             12592: ㄰
             */
            theChar = round(ofRandom(12449, 12543));
        } else if(rangeSelector < 0.5){
            theChar = round(ofRandom(12549, 12588));
        } else {
            theChar = round(ofRandom(12593, 12615));
        }
        
        
            //ofLog() << theChar;
        letter.clear();
        
        ofUTF8Append(letter, theChar);
            //letter= ofToString(theChar);
            //letter = "サッカ";
        
        
        //ofLog() << mesh.getVertices().size();
        /*fbo.allocate(fontW, fontH, GL_RGBA, 4);
        fbo.begin();
        ofClear(0,0);
        ofFill();
        ofSetColor(color);
        font.drawString(letter, 0, 0);
        fbo.end();*/
        
        
        /*mesh.clear();
        mesh = font.getStringMesh(letter,0, 0, false);
            // Includes 4 vertices
            // 1st vertex position - top-left
        mesh.getVertices()[0].x = x;
        mesh.getVertices()[0].y = y;
        
            // 2nd vertex position top-right
        mesh.getVertices()[1].x = x + fontW;
        mesh.getVertices()[1].y = y;
        
            // 3rd vertex position bottom-right
        mesh.getVertices()[2].x = x + fontW;
        mesh.getVertices()[2].y = y + fontH;
        
            // 4th vertex position bottom-left
        mesh.getVertices()[2].x = x;
        mesh.getVertices()[2].y = y + fontH;
        
        // Includes 4 vertices
        // 1st vertex position - top-left
        /*mesh.getVertices()[0].x = x;
        mesh.getVertices()[0].y = y;
        
        // 2nd vertex position top-right
        mesh.getVertices()[1].x = x + fontW;
        mesh.getVertices()[1].y = y;
        
        // 3rd vertex position bottom-right
        mesh.getVertices()[2].x = x + fontW;
        mesh.getVertices()[2].y = y + fontH;
        
        // 4th vertex position bottom-left
        mesh.getVertices()[2].x = x;
        mesh.getVertices()[2].y = y + fontH;*/
        
    }
};
#endif /* matrixChar_h */
