#ifndef _BMP_H_
#define _BMP_H_

#include <iostream>
#include "Layer.h"s
#include <stdio.h>

class BMP
{
public:
	bool  format_input(FILE *f, Layer &l, int sirina, int visina)
	{
		bool ret = false;
		unsigned char info[54];
		fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header

		// extract image height and width from header
		int width = *(int*)&info[18];
		int height = *(int*)&info[22];

		cout << endl;
		//cout << "  Name: " << filename << endl;
		cout << " Width: " << width << endl;
		cout << "Height: " << height << endl;

		int row_padded = (width * 3 + 3) & (~3);
		unsigned char* data = new unsigned char[row_padded];
		unsigned char tmp;

		bool veca = ((sirina <= width) && (visina <= height));
		bool manja = ((sirina > width) && (visina > height));

		if (veca)
		{
			ret = true;
			l.Set_Num_Hor(width);
			l.Set_Num_Ver(height);
			//povecaj_layere(int,int)
			for (int i = 0; i < height; i++)
			{

				fread(data, sizeof(unsigned char), row_padded, f);

				vector <Pixel> vektor;
				for (int j = 0; j < width * 3; j += 3)
				{


					if (j >= width * 3)
					{
						Pixel temp(0, 0, 0);
						vektor.push_back(temp);
						//cout << "neko nesto";

					}

					else
					{
						// Convert (B, G, R) to (R, G, B)
						tmp = data[j];
						data[j] = data[j + 2];
						data[j + 2] = tmp;
						Pixel temp(data[j], data[j + 1], data[j + 2]);
						vektor.push_back(temp);
						//	cout << "R: " << (int)data[j] << " G: " << (int)data[j + 1] << " B: " << (int)data[j + 2] << endl;
					}
				}

				l.lyr.push_back(vektor);
			}
		}
		if (manja)
		{

			for (int i = 0; i < visina; i++)
			{
				if (i < height)
				{
					fread(data, sizeof(unsigned char), row_padded, f);
				}
				vector <Pixel> vektor;
				for (int j = 0; j < sirina * 3; j += 3)
				{
					if (i >= height)
					{
						Pixel temp(0, 0, 0);
						vektor.push_back(temp);
					}
					else
					{
						if (j >= width * 3)
						{
							Pixel temp(0, 0, 0);
							vektor.push_back(temp);
							//cout << "neko nesto";

						}

						else
						{
							// Convert (B, G, R) to (R, G, B)
							tmp = data[j];
							data[j] = data[j + 2];
							data[j + 2] = tmp;
							Pixel temp(data[j], data[j + 1], data[j + 2]);
							vektor.push_back(temp);
							//	cout << "R: " << (int)data[j] << " G: " << (int)data[j + 1] << " B: " << (int)data[j + 2] << endl;
						}
					}
				}
				l.lyr.push_back(vektor);
			}
		}
		return ret;
	}
	bool  format_input2(FILE *f, Layer &l, int sirina, int visina)
	{
		bool ret = false;
		unsigned char info[54];
		fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header

		// extract image height and width from header
		int width = *(int*)&info[18];
		int height = *(int*)&info[22];

		cout << endl;
		//cout << "  Name: " << filename << endl;
		cout << " Width: " << width << endl;
		cout << "Height: " << height << endl;

		int row_padded = (width * 4);
		unsigned char* data = new unsigned char[row_padded];
		unsigned char tmp;

		bool veca = ((sirina <= width) && (visina <= height));
		bool manja = ((sirina > width) && (visina > height));

		if (veca)
		{
			ret = true;
			l.Set_Num_Hor(width);
			l.Set_Num_Ver(height);

			for (int i = 0; i < height; i++)
			{

				fread(data, sizeof(unsigned char), row_padded, f);

				vector <Pixel> vektor;
				for (int j = 0; j < width * 4; j += 4)
				{


					if (j >= width * 4)
					{
						Pixel temp(0, 0, 0);
						temp.Set_Alpha(0);
						vektor.push_back(temp);
						//cout << "neko nesto";

					}

					else
					{
						// Convert (B, G, R) to (R, G, B)
						tmp = data[j];
						data[j] = data[j + 2];
						data[j + 2] = tmp;

						Pixel temp(data[j], data[j + 1], data[j + 2]);
						temp.Set_Alpha(data[j + 3]);
						vektor.push_back(temp);
						//	cout << "R: " << (int)data[j] << " G: " << (int)data[j + 1] << " B: " << (int)data[j + 2] << endl;
					}
				}

				l.lyr.push_back(vektor);
			}
		}
		if (manja)
		{

			for (int i = 0; i < visina; i++)
			{
				if (i < height)
				{
					fread(data, sizeof(unsigned char), row_padded, f);
				}
				vector <Pixel> vektor;
				for (int j = 0; j < sirina * 4; j += 3)
				{
					if (i >= height)
					{
						Pixel temp(0, 0, 0);
						vektor.push_back(temp);
					}
					else
					{
						if (j >= width * 4)
						{
							Pixel temp(0, 0, 0);
							vektor.push_back(temp);
							//cout << "neko nesto";

						}

						else
						{
							// Convert (B, G, R) to (R, G, B)
							tmp = data[j];
							data[j] = data[j + 2];
							data[j + 2] = tmp;
							Pixel temp(data[j], data[j + 1], data[j + 2]);
							temp.Set_Alpha(data[j + 3]);
							vektor.push_back(temp);
							//	cout << "R: " << (int)data[j] << " G: " << (int)data[j + 1] << " B: " << (int)data[j + 2] << endl;
						}
					}
				}
				l.lyr.push_back(vektor);
			}
		}
		return ret;
	}
	void format_output(Layer l)
	{
		FILE *f2;
		string ime;
		int w = l.Get_Num_Hor_Pix();
		int h = l.Get_Num_Ver_Pix();
		/*cout <<"w-----"<< w;
		cout <<"h-----"<< h;*/
		unsigned char *img = NULL;
		int filesize = 54 + 3 * w*h;  //w is your image width, h is image height, both int

		img = (unsigned char *)malloc(3 * w*h);
		memset(img, 0, 3 * w*h);

		for (int i = 0; i < w; i++)
		{
			for (int j = 0; j < h; j++)
			{
				int x = i; int y = (h - 1) - j;
				int r = l.Get_Pixels()[j][i].GetCrveno();
				int g = l.Get_Pixels()[j][i].GetZeleno();
				int b = l.Get_Pixels()[j][i].GetPlavo();
				img[(x + y * w) * 3 + 2] = (unsigned char)(r);
				img[(x + y * w) * 3 + 1] = (unsigned char)(g);
				img[(x + y * w) * 3 + 0] = (unsigned char)(b);
			}
		}

		unsigned char bmpfileheader[14] = { 'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0 };
		unsigned char bmpinfoheader[40] = { 40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0 };
		unsigned char bmppad[3] = { 0,0,0 };

		bmpfileheader[2] = (unsigned char)(filesize);
		bmpfileheader[3] = (unsigned char)(filesize >> 8);
		bmpfileheader[4] = (unsigned char)(filesize >> 16);
		bmpfileheader[5] = (unsigned char)(filesize >> 24);

		bmpinfoheader[4] = (unsigned char)(w);
		bmpinfoheader[5] = (unsigned char)(w >> 8);
		bmpinfoheader[6] = (unsigned char)(w >> 16);
		bmpinfoheader[7] = (unsigned char)(w >> 24);
		bmpinfoheader[8] = (unsigned char)(h);
		bmpinfoheader[9] = (unsigned char)(h >> 8);
		bmpinfoheader[10] = (unsigned char)(h >> 16);
		bmpinfoheader[11] = (unsigned char)(h >> 24);
		cout << "Unesi ime izlazne datoteke: ";
		cin >> ime;
		f2 = fopen(ime.c_str(), "wb");
		fwrite(bmpfileheader, 1, 14, f2);
		fwrite(bmpinfoheader, 1, 40, f2);
		for (int i = 0; i < h; i++)
		{
			fwrite(img + (w*(h - i - 1) * 3), 3, w, f2);
			fwrite(bmppad, 1, (4 - (w * 3) % 4) % 4, f2);
		}

		free(img);
		fclose(f2);

	}


};
#endif