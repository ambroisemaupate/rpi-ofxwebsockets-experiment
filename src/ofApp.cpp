#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofHideCursor();

	client.connect("nestor.maupate.com", 8081);
//    client.connect("echo.websocket.org", true); // optionally use SSL
	ofSetLogLevel(OF_LOG_ERROR);
	
	client.addListener(this);


	this->addPoint("w=100&h=100&x=3&y=4");

	ofSetFrameRate(60);
}

//--------------------------------------------------------------
void ofApp::update(){

	for (unsigned int i = 0; i < points.size(); i++)
	{
		points[i]->update();
	}
}

//--------------------------------------------------------------
void ofApp::draw(){

	ofBackground(200,200,200);

	//int wCount = 15;
	//int hCount = 15;

	//int rectSize  = 10;

	ofSetColor(0,0,0);
	ofFill();

	for (unsigned int i = 0; i < points.size(); i++)
	{
		points[i]->draw();
	}

	// ofPushMatrix();
	// 	ofSetColor(0,0,250);
	//     ofFill();


	//     ofTranslate((1920/2),(1080/2));

	// 	ofRotateZ( ofGetElapsedTimef() * 45.0 );

	//     ofPushMatrix();
		
	//     	ofTranslate((1920/-2),(1920/-2));
		
	//     	for (int j = 0; j < hCount; ++j)
	//     	{
	//     		/* code */
	// 		    for (int i = 0; i < wCount; ++i)
	// 		    {
	// 				ofPushMatrix();
		
	// 					ofTranslate((1920/wCount) * i,(1920/hCount) * j);
		
	// 					ofPushMatrix();
	// 						ofRotateZ( ofGetElapsedTimef() * -90.0 );
	// 						ofRect(rectSize/-2, rectSize/-2,rectSize,rectSize);
	// 					ofPopMatrix();
	// 				ofPopMatrix();
	// 		    }
	//     	}


	//     ofPopMatrix();
	// ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}


//--------------------------------------------------------------
void ofApp::onConnect( ofxLibwebsockets::Event& args ){
	cout<<"on connected"<<endl;
}

//--------------------------------------------------------------
void ofApp::onOpen( ofxLibwebsockets::Event& args ){
	cout<<"on open"<<endl;
}

//--------------------------------------------------------------
void ofApp::onClose( ofxLibwebsockets::Event& args ){
	cout<<"on close"<<endl;
}

//--------------------------------------------------------------
void ofApp::onIdle( ofxLibwebsockets::Event& args ){
	cout<<"on idle"<<endl;
}

//--------------------------------------------------------------
void ofApp::onMessage( ofxLibwebsockets::Event& args ){
	//cout<<"got message "<<args.message<<endl;
	this->addPoint(args.message);
}

//--------------------------------------------------------------
void ofApp::onBroadcast( ofxLibwebsockets::Event& args ){
	//cout<<"got broadcast "<<args.message<<endl;    
}

void ofApp::addPoint(string msg) {
	unsigned int width = 0;
	unsigned int height = 0;
	unsigned int x = 0;
	unsigned int y = 0;

	vector<string> result=ofSplitString(msg, "&");

	for (unsigned int i = 0; i < result.size(); i++)
	{
		vector<string> param=ofSplitString(result[i], "=");

		if(param[0] == "w"){
			width = atoi(param[1].c_str());
		}
		if(param[0] == "h"){
			height = atoi(param[1].c_str());
		}
		if(param[0] == "x"){
			x = atoi(param[1].c_str());
		}
		if(param[0] == "y"){
			y = atoi(param[1].c_str());
		}
	}

	cout << "New point : " << x << " : " << y << "\n";

	float newX = ofMap(x, 0, width, 0, WINDOW_WIDTH);
	float newY = ofMap(y, 0, height, 0, WINDOW_HEIGHT);

	cout << "Mapped point : " << newX << " : " << newY << "\n";

	this->points.push_back(new rzParticuleEmitter( newX, newY, 0.0 ));

	if (this->points.size() > 100)
	{
		delete this->points[0];
		this->points.erase(this->points.begin());
	}
}