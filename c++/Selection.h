#ifndef _Selection_H_
#define _Selection_H_
#include "Rectangle.h"
#include "Layer.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Selection

{
private:
	friend class Image;
	friend class MyFormatter;
	
	string ime;
	//aktivnost selekcije
	bool aktiv;
	vector<Rectangle> selekcije;
	//Konstruktori
	Selection()
	{
		
	
		aktiv = true;

	}
	//broji pravougaonike
	int Count_Rectangles() const
	{
		return selekcije.size();
	}
public:
	//Geteri
	string Get_Ime() const { return ime; }
bool Get_Aktiv() const { return aktiv; }

    //Seteri
	void SetAktivTrue()
	{
		aktiv = true;
	}
	void SetAktivFalse()
	{
		aktiv = false;
	}
	//postavljanje boje nad selekcijom
	void SetColor(Pixel P, Layer &l)
	{
	
		for_each(selekcije.begin(), selekcije.end(), [&l,P](Rectangle R) 
		{
			int height = R.GetHeight();
			int width = R.GetWidth();
	
			if ((R.GetHeight() + R.GetPoz().GetRed()) > l.Get_Num_Ver_Pix()) height = l.Get_Num_Ver_Pix() - R.GetPoz().GetRed();
			if ((R.GetWidth() + R.GetPoz().GetKolona()) > l.Get_Num_Hor_Pix()) width = l.Get_Num_Hor_Pix() - R.GetPoz().GetKolona();
			for (int i = 0; i < height; i++)
			{
				for (int j = 0; j < width; j++)
				{
				
					l.Set_Pixel(P, i + R.GetPoz().GetKolona(), j + R.GetPoz().GetRed());
				

				}
			}
			
					
			
		}
		);
		
	}
	
	//
	vector<Rectangle>& GetRectangles()
	{
		return selekcije;
	}
	//prolazak kroz pravougaonike
	void Visit(void(*predicate)(Pixel &, int a), Layer &l, int c)
	{
		
		for_each(selekcije.begin(), selekcije.end(), [ predicate, &l, c](Rectangle R)
		{
	
			int height = R.GetHeight();
			int width = R.GetWidth();
			
			if ((R.GetHeight() + R.GetPoz().GetKolona()) > l.Get_Num_Ver_Pix()) height = l.Get_Num_Ver_Pix() - R.GetPoz().GetKolona();
			if ((R.GetWidth() + R.GetPoz().GetRed()) > l.Get_Num_Hor_Pix()) width = l.Get_Num_Hor_Pix() - R.GetPoz().GetRed();
			for (int i = 0; i < height; i++)
			{
				for (int j = 0; j < width; j++)
				{
				
					predicate(l.Get_Pixels()[i +R.GetPoz().GetKolona() ][j+ R.GetPoz().GetRed()], c);

				}
			}

		}
		);
	}
	//ispis slekcije
	friend ostream& operator<<(ostream &ot, const Selection &s) 
	{
		ot << s.Get_Ime() << endl;
		if(s.Get_Aktiv())
		{
			ot << 1 << endl;
		}
		else { ot << 0 << endl; }

		int k = s.Count_Rectangles();
		ot << k<<endl;
		for ( Rectangle R : s.selekcije)
		{
			ot << R << endl;
			
		}

		return ot;
	}

};

#endif