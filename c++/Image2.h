#ifndef _Image2_H_
#define _Image2_H_

#include <iostream>
#include <string.h>
#include "Selection.h"

#include <vector>
#include <algorithm>
# include <math.h>
# include <regex>
#include <fstream>
#include "Operations.h"

//#include "BasicOperation.h"

#include <map>

using namespace std;
class Image
{


private:
	friend class MyFormatter;
	bool jeste = false;
	static Image *instance;
	vector<Layer> slika;

	Selection *selekcija;
	//velicina slike
	int num_ver_pix;
	int num_hor_pix;
	int num_layers=0;
	int num_selections;
	string trenutna_selekcija;
	Image(int sirina, int visina)
	{
		num_ver_pix = visina;
		num_hor_pix = sirina;
		num_layers = 0;
		num_selections = 0;
		trenutna_selekcija = "";
	}
	void Set_Num_Ver_Pix(int a)
	{
		num_ver_pix = a;
	}
	void Set_Num_Hor_Pix(int a)
	{
		num_hor_pix = a;
	}
	
public:
	//pristupanje selekciji preko njenog imena

	//Pravi jednu instancu klaese Image
	static Image *GetInstance(int a, int b) {

		if (!instance)
			instance = new Image(a, b);
		return instance;
	}
	Image(const Image&) = delete;

	//Geteri
	int Get_num_ver_pix() const { return num_ver_pix; };
	int Get_num_hor_pix() const { return num_hor_pix; };
	int  Get_num_layers()const { return num_layers; };
	string Get_not_ini()
	{
		return trenutna_selekcija;
	}
	Layer& Get_last_layer() { return slika[num_layers - 1]; }
	//Formira sliku od svih layera
	Selection * Get_Selection() { return selekcija; }
	Layer& Get_Image()
	{
		int tren = num_layers - 1;
	
		if (tren >= 0)
		{

			Layer l = slika[tren];
			l.Set_Num_Hor(slika[tren].Get_Num_Hor_Pix());
			l.Set_Num_Ver(slika[tren].Get_Num_Ver_Pix());
			for (int i = tren - 1; i >= 0; i--)
			{

				
					for (int v = 0; v < l.Get_Num_Ver_Pix(); v++)
					{

						for (int h = 0; h < l.Get_Num_Hor_Pix(); h++)
						{
							if (l.Get_Pixels()[v][h].GetAlfa() != 255)
							{
								//cout << slika[i].Get_Pixels()[v][h].GetAlfa();

								int a = l.Get_Pixels()[v][h].GetAlfa();
								
								int a_staro = a;
								int a2 = slika[i].Get_Pixels()[v][h].GetAlfa();
								a = a_staro + a2 * ((255 - a_staro) / (double)255);

								l.Get_Pixels()[v][h].Set_Alpha(a);

								int r = l.Get_Pixels()[v][h].GetCrveno();
								int r2 = slika[i].Get_Pixels()[v][h].GetCrveno();
								r = (int)r*(a_staro / (double)a) + r2 * (int)slika[i].Get_Pixels()[v][h].GetAlfa()*((255 - a_staro) / (double)255) / a;
								l.Get_Pixels()[v][h].Set_Crveno(r);

								int g = l.Get_Pixels()[v][h].GetZeleno();
								int g2 = slika[i].Get_Pixels()[v][h].GetZeleno();
								g = g * (a_staro / (double)a) + g2 * ((int)slika[i].Get_Pixels()[v][h].GetAlfa()*((255 - a_staro) / (double)255) / a);

								l.Get_Pixels()[v][h].Set_Zeleno(g);

								int b = l.Get_Pixels()[v][h].GetPlavo();
								int b2 = slika[i].Get_Pixels()[v][h].GetPlavo();
								b = b * (a_staro / (double)a) + b2 * (int)slika[i].Get_Pixels()[v][h].GetAlfa()*((255 - a_staro) / (double)255) / a;
								l.Get_Pixels()[v][h].Set_Plavo(b);

							}


						}
					}
				}


			
			
			num_layers++;
			slika.push_back(l);
			return this->Get_last_layer();
		}

		else {
			
			return this->Get_last_layer();
		}
	}
	Layer& Get_Layer(int a)
	{

		if (a < num_layers) return slika[a];
	}
	vector <Layer> & Get_Layers() { return slika; }
	

