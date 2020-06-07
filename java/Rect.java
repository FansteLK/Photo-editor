package obrada_slika;

import java.awt.BasicStroke;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Stroke;

public class Rect {
	private int x;
	 private int y;
	private int width;
	private int height;
	public Rect(int x,int y,int width,int height) 
	{
	this.x=x;
	this.y=y;
	this.width=width;
    this.height=height;
	}
	public int getHeight() {
		return height;
	}
	public void setHeight(int height) {
		this.height = height;
	}
	public int getWidth() {
		return width;
	}
	public void setWidth(int width) {
		this.width = width;
	}
	public int getY() {
		return y;
	}
	public void setY(int y) {
		this.y = y;
	}
	public int getX() {
		return x;
	}
	public void setX(int x) {
		this.x = x;
	}
	public void draw(Graphics g) 
	{
		 Graphics2D g2d = (Graphics2D) g.create();
		 Stroke dashed = new BasicStroke(3, BasicStroke.CAP_BUTT, BasicStroke.JOIN_BEVEL, 0, new float[]{9}, 0);
	        g2d.setStroke(dashed);
		g2d.drawRect(x, y, width,height);
		g2d.dispose();
	}
	public void ispis (files Fajl,double ratio_old_new_x,double ratio_old_new_y,int pocetnox ,int pocetnoy,int slika) 
	{
		System.out.print(x);
		System.out.print(" ");
				
		System.out.print(y);
		String s="";
		int width2=(int)(width*ratio_old_new_x);
		int height2=(int)(height*ratio_old_new_y);
		int x2=(int) ((x-pocetnox)*ratio_old_new_x);
		int y2=(int) (((slika-(y-pocetnoy)))*ratio_old_new_y)-height2;
		s+=x2;
		Fajl.file_write(s);
		Fajl.file_write(" ");
		 s="";
		 s+=y2;
		Fajl.file_write(s);
		Fajl.file_write(" ");
	s="";
		s+=width2;
		Fajl.file_write(s);
		Fajl.file_write(" ");
		 s="";
		s+=height2;
		Fajl.file_write(s);
		Fajl.file_write(" ");
	}

}
