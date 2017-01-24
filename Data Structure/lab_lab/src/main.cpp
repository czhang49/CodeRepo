#include <iostream>
#include "epng.h"
using namespace epng;
using namespace std;

void removeColor()
{
	int Im_Width;
	int Im_Height;
	int count_wid;
	int count_heit;

	cout<<"In removeColor!"<<endl;
	png image("in.png");

	Im_Width=image.width();
	Im_Height=image.height();

	for ( count_wid=0;count_wid<Im_Width;count_wid++)
	  { for ( count_heit=0;count_heit<Im_Height;count_heit++)
		{  image(count_wid,count_heit)->green=0; }
	  }
	image.save("removed.png");

}

int main()
{
	cout<<"In Main !"<<endl;
	removeColor();
	return 0;
}
