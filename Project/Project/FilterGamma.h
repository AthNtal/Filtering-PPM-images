#ifndef  _FILTERGAMMA
#define _FILTERGAMMA

#include "Filter.h"
#include "Image.h"
#include "Vec3.h"
#include <vector>
#include <iostream>
#include <cmath>

using namespace std;
namespace imaging {
	class FilterGamma : public Filter {
	protected:
		double y;
	public:

		FilterGamma() {}

		FilterGamma(double y2) {
			y = y2;
		}

		FilterGamma(const FilterGamma & src) {
			y = src.y;
		}

		Image operator << (const Image & image) {
			Image tempImage(image.getWidth(), image.getHeight());
			vector<Color>buffer(image.getWidth()*image.getHeight());
			unsigned int k = 0;
			if (y >= 0.5 && y <= 2.0) { // checking if y is valid
				// filtering the image
				for (unsigned int i = 0; i < image.getWidth(); i++) {
					for (unsigned int j = 0; j < image.getHeight(); j++) {
						buffer[k].r = pow(image.getElement(i, j).r, y);
						buffer[k].g = pow(image.getElement(i, j).g, y);
						buffer[k].b = pow(image.getElement(i, j).b, y);
						//boundary checking
						buffer[k] = buffer[k].clampToLowerBound(0.0f);
						buffer[k] = buffer[k].clampToUpperBound(1.0f);
						k++;
					}
				}
				tempImage.setData(buffer);
				return tempImage;
			}else { //returning the image without any change
				cout << "Error! Invalid value at y. Filter cannot be applied" << endl;
				return image;
			}
		}
	};
}
#endif

