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
    
    //エネルギーの初期半径
    radius = 0;
    
    //Phaseの初期値をFalseに
    phase0 = true;
    phase1 = false;
    phase2 = false;
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
                if (r < 230 && r > 180 && g < 120 && r > 80 && b < 120 && b > 80) {
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
            //全開の値を入力
            x_pre = x;
            y_pre = y;
            
            //平均を取得する
            x = (x_sum/x_group.size());
            y = (y_sum/y_group.size());
            
            //加速度を代入
            accelerat = sqrt(( x - x_pre ) * ( x - x_pre ) + ( y - y_pre ) * ( y - y_pre ));
        }
    }
    
    
    //各Phaseに関する処理
    //Phase0であまり動いてない時
    if (phase0 && accelerat < 5) {
        //Phase0カウントを追加する
        phase0_count++;
        
        //Phase0カウントが溜まったら次のPhaseに移行する
        if (phase0_count > 100) {
            phase0_count = 0;
            phase0 = false;
            phase1 = true;
        }
    //Phase1のとき
    }else if (phase1){
        //Phase1カウントを追加
        phase1_count++;
        //エネルギー球の大きさを拡大
        radius += 0.1f;
        
        //急加速した時
        if (accelerat > 80 && radius > 50) {
            phase1_count = 0;
            phase1 = false;
            phase2 = true;
        }
        
    //Phase2のとき
    }else if (phase2){
        //Phase2のカウント追加
        phase2_count++;
        
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    //Video描画
    ofSetColor(255, 255, 255);
    video.draw(0, 0);
    
    //色の変更
    ofSetColor(255, 100, 100);
    
    //中心に円を描写
    ofCircle(x, y, radius);

    //Phase2のとき
    if (phase2) {
        ofRect(x, (y - radius), ofGetWidth(), radius*2);
    }
    
    //値の出力
    ofDrawBitmapString("X" + ofToString(x) + ", Y" + ofToString(y) + ", AC" + ofToString(accelerat) , 20, 20);
    
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
