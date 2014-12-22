#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    //WebCameraの映像を取得するクラスのインスタンス生成
    ofVideoGrabber video;
    
    //カラー画像用オブジェクト
    ofxCvColorImage colorImage;
        
    //黒色オブジェクトの座標の中心
    int x;
    int y;

    
};
