#include "ofMain.h"
	
#include "ofApp.h"

/*
 * Use make -j3 CXX=/usr/lib/distcc/arm-linux-gnueabihf-g++ CC=/usr/lib/distcc/arm-linux-gnueabihf-gcc && make run
 *
 * to use distcc
 */

//========================================================================
int main( ){

	ofSetupOpenGL(WINDOW_WIDTH, WINDOW_HEIGHT, OF_FULLSCREEN);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new ofApp());

}
