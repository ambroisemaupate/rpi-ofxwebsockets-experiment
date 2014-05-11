#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "ofMain.h"
#include "rzParticule.h"

using namespace std;

class ofApp;

class rzParticuleEmitter : public ofPoint {

	vector<rzParticule> particules;
    
    ofApp * mainApplication;
    
    string username;
    ofColor color;
    bool initiated;
    int birthtime;
    
    // write our boolean remove function
    static bool shouldRemove(rzParticule &p);

public:
    
    static int PARTICULE_CREATION_COUNT;
    static int MAX_PARTICULE_COUNT;

	void update();
	void draw();
    bool isDead();
    void createParticule();

	rzParticuleEmitter( float x, float y , float z , ofApp *mainApp );
    rzParticuleEmitter( float x, float y , float z , string username, ofApp *mainApp );
};