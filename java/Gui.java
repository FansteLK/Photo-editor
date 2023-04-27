package obrada_slika;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.FocusEvent;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.text.NumberFormat;
import java.util.ArrayList;
import java.util.Random;
import java.util.List;
import javax.imageio.ImageIO;
import javax.swing.*;
import javax.swing.text.NumberFormatter;

public class Gui extends JFrame implements ActionListener, ItemListener {
//INICIJALIZATORI ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//izlazak iz programa
	boolean izlazak=false;
	//Boolean da li je sacuvano nakon promene
	boolean sacuvano=false;
	// Pozicije misa
	private int x, y, x2, y2;
	private int ximage, yimage, xwidth, yheight,image_visina;
	
	private double ratio_old_new_x, ratio_old_new_y;

	// Pozicije misa
//String bafer
	StringBuilder composite = new StringBuilder("");

	// Current Rect
	Rect currentRect;
	// Mouse

	private MouseListenerz listener;
	// Selekcije
	private List<Rect> selekcija = new ArrayList<>();
	private selekcija[] selekcije;
	// Selekcije

	// Files
	private files[] fajlovi;
	// Files

	// Slika
	private ImageIcon img;
	// Slika

	// Paneli
	private JPanel sredina;
	private JPanel gore;
	private JPanel desno;
	private JPanel levo1;
	private JPanel levo21;
	private JPanel levo22;
	// Container levih panela panel
	private JPanel levo;
	private JPanel dole;
	// Dialog paneli
	private JPanel dialog_dole;
	private JPanel dialog_gore;

	// Paneli

	// Labeli
	private JLabel labels[];
	public JLabel label1;
	// Labeli

	// Chooser
	private JFileChooser chooser = new JFileChooser();

	// Chooser

	// Butons && RadioButtons && CheckButtons && Dialog buttons &&Top bar
	private JButton open;
	private Button button_napravi_selekciju;
	private Button button_izvrsi_operaciju;
	// RadioButtons
	private ButtonGroup radio;
	private JRadioButton radio_buttons[];
	// CheckButtons
	String[] operacije = { "Kompozitna", "sabiranje", "oduzimanje", "inverzno oduzimanje", "mnozenje", "deljenje", "inverzno deljenje",
			"stepenovanje", "logaritam", "min ", "max", "inverzija", "black&white", "greyscale", "medijana" };
	String[] operacije_kompozitna = {  "sabiranje", "oduzimanje", "inverzno oduzimanje", "mnozenje", "deljenje", "inverzno deljenje",
			"stepenovanje", "logaritam", "min ", "max", "inverzija", "black&white", "greyscale", "medijana","abs"  };
	private Button[] checkb;
	// DialogButtons
	private Button button_dialog_dodaj;
	private Button button_dialog_zavrsi;
	// Top Buttons
	private Button button_sacuvaj;
	private Button button_izadji;
	private Button button_ponisti;
	private Button button_obrisi;
	private Button button_formiraj;
	// Butons && RadioButtons && CheckButtons && Dialog buttons &&Top bar

	// TextFields
	private JTextField txt;
	private JTextField txtdesno;
	private JTextField txtdialog;
	private JTextField txtdialogdole;
	// TextFields

	// ComboBox
	private JComboBox operations;
	private JComboBox operations2;
	// ComboBox

	// Dialog
	private JDialog dialog;
	// Dialog

	// Scroll pane
	private JScrollPane scrollPane;
	//

	// Niz TextFieldova
	private JSpinner[] transparenti;

	// lokacije slika
	private String[] lokacije;
	/*
	 * ] //Menu private JMenuBar menuBar; private JMenu menu, submenu; private
	 * JMenuItem menuItem; //Menu
	 */
//INICIJALIZATORI ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	

