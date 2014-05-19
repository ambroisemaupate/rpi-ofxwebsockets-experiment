//
//  rzParticuleEmitter.cpp
//  rpi-ofxwebsockets-experiment
//
//  Created by Ambroise Maupate on 02/05/2014.
//
//

#include "../ofApp.h"
#include "rzParticuleEmitter.h"

int rzParticuleEmitter::PARTICULE_CREATION_COUNT = 5;
int rzParticuleEmitter::MAX_PARTICULE_COUNT = 50;

void rzParticuleEmitter::update() {
    
	if ((ofGetElapsedTimeMillis() - this->birthtime) <= 300)
	{
		for (unsigned int i = 0; i < PARTICULE_CREATION_COUNT; i++) {
			this->createParticule();
		}
	}
}

void rzParticuleEmitter::draw() {
	
	ofPushMatrix();
	ofTranslate(this->x,this->y,this->z);
    
    ofRemove(this->particules,rzParticuleEmitter::shouldRemove);
    
    if (this->particules.size() > 0){
        for (auto iter = this->particules.begin(); iter != this->particules.end(); ++iter) {
        	//if (iter != NULL)
        	//{
	            (*iter).update();
	            (*iter).draw();
        	//}
        }
    }
    
	ofPopMatrix();
    
}

bool rzParticuleEmitter::isDead() {
	return (this->particules.size() <= 0);
}

void rzParticuleEmitter::createParticule() {
    
	rzParticule p = rzParticule(0,0,0);
	
	try {
	    if (this->username != "" &&
	        this->mainApplication->usersColor.find(this->username) != this->mainApplication->usersColor.end() ) {
			p.setColor( this->mainApplication->usersColor.at(this->username) );
		}
	}
	catch (const std::out_of_range& oor) {
	    std::cerr << "Out of Range error: " << oor.what() << '\n';
	}
	
	
	this->particules.push_back(p);
}

rzParticuleEmitter::rzParticuleEmitter( float x, float y , float z , ofApp *mainApp ) : ofPoint(x, y, z){
	
	this->mainApplication = mainApp;
	this->username = "";
    this->birthtime = ofGetElapsedTimeMillis();
    this->initiated = true;
	
	for (unsigned int i = 0; i < PARTICULE_CREATION_COUNT; i++) {
		this->createParticule();
	}
}
rzParticuleEmitter::rzParticuleEmitter( float x, float y , float z , string username, ofApp *mainApp ) : ofPoint(x, y, z){
	
	this->mainApplication = mainApp;
	this->username = username;
    this->birthtime = ofGetElapsedTimeMillis();
	this->initiated = true;
    
	for (unsigned int i = 0; i < PARTICULE_CREATION_COUNT; i++) {
		this->createParticule();
	}
}
bool rzParticuleEmitter::shouldRemove(rzParticule &p){
    if(p.isDead() )return true;
    else return false;
}