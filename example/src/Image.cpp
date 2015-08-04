#include "Image.h"

// THIS LINE IS IMPORTANT! otherwise you'll get linker errors
OFXSINGLETON_DEFINE(Image);

//----------
Image::Image() {
	this->image.load("zoom_fit.png");
}