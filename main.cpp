#include "hw2.h"

int main()
{
	ImageProcess* ip = new ImageProcess{ "Format_test.txt" };

	int* ar = new int[9] { 1, 1, 1, 1, 1, 1, 1, 1, 1, };
	Img* mask = new Img{ ar, 3, 3 };
	ip->updateMask(*mask);
	delete[] ar;
	//ip->erosion(1);

	return 0;
}
