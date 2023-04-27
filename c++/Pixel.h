#ifndef _Pixel_H_
#define _Pixel_H_

#include <iostream>
#include <string>
using namespace std;

class Pixel {

private:
	int crveno;
	int zeleno;
	int plavo;
	int alfa_kanal;
	bool selektovan;
public:
	Pixel(int c = 0, int z = 0, int  p = 0,int alfa=0) 
	{
		
		if ((c < 0) || (c > 255) || (z < 0) || (z > 255) || (p < 0) || (p > 255))
			exit(1);

		crveno = c;
		zeleno = z;
		alfa_kanal = 0;
		plavo = p;
		selektovan = false;
	}
	//Geteri
	int  GetCrveno()const
	{
		return crveno;
	}
	int GetPlavo()const
	{
		return plavo;
	}
	int GetZeleno() const 
	{
		return zeleno;
	}
	int GetAlfa() const
	{
		return alfa_kanal;
	}
	bool GetSelektovan() const { return selektovan; }
	void Set_Alpha(int a)
	{
		alfa_kanal = a;
	}
	//Seteri
	void Set_Crveno(int a) { crveno = a; }
	void Set_Zeleno(int a) { zeleno = a; }
	void Set_Plavo(int a) { plavo = a; }
	void Set_Selektovano_True() { selektovan = true; };
	void Set_Selektovano_False() { selektovan = false; };
	//Ispis piksela
	friend ostream& operator<<(ostream &ot, const Pixel &p) {
	return	ot <<  p.crveno << " " << p.zeleno << " " <<p.plavo <<" "<<p.alfa_kanal ;			}

};



#endif 