	Gui() {

		setSize(1667, 970);
		setBounds(100, 10, 1667, 970);
		this.setUndecorated(true);
		setResizable(false);
		SetPanels();
		init_Locations();
		init_J_Dialog();
		init_Selekcije();
		init_choosers();
		init_fajlovi();
		for(int i=0;i<4;i++) 
		{
			fajlovi[i].ClearFile();
		}
		this.pack();

	}

// PANELI PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP
	// Formira panele
	public void CreatePanels() {

		// Levo1---------------------------------------------------------

		// Podesavanje panela
		levo1 = new JPanel();
		levo1.setLayout(new GridLayout(8, 1));
		levo1.setPreferredSize(new Dimension(166, 896));
		levo1.setBackground(Color.black);
		// Smestanje u panel
		for (int i = 0; i < 8; i++) {
			labels[i].setVisible(false);
			levo1.add(labels[i]);
		}

		// Levo1---------------------------------------------------------

		// Levo21---------------------------------------------------------
		// Podesavanje panela
		levo21 = new JPanel();
		levo21.setLayout(new BoxLayout(levo21, BoxLayout.Y_AXIS));
		levo21.setPreferredSize(new Dimension(59, 896));
		// Inicijalizovanje smestanje
		initCheckButtons();

		// Levo21---------------------------------------------------------

		// Levo22-----------------------------------------------------------

		// Podesavanje panela
		levo22 = new JPanel();
		levo22.setLayout(new BoxLayout(levo22, BoxLayout.Y_AXIS));
		levo22.setPreferredSize(new Dimension(50, 896));
		// init fields
		init_transparenti();

		// Levo22-----------------------------------------------------------

		// Levo----------------------------------------------------------
		// Podesavanje panela
		levo = new JPanel(new BorderLayout());
		levo.setPreferredSize(new Dimension(275, 896));
		// Smestanje u panel
		levo.add(levo1, BorderLayout.CENTER);
		levo.add(levo21, BorderLayout.EAST);
		levo.add(levo22, BorderLayout.WEST);

		// Levo----------------------------------------------------------

		// Sredina-------------------------------------------------------
		// Podesvanje panela
		sredina = new JPanel(new GridLayout(1, 1));
		sredina.setBackground(Color.BLACK);
		sredina.setPreferredSize(new Dimension(1192, 896));
		// Smestanje

		sredina.add(label1);

		// Sredina-------------------------------------------------------

		// Desno---------------------------------------------------------

		// Podesavanja panela
		desno = new JPanel();
		desno.setBackground(Color.black);
		desno.setPreferredSize(new Dimension(200, 896));
		desno.setLayout(new GridLayout(10, 1));
		// Inicijalizovanje
		initButtons();
		init_Radio_Buttons();
		initTextField();
		// Smestanje
		desno.add(txtdesno);
		desno.add(button_napravi_selekciju);

		// Desno---------------------------------------------------------

		// Dole-----------------------------------------------------------

		// Podesavanje panela
		dole = new JPanel(new GridLayout(1, 3));
		dole.setPreferredSize(new Dimension(1657, 44));

		// Inicijalizovanje komponenti
		init_JCombo();

		Font f = new Font("Calibri", Font.PLAIN, 20);
		button_izvrsi_operaciju = new Button("izvrsi operaciju");
		button_izvrsi_operaciju.setFont(f);
		button_izvrsi_operaciju.addActionListener(this);

		// Smestanje u panel
		dole.add(txt);
		dole.add(operations);
		dole.add(button_izvrsi_operaciju);

		// Dole----------------------------------------------------------

		// Gore-----------------------------------------------------------
		// Podesavanje panela

		gore = new JPanel();
		gore.setBackground(Color.DARK_GRAY);
		gore.setPreferredSize(new Dimension(1657, 30));
		gore.setLayout(new GridLayout(1, 5));
		// Smestanje u panel
		// pad
		/*
		 * for (int i = 0; i < 2; i++) { gore.add(new Label("")); }
		 */
		gore.add(button_formiraj);
		gore.add(button_obrisi);
		gore.add(button_ponisti);
		gore.add(button_sacuvaj);
		gore.add(button_izadji);

		// Gore-----------------------------------------------------------

		// Dialog gore-----------------------------------------------------
		// Podesavanje panela
		dialog_gore = new JPanel(new GridLayout(1, 4));
		// Smestanje
		dialog_gore.add(operations2);
		dialog_gore.add(txtdialog);
		dialog_gore.add(button_dialog_dodaj);
		dialog_gore.add(button_dialog_zavrsi);

		// Dialog gore-----------------------------------------------------

		// Dialog dole-----------------------------------------------------

		// Podesavanje panela
		dialog_dole = new JPanel(new GridLayout(1, 1));
		// Smestanje
		dialog_dole.add(scrollPane);

		// Dialog dole-----------------------------------------------------

	}

