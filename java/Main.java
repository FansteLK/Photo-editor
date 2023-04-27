package obrada_slika;

import java.io.IOException;

import javax.swing.JFrame;
import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;

public class Main {

	public static void main(String[] args)

	{
		try {

			UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());

		} catch (ClassNotFoundException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		} catch (InstantiationException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		} catch (IllegalAccessException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		} catch (UnsupportedLookAndFeelException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
		Gui gui = new Gui();
		gui.setVisible(true);
		String s="";
		
		 s = gui.getPath(0);
		gui.SetImage(s,1);
	/*while(!gui.getKraj()) {
		
		boolean uspelo = true;
		String file = "..\\c++\\Project_POOP.exe " + s;
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
	}*/
	}

}
