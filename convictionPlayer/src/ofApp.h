#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
// #define PORT 12345

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

	private:
		ofVideoPlayer* currentVideo;
		vector<ofVideoPlayer*> videos;
		int numVideos = 0;
		int currentVideoIndex;
		void changeVideo(int key);
		void fadeDown(bool d, float s);

		float fadeSpeed = 0.0;
		bool fadingDown = false;
		float opacity = 1.0;

		ofxOscReceiver oscReceiver;
		ofxOscSender oscSender;
		void sendOscMessage(string address, string message);
};
