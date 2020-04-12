#ifndef _BasicOperation_H_
#define _BasicOperation_H_

#include <iostream>
#include <stdio.h>
#include "Pixel.h"
//#include "Layer.h"
class BasicOperation
{
	friend class Operations;

	static void sabiranje(Pixel &P, int a)
	{
		P.Set_Crveno(P.GetCrveno() + a) ;
		P.Set_Plavo(P.GetPlavo() + a) ;
		P.Set_Zeleno (P.GetZeleno() + a) ;
	}
	static void oduzimanje(Pixel &P, int a)
	{
		P.Set_Crveno (P.GetCrveno() - a);
		P.Set_Plavo  (P.GetPlavo() - a);
		P.Set_Zeleno  (P.GetZeleno() - a);
	}
	static void inverzno_oduzimanje(Pixel &P, int a)
	{
		P.Set_Crveno (a - P.GetCrveno());
		P.Set_Plavo  (a - P.GetPlavo());
		P.Set_Zeleno  (a - P.GetZeleno());
	}
	static void mnozenje(Pixel &P, int a)
	{
		P.Set_Crveno (P.GetCrveno() * a);
		P.Set_Plavo (P.GetPlavo() * a);
		P.Set_Zeleno (P.GetZeleno() * a) ;

	}
	static void deljenje(Pixel &P, int a)
	{
		if (a != 0) 
        {
			P.Set_Crveno((int)abs((int)(P.GetCrveno() / a)));
			P.Set_Plavo((int)abs((int)(P.GetPlavo() / a)));
			P.Set_Zeleno(((int)abs((int)(P.GetZeleno() / a))));
		}
	}
	static void inverzno_deljenje(Pixel &P, int a)
	{
		P.Set_Crveno ((int)abs((int)(a / P.GetCrveno())));
		P.Set_Plavo ((int)abs((int)(a / P.GetPlavo())));
		P.Set_Zeleno ((int)abs((int)(a / P.GetZeleno())));
	}
	static void power(Pixel &P, int a)
	{
		if (a < 20) 
		{
			P.Set_Crveno((int)pow(P.GetCrveno(), a));
			P.Set_Plavo((int)pow(P.GetPlavo(), a));
			P.Set_Zeleno((int)pow(P.GetZeleno(), a));
		}
	}
	static void logarithm(Pixel &P, int a)
	{
		P.Set_Crveno ((int)log(P.GetCrveno()));
		P.Set_Plavo ((int)log(P.GetPlavo()));
		P.Set_Zeleno ((int)log(P.GetZeleno()));
	}
	static void min(Pixel &P, int a)
	{
		if (P.GetCrveno() > a) P.Set_Crveno(a);
		if (P.GetPlavo() > a) P.Set_Plavo(a);
		if (P.GetZeleno() > a) P.Set_Zeleno(a);
	}
	static void max(Pixel &P, int a)
	{
		if (P.GetCrveno() < a) P.Set_Crveno(a);
		if (P.GetPlavo() < a) P.Set_Plavo(a);
		if (P.GetZeleno() < a) P.Set_Zeleno(a);
	}
	static void inverzija(Pixel &P, int d)
	{
		inverzno_oduzimanje(P, 255);
	}
	static void GrayScale(Pixel &P, int d)
	{
		int k = ((int)(P.GetCrveno() + P.GetPlavo() + P.GetZeleno()) / 3);
		{P.Set_Plavo(k); P.Set_Crveno(k);  P.Set_Zeleno(k); }
	}
	static void BW(Pixel &P, int d)
	{
		int k = ((int)(P.GetCrveno() + P.GetPlavo() + P.GetZeleno()) / 3);
		if (k > 127) { P.Set_Plavo(255); P.Set_Crveno(255);  P.Set_Zeleno(255); }
		else { P.Set_Plavo(0); P.Set_Crveno(0);  P.Set_Zeleno(0) ; }
	}
static	void ABS(Pixel &P,int r)
	{
		P.Set_Crveno(abs(P.GetCrveno()));
		P.Set_Plavo(abs(P.GetPlavo()));
		P.Set_Zeleno(abs(P.GetZeleno()));
	}
};
#endif;