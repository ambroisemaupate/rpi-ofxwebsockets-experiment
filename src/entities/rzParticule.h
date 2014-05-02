#pragma once

#include <iostream>
#include <vector>
#include <string>


#include "ofMain.h"

using namespace std;

class rzParticule : public ofPoint {

	ofPoint* motion;
    ofColor* color;
	float life;
    int static const INITIAL_FORCE = 5;
    int static const MAX_DEVIATION = 1;

public:

	void update(){
        
        ofSeedRandom();
		//Gravity
		this->motion->x += (ofRandomf()*MAX_DEVIATION)-(MAX_DEVIATION/2);
		this->motion->y += (ofRandomf()*MAX_DEVIATION)-(MAX_DEVIATION/2);
		this->motion->z += (ofRandomf()*MAX_DEVIATION)-(MAX_DEVIATION/2);

		this->x += this->motion->x;
		this->y += this->motion->y;
		this->z += this->motion->z;

		this->life -= 0.02;
	}

	void draw() {

		int rectSize = 10;
        
        ofSetColor(color->r,color->g,color->b, 255*this->life);
        
		ofPushMatrix();
			ofTranslate(this->x,this->y,this->z);
            ofCircle(0,0,rectSize/-2);
			//ofRect(rectSize/-2, rectSize/-2,rectSize,rectSize);
		ofPopMatrix();
	}

	rzParticule( float x, float y , float z) : ofPoint(x, y, z){
        this->color = new ofColor(255,255,255);
		this->motion = new ofPoint( (ofRandomf()*INITIAL_FORCE)-(INITIAL_FORCE/2), (ofRandomf()*INITIAL_FORCE)-(INITIAL_FORCE/2), 0 );
		this->life = 1.0;
	}
//	~rzParticule() {
//        if ( this->motion != NULL ) {
//            delete this->motion;
//        }
//    }

	ofPoint * getMotion(){
		return this->motion;
	}
    
    void setColor( ofColor * color ){
        this->color = color;
    }

	bool isDead(){
		return (this->life <= 0.0);
	}
};