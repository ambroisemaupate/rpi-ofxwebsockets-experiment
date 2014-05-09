//
//  rzParticule.cpp
//  rpi-ofxwebsockets-experiment
//
//  Created by Ambroise Maupate on 06/05/2014.
//
//

#include "rzParticule.h"

float rzParticule::INITIAL_FORCE = 2.0f;
float rzParticule::INITIAL_LIFE = 5.0f;
float rzParticule::MAX_SIZE = 20.0f;
float rzParticule::MIN_SIZE = 3.0f;
float rzParticule::MAX_DEVIATION = 1.0f;

void rzParticule::update(){
    int proba = (int)(ofRandomf()*10.0f);
    if (proba % 5 == 0){
        this->alterMotion();
    }
    
    this->x += this->motion->x;
    this->y += this->motion->y;
    //this->z += this->motion->z;
    
    this->life -= 0.01;
}

void rzParticule::alterMotion() {
    //Gravity
    
    float xDeviation = (ofRandomf()*rzParticule::MAX_DEVIATION);
    float yDeviation = (ofRandomf()*rzParticule::MAX_DEVIATION);
    
    this->motion->x += ((xDeviation)-(xDeviation/2));
    this->motion->y += ((yDeviation)-(yDeviation/2));
    //this->motion->z += (ofRandomf()*MAX_DEVIATION)-(MAX_DEVIATION/2); // Pas de 3D
}

void rzParticule::draw() {
    
    ofSetColor(color->r,color->g,color->b, 255*this->life);
    
    ofPushMatrix();
        ofTranslate(this->x,this->y,this->z);
    
    switch (this->type) {
        case CIRCLE:
            ofFill();
            ofCircle(0,0,this->size/-2);
            break;
        case RECT:
            ofFill();
            ofRect(this->size/-2, this->size/-2,this->size, this->size);
            break;
        case STROKE_CIRCLE:
            ofNoFill();
            ofCircle(0,0,this->size/-2);
            break;
        case STROKE_RECT:
            
            ofNoFill();
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
    
    this->motion = new ofPoint( (motionX)-(motionX/2), (motionY)-(motionY/2), 0 );
    this->life = (int)(ofRandomf()*rzParticule::INITIAL_LIFE);
    this->size = (int)(ofRandomf()*rzParticule::MAX_SIZE) + rzParticule::MIN_SIZE;
    
    
    this->type = (int)(ofRandomf()*4);
}

ofPoint * rzParticule::getMotion(){
    return this->motion;
}

void rzParticule::setColor( ofColor * color ){
    this->color = color;
}

bool rzParticule::isDead(){
    return (this->life <= 0.0);
}