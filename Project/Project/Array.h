#ifndef _ARRAY
#define _ARRAY

#include <iostream>
#include <string>
#include <vector>


using namespace std;

namespace math {

	//------------------------------------ class Array ------------------------------------------------
	template <typename T>
	class Array {
	protected:
		vector<T> buffer; // Holds  data
		unsigned int width, height;

	public:
		//Returns the width of the array in pixels
		const unsigned int getWidth() const { return width; }

		//Returns the height of the array in pixels
		const unsigned int getHeight() const { return height; }

		//Obtains a pointer to the internal data
		vector<T> getRawDataPtr() {
			return buffer;
		}

		T getElement(unsigned int x, unsigned int y) const {
			T element;
			if (x > width || y > height || buffer.empty()) { // validity checking
				cout << "Error! Data's location is out of bounds!" << endl;
				return element;
			}
			else {
				// (y*width + x) is how we find the location in the pixel dimensional array
				return buffer[y*width + x];
			}
		}

		void setElement(unsigned int x, unsigned int y, T &value) {
			if (x > width || y > height) {
				cout << "Error! Invalid x y values!" << endl;
			}
			else {
				if (buffer.empty()) {
					cout << "Error! Empty buffer!" << endl;
				}
				else {// (y*width + x) is how we find the location in the pixel dimensional array
					buffer[y*width + x] = value;
				}
			}
		}

		void setData(const vector<T>  &data_ptr) {
			if (data_ptr.size() > buffer.size()) { 
				buffer.resize(width*height);// fixing the possible error
			}
			buffer = data_ptr;
		}

		Array() {
			width = 0;
			height = 0;
			buffer = vector<T>(0);
		}

		Array(unsigned int width, unsigned int height) {
			this->width = width;
			this->height = height;
			this->buffer = vector<T>(width*height);
		}

		Array(unsigned int width, unsigned int height, vector<T> data_ptr) {
			this->width = width;
			this->height = height;
			this->buffer = vector<T>(width*height);
			setData(data_ptr);
		}

		Array(const Array &src) :Array(src.getWidth(), src.getHeight(), src.buffer){}

		~Array() {
			buffer.clear();
		}

		Array & operator = (const Array & right) {
			// posing the dimensions at the new Image  
			if (this->width != right.width) {
				this->width = right.width;
			}
			if (this->height != right.height) {
				this->height = right.height;
			}
			if (!buffer.empty()) {
				buffer.clear();
			}
			setData(right.buffer); // copy
			return *this;
		}

		Array & operator ()(unsigned int x, unsigned int y) {
			return buffer[y*width + x];
		}
	};
}
#endif
