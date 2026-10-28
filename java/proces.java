package obrada_slika;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

// Runs the C++ engine on the files written by the GUI and shows the result.
public class proces {

	// Path of the engine executable; override with -Dphotoeditor.engine=...
	static String enginePath() {
		String path = System.getProperty("photoeditor.engine", "build" + File.separator + "photo-engine");
		if (System.getProperty("os.name").startsWith("Windows") && !path.endsWith(".exe")) path += ".exe";
		return path;
	}

	// Output path without extension; the engine writes <outputBase()>.bmp
	static String outputBase() {
		return new File(System.getProperty("java.io.tmpdir"), "photo-editor-output").getAbsolutePath();
	}

	public static void izvrsi(files[] fajlovi, Gui g) {
		List<String> command = new ArrayList<>();
		command.add(enginePath());
		for (int i = 0; i < 3; i++) {
			command.add(fajlovi[i].getAbsPath());
		}
		command.add(outputBase());
		try {
			Process process = new ProcessBuilder(command).inheritIO().start();
			if (process.waitFor() != 0) {
				System.err.println("Engine failed: " + String.join(" ", command));
				return;
			}
		} catch (IOException e) {
			System.err.println("Cannot start the engine at " + enginePath() + ": " + e.getMessage());
			return;
		} catch (InterruptedException e) {
			Thread.currentThread().interrupt();
			return;
		}
		g.SetImage(outputBase() + ".bmp", 0);
	}

}
