#pragma once

#include <iostream>
#include <vector>
#include <string>


#include "ofMain.h"

using namespace std;

class rzParticule : public ofPoint {

	ofPoint* motion;
	float life;

public:

	void update(){
		//Gravity
		this->motion->y += 0.5;

		this->x += this->motion->x;
		this->y += this->motion->y;
		this->z += this->motion->z;

		this->life -= 0.02;
	}

	void draw() {

		int rectSize = 3;

		ofPushMatrix();
			ofTranslate(this->x,this->y,this->z);
			ofRect(rectSize/-2, rectSize/-2,rectSize,rectSize);
		ofPopMatrix();
	}

	rzParticule( float x, float y , float z) : ofPoint(x, y, z){
		this->motion = new ofPoint( (ofRandomf()*4)-2, (ofRandomf()*4)-2, 0 );
		this->life = 1.0;
	}
	~rzParticule() {

		delete this->motion;
	}

	ofPoint * getMotion(){
		return this->motion;
	}

	bool isDead(){
		return (this->life <= 0.0);
	}
};