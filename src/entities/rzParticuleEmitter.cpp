//
//  rzParticuleEmitter.cpp
//  rpi-ofxwebsockets-experiment
//
//  Created by Ambroise Maupate on 02/05/2014.
//
//

#include "../ofApp.h"
#include "rzParticuleEmitter.h"

void rzParticuleEmitter::update() {
    
    if (this->particules.size() <  MAX_PARTICULE_COUNT )
    {
        for (unsigned int i = 0; i < PARTICULE_CREATION_COUNT; i++) {
            this->createParticule();
        }
    }
    
    
    for (int i = 0; i < this->particules.size(); ++i)
    {
        rzParticule * p = this->particules[i];
        if (!p->isDead())
        {
            p->update();
        }
    }
}

void rzParticuleEmitter::draw() {
    
    ofPushMatrix();
    ofTranslate(this->x,this->y,this->z);
    for (int i = 0; i < this->particules.size(); ++i)
    {
        rzParticule * p = this->particules[i];
        if (p != NULL && !p->isDead())
        {
            p->draw();
        }
    }
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
    
    //		for (int i = 0; i < particules.size(); ++i)
    //		{
    //            rzParticule * p = this->particules[i];
    //            if  (p != NULL) {
    //                delete p;
    //            }
    //		}
}