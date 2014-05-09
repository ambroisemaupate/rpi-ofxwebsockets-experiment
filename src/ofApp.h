#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <map>


#include "ofMain.h"
#include "ofxXmlSettings.h"
#include "ofxLibwebsockets.h"

#include "entities/rzParticuleEmitter.h"

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

using namespace std;

class ofApp : public ofBaseApp {
    
        ofxXmlSettings settings;
    
	public:
		vector<string> messages;
		vector<rzParticuleEmitter*> points;
        map <string, ofColor*> usersColor;

		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);


        void addPoint(string msg);
        void getConfiguration();

		
        ofxLibwebsockets::Client client;
    
        // websocket methods
        void onConnect( ofxLibwebsockets::Event& args );
        void onOpen( ofxLibwebsockets::Event& args );
        void onClose( ofxLibwebsockets::Event& args );
        void onIdle( ofxLibwebsockets::Event& args );
        void onMessage( ofxLibwebsockets::Event& args );
        void onBroadcast( ofxLibwebsockets::Event& args );
};
