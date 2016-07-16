#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	//Workaround to hide cursor in a
	Display* display = ofGetX11Display();
 	Window window = ofGetX11Window();
 
 	Cursor invisibleCursor;
 	Pixmap bitmapNoData;
 	XColor black;
 	static char noData[] = { 0,0,0,0,0,0,0,0 };
 	black.red = black.green = black.blue = 0;

	bitmapNoData = XCreateBitmapFromData(display, window, noData, 8, 8);
	invisibleCursor = XCreatePixmapCursor(display, bitmapNoData, bitmapNoData, &black, &black, 0, 0);
	XDefineCursor(display,window, invisibleCursor);
	XFreeCursor(display, invisibleCursor);


	//set up OSC
	oscReceiver.setup(PORT);


	ofHideCursor();
	cout << endl <<  "//startingCONVICTION----------------------" << endl;

	ofDirectory dir("videos");
	dir.allowExt("mov");
	dir.listDir();
	dir.sort();

	for(int i = 0; i < dir.size(); i++){
		cout << "cue " << (i+1) << " = " << dir.getName(i);

		ofVideoPlayer* newVideo = new ofVideoPlayer();
		newVideo->loadMovie(dir.getPath(i));

		//check filename for loop flag
		if(ofIsStringInString( ofToUpper(dir.getName(i)), "LOOP"))
			cout << " (looping)" << endl;
		else{
			cout << endl;
			newVideo->setLoopState(OF_LOOP_NONE);
		}
		videos.push_back(newVideo);		
	}

	cout << "Number of cues loaded = " << videos.size() << endl << endl;
	changeVideo(0);
	opacity = 0.0;
	fadingDown = true;
}

//--------------------------------------------------------------
void ofApp::update(){

	while(oscReceiver.hasWaitingMessages()){
		cout << "messages waiting" << endl;
		ofxOscMessage m;
		oscReceiver.getNextMessage(m);
		if(m.getAddress() == "/command")
			cout << m.getArgAsString(0) << endl;
	}

	if(currentVideoIndex >= 0)
		currentVideo->update();

	//loop from 50%
	if(currentVideo->getLoopState() != OF_LOOP_NONE && currentVideo->getPosition() > 0.99)
		currentVideo->setPosition(0.5);	

	if(fadingDown && opacity > 0.0)
		opacity -= 1.0/fadeSpeed * ofGetLastFrameTime();
	if(!fadingDown && opacity < 1.0)
		opacity += 1.0/fadeSpeed * ofGetLastFrameTime();

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofClear(0);
	ofSetColor(255, 255 * opacity);
	if(currentVideoIndex >= 0)
		currentVideo->draw(0, 0, ofGetWidth(), ofGetHeight());
	else{
		ofSetColor(0);
		ofDrawRectangle(0.0, 0.0, ofGetWidth(), ofGetHeight());
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	int keyInt =  key - 48;	

	if( keyInt > 0 && keyInt <= videos.size())
		changeVideo(keyInt-1);

	else if(key == ' ' && currentVideoIndex < videos.size() - 1){
		int i = currentVideoIndex + 1;
		changeVideo(i);
	}

	else if(key == 'a'){
		fadeDown(false, 0.0);
		opacity = 1.0;
	}
	else if(key == 'z'){
		fadeDown(true, 0.0);
		opacity = 0.0;
	}

	else if(key == 's')
		fadeDown(false, 1.0);
	else if(key == 'x')
		fadeDown(true, 1.0);

	else if(key == 'd')
		fadeDown(false, 2.0);
	else if(key == 'c')
		fadeDown(true, 2.0);

	else if(key == 'f')
		fadeDown(false, 3.0);
	else if(key == 'v')
		fadeDown(true, 3.0);

	else if(key == 'g')
		fadeDown(false, 5.0);
	else if(key == 'b')
		fadeDown(true, 5.0);

	else if(key == 'h')
		fadeDown(false, 10.0);
	else if(key == 'n')
		fadeDown(true, 10.0);

	else if(key == 'j')
		fadeDown(false, 15.0);
	else if(key == 'm')
		fadeDown(true, 15.0);

	else if(key == 'k')
		fadeDown(false, 20.0);
	else if(key == ',')
		fadeDown(true, 20.0);

}


//--------------------------------------------------------------
void ofApp::fadeDown(bool d, float s){
	fadingDown = d;
	fadeSpeed = s;

	string prompt = "fading up in ";
	if(d)
		prompt = "fading down in ";
	cout << prompt << s << "s" << endl;
}

//--------------------------------------------------------------
void ofApp::changeVideo(int key){
	currentVideoIndex = key;

	if(currentVideoIndex >= videos.size())
		currentVideoIndex = 0;

	cout << "Current cue = " << (currentVideoIndex + 1) << endl;
	
	for(auto v : videos)
		v->stop();

	if(currentVideoIndex >= 0){
		currentVideo = videos[currentVideoIndex];
		currentVideo->play();
	}


	// fade in and out 1 2 3 5 10 15 20
}


//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

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
