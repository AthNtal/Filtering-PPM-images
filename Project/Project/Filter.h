
#ifndef _FILTER
#define _FILTER

#include "Image.h"
namespace imaging {

	typedef math::Vec3<float> Color;
	class Filter {
		public:
			virtual Image operator << (const Image & image) = 0; // a pure virtual method
	};
}
#endif 

