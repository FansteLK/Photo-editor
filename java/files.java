package obrada_slika;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

public class files {


	private String absolutePath ;
private File f;


	// Read the content from file

	public files(String file_name) {
		absolutePath = System.getProperty("user.dir") + File.separator + file_name;
		 f= new File(absolutePath);

	}
	public void file_write(String s) 
	{
		// Write the content in file 
		try(BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(absolutePath,true))) {
		    bufferedWriter.write(s);
		} catch (IOException e) {
		    // Exception handling
		}

	}
	public void file_read() 
	{
		try(BufferedReader bufferedReader = new BufferedReader(new FileReader(absolutePath))) {
		    String line = bufferedReader.readLine();
		    while(line != null) {
		        System.out.println(line);
		        line = bufferedReader.readLine();
		    }
		} catch (FileNotFoundException e) {
		    // Exception handling
		} catch (IOException e) {
		    // Exception handling
		}	
	}
	public void ClearFile() 
	{
		 FileWriter fileOut;
			try {
				fileOut = new FileWriter(this.f);
				fileOut.write("");
			} catch (IOException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}
	}
public File get_File()
{
	return f;
}
public String getAbsPath() 
{
	return absolutePath;}

}
