#ifndef _Formatter_H_
#define _Formatter_H_

#include <iostream>
#include <stdio.h>

#include "BMPF.h"
#include "PAMFormatter.h"
#include "MyFormatter.h"

class Formatter
{

public:
	static bool input(Layer  &l, const char * input_name, string format, int sirina, int visina)
	{
		bool ret = false;
		FILE * f = fopen(input_name, "r");
		if (f == NULL) {
			exit(1);

		}
		if (format == "bmp")
		{
			BMPFormatter bmp;
			ret = bmp.format_input(f, l, sirina, visina);
		}
		else if (format == "pamf")
		{
			/*PAMFFormatter PAMF;
			PAMF.format_input(f);*/
		}
		else if (format == "myformat")
		{
			/*MyFormatter My;
			My.format_input(f);*/
		}
		fclose(f);
		return ret;
	}
	static void output(string format, Layer l)
	{


		if (format == "bmp")
		{
			BMPFormatter bmp;
			bmp.format_output(l);
		}
		else if (format == "pamf")
		{
			//PAMFFormatter PAMF;
			//PAMF.format_output();
		}
		else if (format == "myformat")
		{
			//MyFormatter My;
			//My.format_output();
		}


	}


};



#endif