	// Rasporedjuje panele u glavni Layout
	public void SetPanels() {

		initJPanels();
		CreatePanels();
		add(levo, BorderLayout.WEST);
		add(sredina, BorderLayout.CENTER);
		add(desno, BorderLayout.EAST);
		add(dole, BorderLayout.SOUTH);
		add(gore, BorderLayout.NORTH);

	}

// PANELI PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP

// INITI IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
	/*
	 * public void init_Menu() { menuBar = new JMenuBar(); menu = new JMenu("Menu");
	 * menuItem= new JMenuItem("kompozitna operacija"); }
	 */
	public void init_Locations() 
	{
		lokacije = new String[8];
		for (int i = 0; i < 8; i++) {
			lokacije[i] = "";
		}
	}

	public void init_transparenti() {
		Font f2 = new Font("Calibri", Font.PLAIN, 16);

		transparenti = new JSpinner[8];
		for (int i = 0; i < 8; i++) {
			SpinnerModel model = new SpinnerNumberModel(255, // initial value
					0, // min
					255, // max
					5);
			transparenti[i] = new JSpinner(model);
			transparenti[i].setFont(f2);
			transparenti[i].setAlignmentX(CENTER_ALIGNMENT);
			transparenti[i].setAlignmentY(CENTER_ALIGNMENT);
			JSpinner.DefaultEditor editor = (JSpinner.DefaultEditor) transparenti[i].getEditor();
			editor.getTextField().setEnabled(true);
			editor.getTextField().setEditable(false);
			editor.getTextField().setForeground(Color.CYAN);
			editor.getTextField().setBackground(Color.DARK_GRAY);
			levo22.add(transparenti[i]);
		}
	}

	public void init_fajlovi() {
		fajlovi = new files[4];
		fajlovi[0] = new files("slike.txt");
		fajlovi[1] = new files("operacije.txt");
		fajlovi[2] = new files("selekcije.txt");
		fajlovi[3] = new files("izlazni_direktorijum.txt");
		for (int i=0;i<4;i++) 
		{
			fajlovi[i].ClearFile();
		}
		fajlovi[3].file_write(System.getProperty("user.dir"));
	}

	public void init_choosers() {
		chooser.setCurrentDirectory(new java.io.File("."));
	}

	public void init_Selekcije() {

		int x = 0;
		int y = 0;
		int w = 0;
		int h = 0; //
		currentRect = new Rect(0, 0, 0, 0);
		selekcije = new selekcija[8];
		for (int i = 0; i < 8; i++) {

			selekcije[i] = new selekcija();

		}
		MouseListenerz listener = new MouseListenerz();
		addMouseListener(listener);
		addMouseMotionListener(listener);
	}

	public void init_J_Dialog() {
		dialog = new JDialog(this, "Formiranje kompozitne");
		dialog.setLayout(new GridLayout(2, 1));
		dialog.setBounds(500, 500, 400, 200);
		dialog.setResizable(false);
		dialog.add(dialog_gore);
		dialog.add(dialog_dole);
		// Dialog cuvanje

	}

	public void init_Radio_Buttons() {
		radio = new ButtonGroup();

		radio_buttons = new JRadioButton[8];
		for (int i = 0; i < 8; i++) {
			Font f = new Font("", Font.PLAIN, 20);
			radio_buttons[i] = new JRadioButton("Selection" + i);
			radio_buttons[i].setFont(f);
			radio_buttons[i].setAlignmentX(CENTER_ALIGNMENT);
			radio_buttons[i].addActionListener(this);
			radio_buttons[i].setVisible(false);
			radio_buttons[i].addItemListener(this);
			radio.add(radio_buttons[i]);
			desno.add(radio_buttons[i]);

		}

	}

	public void init_JCombo() {
		// Obicna operacija
		operations = new JComboBox(operacije);

		operations.addActionListener(this);
		// Dijalog
		operations2 = new JComboBox(operacije_kompozitna);

		operations2.addActionListener(this);
	}

