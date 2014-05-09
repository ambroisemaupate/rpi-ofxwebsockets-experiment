#include "ofApp.h"
#include "entities/rzParticule.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofHideCursor();
    
    this->getConfiguration();

	client.connect(this->settings.getValue("config:host", "test.com"), this->settings.getValue("config:port", 8081));
    
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
        this->usersColor[u] = new ofColor((ofRandomf()*150)+100,(ofRandomf()*150)+100,(ofRandomf()*150)+100);
    }

	this->points.push_back(new rzParticuleEmitter( newX, newY, 0.0, u, this ));

	if (this->points.size() > 100)
	{
		delete this->points[0];
		this->points.erase(this->points.begin());
	}
}

void ofApp::getConfiguration() {
    
    // Load configuration
    if(!this->settings.loadFile("settings.xml")){
        // Connection
        this->settings.setValue("config:host", "test.com");
        this->settings.setValue("config:port", 8081);
        
        // Vars
        this->settings.setValue("particules:initialForce", 2.0f);
        this->settings.setValue("particules:initialLife", 5.0f);
        this->settings.setValue("particules:maxSize", 20.0f);
        this->settings.setValue("particules:minSize", 3.0f);
        this->settings.setValue("particules:maxDeviation", 1.0f);
        
        // Emitter
        this->settings.setValue("emitter:creationParticulesCount", 5);
        this->settings.setValue("emitter:maxParticulesCount", 50);
        
        this->settings.saveFile("settings.xml");
    }
    
    
    rzParticule::INITIAL_FORCE = this->settings.getValue("particules:initialForce", 2.0f);
    rzParticule::INITIAL_LIFE = this->settings.getValue("particules:initialLife", 5.0f);
    rzParticule::MAX_SIZE = this->settings.getValue("particules:maxSize", 20.0f);
    rzParticule::MIN_SIZE = this->settings.getValue("particules:minSize", 20.0f);
    rzParticule::MAX_DEVIATION = this->settings.getValue("particules:maxDeviation", 1.0f);
    
    
    rzParticuleEmitter::PARTICULE_CREATION_COUNT = this->settings.getValue("emitter:creationParticulesCount", 5);
    rzParticuleEmitter::MAX_PARTICULE_COUNT = this->settings.getValue("emitter:maxParticulesCount", 50);
}