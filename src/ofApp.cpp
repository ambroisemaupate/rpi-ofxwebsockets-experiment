#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofHideCursor();
    
    // Load configuration
    ofxXmlSettings settings;
    
    if(!settings.loadFile("settings.xml")){
        settings.setValue("config:host", "test.com");
        settings.setValue("config:port", 8081);
        settings.saveFile("settings.xml");
    }
    

	client.connect(settings.getValue("config:host", "test.com"), settings.getValue("config:port", 8081));
    
	ofSetLogLevel(OF_LOG_ERROR);
	
	client.addListener(this);

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

	ofBackground(0,0,0);

	//int wCount = 15;
	//int hCount = 15;

	//int rectSize  = 10;

	ofSetColor(0,0,0);
	ofFill();

	for (unsigned int i = 0; i < points.size(); i++)
	{
		points[i]->draw();
	}
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
	string u = "";

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
		if(param[0] == "u"){
			u = param[1];
		}
	}

	//cout << "New point : " << x << " : " << y << "\n";

	float newX = ofMap(x, 0, width, 0, WINDOW_WIDTH);
	float newY = ofMap(y, 0, height, 0, WINDOW_HEIGHT);

	//cout << "Mapped point : " << newX << " : " << newY << "\n";
    
    if (this->usersColor[u] == NULL) {
        this->usersColor[u] = new ofColor((ofRandomf()*255),(ofRandomf()*255),(ofRandomf()*255));
    }

	this->points.push_back(new rzParticuleEmitter( newX, newY, 0.0, u, this ));

	if (this->points.size() > 100)
	{
		delete this->points[0];
		this->points.erase(this->points.begin());
	}
}