	public void initTextField() {

		// Donji TextField
		Font f = new Font("Calibri", Font.PLAIN, 20);
		Font f2 = new Font("Calibri", Font.PLAIN, 16);
		txt = new JTextField();
		txt.setFont(f);
		txt.setHorizontalAlignment(JTextField.CENTER);
		txt.addActionListener(this);

		// Desni TextField

		txtdesno = new JTextField();
		txtdesno.setFont(f);
		txtdesno.setHorizontalAlignment(JTextField.CENTER);
		txtdesno.addActionListener(this);

		// Dialog TextField gore

		txtdialog = new JTextField();
		txtdialog.setFont(f);
		txtdialog.setHorizontalAlignment(JTextField.CENTER);

		// Dialog TextField dole

		txtdialogdole = new JTextField();
		txtdialogdole.setFont(f2);
		txtdialogdole.setBackground(Color.LIGHT_GRAY);
		txtdialogdole.setForeground(Color.BLUE);
		txtdialogdole.setHorizontalAlignment(JTextField.CENTER);
		scrollPane = new JScrollPane(txtdialogdole);
		txtdialogdole.setEditable(false);

	}

	public void initJPanels() {
		label1 = new JLabel();
		labels = new JLabel[8];

		for (int i = 0; i < 8; i++) {
			labels[i] = new JLabel();
		}

	}

	public void initCheckButtons() {
		checkb = new Button[16];
		for (int i = 0; i < 16; i++) {
			Font f = new Font("TimesNewRoman", Font.PLAIN, 14);
			Font f2 = new Font("Calibri", Font.ITALIC, 14);

			if (i % 2 == 0) {
				checkb[i] = new Button("layer" + (i + 1) / 2);
				checkb[i].setBackground(Color.GREEN);
				checkb[i].setFont(f2);

			}
			if (i % 2 == 1) {
				checkb[i] = new Button("ucitaj");
				checkb[i].setBackground(Color.DARK_GRAY);
				checkb[i].setForeground(Color.CYAN);
				checkb[i].setFont(f);
			}

			checkb[i].addActionListener(this);
			levo21.add(checkb[i]);

		}
	}

