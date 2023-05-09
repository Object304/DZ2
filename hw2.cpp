#include "hw2.h"

Img::Img() {
	srcImg = nullptr;
	width = 0;
	height = 0;
	x_c = 0;
	y_c = 0;
}

Img::Img(int w, int h) {
	srcImg = nullptr;
	width = w;
	height = h;
	x_c = 0;
	y_c = 0;
}

Img::Img(const int* src, int w, int h) {
	srcImg = new int[w * h];
	for (int i = 0; i < w * h; i++)
		srcImg[i] = src[i];
	width = w;
	height = h;
	x_c = 0;
	y_c = 0;
}

Img::~Img() {
	delete[] srcImg;
	srcImg = nullptr;
}

void ImageProcess::imgOut() {
	for (int i = 0; i < srcImg->height; i++) {
		for (int j = 0; j < srcImg->width; j++) {
			cout << srcImg->srcImg[i * srcImg->width + j];
		}
		cout << endl;
	}
}

ImageProcess::ImageProcess() {
	srcImg = new Img;
	processedImg = srcImg;
	int* ar = new int[9] { 0, 1, 0, 1, 1, 1, 0, 1, 0};
	mask = new Img{ ar, 3, 3 };
	delete[] ar;
}

ImageProcess::ImageProcess(int w, int h) {
	srcImg = new Img{ w, h };
	processedImg = srcImg;
	int* ar = new int[9] { 0, 1, 0, 1, 1, 1, 0, 1, 0};
	mask = new Img{ ar, 3, 3 };
	delete[] ar;
}

ImageProcess::ImageProcess(const Img* img) {
	srcImg = new Img{ img->srcImg, img->width, img->height };
	processedImg = srcImg;
	int* ar = new int[9] { 0, 1, 0, 1, 1, 1, 0, 1, 0};
	mask = new Img{ ar, 3, 3 };
	delete[] ar;
}

ImageProcess::ImageProcess(const char* fileName) {
	FILE* fLog = fopen(fileName, "r");
	int w, h;
	if (fscanf(fLog, "%d\t%d", &w, &h) == false) { 
		cout << "wrong input" << endl; 
		return;
	}
	int* ar = new int[w * h];

	string text;
	char* buf = new char[255];
	while (fscanf(fLog, "%s", buf) != EOF) {
		text += buf;
	};

	for (int i = 0; i < h * w; i++) {
		ar[i] = (int)text[i] - '0';
	}
	fclose(fLog);
	srcImg = new Img{ ar, w, h };
	processedImg = srcImg;
	int* array = new int[9] { 0, 1, 0, 1, 1, 1, 0, 1, 0};
	mask = new Img{ array, 3, 3 };
	delete[] array;
	delete[] ar;
	delete[] buf;
	imgOut();
}

ImageProcess::~ImageProcess() {
	delete srcImg;
	delete processedImg;
	delete mask;
	srcImg = nullptr;
	processedImg = nullptr;
	mask = nullptr;
}

