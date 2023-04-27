#include "CompositeOperation.h"
#include"Image2.h"
 void CompositeOperation::zapisi(string ime, Image *im)
{
	 
	int konst = 0;
	//lokalna adresa
	ifstream file( ime );
	string text;
	// sabiranje 10;
	regex rx("([^;]*);([^;]*);");
	while (getline(file, text))
	{
		smatch result;
		//	cout << text << endl;
		if (regex_match(text, result, rx))
		{

			string ime = result.str(1);
			int konst = atoi(result.str(2).c_str());
			cout << endl << ime << konst;


			if (ime == "sabiranje") { cout << "uso"; im->Visit(Operations::Saberi, konst); }
			if (ime == "oduzimanje") { im->Visit(Operations::Oduzmi, konst); }
			if (ime == "inverzno oduzimanje") { im->Visit(Operations::Inverzno_Oduzmi, konst); }
			if (ime == "mnozenje") { im->Visit(Operations::Pomnozi, konst); }
			if (ime == "deljenje") { im->Visit(Operations::Podeli, konst); }
			if (ime == "inverzno deljenje") { im->Visit(Operations::Inverzno_Podeli, konst); }
			if (ime == "stepenovanje") { im->Visit(Operations::Stepenuj, konst); }
			if (ime == "logaritam") { im->Visit(Operations::Prirodni_Log, konst); }
			if (ime == "min") { im->Visit(Operations::MIN, konst); };
			if (ime == "max") { im->Visit(Operations::MAX, konst); }
			if (ime == "inverzija") { im->Visit(Operations::Invert, konst); }
			if (ime == "greyscale") { im->Visit(Operations::Nijanse_Sive, konst); }
			if (ime == "black&white") { im->Visit(Operations::Crno_Belo, konst); }
			if (ime == "abs") { im->Visit(Operations::Apsolutno, konst); }
			if (ime == "medijana") { Operations::Medijana(im); }
		}

	}

	file.close();
}