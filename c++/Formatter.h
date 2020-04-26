
#ifndef _Formatter_H_
#define _Formatter_H_

#include <iostream>
#include <stdio.h>
#include "BMPF.h"
#include "PAMFormatter.h"
//#include "MyFormatterr.h"
class Formatter
{

public:
	static bool input(Layer  &l, const char * input_name, string format, int sirina, int visina,int transparentost, int pozicijax, int pozicijay, Image *im = NULL);
	
	static void output(string ime, string format, Layer l, Image *im = NULL);


};

#endif