	public void initButtons() {

		button_napravi_selekciju = new Button("napravi selekciju");

		Font f = new Font("Calibri", Font.PLAIN, 20);
		button_napravi_selekciju.setFont(f);
		button_napravi_selekciju.addActionListener(this);
		// Dialog buttons
		button_dialog_dodaj = new Button("dodaj");
		button_dialog_zavrsi = new Button("zavrsi");
		button_dialog_dodaj.setFont(f);
		button_dialog_zavrsi.setFont(f);
		button_dialog_dodaj.setForeground(Color.CYAN);
		button_dialog_zavrsi.setForeground(Color.CYAN);
		button_dialog_dodaj.setBackground(Color.DARK_GRAY);
		button_dialog_zavrsi.setBackground(Color.DARK_GRAY);
		button_dialog_dodaj.addActionListener(this);
		button_dialog_zavrsi.addActionListener(this);
		// Top bar buttons

		// izadji
		button_izadji = new Button("Exit");
		button_izadji.setFont(f);
		button_izadji.setBackground(Color.RED);
		button_izadji.setForeground(Color.YELLOW);
		button_izadji.addActionListener(this);
		// sacuvaj
		button_sacuvaj = new Button("Sacuvaj");
		button_sacuvaj.setFont(f);
		button_sacuvaj.setBackground(Color.DARK_GRAY);
		button_sacuvaj.setForeground(Color.YELLOW);
		button_sacuvaj.addActionListener(this);
		// ponisti
		button_ponisti = new Button("Ponisti");
		button_ponisti.setFont(f);
		button_ponisti.setBackground(Color.DARK_GRAY);
		button_ponisti.setForeground(Color.YELLOW);
		button_ponisti.addActionListener(this);
		// obrisi selekciju
		button_obrisi = new Button("Obrisi");
		button_obrisi.setFont(f);
		button_obrisi.setBackground(Color.DARK_GRAY);
		button_obrisi.setForeground(Color.YELLOW);
		button_obrisi.addActionListener(this);
		// formiraj sliku
		button_formiraj = new Button("Formiraj");
		button_formiraj.setFont(f);
		button_formiraj.setBackground(Color.DARK_GRAY);
		button_formiraj.setForeground(Color.YELLOW);
		button_formiraj.addActionListener(this);

	}
// INITI IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII

//HELPERI HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH	
//izlazal
	public boolean getKraj() {return izlazak;}
//Izlazi iz aplikacije i daje korisniku opciju da sacuva sliku
	public void exit_Save() 
	{
		 int confirmed = JOptionPane.showConfirmDialog(null, 
			        "Da li zelite da napustite program?", "Exit Program Message Box",
			        JOptionPane.YES_NO_OPTION);

			    if (confirmed == JOptionPane.YES_OPTION)
			    {
			    	if(!sacuvano) {
			   	 int confirmed2 = JOptionPane.showConfirmDialog(null, 
					        "Najnovija promena nije sacuvana,da li zelite da sacuvate?", "Exit Program Message Box",
					        JOptionPane.YES_NO_OPTION);
			   	 if (confirmed2 == JOptionPane.YES_OPTION)
			   	 {
			   		 save_Image();
			   	 }
			    
			      dispose();
			    }}
			    izlazak=true;
	}
//Formira basic operaciju
	public void basic_Operation() 
	{
		fajlovi[1].ClearFile();
		if (operacije[operations.getSelectedIndex()] == "Kompozitna") {

			dialog.setVisible(true);
		} else {
			String s = "";
			s += operacije[operations.getSelectedIndex()];
			s += ";";
			if (txt.getText().isEmpty()) {

				s += "0";
			} else {

				int i;
				try {
					i = Integer.parseInt(txt.getText());
					s += txt.getText();

				} catch (NumberFormatException er) {
					JOptionPane.showMessageDialog(null, "Unesite integer");
					return;
				}

			}
			s += ";";
			fajlovi[1]=new files("basicop.txt");
			fajlovi[1].ClearFile();
			fajlovi[1].file_write(s);
			String s2= fajlovi[1].getAbsPath();
			fajlovi[1]=new files("operacije.txt");
			fajlovi[1].file_write(s2);
			
		}
	
	}
//Konacna kompozitna
	public void final_Composite()
	{
		if(!txtdialog.getText().isEmpty()) {
			fajlovi[1] = new files(txtdialog.getText() + ".txt");

			String text = composite.toString();

			// split by new line
			String[] lines = text.split("\\r?\\n");
			for (String line : lines) {
				System.out.print(line);
				fajlovi[1].file_write(line);
				fajlovi[1].file_write("\r\n");
			}
		}
		

		//String text = composite.toString();

		/*// split by new line
		String[] lines = text.split("\\r?\\n");
		for (String line : lines) {
			System.out.print(line);
			fajlovi[1].file_write(line);
			fajlovi[1].file_write("\r\n");
		}*/
		fajlovi[1]= new files("operacije.txt");
	String s=this.getPath(0);
	fajlovi[1].file_write(s);
		formLayers_Selections();
		dialog.setVisible(false);
		operations2.setSelectedItem("Saberi");
		txtdialog.setText("");
		txtdialogdole.setText("");
		composite = new StringBuilder("");
		formLayers_Selections();
	}
//Cuva sliku
	public void save_Image() 
	{
		sacuvano=true;
		String s = "";
		try {
			this.save("C:\\Users\\stefa\\Desktop\\novo");
		} catch (IOException e) {
	
		}
		chooser.setSelectedFile(new File(""));
		chooser.setCurrentDirectory(new java.io.File("."));

	}
//Brise selekciju
	public void delete_Selection() 
	{
		for (int i = 0; i < 8; i++) {
			if (radio_buttons[i].isSelected()) {
				radio.clearSelection();
				radio_buttons[i].setVisible(false);
				radio_buttons[i].setText("Selection" + i);
				selekcije[i].Get_pravougaonici().clear();

			}
		}
	}
//Formira	Layere
	public void formLayers_Selections() {
		sacuvano=false;
		fajlovi[0].ClearFile();
		fajlovi[2].ClearFile();
		
		for (int i = 7; i>=  0; i--) {
			if (lokacije[i] != "") {
				if (checkb[i * 2].getBackground() == Color.GREEN) {
					JSpinner.DefaultEditor editor = (JSpinner.DefaultEditor) transparenti[i].getEditor();
					String broj = editor.getTextField().getText();
					String s = lokacije[i];
					s += " ";
					s += Integer.parseInt(broj);
					//s += ";";
					fajlovi[0].file_write(s);
					fajlovi[0].file_write("\r\n");
				}
			}
		}
		for (int j=0; j<8;j++) 
		{
			if(radio_buttons[j].isSelected()&&radio_buttons[j].isVisible()) 
			{
				selekcije[j].ispis(fajlovi[2],ratio_old_new_x,ratio_old_new_y,ximage, yimage,image_visina);
			}
			
		}
		proces.izvrsi(fajlovi,this);
	}

//Formira CheckButtone
	public void formCheckButtons(int i) {

		if (i % 2 == 0) {
			if (checkb[i].getBackground() == Color.GREEN)
				checkb[i].setBackground(Color.RED);
			else {
				checkb[i].setBackground(Color.GREEN);
			}
		}
		if (i % 2 == 1) {
			if (checkb[i].getLabel() == "ucitaj") {
				checkb[i].setLabel("izbrisi");
				String s = "";
				s = this.getPath(0);
				SetImage(s, labels[(i - 1) / 2]);
				labels[(i - 1) / 2].setVisible(true);
			} else {
				lokacije[(i - 1) / 2] = "";
				checkb[i].setLabel("ucitaj");
				labels[(i - 1) / 2].setVisible(false);
			}
		}
		boolean ima=false;
		int j=0;
		while((!ima)&&(j<8)){
		{
			if(labels[j].isVisible()) ima=true;
			
			j++;
		}
		if(ima) 
		{
			
			SetImage(lokacije[--j],label1);
			label1.setVisible(true);
		}
		if(!ima) 
		{
			label1.setVisible(false);
		}
		
		}
	}

//Formira selekciju	
	public void formSelekcija()

