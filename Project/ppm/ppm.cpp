#include <iostream>
#include <string>
#include <fstream>
#include "ppm.h"
using namespace std;

namespace imaging {

	float* ReadPPM(const char * filename, int * w, int * h) {

		fstream imageFile(filename, ios::in | ios::binary); // Opening the image-file for reading

		if (imageFile.is_open()) {
			string imageType;
			imageFile >> imageType; //reading the ppm format

			if (imageType.compare("P6") == 0) {
				imageFile >> *w >> *h; //reading the dimensions

				if (*w > 0 && *h > 0) {
					int max_val;
					imageFile >> max_val; // reading the maximum value of a pixel

					if (max_val <= 255) {
						char separatorChar = imageFile.get(); // reading the char after the image information

						if (separatorChar == ' ' || separatorChar == '\n' || separatorChar == '\t' || separatorChar == '\r') {
							unsigned int size = 3 * (*w)*(*h);
							unsigned char *tempBuffer = new unsigned char[size];
							imageFile.read((char*)tempBuffer, size); // reading all values

							float * imageBuffer = new float[size];
							//parsing the data 
							for (unsigned int i = 0; i < size; i++) {
								imageBuffer[i] = tempBuffer[i] / (float)max_val;
							}

							delete[] tempBuffer;
							imageFile.flush(); //Making sure everything passed into the file
							imageFile.clear(); //Erasing the contents of the image
							imageFile.close(); //Closing the file
							return imageBuffer; //this is the float array which is returned

						}
						else { // error with  separatorChar
							cout << "Error! Separator character between  image header and image data not found!" << endl;
							return nullptr;
						}

					}
					else { // error with  max_val
						cout << "Error! Only 24bit images are supported!" << endl;
						return nullptr;
					}
				}
				else { //error with dimensions
					cout << "Error! Something went wrong with the reading of the dimensions" << endl;
					return nullptr;
				}
			}
			else { // ppm  format error
				cout << "Error! Only ppm format is supported" << endl;
				return nullptr;
			}
		}
		else { //opening error
			cout << "Error! Cannot open the image!" << endl;
			return nullptr;
		}

	}

	bool WritePPM(const float * data, int w, int h, const char * filename) {
		fstream imageFile(filename, ios::out | ios::binary); // Opening the image-file for writing

		if (imageFile.is_open()) {
			if (data != nullptr) {
				string imageType = "P6";
				int max_val = 255;
				//writing  header info into the image
				imageFile << imageType << endl << w << endl << h << endl << max_val << endl;
				unsigned int size = 3 * w * h;
				unsigned char *tempBuffer = new unsigned char[size];
				for (unsigned int i = 0; i < size; i++) {
					tempBuffer[i] = data[i] * max_val;
				}
				imageFile.write((char*)tempBuffer, size); //writing all values
				delete[] tempBuffer;
				imageFile.flush(); //Making sure everything passed into the file
				imageFile.clear(); //Erasing the contents of the image
				imageFile.close(); //Closing the file
				return true;

			}
			else {//There is no data
				cout << "Error! There is no data!" << endl;
				return false;
			}
		}
		else {//error opening the file
			cout << "Error! Cannot open the image! " << endl;
			return false;
		}
	}

}