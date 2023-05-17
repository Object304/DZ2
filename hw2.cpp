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

void ImageProcess::imgOut(Img* &Image) {
	for (int i = 0; i < Image->height; i++) {
		for (int j = 0; j < Image->width; j++) {
			cout << Image->srcImg[i * Image->width + j] << " ";
		}
		cout << endl;
	}
	cout << endl;
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
	y -= mask->height / 2;
	x -= mask->width / 2;
	for (int i = 0; i < mask->height; i++, y++) {
		if (y < 0 || y > height - 1)
			continue;
		for (int j = 0; j < mask->width; j++, x++) {
			if (x < 0 || x > width - 1)
				continue;
			if (A[y][x] == 0) {
				A[y][x] = mask->srcImg[i * mask->width + j];
				if (A[y][x] == 1)
					Used[y][x] = 1;
			}
		}
		x -= mask->width;
	}
}

void ImageProcess::checkMask(int** A, int y, int x, int height, int width, int** &Mirror) {
	int sourceX = x, sourceY = y;
	y -= mask->height / 2;
	x -= mask->width / 2;
	for (int i = 0; i < mask->height; i++, y++) {
		if (y < 0 || y > height - 1)
			continue;
		for (int j = 0; j < mask->width; j++, x++) {
			if (x < 0 || x > width - 1)
				continue;
			if (A[y][x] < mask->srcImg[i * mask->width + j]) {
				Mirror[sourceY][sourceX] = 0;
			}
		}
		x -= mask->width;
	}
}

void ImageProcess::copyImg(Img* &target, Img* source) {
	delete target;
	target = new Img(source->srcImg, source->width, source->height);
}

void ImageProcess::copyImg(Img* &target, const Img* source) {
	delete target;
	target = new Img(source->srcImg, source->width, source->height);
}

ImageProcess::ImageProcess() {
	srcImg = new Img;
	processedImg = new Img;
	int* ar = new int[9] { 0, 1, 0, 1, 1, 1, 0, 1, 0};
	mask = new Img{ ar, 3, 3 };
	delete[] ar;
}

ImageProcess::ImageProcess(int w, int h) {
	srcImg = new Img( w, h );
	processedImg = new Img( w, h );
	int* ar = new int[9] { 0, 1, 0, 1, 1, 1, 0, 1, 0};
	mask = new Img{ ar, 3, 3 };
	delete[] ar;
}

ImageProcess::ImageProcess(const Img* img) {
	srcImg = new Img( img->srcImg, img->width, img->height );
	processedImg = new Img(img->srcImg, img->width, img->height);
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
		processedImg = new Img;
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
	processedImg = new Img{ ar, w, h };;
	int* array = new int[9] { 0, 1, 0, 1, 1, 1, 0, 1, 0};
	mask = new Img( array, 3, 3 );
	delete[] array;
	delete[] ar;
	delete[] buf;
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
	copyImg(mask, &newMask);
	return 0;
}

int ImageProcess::updateSrcImg() {
	copyImg(srcImg, processedImg);;
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
	if (key == 1)
		copyImg(processedImg, srcImg);
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

	if (key == 1)
		copyImg(processedImg, srcImg);
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			processedImg->srcImg[i * w + j] = A[i][j];
		}
	}
	deleteMat(A);
	deleteMat(Mirror);
	return 0;
}

int ImageProcess::loadImgFromFile(const char* fileName, int format) {
	FILE* fLog = fopen(fileName, "r");
	int w, h;
	if (fscanf(fLog, "%d\t%d", &w, &h) == false) {
		cout << "wrong input" << endl;
		fclose(fLog);
		return 1;
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
	Img* NEWsrcImg = new Img{ ar, w, h };
	copyImg(srcImg, NEWsrcImg);
	delete NEWsrcImg;
	delete[] ar;
	delete[] buf;
	return 0;
}

int ImageProcess::saveImgToFile(const char* fileName, int format) {
	if ((format == 1 || format == 0) == false) {
		cout << "wrong input" << endl;
		return 1;
	}
	FILE* fLog = fopen(fileName, "w");
	fprintf(fLog, "%d\t%d\n", srcImg->width, srcImg->height);
	for (int i = 0; i < srcImg->height; i++) {
		for (int j = 0; j < srcImg->width; j++) {
			fprintf(fLog, "%d", srcImg->srcImg[i * srcImg->width + j]);
		}
		if (format == 1) {
			fprintf(fLog, "\n");
		}
	}
	fclose(fLog);
	return 0;
}

list<list<pair<int /*x*/, int /*y*/>>> ImageProcess::getListContours() {
	dilatation(1);
	list<list<pair<int /*x*/, int /*y*/>>> contours;
	list<pair<int /*x*/, int /*y*/>> contour;
	pair<int, int> point;
	for (int i = 0; i < srcImg->height; i++) {
		for (int j = 0; j < srcImg->width; j++) {
			if (srcImg->srcImg[i * srcImg->width + j] != processedImg->srcImg[i * srcImg->width + j]) {
				point.first = j;
				point.second = i;
				contour.push_back(point);
			}
		}
	}
	contours.push_back(contour);
	return contours;
}