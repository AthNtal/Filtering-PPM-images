#include <iostream>
#include <string>

#include "FilterGamma.h"
#include "FilterLinear.h"
#include "Image.h"
#include "Filter.h"

using namespace std;
using namespace imaging;
using namespace math;

int main(int argc, char* argv[]) {
	Image *image = new Image();

	/* the condition is (argc<3) because the arguments must be at least:
		-  -f
		- image path
		- filter
	*/
	if (argc < 3) {
		cout << "Error! Image or Filter is missing! The program will exit!" << endl;
		system("pause");
		return -1;
	}

	//loading the image
	string filename = argv[argc - 1];
	int ImFound = filename.find("Image") || filename.find("image");
	if (ImFound != string::npos) {
		bool loaded = image->load(filename, "ppm");
		if (!loaded) {
			cout << "Error! No image! The program will exit!" << endl;
			system("pause");
			return -1;
		}else {
			cout << "Image succesffully loaded" << endl;
		}
	}

	Image finalImage(*image);

	// matching the filters
	int i = 1;
	while (i < (argc-1 )) {
		if (string(argv[i]) == "-f") {
			i++;
			if (string(argv[i]) == "linear") {
				float linearAC[6]; // the array with a,c values for rgb
				for (int j = 0; j < 6; j++) {
					i++;
					linearAC[j] = stof(argv[i]);
				}
				Color a = Color(linearAC[0], linearAC[1], linearAC[2]);
				Color c = Color(linearAC[3], linearAC[4], linearAC[5]);
				FilterLinear filterL(a, c);
				finalImage = filterL << finalImage;
				i++;
				
			}else if (string(argv[i]) == "gamma") {
				i++;
				double y = atof(argv[i]);
				FilterGamma filterG(y);
				finalImage = filterG << finalImage;
				i++;
				
			}else {
				cout << "Error! Filter must be linear of gamma." << endl;
				system("pause");
				return -1;
			}
		}else {
			cout << "Error! The first argument must be -f" << endl;
			system("pause");
			return -1;
		}
	}

	//fixing the name
	string temp = "filtered_";
	temp.append(filename);

	bool saved = finalImage.save(temp, "ppm");
	if (saved) {
		cout << "Filtered image created!" << endl;
	}
	else {
		cout << "Error at saving the image!" << endl;
	}
	delete image;
	system("pause");
	return 0;
}