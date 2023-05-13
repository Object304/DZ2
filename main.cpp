#include "hw2.h"

int main()
{
	ImageProcess* ip = new ImageProcess;
	ip->loadImgFromFile("Format1.txt");

	/*int* ar = new int[9] { 1, 1, 1, 1, 1, 1, 1, 1, 1, };
	Img* mask1 = new Img{ ar, 3, 3 };
	while (true)
	{
		ImageProcess* ip = new ImageProcess(mask1);
		delete ip;
	}*/

	int* ar = new int[25] { 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, };
	Img* mask1 = new Img{ ar, 5, 5 };
	ip->updateMask(*mask1);
	delete[] ar;
	delete mask1;

	list<list<pair<int /*x*/, int /*y*/>>> contours = ip->getListContours();
	//ip->checkListContours(contours);

	ip->dilatation(1);
	ip->updateSrcImg();
	ip->saveImgToFile("save1.txt");
	ip->dilatation(1);
	ip->updateSrcImg();
	ip->saveImgToFile("save2.txt");

	contours = ip->getListContours();
	//ip->checkListContours(contours);

	ip->erosion(1);
	ip->updateSrcImg();
	ip->saveImgToFile("save3.txt");
	ip->erosion(1);
	ip->updateSrcImg();
	ip->saveImgToFile("save4.txt");
	ip->erosion(1);
	ip->updateSrcImg();
	ip->saveImgToFile("save5.txt");
	ip->updateSrcImg();

	return 0;
}
