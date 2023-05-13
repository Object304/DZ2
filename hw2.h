#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <list>
#include <string>

using namespace std;


struct Img{
	int* srcImg;
	int width;
	int height;

	int x_c;
	int y_c;

	Img();
	Img(int w, int h);
	Img(const int* src, int w, int h);
	~Img();
};

class ImageProcess {
private:
	Img* srcImg;
	Img* processedImg;
	Img* mask;

	void imgOut(Img*& Image);
	int** createMat(int n, int m);
	void deleteMat(int** A);
	void matOut(int** A, int height, int width);
	void putMask(int**& A, int y, int x, int height, int width, int** &Used);
	void checkMask(int** A, int y, int x, int height, int width, int** &Mirror);
	void copyImg(Img* &target, Img* source);
	void copyImg(Img* &target, const Img* source);
	void checkListContours(list<list<pair<int /*x*/, int /*y*/>>> contours);
	//здесь можно объ€вл€ть другие переменные и функции
public:
	//здесь нельз€ объ€вл€ть функции и переменные
	/**/
	ImageProcess();
	/* выдел€етс€ пам€ть дл€ картинки размера w*h */
	ImageProcess(int w, int h);
	/* выдел€етс€ пам€ть дл€ картинки размера w*h и копируетс€ картинка*/
	ImageProcess(const Img* img);
	/* выдел€етс€ пам€ть дл€ картинки копируетс€ картинка из файла, перва€ строчка в файле содержит ширину и высоту картинки*/
	ImageProcess(const char* fileName);
	~ImageProcess();

	/*задание маски*/
	int updateMask(const Img& mask);
	/*перезаписать исходную картинку картинкой, котора€ была получена в результате дилатации и/или эрозии*/
	int updateSrcImg();
	/*дилатаци€ картинки, результат записать в processedImg*/
	/*
		input		:	srcImg = 1, обрабатываетс€ srcImg  - результат записываетс€ в processedImg
						srcImg = 0, обрабатываетс€ processedImg - результат записываетс€ в processedImg
	*/
	int dilatation(int srcImg = 1);	//исправить на dilatation
	/*эрози€ картинки, результат записать в processedImg*/
	int erosion(int srcImg = 1);
	/*
		загрузить/сохранить из файла с имененм fileName картинку
		input		:	fileName - им€ файла
						format - формат файла 	0 - последовательность 0 и 1, без перехода на новую строку
												1 - последовательность 0 и 1, с переходом на новую строку
	*/
	int loadImgFromFile(const char* fileName, int format = 1);
	int saveImgToFile(const char* fileName, int format = 1);

	/*на зачЄт без зачЄта*/
	std::list<std::list<std::pair<int /*x*/, int /*y*/>>> getListContours();
};