	{
		int i = 0;
		boolean end = false;

		while ((i < 8) && (!end)) {
			if (!radio_buttons[i].isVisible()) {
				if (!txtdesno.getText().isEmpty()) {
					if (check_diffrent_name(txtdesno.getText())) {
						radio_buttons[i].setText(txtdesno.getText());
						radio_buttons[i].setVisible(true);
						radio_buttons[i].setBackground(RandomBoja());
						end = true;
					} else {
						JOptionPane.showMessageDialog(null, "Postoji selekcija sa datim imenom");
						return;
					}
				} else {
					radio_buttons[i].setBackground(RandomBoja());
					radio_buttons[i].setVisible(true);
					end = true;
				}

			}
			i++;
		}
		if (!end)
			JOptionPane.showMessageDialog(null, "Ne moze se dodati vise selekcija");
	}

//Formira kompozitnu funkciju
	public void formKompozitna() {
		String s = txtdialogdole.getText();

		if (!s.isEmpty()) {
			s += ", ";
			composite.append("\n");

		}
		s += operacije_kompozitna[operations2.getSelectedIndex()];
		composite.append(operacije_kompozitna[operations2.getSelectedIndex()]);
		composite.append(";");
		s += " ";
		if (!txtdialog.getText().isEmpty()) {
boolean tr=false;

			try {

				int i = Integer.parseInt(txtdialog.getText());
				s += txtdialog.getText();
				composite.append(txtdialog.getText());
				composite.append(";");
				tr=true;
			} catch (NumberFormatException e) {
				JOptionPane.showMessageDialog(null, "Kompozitna funkcija se odbacuje zbog neispravnog unosa");
				dialog.setVisible(false);
				operations2.setSelectedItem("Saberi");
				txtdialog.setText("");
				txtdialogdole.setText("");
				composite = new StringBuilder("");
				return;
			}

		} else {
			s += "0";
			composite.append("0");
			composite.append(";");

		}
		
		txtdialogdole.setText(s);
	}

//Vraca putanju choosera
	public String getPath(int i) {

		if (i == 0) {
			chooser.setFileSelectionMode(JFileChooser.FILES_ONLY);
			while (chooser.showOpenDialog(open) != JFileChooser.APPROVE_OPTION)
				;
			return chooser.getSelectedFile().getAbsolutePath();
		} else {
			chooser.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
			while (chooser.showSaveDialog(null) != JFileChooser.APPROVE_OPTION)
				;

			return chooser.getSelectedFile().getAbsolutePath();
		}
	}

//Proverava dal neka selekcija ima uneto ime	
	public boolean check_diffrent_name(String s) {
		for (int i = 0; i < 8; i++) {
			if (radio_buttons[i].getText().equals(s)) {
				return false;
			}

		}
		return true;
	}

//Vraca Random boju
	public Color RandomBoja()

