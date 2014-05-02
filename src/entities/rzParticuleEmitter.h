#pragma once

#include <iostream>
#include <vector>
#include <string>


#include "ofMain.h"
#include "rzParticule.h"


using namespace std;

class rzParticuleEmitter : public ofPoint {

	vector<rzParticule*> particules;

public:

	void update() {

		if (this->particules.size() <  100 )
		{
			rzParticule * p = new rzParticule(0,0,0);
			this->particules.push_back(p);
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

	void draw() {

		ofPushMatrix();
			ofTranslate(this->x,this->y,this->z);
			for (int i = 0; i < this->particules.size(); ++i)
			{
				rzParticule * p = this->particules[i];
				if (!p->isDead())
				{
					p->draw();
				}
			}
		ofPopMatrix();
	}

	rzParticuleEmitter( float x, float y , float z) : ofPoint(x, y, z){

	}
	~rzParticuleEmitter() {

		for (int i = 0; i < particules.size(); ++i)
		{
			delete particules[i];
		}
	}
};