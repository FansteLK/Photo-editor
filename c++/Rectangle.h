#ifndef _Rectangle_H_
#define _Rectangle_H_

#include "Position.h"
#include <iostream>
#include <string>
using namespace std;


class Rectangle
{
private:
	friend class MyFormatter;
	Position poz;
	int width;
	int height;
	
	
public:
	Rectangle(Position p,int w, int h):poz(p),width(w), height(h)
	{
	}
//Geteri
 int GetWidth() const
 {
	 return width;

 }
 int GetHeight() const
 {
	 return height;
 }
 Position GetPoz()const 
 {
	 return poz;
 }
 //Ispis pravougaonika
 friend ostream& operator<<(ostream &ot, const Rectangle &r) {
	ot << r.GetPoz().GetKolona() << " " << r.GetPoz().GetRed() << " " <<r.GetWidth() << " " << r.GetHeight();	return ot; }



};
#endif