#ifndef _Layer_H_
#define _Layer_H_
#include"Pixel.h"
#include "Position.h"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "BasicOperation.h"
class Image;
using namespace std;

class Layer{
private:
	//friend class BMPFormatter;
	friend class MyFormatter;
	friend class Image;
	//velicina
	int num_ver_pix;
	int num_hor_pix;
	//putanja do layera
	string putanja;
	//aktivnost layera
	bool active;
	//indikator promene velicine
	bool change;
	//Konstruktori
	
	Layer(int ver, int hor, bool ak)
	{
		num_ver_pix = ver;
		num_hor_pix = hor;
	
		active = ak;
		change = false;

	}
	Layer(const char*, string,int, int, int,int,int);
	
		//Privatni Seteri
   void Set_transparency(int a)  
   {
	   for (vector<Pixel> &p : lyr)
	   {
		   for (Pixel &pix : p) 
		   {
			   pix.Set_Alpha(a);
		   }
		
	   }

	  
   }

	void Set_Active_False()
	{
		active = false;
	}
	void Set_Active_True()
	{
		active = true;
	}
	void Set_Change()
	{
		change = true;
	}
	void reset_change()
	{
		change = false;
	}
	vector<vector <Pixel>> lyr;
public:

	//Geteri
	int Get_Num_Ver_Pix() const { return num_ver_pix; };
	int Get_Num_Hor_Pix() const { return num_hor_pix; };
	int Get_Active() const { return active; };
	
	vector<vector <Pixel>> & Get_Pixels() { return lyr; }
	Pixel Get_Pixel(int a,int b)
	{
		return lyr[a][b];
	}
	//Seteri
	void Set_Pixel(Pixel p, int a, int b)
	{
		lyr[a][b] = p;

	}
	void Set_Num_Ver(int a)
	{
		num_ver_pix = a;
	}
	void Set_Num_Hor(int a)
	{
		num_hor_pix = a;
	}
//Prolazak kroz sve piksele layera i vrsenje operacije
void Visit(void (*predicate)(Pixel &p,int a),int b,bool k)
	{
		
		for (vector<Pixel> &p : lyr)
		{
			for (Pixel &pix : p)
			{
				if(k)
				{
					if (pix.GetSelektovan())
					{
						predicate(pix, b);
					}
				}
				else
				{
					predicate(pix, b);
				}
				
			}
			
		}
	}
//Ispis layera
friend ostream& operator<<(ostream &ot, const Layer &l) {

	if (l.Get_Active()) ot << "1\n";
	else ot << "0\n";
	for (vector<Pixel> p : l.lyr)
	{
		for (Pixel pix : p) {
			ot << pix << "  "; 
		}
		ot<< "\n";
	}
	
	return ot;
}

};



#endif 