	{
		Random random = new Random();
		int r1 = 0;
		int g1 = 0;
		int b1 = 0;
		boolean isti = true;
		// da se boje razlikuju i da budu svetle
		while ((isti) && (r1 + g1 + b1 < 400)) {
			r1 = random.nextInt(255);
			g1 = random.nextInt(255);
			b1 = random.nextInt(255);
			// pravi da boje budu razlicite
			for (int i = 0; i < 8; i++) {
				int r = radio_buttons[i].getBackground().getRed();
				int g = radio_buttons[i].getBackground().getGreen();
				int b = radio_buttons[i].getBackground().getBlue();
				if ((Math.abs(r1 - r) > 22) || (Math.abs(g1 - g) > 22) || (Math.abs(b1 - b) > 22))
					isti = false;
			}
		}

		return new Color(r1, g1, b1);

	}

//Postavlja glavnu sliku
	public void SetImage(String s,int i) {
		if(i==1) {
		SetImage(s,labels[0]);
		labels[0].setVisible(true);
		checkb[1].setLabel("izbrisi");
		}
		chooser.setSelectedFile(new File(""));
		chooser.setCurrentDirectory(new java.io.File("."));
		File imagefajl = new File(s);

		Image im;
		try {
			im = ImageIO.read(imagefajl);
		} catch (IOException e) {
			im = null;
		}
		img = new ImageIcon(im);

		double oldHeight = img.getIconHeight();
		double oldWidth = img.getIconWidth();
		Point p = sredina.getLocation();

		label1.setIcon(img = this.resize_img(img, label1));
		label1.revalidate();
		sredina.revalidate();

	

		ximage = (int) p.getX();
		double xwidthd = img.getIconWidth();
		xwidth = (int) xwidthd;
		yimage = (int) p.getY()+((sredina.getHeight()-img.getIconHeight())/2);
		double yheightd = img.getIconHeight();
		yheight = (int) yheightd;
		this.ratio_old_new_x = (oldWidth /(double) xwidth);
		this.ratio_old_new_y = (oldHeight /(double) yheight);
image_visina=yheight;
	}

//Postavlja sliku na j label
	public void SetImage(String s, JLabel j) {
		chooser.setSelectedFile(new File(""));
		chooser.setCurrentDirectory(new java.io.File("."));
		for (int i = 0; i < 8; i++) {
			if (labels[i] == j) {
				lokacije[i] = s;

			}
		}
		File imagefajl = new File(s);

		Image im;
		try {
			im = ImageIO.read(imagefajl);
		} catch (IOException e) {
			im = null;
		}
		ImageIcon img = new ImageIcon(im);
		j.setIcon(this.resize_img(img, j));
		j.setAlignmentY(CENTER_ALIGNMENT);

	}

//Skalira sliku
	public ImageIcon resize_img(ImageIcon im, JLabel j) {
	
		Image img = im.getImage();
		double d = j.getWidth() / (double) im.getIconWidth();
		int height = (int) (d * im.getIconHeight());
		if (height > j.getHeight())
			height = j.getHeight();
		Image newimg = img.getScaledInstance(j.getWidth(), height, java.awt.Image.SCALE_SMOOTH);

		return new ImageIcon(newimg);
	}
//Cuva konacnu sliku na odabranu lokaciju	
	private  void save(String fileName) throws IOException {

		File file = new File(fileName + ".bmp");
		   BufferedImage image =  ImageIO.read(file);
		try {
			String s=this.getPath(1);
			File outputfile = new File(s+"\\saved.bmp");
		   ImageIO.write(image, "bmp",outputfile);  
		} catch(IOException e) {
	
		  }
		 }

//HELPERI HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH	

// Selekcije crtanje SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS

// Pocetna kordinata pravougaonika
	public void setStartPoint(int x, int y) {
		this.x = x;
		this.y = y;
	}

// Krajnja kordinata pravougaonika
	public void setEndPoint(int x, int y) {
		x2 = (x);
		y2 = (y);
	}

// MouseListener
	class MouseListenerz extends MouseAdapter {
		public void mousePressed(MouseEvent e) {
			setStartPoint(e.getX(), e.getY());
		}

		public void mouseDragged(MouseEvent e) {
			
			setEndPoint(e.getX(), e.getY());
			Ispravnost_Trenutnog_Pravougaonika();
			azurirajCurrent();
			repaint();
			
		}

