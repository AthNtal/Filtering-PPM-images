#include <iostream>
#include <string>
#include <vector>
#include "Image.h"
#include "../ppm/ppm.h"


using namespace std;
using namespace imaging;

	bool Image::load(const std::string & filename, const std::string & format) {
		if (format != "ppm" && format != "PPM") { // format validity
			cout << "Error at loading! Only the 'ppm' extension is supported !" << endl;
			return false;
		}
		
		float *buff = ReadPPM(filename.c_str(), (int*)&width, (int*)&height);
		//loading  data (data is read by ReadPPM)
		if (buff != nullptr) {
			buffer = vector<Color>(width*height);
			unsigned int index = 0;
			for (unsigned int i = 0; i < buffer.size(); i++) {
				buffer[i].r = buff[index++];
				buffer[i].g = buff[index++];
				buffer[i].b = buff[index++];
			}
		}else {
			cout << "Error! Empty buffer!" << endl;
		}
		delete[] buff;
		return true;
	}

	bool Image::save(const std::string & filename, const std::string & format) {

		if (format != "ppm" && format != "PPM") { //format validity
			cout << "Error at saving! Only the 'ppm' extension is supported !" << endl;
			return false;
		}

		//passing data to buffer
		float *buff = new float[3*width*height];
		unsigned int index = 0;
		for (unsigned int i = 0; i <width*height; i++) {
			buff[index++] = buffer[i].r;
			buff[index++] = buffer[i].g;
			buff[index++] = buffer[i].b;
		}

		bool ready = WritePPM(buff, width, height, filename.c_str());
		delete[]buff;
		if (!ready) {//error at WritePPM
			cout << "Error at writing! " << endl;
			return false;
		}else {
			return true;
		}
	}