	//Seteri
	void Set_Layer_Active(int num)
	{
		slika[num].Set_Active_True();

	}
	void Set_Layer_False(int num)
	{
		slika[num].Set_Active_False();
	}


	void Set_Num_Layers(int a)
	{
		num_layers = a;
	}

	//Adderi

	//dodavanje layera slike
	void AddLayer(const char* input_name, string form,int transparentnost, int pozicijax = 0, int pozicijay = 0)
	{


		slika.push_back(Layer(input_name, form, this->Get_num_hor_pix(), this->Get_num_ver_pix(), transparentnost,pozicijax, pozicijay));
		num_layers++;

		if (this->Get_last_layer().change == 1)
		{

			for_each(slika.begin(), slika.end() - 1, [this](Layer &l)
			{

				Layer L2(num_hor_pix, num_ver_pix, true);
				for (int i = 0; i < this->Get_last_layer().Get_Num_Ver_Pix(); i++)
				{



					vector <Pixel> vektor;
				
					for (int j = 0; j < this->Get_last_layer().Get_Num_Hor_Pix(); j++)
					{
						if ((i < l.Get_Num_Ver_Pix()) && (j < l.Get_Num_Hor_Pix()))
						{
							vektor.push_back(l.Get_Pixels()[i][j]);
						}

						else
						{
							Pixel P(0, 0, 0);
							P.Set_Alpha(0);
							vektor.push_back(P);
						}


					}

					L2.lyr.push_back(vektor);
				}
				L2.Set_Num_Hor(this->Get_last_layer().Get_Num_Hor_Pix());
				L2.Set_Num_Ver(this->Get_last_layer().Get_Num_Ver_Pix());
				l = L2;

			}

			);
		}
		num_hor_pix = this->Get_last_layer().Get_Num_Hor_Pix();
		num_ver_pix = this->Get_last_layer().Get_Num_Ver_Pix();
		//...

		this->Get_last_layer().reset_change();
		//}

	}
	//dodavanje praznog layera
	void AddLayer(bool active,int num_v,int num_h,int transparentnost=0)
	{
		if (num_layers >= 0) {
			Layer L(num_v, num_h, active);
			
			for (int i = 0; i < L.Get_Num_Ver_Pix(); i++)
			{

				vector <Pixel> vektor;
				for (int j = 0; j <L.Get_Num_Hor_Pix(); j++)
				{
	
					Pixel temp(255, 255, 255);
					temp.Set_Alpha(transparentnost);
					vektor.push_back(temp);
				}

				L.Get_Pixels().push_back(vektor);
			}
			slika.push_back(L);
			num_layers++;
		}
	}
	//dodavanje selekcije
	void AddSelection()
	{


		 selekcija = new Selection();
		selekcija->ime = "Selekcija";
		jeste = true;

	}
	//kretanje kroz layere i selekcije slike
	void Visit(void(*predicate)(Pixel &p, int a), int c)
	{

	
		if (!jeste)
		{

			for_each(this->Get_Layers().begin(), this->Get_Layers().end(), [predicate, c](Layer &l)
			{

				l.Visit(predicate, c, false);
			}

			);
			return;
		}
		
		
		
		

			for_each(this->Get_Layers().begin(), this->Get_Layers().end(), [this, c](Layer &l)
			{

				selekcija->Visit(Operations::Selektuj, l, c);


			}
			);


			for_each(this->Get_Layers().begin(), this->Get_Layers().end(), [predicate, c](Layer &l)
			{

				l.Visit(predicate, c, true);
			}

			);

			for_each(this->Get_Layers().begin(), this->Get_Layers().end(), [this, c](Layer &l)
			{

				selekcija->Visit(Operations::De_Selektuj, l, c);


			}
			);
			
			return;
		}
	

	
 void setFalse() 
	{
		jeste=false;
	}

	
//izvrsavanje operacije nad slikom
	void operisi()
	{

		int oper;
		int konst = 0;
		cout << "Unesi odredjenu operaciju koja zelis da se izvrsi: \n 1.Sabiranje(x) \n 2.Oduzimanje(x) \n 3.Inverzno oduzimanje(x) \n 4.Mnozenje(x) \n 5.Deljenje(x) \n 6.Inverzno deljenje(x) \n 7.Stepenovanje(x) \n 8.Prirodni logaritam \n 9.Min(x) \n 10.Max(x) \n 11.Invert \n 12.GrayScale \n 13.BlackWhite \n 14.Medijana\n 15.Kompozitna operacija (adresa) \n";
		cin >> oper;
		switch (oper)
		{
		case 1: {
			cout << "Unesi konstantu: ";
			cin >> konst;

			Visit(Operations::Saberi, konst);
		}break;
		case 2: {
			cout << "Unesi konstantu: ";
			cin >> konst;
			Visit(Operations::Oduzmi, konst);
		}break;
		case 3:
		{
			cout << "Unesi konstantu: ";
			cin >> konst;
			Visit(Operations::Inverzno_Oduzmi, konst);

		}break;
		case 4:
		{
			cout << "Unesi konstantu: ";
			cin >> konst;
			Visit(Operations::Pomnozi, konst);
		}break;
		case 5:
		{
			cout << "Unesi konstantu: ";
			cin >> konst;
			Visit(Operations::Podeli, konst);

		}break;
		case 6:
		{
			cout << "Unesi konstantu: ";
			cin >> konst;
			Visit(Operations::Inverzno_Podeli, konst);
		}break;
		case 7:
		{
			cout << "Unesi konstantu: ";
			cin >> konst;
			Visit(Operations::Stepenuj, konst);

		}break;
		case 8:
		{
			Visit(Operations::Prirodni_Log, konst);
		}break;
		case 9:
		{
			cout << "Unesi konstantu: ";
			cin >> konst;
			Visit(Operations::MIN, konst);
		}break;
		case 10:
		{
			cout << "Unesi konstantu: ";
			cin >> konst;
			Visit(Operations::MAX, konst);
		}break;
		case 11:
		{
			Visit(Operations::Invert, konst);
		}break;
		case 12:
		{
			Visit(Operations::Nijanse_Sive, konst);
		}break;
		case 13:
		{
			Visit(Operations::Crno_Belo, konst);
		}break;


		case 14:
		{
			Operations::Medijana(this);
		}break;

		case 15:
		{
			int izbor2 = 0;
			cout << endl << endl << "Unesi 1 za unos nove funkcije a 2 za koriscenje  stare:";
			while ((izbor2 != 1) && (izbor2 != 2))
			{
				cin >> izbor2;
			}
			if (izbor2 == 1)
			{
				Operations::UcitajKompozitnu();
			}
			else
			{
				string ime;
				cout << endl << "Unesi ime funkcije:";
				cin >> ime;
				Operations::FormirajKompozitnu(ime, this);
			}

		}
		break;
		}
		Visit(Operations::Unormali, 1);
	}