		public void mouseReleased(MouseEvent e) {
			setEndPoint(e.getX(), e.getY());
			Ispravnost_Trenutnog_Pravougaonika();
			azurirajCurrent();
			setRectangleinSelection();
			repaint();
		}
	}

//Azurira current rectangle		
	public void azurirajCurrent() {
		int x1 = Math.min(x, x2);
		int y1 = Math.min(y, y2);
		int width = Math.abs(x - x2);
		int height = Math.abs(y - y2);
		currentRect.setX(x1);
		currentRect.setY(y1);
		currentRect.setWidth(width);
		currentRect.setHeight(height);

	}

// Proverava da li moze da se nacrta
	public boolean Ispravnost_Trenutnog_Pravougaonika() {

		Point p = sredina.getLocation();

		int x1ekran = (int) p.getX();

		int x2ekran = (int) x1ekran + img.getIconWidth();
		int y1ekran = (int) ((p.getY() + (sredina.getHeight() - img.getIconHeight()) / 2));

		int y2ekran = (int) y1ekran + img.getIconHeight();

		boolean x1_okej = (x >= x1ekran) && (x <= x2ekran);
		boolean y1_okej = (y >= y1ekran) && (y <= y2ekran);

		if (x2 < x1ekran)
			x2 = x1ekran;
		if (x2 > x2ekran)
			x2 = x2ekran;
		if (y2 < y1ekran)
			y2 = y1ekran;
		if (y2 > y2ekran)
			y2 = y2ekran;

		if (x1_okej && y1_okej)
			return true;
		else
			return false;
	}

//Postavlja rectangle u selekciju
	public void setRectangleinSelection() {

		if (Ispravnost_Trenutnog_Pravougaonika()) {
			Rect r = new Rect(currentRect.getX(), currentRect.getY(), currentRect.getWidth(), currentRect.getHeight());
			for (int i = 0; i < 8; i++) {
				if (radio_buttons[i].isSelected()) {

					selekcije[i].add_Rectangle(r);
				}

			}
		}
	}

//Crta selekcije
	public void paint(Graphics g) {
		super.paint(g);
		boolean postoji = false;
		for (int i = 0; i < 8; i++) {
			if (radio_buttons[i].isSelected()) {
				g.setColor(radio_buttons[i].getBackground());
				if (selekcije[i] != null) {
					selekcije[i].SetColor(radio_buttons[i].getBackground());
					selekcije[i].draw(g);
				}

				postoji = true;
			}

		}
		if (postoji) {
			if (Ispravnost_Trenutnog_Pravougaonika())

				currentRect.draw(g);

		}
	}
// Selekcije crtanje SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS

// LISTENERI LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
	@Override
	public void itemStateChanged(ItemEvent e) {
		for (int i = 0; i < 8; i++) {
			if (e.getSource() == radio_buttons[i]) {
				currentRect.setHeight(0);
				currentRect.setWidth(0);
				repaint();
			}
		}

	}

	public void actionPerformed(ActionEvent e) {
		Gui gui = this;
		// Formiraj
		if (e.getActionCommand() == "Formiraj") {
			this.formLayers_Selections();
		}
		// Obrisi
		if (e.getActionCommand() == "Obrisi") {
			delete_Selection();
			this.formLayers_Selections();
		}
		// Ponisti
		if (e.getActionCommand() == "Ponisti") {
			radio.clearSelection();
			this.formLayers_Selections();

		}
		// Sacuvaj
		if (e.getActionCommand() == "Sacuvaj") {
			save_Image();
		}
		// Exit
		if (e.getActionCommand() == "Exit") {
			 exit_Save();
		}
		// Dijalog
		if (e.getActionCommand() == "zavrsi") {
			final_Composite();
		}

		// Dijalog2
		if (e.getActionCommand() == "dodaj") {
			formKompozitna();
		}

		// Ispisuje jednu operaciju u fajl
		if (e.getActionCommand() == "izvrsi operaciju") {
			basic_Operation(); 
			formLayers_Selections();
		}
		// Napravi selekciju
		if (e.getActionCommand() == "napravi selekciju") {
			formSelekcija();
		}
		// CheckButtoni

		for (int i = 0; i < 16; i++) {

			if (e.getSource() == checkb[i]) {
				this.formCheckButtons(i);
				formLayers_Selections();
			}
			
		}
	}
// LISTENERI LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
}
