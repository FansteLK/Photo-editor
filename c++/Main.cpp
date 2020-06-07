
#include "Image2.h"
#include "Selection.h"
Image *Image::instance = 0;
//vector<Rectangle>;
#include "Formatter.h"

#include <iostream>;
#include <fstream>
#include <cstring>
#include "CompositeOperation.h"
using namespace std;
int main(int argc, char **argv)
{
	Image *im=NULL;
	string slika;
	string trans;
	int broj_lejera = 0;
	std::ifstream infile(argv[1]);
	bool prvi = true;
	while (infile>>slika>>trans)
	{
		if (prvi) {
			FILE	*f = fopen(slika.c_str(), "r");
			unsigned char info[54];
			fread(info, sizeof(unsigned char), 54, f);
			int width = *(int*)&info[18];
			int height = *(int*)&info[22];
			fclose(f);
			im = im->GetInstance(width, height);

			im->AddLayer(slika.c_str(), "bmp", atoi(trans.c_str()));
			
			++broj_lejera;
		}
		else
		{

			im->AddLayer(slika.c_str(), "bmp", atoi(trans.c_str()));

		++broj_lejera;
		}
		prvi = false;
		
		
	}

	bool ima = false;
	std::ifstream infile3(argv[3]);
	string x, y, sirina, visina;

	while (infile3 >> x>> y>>sirina>>visina)
	{
		if(ima==false) 	im->AddSelection();
		ima = true;
		Position P(atoi(x.c_str()), atoi(y.c_str()));
		Rectangle R(P, atoi(sirina.c_str()), atoi(visina.c_str()));

		im->Get_Selection()->GetRectangles().push_back(R);
		

	}
	//im->setFalse();
	string kompozitna;
	std::ifstream infile2(argv[2]);
	infile2 >> kompozitna;
	CompositeOperation::zapisi(kompozitna, im);
	
	Formatter::output("C:\\Users\\stefa\\Desktop\\novo", "bmp", im->Get_Image());
		/*FILE	*f = fopen(argv[1], "r");
		unsigned char info[54];
		fread(info, sizeof(unsigned char), 54, f);
		int width = *(int*)&info[18];
		int height = *(int*)&info[22];
		fclose(f);
		Image *im = im->GetInstance(width, height);
		im->AddLayer(argv[1], "bmp",200);
		im->Visit(Operations::Crno_Belo, 1);
		*/
		//Formatter::output("C:\\Users\\stefa\\Desktop\\novo", "bmp", im->Get_Image());
		
		/*if (im->Get_num_layers() > 1) {
			im->Set_Num_Layers(im->Get_num_layers() - 1);
		}
		im->pop();*/
}