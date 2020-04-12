#ifndef _Operations_H_
#define _Operations_H_
#include "BasicOperation.h"
#include "Pixel.h"
class Image;
class Operations
{
public:

	static void PostaviAlfa(Pixel &p, int a) 
	{
		p.Set_Alpha(a);
	}
	static void SaberiAlfa(Pixel &p, int a)
	{
		p.Set_Alpha(p.GetAlfa() + a);
	}
	static void OduzmiAlfa(Pixel &p, int a)
	{
		if (p.GetAlfa() - a < 0)
		{
			p.Set_Alpha(1);
		}
		else
		{
			p.Set_Alpha(p.GetAlfa() - a);
		}

	}
	static void Saberi(Pixel &p, int a)
	{
		
		BasicOperation::sabiranje(p, a);
		p.Set_Crveno(p.GetCrveno());
		p.Set_Plavo(p.GetPlavo() );
		p.Set_Zeleno(p.GetZeleno());

	}
	static void Oduzmi(Pixel &p, int a)
	{
	
		 BasicOperation::oduzimanje(p, a);
		p.Set_Crveno((p.GetCrveno()));
		p.Set_Plavo((p.GetPlavo()));
		p.Set_Zeleno((p.GetZeleno()));
	}
	static void Inverzno_Oduzmi(Pixel &p, int a)
	{
		
		BasicOperation::inverzno_oduzimanje(p, a);
		p.Set_Crveno((p.GetCrveno()));
		p.Set_Plavo((p.GetPlavo()));
		p.Set_Zeleno((p.GetZeleno()));
	}
	static void Pomnozi(Pixel &p, int a)
	{
	
		BasicOperation::mnozenje(p, a);
		p.Set_Crveno(p.GetCrveno() );
		p.Set_Plavo(p.GetPlavo() );
		p.Set_Zeleno(p.GetZeleno());
	}
	static void Podeli(Pixel &p, int a)
	{
		
		BasicOperation ::deljenje(p, a);
	}
	static void Inverzno_Podeli(Pixel &p, int a)
	{
	
		BasicOperation ::inverzno_deljenje(p, a);
	}
	static void Stepenuj(Pixel &p, int a)
	{
	
		BasicOperation ::power(p, a);
		p.Set_Crveno(p.GetCrveno());
		p.Set_Plavo(p.GetPlavo() );
		p.Set_Zeleno(p.GetZeleno() );
	}
	static void Prirodni_Log(Pixel &p, int a)
	{
		
		BasicOperation ::logarithm(p, a);
	}
	static void MIN(Pixel &p, int a)
	{
		
		BasicOperation ::min(p, a);
	}
	static void MAX(Pixel &p, int a)
	{
		
		BasicOperation ::max(p, a);
	}
	static void Invert(Pixel &p, int a)
	{
	
		BasicOperation ::inverzija(p, a);
	}
	static void Nijanse_Sive(Pixel &p, int a)
	{
		
		BasicOperation ::GrayScale(p, a);
	}
	static void Crno_Belo(Pixel &p, int a)
	{
		
		BasicOperation ::BW(p, a);
	}
	static void Selektuj(Pixel &p, int a)
	{
		p.Set_Selektovano_True();
	}
	static void De_Selektuj(Pixel &p, int a)
	{
		p.Set_Selektovano_False();
	}
	static void Apsolutno(Pixel &p,int a)
	{
		
		BasicOperation ::ABS(p, a);
	}
	static void Unormali(Pixel &p, int a)
	{
		p.Set_Crveno(abs(p.GetCrveno()) % 256);
		p.Set_Zeleno(abs(p.GetZeleno()) % 256);
		p.Set_Plavo(abs(p.GetPlavo()) % 256);

	}
	static void  UcitajKompozitnu();
	static void FormirajKompozitnu(string ime, Image *im);
	static void Medijana(Image *im);
};

#endif
