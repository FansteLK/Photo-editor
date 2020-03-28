
#include "Layer.h"
#include "Formatter.h"

Layer::Layer(const char * input_name,string form,int sirina,int visina,int transparentnost,int pozicijax,int pozicijay )
{
	
	if (Formatter::input(*this, input_name, form, sirina, visina,transparentnost,pozicijax ,pozicijay)) this->Set_Change();
	this->putanja = input_name;
	this->Set_Active_True();


}