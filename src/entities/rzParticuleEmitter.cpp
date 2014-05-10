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
	
	if (this->particules.size() <  MAX_PARTICULE_COUNT )
	{
		for (unsigned int i = 0; i < PARTICULE_CREATION_COUNT; i++) {
			this->createParticule();
		}
	}
	
	vector<rzParticule*>::iterator iter;
	for (iter = this->particules.begin(); iter != this->particules.end(); iter++) {

		if (!(*iter)->isDead())
		{
			(*iter)->update();
		}
		/*else {
			iter = this->particules.erase(iter);
		}*/
	}   
}

void rzParticuleEmitter::draw() {
	
	ofPushMatrix();
	ofTranslate(this->x,this->y,this->z);

	vector<rzParticule*>::iterator iter;
	for (iter = this->particules.begin(); iter != this->particules.end(); iter++) {

		if (!(*iter)->isDead())
		{
			(*iter)->draw();
		}
	} 

	//ofDrawBitmapString(this->username, 20, 20);
	ofPopMatrix();
}

bool rzParticuleEmitter::isDead() {
	return this->particules.size() <= 0;
}

void rzParticuleEmitter::createParticule() {
	rzParticule * p = new rzParticule(0,0,0);
	
	if (this->username != "" && this->mainApplication->usersColor[this->username] != NULL ) {
		p->setColor(this->mainApplication->usersColor[this->username]);
	}
	
	this->particules.push_back(p);
}

rzParticuleEmitter::rzParticuleEmitter( float x, float y , float z , ofApp *mainApp ) : ofPoint(x, y, z){
	
	this->mainApplication = mainApp;
	this->username = "";
	
	for (unsigned int i = 0; i < PARTICULE_CREATION_COUNT; i++) {
		this->createParticule();
	}
}
rzParticuleEmitter::rzParticuleEmitter( float x, float y , float z , string username, ofApp *mainApp ) : ofPoint(x, y, z){
	
	this->mainApplication = mainApp;
	this->username = username;
	
	for (unsigned int i = 0; i < PARTICULE_CREATION_COUNT; i++) {
		rzParticule * p = new rzParticule(0,0,0);
		this->particules.push_back(p);
	}
}
rzParticuleEmitter::~rzParticuleEmitter() {
	
}