	void pop()
	{
		slika.pop_back();
	}

	void Rotiraj_Ulevo() 
	{
for_each(slika.begin(), slika.end() - 1, [this](Layer &l)
			{

	int temp=num_hor_pix;
	num_hor_pix = num_ver_pix;
	num_ver_pix = temp;
				Layer L2(num_hor_pix, num_ver_pix, true);
				for (int i = 0; i < this->Get_last_layer().Get_Num_Ver_Pix(); i++)
				{



					vector <Pixel> vektor;
					for (int j = 0; j < this->Get_last_layer().Get_Num_Hor_Pix(); j++)
					{
						if ((i < l.Get_Num_Ver_Pix()) && (j < l.Get_Num_Hor_Pix()))
						{
							vektor.push_back(l.Get_Pixels()[i][j]);
						}

						else
						{
							Pixel P(0, 0, 0);
							P.Set_Alpha(0);
							vektor.push_back(P);
						}


					}

					L2.lyr.push_back(vektor);
				}
				L2.Set_Num_Hor(this->Get_last_layer().Get_Num_Hor_Pix());
				L2.Set_Num_Ver(this->Get_last_layer().Get_Num_Ver_Pix());
				l = L2;

			}

			);
	}
	//Preklopljeni operatori

	//ispis nekih stavki slike

	//smanjuje vidljivost layera
	Image* operator --(int a)
	{
		
		this->Get_Layer(a).Visit(Operations::OduzmiAlfa, 10, false);
		return this;
	}
	//povecava vidljivost layera
	Image* operator ++(int a)
	{
		this->Get_Layer(a).Visit(Operations::SaberiAlfa, 10, false);
		return this;
	}
	void  setLayerOpacity(int a,int b) 
	{
		this->Get_Layer(a).Visit(Operations::PostaviAlfa, b, false);
	
	}

};

#endif
