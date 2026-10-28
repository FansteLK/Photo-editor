// Command-line image processing engine used by the Java GUI.
//
//   photo-engine <layers.txt> <operations.txt> <selections.txt> [output]
//
// layers.txt      one layer per line: <path.bmp> <opacity 0-100>
// operations.txt  one operation per line: <name>;<constant>;   (or a file containing the path of such a file)
// selections.txt  zero or more rectangles: <x> <y> <width> <height>; operations apply only inside them
// output          output path without extension (default: output); written as <output>.bmp

#include "Image2.h"
#include "Selection.h"
Image *Image::instance = 0;
#include "Formatter.h"

#include <iostream>
#include <fstream>
#include <cstring>
#include "CompositeOperation.h"
using namespace std;

static bool read_bmp_size(const string &path, int &width, int &height)
{
	FILE *f = fopen(path.c_str(), "rb");
	if (f == NULL) return false;
	unsigned char info[54];
	// Only 32-bit BGRA bitmaps are supported by the BMP reader.
	bool ok = fread(info, sizeof(unsigned char), 54, f) == 54 && info[0] == 'B' && info[1] == 'M' && info[28] == 32;
	fclose(f);
	if (!ok) return false;
	width = *(int*)&info[18];
	height = *(int*)&info[22];
	return true;
}

int main(int argc, char **argv)
{
	if (argc < 4)
	{
		cerr << "usage: " << argv[0] << " <layers.txt> <operations.txt> <selections.txt> [output]" << endl;
		return 2;
	}
	string output = argc > 4 ? argv[4] : "output";

	Image *im = NULL;
	string slika;
	string trans;
	ifstream infile(argv[1]);
	while (infile >> slika >> trans)
	{
		if (im == NULL)
		{
			// The first layer defines the canvas size.
			int width, height;
			if (!read_bmp_size(slika, width, height))
			{
				cerr << "Cannot read " << slika << " (expected a 32-bit BMP)" << endl;
				return 1;
			}
			im = im->GetInstance(width, height);
		}
		im->AddLayer(slika.c_str(), "bmp", atoi(trans.c_str()));
	}
	if (im == NULL)
	{
		cerr << "No layers listed in " << argv[1] << endl;
		return 1;
	}

	bool ima = false;
	ifstream infile3(argv[3]);
	string x, y, sirina, visina;
	while (infile3 >> x >> y >> sirina >> visina)
	{
		if (!ima) im->AddSelection();
		ima = true;
		Position P(atoi(x.c_str()), atoi(y.c_str()));
		Rectangle R(P, atoi(sirina.c_str()), atoi(visina.c_str()));
		im->Get_Selection()->GetRectangles().push_back(R);
	}

	// The GUI passes a file holding the path of the operations file; the CLI may pass it directly.
	string kompozitna = argv[2];
	ifstream infile2(argv[2]);
	string first;
	if (getline(infile2, first) && first.find(';') == string::npos && !first.empty())
		kompozitna = first;
	CompositeOperation::zapisi(kompozitna, im);
	im->Visit(Operations::Unormali, 1);

	Formatter::output(output, "bmp", im->Get_Image());
	return 0;
}
