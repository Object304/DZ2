#include "hw2.h"

void checkListContours10(list<list<pair<int /*x*/, int /*y*/>>> contours) {
	list<list<pair<int /*x*/, int /*y*/>>>::iterator this_contour = contours.begin();
	list<pair<int /*x*/, int /*y*/>> contour = *this_contour;
	list<pair<int /*x*/, int /*y*/>>::iterator this_pair = contour.begin();
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			bool one = false;
			while (this_pair != contour.end()) {
				if (i == this_pair->second && j == this_pair->first) {
					cout << "1" << " ";
					one = true;
					break;
				}
				this_pair++;
			}
			if (!one)
				cout << "0" << " ";
			this_pair = contour.begin();
		}
		cout << endl;
	}
	cout << endl;
}

int main()
{
	#ifdef MEMORY_LEAK
	{
		int* ar = new int[9] { 1, 1, 1, 1, 1, 1, 1, 1, 1, };			//memory leak test
		Img* image = new Img{ ar, 3, 3 };
		while (true)
		{
			ImageProcess* ip = new ImageProcess(image);
			delete ip;
		}
	}
	#endif

	{
		ImageProcess* ip = new ImageProcess;
		ip->loadImgFromFile("test1_format1.txt");
		ip->dilatation(1);
		ip->dilatation(0);
		ip->updateSrcImg();
		ip->saveImgToFile("save1_dilat.txt");
		ip->erosion(1);
		ip->erosion(0);
		ip->updateSrcImg();
		ip->saveImgToFile("save1_eros.txt");
		list<list<pair<int /*x*/, int /*y*/>>> contours = ip->getListContours();
		checkListContours10(contours);
		delete ip;
	}

	{
		int* ar = new int[25] { 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, };
		Img* mask1 = new Img{ ar, 5, 5 };
		ImageProcess* ip = new ImageProcess("test2_format0.txt");
		ip->updateMask(*mask1);
		ip->dilatation(1);
		ip->updateSrcImg();
		ip->saveImgToFile("save2_dilat.txt");
		ip->erosion(1);
		ip->updateSrcImg();
		ip->saveImgToFile("save2_eros.txt");
		delete[] ar;
		delete mask1;
		delete ip;
	}

	return 0;
}
