#pragma once
#include "ofxSingleton.h"
#include "ofMain.h"

class Image : public ofxSingleton::Singleton<Image> {
public:
	Image();

	ofImage image;
};
