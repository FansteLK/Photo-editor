#ifndef _CompositeOperation_H_
#define _CompositeOperation_H_
#include "BasicOperation.h"

#include <fstream>
#include <iostream>
#include <regex>
class Image;
class CompositeOperation
{
public:
	friend class Operations;
//kreiranje kompozitne funkcije
 static void  kompozitna()
  {
	  string ime;
	  cout << "Unesi ime kompozitne funkcije:"<<endl;
	  cin >> ime;
	  ofstream Txt;
	  //lokalna adresa
	  Txt.open("C:\\Users\\stefa\\Desktop\\Project_POOP\\Project_POOP\\functions\\"+ime+".txt");
	  int izbor=-1;
	  while (izbor != 15)
	  {
		  cout << "Unesi odredjenu operaciju koja zelis da se izvrsi: \n 1.Sabiranje(x) \n 2.Oduzimanje(x) \n 3.Inverzno oduzimanje(x) \n 4.Mnozenje(x) \n 5.Deljenje(x) \n 6.Inverzno deljenje(x) \n 7.Stepenovanje(x) \n 8.Prirodni logaritam \n 9.Min(x) \n 10.Max(x) \n 11.Invert \n 12.GrayScale \n 13.BlackWhite \n 14.Abs\n 15.Za zavrsavanje unosa operacije \n";
		  cin >> izbor;
		  switch(izbor)
		  {
		  case 1: {  Txt << "sabiranje"; }break;
		  case 2: { Txt << "oduzimanje"; }break;
		  case 3: { Txt << "inverzno oduzimanje"; }break;
		  case 4: { Txt << "mnozenje"; }break;
		  case 5: { Txt << "deljenje"; }break;
		  case 6: { Txt << "inverzno deljenje"; }break;
		  case 7: { Txt << "stepenovanje"; }break;
		  case 8: { Txt << "logaritam"; }break;
		  case 9: { Txt << "min"; }break;
		  case 10: { Txt << "max"; }break;
		  case 11: { Txt << "inverzija"; }break;
		  case 12: { Txt << "greyscale"; }break;
		  case 13: { Txt << "black&white"; }break;
		  case 14: { Txt << "abs"; }break;
		  
		  }
		  if ((izbor == 1) || (izbor == 2) || (izbor == 3) || (izbor == 4) || (izbor == 5) || (izbor == 6) || (izbor == 7) || (izbor == 10) || (izbor == 9))
		  {
			  int konst;
			  cout << endl<< "Unesi konstantu za operaciju :";
				  cin >> konst;
				  Txt << ";"<<konst << ";\n";;

	      }
		  else
		  {
			  if (izbor != 15)
			  {
				  Txt << ";" << 0 << ";\n";
			  }

		  }

	  }
	  Txt.close();

  }
 //koriscenje kompozitne funkcije
 static void zapisi(string ime, Image *im);
 



};
#endif