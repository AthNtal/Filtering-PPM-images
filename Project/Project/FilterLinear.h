#pragma once
#ifndef  _FILTERLINEAR
#define _FILTERLINEAR

#include "Filter.h"
#include "Vec3.h"
#include "Image.h"

#include <iostream>
namespace imaging {
	class FilterLinear : public Filter {
		Color a, c;
	public:
		// constructors
		FilterLinear() {}
		FilterLinear(Color x, Color y) {
			a = x;
			c = y;
		}
		FilterLinear(const FilterLinear & src) {
			a = src.a;
			c = src.c;
		}

		Image operator << (const Image & image) {
			Image tempImage(image.getWidth(), image.getHeight());
			vector<Color>buffer(image.getWidth()*image.getHeight());
			
			//filtering the image
			unsigned int k = 0;
			for (unsigned int i = 0; i < image.getWidth(); i++) {
				for (unsigned int j = 0; j < image.getHeight(); j++) {

					buffer[k]=Color(a * image.getElement(i, j) + c);
					// fixing the values
					buffer[k] = buffer[k].clampToLowerBound(0.0f);
					buffer[k] = buffer[k].clampToUpperBound(1.0f);
					k++;
					
				}
			}
			tempImage.setData(buffer);
			return tempImage;
		}
	};
}

#endif  

