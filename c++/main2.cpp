/*
#include "Image2.h"
Image *Image::instance = 0;
vector<Rectangle>;
#include "Formatter.h"


int main()
{
	//Inicijalizatori

	string form;
	string ini = "ini";
	string file;
	int izbor = 0;
	int height;
	int width;
	int pom;
	char c;
	string izlaz;
	//Kreiranje pocetnog objekta
	cout << "Unesite d za ucitavanje prazne slike a n za inicijalizovanje slikom:   ";
	cin >> c;
	while ((c != 'd') && (c != 'n'))
	{
		cout << endl << "d ili n" << endl;
		cin >> c;
	}
	if (c == 'd')
	{
		cout << endl << "Unesite dimenizije slike u formatu visina sirina:   ";
		while (!((cin >> width) && (cin >> height))) {
			cout << "Unesite integere" << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}

	}
	if (c == 'n')
	{

		cout << endl << "Unesi format date slike:  ";
		getchar();
		cin >> form;

		while ((form != "bmp") && (form != "pam"))
		{
			cout << endl << "bmp ili pam" << endl;
			cin >> form;
		}
		if (form == "bmp") {
			FILE *f = NULL;
			while (f == NULL)
			{
				cout << "Unesi ime ulazne datoteke : ";
				cin >> ini;
				ini += ".bmp";
				f = fopen(ini.c_str(), "r");
				if (f == NULL)  cout << "Ne moze se otvoriti fajl " << ini << endl;
			}
			unsigned char info[54];
			fread(info, sizeof(unsigned char), 54, f);
			width = *(int*)&info[18];
			height = *(int*)&info[22];
			fclose(f);
		}
		if (form == "pam")
		{


			cout << "Unesi ime ulazne datoteke : ";
			cin >> ini;
			ini += ".pam";
			ifstream File(ini, ios::binary);
			while (File.fail())
			{
				cout << "Ne moze se otvoriti fajl " << ini << endl;
				cout << "Unesi ime ulazne datoteke : ";
				cin >> ini;
				ini += ".pam";
				ifstream File(ini, ios::binary);



			}
			string num, w_str, h_str, tmp;
			File >> num;
			File >> tmp >> w_str >> tmp >> h_str;

			width = atoi(w_str.c_str()); //Takes the number string and converts it to an integer
			height = atoi(h_str.c_str());


			File.close();


		}

	}

	Image *im = im->GetInstance(width, height);
	//
	if (ini != "ini")
	{
		if (form == "bmp") {
			im->AddLayer(ini.c_str(), "bmp",255);
		}
		if (form == "pam")
		{
			im->AddLayer(ini.c_str(), "pam",255);
		}
	}
	else
	{
		im->AddLayer(true, height, width);
	}
	//Meni(Korisnicki interfejs)
	while (izbor != 15)
	{
		cout << endl << " 1.Dodaj layer \n 2.Dodaj selekciju\n 3.Obrisi selekciju(string) \n 4.Oboj selekciju \n 5.Aktiviraj layer(int)\n 6.Deaktviraj layer(int)\n 7.Ispisi selekcije \n 8.Izvrsi operaciju  \n 9.Sacuvaj sliku \n 10.Unesi prazan layer \n 11.Povecaj tranparentonst layera(int) \n 12.Smanji transparentnost layera \n 13.Promena selekcije \n 14.Otvori sliku iz myformata i sacuvaj trenutnu\n 15. Exit \n 16.Postavi transparentnost layera \n";
		cin >> izbor;
		switch (izbor)
		{
		case 1:
		{
			cout << endl << "Unesi ime ulazne datoteke: ";
			cin >> file;
			regex rx("([^.]*).(...)");

			smatch result;

			if (regex_match(file, result, rx))
			{

				string ime = result.str(1);
				string format = result.str(2);
				if ((format == "bmp") || (format == "pam"))
				{
					cout << endl << "sacekajte..." << endl;
					im->AddLayer(file.c_str(), format,255);
				}
				else cout << "Nepodrzan format slike";

			}
			else cout << endl << "morate uneti sliku u formatu ime.ekstenzija" << endl;

		}
		break;
		case 2:
		{
			im->AddSelection();
		}
		break;
		case 3:
		{
			cout << endl << "Unesi ime selekcije koju zelis obrisati: ";
			cin >> file;
			im->Brisi_Selekciju(file.c_str());
		}
		break;
		case 4:
		{
			int r;
			int g;
			int b;
			cout << endl << "Unesi boju u obliku r:0-255 g:0-255 b:0-255 : ";
			while (!((cin >> r) && (cin >> g) && (cin >> b))) {
				cout << "Unesite integere" << endl;
				cin.clear();
				cin.ignore(INT_MAX, '\n');
			}

			while (!((r >= 0) && (r <= 255) && (g >= 0) && (g <= 255)&(b >= 0) && (b <= 255)))
			{
				cout << endl << "Unesi boju u obliku r:0-255 g:0-255 b:0-255 : ";
				while (!((cin >> r) && (cin >> g) && (cin >> b))) {
					cout << "Unesite integere" << endl;
					cin.clear();
					cin.ignore(INT_MAX, '\n');
				}
			}
			Pixel P(r, g, b);

			if (im->Get_not_ini() != "")
			{

				if (im->Get_Last_Selection()->Get_Aktiv())
				{
					im->Set_Selection_Color(P);
				}
			}

		}
		break;
		case 5:
		{
			cout << endl << "Unesi layer koji zelis aktivirati ";
			while (!((cin >> pom))) {
				cout << "Unesite integer" << endl;
				cin.clear();
				cin.ignore(INT_MAX, '\n');
			}
			if (pom < im->Get_num_layers())
			{
				im->Set_Layer_Active(pom);
			}
		}
		break;
		case 6:
		{
			cout << endl << "Unesi layer koji zelis deaktivirati ";
			while (!((cin >> pom))) {
				cout << "Unesite integer" << endl;
				cin.clear();
				cin.ignore(INT_MAX, '\n');
			}
			if (pom < im->Get_num_layers())
			{
				im->Set_Layer_False(pom);
			}
		}
		break;
		case 7:
		{
			cout << *im;
		}
		break;
		case 8:
		{
			im->operisi();
		}
		break;
		case 9:
		{

			cout << "Unesi ime izlazne datoteke: ";
			cin >> file;
			cout << endl << "Unesi format izlaza: ";
			string form;
			while ((form != "pam") && (form != "bmp"))
			{
				cin >> form;
			}

			Formatter::output(file, form, im->Get_Image());

			if (im->Get_num_layers() > 1) {
				im->Set_Num_Layers(im->Get_num_layers() - 1);
			}
			im->pop();

		}
		break;
		case 10:
		{
			cout << endl << "Unesi transparentnost: ";
			while (!((cin >> pom))) {
				cout << "Unesite integer" << endl;
				cin.clear();
				cin.ignore(INT_MAX, '\n');
			}
			while ((pom < 0) || (pom > 255))
			{
				while (!((cin >> pom))) {
					cout << "Unesite integer" << endl;
					cin.clear();
					cin.ignore(INT_MAX, '\n');
				}

			}
			im->AddLayer(true, im->Get_num_ver_pix(), im->Get_num_hor_pix(), pom);
		}break;
		case 11:
		{

			cout << endl << "Unesi zeljeni layer: ";
			while (!((cin >> pom))) {
				cout << "Unesite integer" << endl;
				cin.clear();
				cin.ignore(INT_MAX, '\n');
			}
			if ((pom < im->Get_num_layers()) && (pom >= 0))
			{
				im->operator++(pom);
			}

		}
		break;
		case 12:
		{
			cout << im->Get_num_layers() << "\n";
			cout << endl << "Unesi zeljeni layer: ";
			while (!((cin >> pom))) {
				cout << "Unesite integer" << endl;
				cin.clear();
				cin.ignore(INT_MAX, '\n');
			}
			if ((pom < im->Get_num_layers()) && (pom >= 0))
			{
				im->operator--(pom);
			}
			else cout << "Ne postoji trazeni layer";

		}
		break;
		case 13:
		{
			string selekcija;
			cout << endl << "Unesi ime selekcije koju zelis da aktiviras: ";
			cin >> selekcija;
			im->Set_Selection_Active(selekcija);


		}
		break;
		case 14:
		{
			string ime;
			cout << endl << "Unesi ime ulaznog myf format fajla: ";
			cin >> ime;
			ime += ".myf";
			Formatter::input(im->Get_last_layer(), ime.c_str(), "myf", 1, 1,255, 1, 1, im);
		}
		break;

		case 15:
		{
			Formatter::output(ini, "myf", im->Get_last_layer(), im);
			system("pause");
			exit(1);

		}
		break;

		case 16:
		{
			cout << endl << "Unesi zeljeni layer: ";
			while (!((cin >> pom))) {
				cout << "Unesite integer" << endl;
				cin.clear();
				cin.ignore(INT_MAX, '\n');
			}
			int pom2;
			cout << endl << "Unesi zeljenu transparentnost: ";
			while (!((cin >> pom2))) {
				cout << "Unesite integer" << endl;
				cin.clear();
				cin.ignore(INT_MAX, '\n');
			}
			im->setLayerOpacity(pom, pom2);

		}
		}

	}


}
*/