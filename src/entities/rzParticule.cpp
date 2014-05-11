//
//  rzParticule.cpp
//  rpi-ofxwebsockets-experiment
//
//  Created by Ambroise Maupate on 06/05/2014.
//
//
#include <stdlib.h>     /* abs */
#include "rzParticule.h"

float rzParticule::INITIAL_FORCE = 2.0f;
float rzParticule::INITIAL_LIFE = 5.0f;
float rzParticule::MAX_SIZE = 20.0f;
float rzParticule::MIN_SIZE = 3.0f;
float rzParticule::MAX_DEVIATION = 1.0f;

void rzParticule::update(){
    
    this->age = ofGetElapsedTimeMillis() - this->birthtime;

    //if (this->age % 15 < 3)
    //{
        int proba = (int)(ofRandomuf()*10.0f);
        if (proba % 5 == 0){
            this->alterMotion();
        }

        this->x += this->motion.x;
        this->y += this->motion.y;
        this->z += this->motion.z;
    //}
}

void rzParticule::alterMotion() {
    //Gravity
    
    float xDeviation = (ofRandomf()*rzParticule::MAX_DEVIATION);
    float yDeviation = (ofRandomf()*rzParticule::MAX_DEVIATION);
    float zDeviation = (ofRandomf()*rzParticule::MAX_DEVIATION);
    
    this->motion.x += ((xDeviation));
    this->motion.y += ((yDeviation));
    this->motion.z += ((yDeviation));
}

void rzParticule::draw() {
    
    float lifespan = this->age / this->life;

    ofSetColor(color->r,color->g,color->b, abs(ofMap(lifespan, 0, 1, -255, 0)));
    
    ofPushMatrix();
        ofTranslate(this->x,this->y,this->z);
    
    switch (this->type) {
        case CIRCLE:
            ofFill();
            ofCircle(0,0,this->size/-2);
            break;
        case RECT:
            ofFill();

            ofRotateZ( abs(ofMap(lifespan, 0, 1, 0, 360)) );
            ofRect(this->size/-2, this->size/-2,this->size, this->size);
            break;
        case STROKE_CIRCLE:
            ofNoFill();
            ofCircle(0,0,this->size/-2);
            break;
        case STROKE_RECT:
            
            ofNoFill();
            ofRotateZ( abs(ofMap(lifespan, 0, 1, 0, 360)) );
            ofRect(this->size/-2, this->size/-2,this->size, this->size);
            break;
            
        default:
            break;
    }
    
    ofPopMatrix();
}

rzParticule::rzParticule( float x, float y , float z) : ofPoint(x, y, z){
    this->color = new ofColor(255.0f,255.0f,255.0f);
    
    float motionX = ofRandomf()*rzParticule::INITIAL_FORCE;
    float motionY = ofRandomf()*rzParticule::INITIAL_FORCE;
    float motionZ = ofRandomf()*rzParticule::INITIAL_FORCE;
    
    this->motion = ofPoint( (motionX), (motionY), (motionZ) );
    this->life = (int)(ofRandomuf()*rzParticule::INITIAL_LIFE);
    this->size = (int)(ofRandomuf()*rzParticule::MAX_SIZE) + rzParticule::MIN_SIZE;
    
    
    this->type = (int)(ofRandomuf()*4);
    this->birthtime = ofGetElapsedTimeMillis();
}

ofPoint * rzParticule::getMotion(){
    return &this->motion;
}

void rzParticule::setColor( ofColor * color ){
    this->color = color;
}

bool rzParticule::isDead(){
    return ((this->age > this->life) && this->age > 0);
}