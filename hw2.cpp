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
	x_c = w / 2;
	y_c = h / 2;
}

Img::Img(const int* src, int w, int h) {
	srcImg = new int[w * h];
	for (int i = 0; i < w * h; i++)
		srcImg[i] = src[i];
	width = w;
	height = h;
	x_c = w / 2;
	y_c = h / 2;
}

Img::~Img() {
	delete[] srcImg;
	srcImg = nullptr;
}

void ImageProcess::imgOut(string key) {
	if (key == "source")
		for (int i = 0; i < srcImg->height; i++) {
			for (int j = 0; j < srcImg->width; j++) {
				cout << srcImg->srcImg[i * srcImg->width + j];
			}
			cout << endl;
		}
	if (key == "mask") {
		for (int i = 0; i < 9; i++) {
			cout << mask->srcImg[i];
		}
		cout << endl;
	}
}

int** ImageProcess::createMat(int n, int m) {
	int** A = new int* [n];
	A[0] = new int[n * m];
	for (int i = 1; i < n; i++) {
		A[i] = A[0] + i * m;
	}
	return A;
}

void ImageProcess::deleteMat(int** A) {
	delete[] A[0];
	delete[] A;
}

void ImageProcess::matOut(int** A, int h, int w) {
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++)
			cout << A[i][j] << " ";
		cout << endl;
	}
	cout << endl << endl;
}

void ImageProcess::putMask(int** &A, int y, int x, int height, int width, int** &Used) {
	y -= 1;
	x -= 1;
	for (int i = 0; i < 3; i++, y++) {
		if (y < 0 || y > height - 1)
			continue;
		for (int j = 0; j < 3; j++, x++) {
			if (x < 0 || x > width - 1)
				continue;
			if (A[y][x] == 0) {
				A[y][x] = mask->srcImg[i * 3 + j];
				if (A[y][x] == 1)
					Used[y][x] = 1;
			}
		}
		x -= 3;
	}
}

void ImageProcess::checkMask(int** A, int y, int x, int height, int width, int** &Mirror) {
	int sourceX = x, sourceY = y;
	y -= 1;
	x -= 1;
	for (int i = 0; i < 3; i++, y++) {
		if (y < 0 || y > height - 1)
			continue;
		for (int j = 0; j < 3; j++, x++) {
			if (x < 0 || x > width - 1)
				continue;
			if (A[y][x] < mask->srcImg[i * 3 + j]) {
				Mirror[sourceY][sourceX] = 0;
			}
		}
		x -= 3;
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
	srcImg = new Img( w, h );
	processedImg = srcImg;
	int* ar = new int[9] { 0, 1, 0, 1, 1, 1, 0, 1, 0};
	mask = new Img{ ar, 3, 3 };
	delete[] ar;
}

ImageProcess::ImageProcess(const Img* img) {
	srcImg = new Img( img->srcImg, img->width, img->height );
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
		fclose(fLog);
		srcImg = new Img;
		processedImg = srcImg;
		int* ar = new int[9] { 0, 1, 0, 1, 1, 1, 0, 1, 0};
		mask = new Img{ ar, 3, 3 };
		delete[] ar;
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
	mask = new Img( array, 3, 3 );
	delete[] array;
	delete[] ar;
	delete[] buf;
	//imgOut("mask");
}

ImageProcess::~ImageProcess() {
	delete srcImg;
	delete processedImg;
	delete mask;
	srcImg = nullptr;
	processedImg = nullptr;
	mask = nullptr;
}

int ImageProcess::updateMask(const Img& newMask) {
	*mask = newMask;
	//imgOut("mask");
	return 0;
}

int ImageProcess::updateSrcImg() {
	srcImg = processedImg;
	return 0;
}

int ImageProcess::dilatation(int key) {
	int w = srcImg->width, h = srcImg->height;
	int** A = createMat(h, w);
	if (key == 1) {
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				A[i][j] = srcImg->srcImg[i * w + j];
			}
		}
	} 
	else if (key == 0) {
		w = processedImg->width; 
		h = processedImg->height;
		deleteMat(A);
		int** A = createMat(h, w);
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				A[i][j] = processedImg->srcImg[i * w + j];
			}
		}
	} 
	else {
		deleteMat(A);
		return 1;
	}
	int** Used = createMat(h, w);
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			Used[i][j] = 0;
		}
	}
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			if (A[i][j] == 1 && Used[i][j] != 1) {
				putMask(A, i, j, h, w, Used);
			}
		}
	}
	matOut(A, h, w);
	if (key == 1)
		processedImg = srcImg;
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			processedImg->srcImg[i * w + j] = A[i][j];
		}
	}
	deleteMat(A);
	deleteMat(Used);
	return 0;
}

int ImageProcess::erosion(int key) {
	int w = srcImg->width, h = srcImg->height;
	int** A = createMat(h, w);
	if (key == 1) {
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				A[i][j] = srcImg->srcImg[i * w + j];
			}
		}
	}
	else if (key == 0) {
		w = processedImg->width;
		h = processedImg->height;
		deleteMat(A);
		int** A = createMat(h, w);
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				A[i][j] = processedImg->srcImg[i * w + j];
			}
		}
	}
	else {
		deleteMat(A);
		return 1;
	}
	int** Mirror = createMat(h, w);
	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++)
			Mirror[i][j] = A[i][j];
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			if (A[i][j] == 1) {
				checkMask(A, i, j, h, w, Mirror);
			}
		}
	}
	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++)
			A[i][j] = Mirror[i][j];
	matOut(A, h, w);

	if (key == 1)
		processedImg = srcImg;
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			processedImg->srcImg[i * w + j] = A[i][j];
		}
	}
	deleteMat(A);
	deleteMat(Mirror);
	return 0;
}