#ifndef _PAMFFormatter_H_
#define _PAMFormatter_H_

#include <iostream>
#include <stdio.h>
#include "Layer.h"
#include <fstream>
class PAMFFormatter
{

	friend class Formatter;
	//Podrzani svi formati unosa 
	static bool  format_input(string ime, Layer &l, int sirina, int visina)
	{
		int br=0;
		bool ret = false;
		ifstream File(ime, ios::binary);
		if (File.fail())
		{
			cout << "Ne moze se otvoriti fajl " << ime << endl;
			return false;
		}

		//Read the Magic Number
		string num, w_str, h_str, d_str, max_str, tmp, red_str, green_str, blue_str, alpha_str, format;

		int red, green, blue, alfa = 255;
		File >> num;

		if (num != "P7") {

			File.close();
			return false; //The file is not a ASCII PPM file!
		}

		File >> tmp >> w_str >> tmp >> h_str >> tmp >> d_str >> tmp >> max_str >> tmp >> format >> tmp;
		cout << w_str << h_str << d_str << max_str << tmp;

		int width = atoi(w_str.c_str()); //Takes the number string and converts it to an integer
		int height = atoi(h_str.c_str());
		int depth = atoi(d_str.c_str()); //Takes the number string and converts it to an integer
		int max_value = atoi(max_str.c_str());
		bool veca = ((sirina <= width) && (visina <= height));
		bool manja = ((sirina >= width) && (visina >= height));
		bool veca_sirina = ((sirina <= width) && (visina >= height));
		bool veca_duzina = ((sirina >= width) && (visina <= height));
		File.get();
		unsigned char * img = (unsigned char *)malloc(depth* width*height);
		memset(img, 0, depth * width*height);
		File.read((char*)&img[0], width*height * depth);



		if (veca_sirina)
		{
		
			ret = true;
			l.Set_Num_Hor(width);
			l.Set_Num_Ver(visina);
			for (int i = 0; i < visina; i++)
			{


				vector <Pixel> vektor;
				for (int j = 0; j < width * depth; j += depth)
				{
					if (i >= height)
					{

						Pixel temp(0, 0, 0);
						temp.Set_Alpha(0);
						vektor.push_back(temp);
					


					}

					else
					{
						int x = j / depth; int y = (height - 1) - i;
						if (depth == 4)
						{

							red = (int)img[(x + y * width) * depth + 0];
							green = (int)img[(x + y * width) * depth + 1];
							blue = (int)img[(x + y * width) * depth + 2];
							alfa = (int)img[(x + y * width) * depth + 3];
							Pixel temp(red, green, blue);
							temp.Set_Alpha(alfa);
							vektor.push_back(temp);
						}
						else if (depth == 3)
						{
							br++;
							red = (int)img[(x + y * width) * depth + 0];
							green = (int)img[(x + y * width) * depth + 1];
							blue = (int)img[(x + y * width) * depth + 2];
							Pixel temp(red, green, blue);
							temp.Set_Alpha(255);
							vektor.push_back(temp);

						}
						else if ((depth == 2) && (format == "GRAYSCALE_ALPHA"))
						{
							red = (int)img[(x + y * width) * depth + 0];
							alfa = (int)img[(x + y * width) * depth + 1];
							Pixel temp(red, red, red);
							temp.Set_Alpha(alfa);
							vektor.push_back(temp);
						}
						else if ((depth == 2) && (format == "BLACKANDWHITE_ALPHA"))
						{
							red = (int)img[(x + y * width) * depth + 0];
							alfa = (int)img[(x + y * width) * depth + 1];
							int cb;
							if (red == 1) cb = 255;
							else cb = 0;
							Pixel temp(cb, cb, cb);
							temp.Set_Alpha(alfa);
							vektor.push_back(temp);
						}
						else if ((depth == 1) && (format == "GRAYSCALE"))
						{
							red = (int)img[(x + y * width) * depth + 0];
							Pixel temp(red, red, red);
							vektor.push_back(temp);
						}
						else if ((depth == 1) && (format == "BLACKANDWHITE"))
						{
							red = (int)img[(x + y * width) * depth + 0];
							int cb;
							if (red == 1) cb = 255;
							else cb = 0;
							Pixel temp(cb, cb, cb);
							vektor.push_back(temp);

						}
					}

				}

				l.Get_Pixels().push_back(vektor);
			}
			free(img);
			File.close();
			return ret;
		}

			if (veca_duzina)
			{
				ret = true;
				l.Set_Num_Hor(sirina);
				l.Set_Num_Ver(height);
				for (int i = 0; i < height; i++)
				{



					vector <Pixel> vektor;
					for (int j = 0; j < sirina * depth; j += depth)
					{
						if (j >= width * depth)
						{

							Pixel temp(0, 0, 0);
							temp.Set_Alpha(0);
							vektor.push_back(temp);
							if (depth == 4)
							{
								temp.Set_Alpha(0);
							}

							vektor.push_back(temp);

						}

						else
						{
							int x = j / depth; int y = (height - 1) - i;
							if (depth == 4)
							{

								red = (int)img[(x + y * width) * depth + 0];
								green = (int)img[(x + y * width) * depth + 1];
								blue = (int)img[(x + y * width) * depth + 2];
								alfa = (int)img[(x + y * width) * depth + 3];
								Pixel temp(red, green, blue);
								temp.Set_Alpha(alfa);
								vektor.push_back(temp);
							}
							else if (depth == 3)
							{
								red = (int)img[(x + y * width) * depth + 0];
								green = (int)img[(x + y * width) * depth + 1];
								blue = (int)img[(x + y * width) * depth + 2];
								Pixel temp(red, green, blue);

								vektor.push_back(temp);

							}
						}
					}

					l.Get_Pixels().push_back(vektor);
				}
				free(img);
				File.close();
				return ret;
			}
			if (veca)
			{
				ret = true;
				l.Set_Num_Hor(width);
				l.Set_Num_Ver(height);
				//povecaj_layere(int,int)
				for (int i = 0; i < height; i++)
				{




					vector <Pixel> vektor;
					for (int j = 0; j < width * depth; j += depth)
					{
						if (j >= width * depth)
						{
							Pixel temp(0, 0, 0);
							temp.Set_Alpha(0);
							vektor.push_back(temp);
							if (depth == 4)
							{
								temp.Set_Alpha(0);
							}

							vektor.push_back(temp);

						}

						else
						{

							int x = j / depth; int y = (height - 1) - i;
						
							if (depth == 4)
							{

								red = (int)img[(x + y * width) * depth + 0];
								green = (int)img[(x + y * width) * depth + 1];
								blue = (int)img[(x + y * width) * depth + 2];
								alfa = (int)img[(x + y * width) * depth + 3];
								Pixel temp(red, green, blue);
								temp.Set_Alpha(alfa);
								vektor.push_back(temp);
							}
							else if (depth == 3)
							{
								red = (int)img[(x + y * width) * depth + 0];
								green = (int)img[(x + y * width) * depth + 1];
								blue = (int)img[(x + y * width) * depth + 2];
								Pixel temp(red, green, blue);

								vektor.push_back(temp);

							}

						}
					}

					l.Get_Pixels().push_back(vektor);
				}
				free(img);
				File.close();
				return ret;
			}
			if (manja)
			{
				l.Set_Num_Hor(sirina);
				l.Set_Num_Ver(visina);
				for (int i = 0; i < visina; i++)
				{

					vector <Pixel> vektor;
					for (int j = 0; j < sirina * depth; j += depth)
					{
						if (i >= height)
						{
							Pixel temp(0, 0, 0);
							temp.Set_Alpha(0);
							vektor.push_back(temp);
							if (depth == 4)
							{
								temp.Set_Alpha(0);
							}

							vektor.push_back(temp);

						}
						else
						{
							if (j >= width * depth)
							{
								Pixel temp(0, 0, 0);
								temp.Set_Alpha(0);
								vektor.push_back(temp);
								if (depth == 4)
								{
									temp.Set_Alpha(0);
								}

								vektor.push_back(temp);


							}

							else
							{
								int x = j / depth; int y = (height - 1) - i;
								if (depth == 4)
								{

									red = (int)img[(x + y * width) * depth + 0];
									green = (int)img[(x + y * width) * depth + 1];
									blue = (int)img[(x + y * width) * depth + 2];
									alfa = (int)img[(x + y * width) * depth + 3];
									Pixel temp(red, green, blue);
									temp.Set_Alpha(alfa);
									vektor.push_back(temp);
								}
								else if (depth == 3)
								{
									red = (int)img[(x + y * width) * depth + 0];
									green = (int)img[(x + y * width) * depth + 1];
									blue = (int)img[(x + y * width) * depth + 2];
									Pixel temp(red, green, blue);

									vektor.push_back(temp);

								}
							}
						}
					}
					l.Get_Pixels().push_back(vektor);
				}
				\
				free(img);
				File.close();
				return ret;
			}
			free(img);
	
			File.close();
			return ret;

		
	}

