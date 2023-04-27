#include "Operations.h"
#include"CompositeOperation.h"
#include "Image2.h"

void Operations::UcitajKompozitnu()
{
	CompositeOperation::kompozitna();
}

void Operations::FormirajKompozitnu(string ime, Image * im)
{
	CompositeOperation::zapisi(ime, im);
}
void Operations:: Medijana(Image *im)
{
	for (Layer &l : im->Get_Layers())
	{
		Layer l2 = l;
		for (int i = 0; i < l.Get_Num_Ver_Pix(); i++)
		{

			for (int j = 0; j < l.Get_Num_Hor_Pix(); j++)
			{

				int i2;
				int j2;
				if (i == l.Get_Num_Ver_Pix() - 1) i2 = i - 1;
				else i2 = i;
				if (j == l.Get_Num_Hor_Pix() - 1) j2 = j - 1;
				else j2 = j;

				l.Get_Pixels()[i][j].Set_Crveno((int)((l2.Get_Pixels()[i][abs(j - 1)].GetCrveno() + l2.Get_Pixels()[i][j2 + 1].GetCrveno() + l2.Get_Pixels()[abs(i - 1)][j].GetCrveno() + l2.Get_Pixels()[i2 + 1][j].GetCrveno() + l2.Get_Pixels()[abs(i - 1)][abs(j - 1)].GetCrveno() + l2.Get_Pixels()[abs(i - 1)][j2 + 1].GetCrveno() + l2.Get_Pixels()[i2 + 1][abs(j - 1)].GetCrveno() + l2.Get_Pixels()[i2 + 1][j2 + 1].GetCrveno()) / 8));
				l.Get_Pixels()[i][j].Set_Zeleno((int)((l2.Get_Pixels()[i][abs(j - 1)].GetZeleno() + l2.Get_Pixels()[i][j2 + 1].GetZeleno() + l2.Get_Pixels()[abs(i - 1)][j].GetZeleno() + l2.Get_Pixels()[i2 + 1][j].GetZeleno() + l2.Get_Pixels()[abs(i - 1)][abs(j - 1)].GetZeleno() + l2.Get_Pixels()[abs(i - 1)][j2 + 1].GetZeleno() + l2.Get_Pixels()[i2 + 1][abs(j - 1)].GetZeleno() + l2.Get_Pixels()[i2 + 1][j2 + 1].GetZeleno()) / 8));
				l.Get_Pixels()[i][j].Set_Plavo((int)((l2.Get_Pixels()[i][abs(j - 1)].GetPlavo() + l2.Get_Pixels()[i][j2 + 1].GetPlavo() + l2.Get_Pixels()[abs(i - 1)][j].GetPlavo() + l2.Get_Pixels()[i2 + 1][j].GetPlavo() + l2.Get_Pixels()[abs(i - 1)][abs(j - 1)].GetPlavo() + l2.Get_Pixels()[abs(i - 1)][j2 + 1].GetPlavo() + l2.Get_Pixels()[i2 + 1][abs(j - 1)].GetPlavo() + l2.Get_Pixels()[i2 + 1][j2 + 1].GetPlavo()) / 8));

			}
		}
	}
}