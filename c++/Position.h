#ifndef _Position_H_
#define _Position_H_
class Position
{
private:
	friend class MyFormatter;
	int red;
	int kolona;

public:
	Position(int je, int dv)
	{
		red = je;
		kolona = dv;
	};
	//Geteri
	int GetRed()const
	{
		return red;
	}
	int GetKolona()const
	{
		return kolona;
	}


};
#endif