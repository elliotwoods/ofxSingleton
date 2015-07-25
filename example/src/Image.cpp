#include "Image.h"

// THIS LINE IS IMPORTANT! otherwise you'll get linker errors
Image::SingletonStore Image::singletonStore;

//----------
Image::Image() {
	this->image.load("zoom_fit.png");
}