#ifndef RZ_PARTICULE_H

#define RZ_PARTICULE_H

#include <iostream>
#include <vector>
#include <string>

#include "ofMain.h"

using namespace std;

class rzParticule : public ofPoint {

	ofPoint motion;
    ofColor color;
	float life;
    float size;
    int type;

    int age;
    int birthtime;
    
    static const int CIRCLE = 0;
    static const int RECT = 1;
    static const int STROKE_CIRCLE = 2;
    static const int STROKE_RECT = 3;

public:
    
    static float INITIAL_FORCE;
    static float MAX_DEVIATION;
    static float MIN_SIZE;
    static float MAX_SIZE;
    static float INITIAL_LIFE;

	void update();
    
    void alterMotion();

	void draw();

	rzParticule( float x, float y , float z);

	ofPoint * getMotion();
    
    void setColor( ofColor color );

	bool isDead();
};


#endif
