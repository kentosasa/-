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

    //全開の黒色オブジェクトの座標の中心
    int x_pre;
    int y_pre;

    //加速度
    long accelerat;
    
    //エネルギー球の半径
    double radius;
    
    //phase0初期状態　赤い物体が存在し、わちゃわちゃ動いている
    bool phase0;
    int phase0_count;
    
    //Phase1　赤い物体が存在し、動かないでエネルギーチャージ
    bool phase1;
    int phase1_count;
    
    //Phase2 物体が急加速した時
    bool phase2;
    int phase2_count;
};