	//Ispis u RGB_ALPHA modu
	static void format_output(string ime, Layer &l)
	{
		ime = ime;
		ofstream File(ime, ios::binary);
		File << "P7" << "\n";
		File << "WIDTH " << l.Get_Num_Hor_Pix() << "\n" << "HEIGHT " << l.Get_Num_Ver_Pix() << "\n" << "DEPTH " << 4 << "\n" << "MAXVAL " << 255 << "\n" << "TUPLTYPE " << "RGB_ALPHA" << "\n" << "ENDHDR" << "\n";
		
		 char * img = (  char *)malloc(4 * l.Get_Num_Hor_Pix()*l.Get_Num_Ver_Pix());
		memset(img, 0, 4 * l.Get_Num_Hor_Pix()*l.Get_Num_Ver_Pix());

		for (int i = 0; i < l.Get_Num_Hor_Pix(); i++)
		{
			for (int j = 0; j < l.Get_Num_Ver_Pix(); j++)
			{
				int x = i; int y = (l.Get_Num_Ver_Pix() - 1) - j;
				int alfa = l.Get_Pixels()[j][i].GetAlfa();
				int r = l.Get_Pixels()[j][i].GetCrveno();
				int g = l.Get_Pixels()[j][i].GetZeleno();
				int b = l.Get_Pixels()[j][i].GetPlavo();

				img[(x + y * l.Get_Num_Hor_Pix()) * 4 + 3] = (unsigned char)(alfa);
				img[(x + y * l.Get_Num_Hor_Pix()) * 4 + 2] = (unsigned char)(b);
				img[(x + y * l.Get_Num_Hor_Pix()) * 4 + 1] = (unsigned char)(g);
				img[(x + y * l.Get_Num_Hor_Pix()) * 4 + 0] = (unsigned char)(r);
			}
		}

		size_t size = l.Get_Num_Hor_Pix()* l.Get_Num_Ver_Pix() * 4;
		File.write(img, size);
		free(img);
		File.close();
	}
};
#endif;