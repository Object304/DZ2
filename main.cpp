#include "hw2.h"

int main()
{
	ImageProcess* ip = new ImageProcess("Format1.txt");

	ip->erosion(1);

	/*ip->saveImgToFile("Save1.txt", 2);
	ip->loadImgFromFile("Format1.txt");
	ip->saveImgToFile("Save2.txt", 55);*/

	/*int* ar = new int[9] { 1, 1, 1, 1, 1, 1, 1, 1, 1, };
	Img* mask1 = new Img{ ar, 3, 3 };*/
	/*while (true)
	{
		ImageProcess* ip = new ImageProcess(mask1);
		delete ip;
	}*/

	/*int* ar = new int[9] { 1, 1, 1, 1, 1, 1, 1, 1, 1, };
	Img* mask1 = new Img{ ar, 3, 3 };
	ip->updateMask(*mask1);
	delete[] ar;
	delete mask1;*/

	/*ip->dilatation(1);
	ip->dilatation(0);
	ip->erosion(0);
	ip->erosion(0);
	ip->erosion(0);*/

	//ip->dilatation(1);

	return 0;
}
