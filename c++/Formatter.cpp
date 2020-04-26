

#include "Formatter.h"
#include "MyFormatterr.h"


void Formatter::output(string ime, string format, Layer l, Image * im)
{

	if (format == "bmp")
	{

		BMPFormatter::format_output(ime+".bmp", l);
	}
	else if (format == "pam")
	{
		PAMFFormatter::format_output(ime+".pam", l);
	}
	else if (format == "myf")
	{
		
		MyFormatter::format_output(ime+".myf", im);
	}
}

bool Formatter::input(Layer & l, const char * input_name, string format, int sirina, int visina,int transparentnost, int pozicijax, int pozicijay, Image * im)
{
	bool ret = false;
	
	if (format == "bmp")
	{
		FILE * f = fopen(input_name, "rb");
		if (f == NULL) 
		{
			cout << "Ne moze se otvoriti fajl " << input_name<< endl;
			

		}

		ret = BMPFormatter::format_input(f, l, sirina, visina,transparentnost, pozicijax, pozicijay);
		fclose(f);
	}
	else if (format == "pam")
	{


		ret = PAMFFormatter::format_input(input_name, l, sirina, visina);
	}
	else if (format == "myf")
	{
	
		ret = MyFormatter::format_input(input_name, im);
	}
	else 
	{
		cout << endl << "Nepodrzan format" << endl;
	}
	return ret;
}
