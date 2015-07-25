#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(100, 100, 100);
	ofSetFrameRate(60);

	for (int i = 0; i < 50; i++) {
		MyRectangle newRectangle;
		newRectangle.bounds = ofRectangle(
			ofRandom(ofGetWidth()),
			ofRandom(ofGetHeight()),
			32,
			32);

		this->rectangles.push_back(newRectangle);
	}
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
	for (auto & rectangle : this->rectangles) {
		rectangle.draw();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
}