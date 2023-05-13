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
	//����� ����� ��������� ������ ���������� � �������
public:
	//����� ������ ��������� ������� � ����������
	/**/
	ImageProcess();
	/* ���������� ������ ��� �������� ������� w*h */
	ImageProcess(int w, int h);
	/* ���������� ������ ��� �������� ������� w*h � ���������� ��������*/
	ImageProcess(const Img* img);
	/* ���������� ������ ��� �������� ���������� �������� �� �����, ������ ������� � ����� �������� ������ � ������ ��������*/
	ImageProcess(const char* fileName);
	~ImageProcess();

	/*������� �����*/
	int updateMask(const Img& mask);
	/*������������ �������� �������� ���������, ������� ���� �������� � ���������� ��������� �/��� ������*/
	int updateSrcImg();
	/*��������� ��������, ��������� �������� � processedImg*/
	/*
		input		:	srcImg = 1, �������������� srcImg  - ��������� ������������ � processedImg
						srcImg = 0, �������������� processedImg - ��������� ������������ � processedImg
	*/
	int dilatation(int srcImg = 1);	//��������� �� dilatation
	/*������ ��������, ��������� �������� � processedImg*/
	int erosion(int srcImg = 1);
	/*
		���������/��������� �� ����� � ������� fileName ��������
		input		:	fileName - ��� �����
						format - ������ ����� 	0 - ������������������ 0 � 1, ��� �������� �� ����� ������
												1 - ������������������ 0 � 1, � ��������� �� ����� ������
	*/
	int loadImgFromFile(const char* fileName, int format = 1);
	int saveImgToFile(const char* fileName, int format = 1);

	/*�� ����� ��� ������*/
	std::list<std::list<std::pair<int /*x*/, int /*y*/>>> getListContours();
};