package obrada_slika;

import java.io.IOException;

public class proces {

	public proces() {
		// TODO Auto-generated constructor stub
	}
	public static void izvrsi(files[] fajlovi,Gui g) 
	{
		boolean uspelo = true;
		String file = "C:\\Users\\stefa\\Desktop\\FAKS\\Project_POOP\\Release\\Project_POOP.exe " ;
		for (int i=0;i<4;i++) 
		{
			file+=fajlovi[i].getAbsPath();
			file+=" ";
		}
		System.out.print(file);
		Runtime runtime = Runtime.getRuntime();
		try {
			Process process = runtime.exec(file);
			while (process.isAlive()) {
			}
			;

		} catch (IOException e) {
			System.out.print("Greska");
			uspelo = false;
		}

		if (!uspelo)
			return;
		g.SetImage("C:\\Users\\stefa\\Desktop\\novo.bmp",0);
	}

}
