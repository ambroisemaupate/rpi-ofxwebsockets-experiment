#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "ofMain.h"
#include "rzParticule.h"

using namespace std;

class ofApp;

class rzParticuleEmitter : public ofPoint {

	vector<rzParticule*> particules;
    int static const PARTICULE_CREATION_COUNT = 5;
    int static const MAX_PARTICULE_COUNT = 100;
    
    ofApp * mainApplication;
    
    string username;
    ofColor color;

public:

	void update();
	void draw();
    bool isDead();
    void createParticule();

	rzParticuleEmitter( float x, float y , float z , ofApp *mainApp );
    rzParticuleEmitter( float x, float y , float z , string username, ofApp *mainApp );
	~rzParticuleEmitter();
};