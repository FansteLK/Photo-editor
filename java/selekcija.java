package obrada_slika;

import java.awt.Color;
import java.awt.Graphics;
import java.util.ArrayList;
import java.util.List;


public class selekcija 
{
	private Color color;
	private List<Rect> pravougaonici = new ArrayList<>();
	public selekcija() 
	{
		

	}
public void add_Rectangle(Rect r) 
{
	pravougaonici.add(r);
}
public List<Rect>  Get_pravougaonici() 
{
	return pravougaonici;
}
public void SetColor(Color c) {color=c;}
public void draw(Graphics g) 
{
	for (Rect r : pravougaonici) 
	{
		g.setColor(color);
		r.draw(g);
	}
}
public void ispis(files Fajl,double ratio_old_new_x,double ratio_old_new_y,int pocetnox ,int pocetnoy,int slika) 
{
	for (Rect r :pravougaonici) 
	{
		r.ispis(Fajl,ratio_old_new_x,ratio_old_new_y, pocetnox, pocetnoy,slika);
		Fajl.file_write("\r\n");
	}
}
}
