#include "ofApp.h"
#include "ofxOpenCv.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    //windowサイズ
    ofSetWindowShape(640, 480);
    
    //背景色
    ofBackground(0, 0, 0);
    //フレームレート
    ofSetFrameRate(60);
    
    //VideoGrabberの初期化
    video.initGrabber(640, 480);
    video.setDeviceID(1);

}

//--------------------------------------------------------------
void ofApp::update(){
    
    //黒色のオブジェクトの座標
    vector<int> x_group;
    vector<int> y_group;
    
    //Video更新
    video.update();
    
    //画像アクセス用のポインタ
    unsigned char *pix;
    
    //画像用の配列
    unsigned char pix2[640*480];
    //各色用の変数
    int r,g,b;
    
    //新しいフレームを取得できたら
    if (video.isFrameNew()) {
        //colorImageにキャプチャ画像を突っ込む
        colorImage.setFromPixels(video.getPixels(), 640, 480);
        //colorImageの各ピクセルへのポインタを得る（アドレスを得る）
        pix = colorImage.getPixels();
        
        //各ポインタへアクセスする
        for (int i = 0; i < colorImage.getWidth(); i++) {
            for (int j = 0; j < colorImage.getHeight(); j++) {
                //各色の色を得る
                //640x480の(5, 30)のピクセルは5+(480x30)番目
                //各ピクセルは３バイト(rgb)
                //よって(5, 30)のR値を取得するには(5+(480x30))*3の値を取得する
                r = pix[int((i + colorImage.getWidth() * j) * 3)];
                g = pix[int((i + colorImage.getWidth() * j) * 3) + 1];
                b = pix[int((i + colorImage.getWidth() * j) * 3) + 2];
                
                //黒色か識別する
                if (r < 30 && g < 30 && b < 30) {
                    //X, Y座標を配列に入れる
                    x_group.push_back(i);
                    y_group.push_back(j);
                }
            }
        }
        
        //もし黒色が存在すれば
        if (!x_group.empty()) {
            //X, Y の平均をとる
            int x_sum = 0;
            int y_sum = 0;
            //合計を計算する
            for (int i = 0; i < x_group.size(); i++) {
                x_sum += x_group[i];
                y_sum += y_group[i];
            }
            //平均を取得する
            x = (x_sum/x_group.size());
            y = (y_sum/y_group.size());
        }
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    //Video描画
    ofSetColor(255, 255, 255);
    video.draw(0, 0);
    ofSetColor(255, 100, 100);
    ofCircle(x, y, 100);
    ofDrawBitmapString("X" + ofToString(x) + ", Y" + ofToString(y) , 20, 20);
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
