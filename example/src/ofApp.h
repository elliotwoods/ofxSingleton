#pragma once

#include "ofMain.h"

#include "MyRectangle.h"

class ofApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();
	void keyPressed  (int key);

	vector<MyRectangle> rectangles;
};
