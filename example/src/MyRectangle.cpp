#include "MyRectangle.h"
#include "Image.h"

//----------
void MyRectangle::draw() {
	Image::X().image.draw(this->bounds);
}