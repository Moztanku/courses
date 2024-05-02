import java.awt.*;
import java.awt.event.*;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.lang.Process;
import java.nio.Buffer;

import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextArea;
import javax.swing.JTextField;

public class Gui{
    private int width = 640;
    private int height = 480;
    private JButton button = new JButton("Run");
    private JTextField inputA = new JTextField();
    private JLabel inputALabel = new JLabel("numer wiersza");
    private JTextField inputB = new JTextField();
    private JLabel inputBLabel = new JLabel("wyrazy w wierszu");
    private JTextArea resultLabel = new JTextArea("         ");


    private GridBagConstraints gbc = new GridBagConstraints();

    private static final Font Labelfont = new Font("Serif",Font.PLAIN,24);
    private static final Font Inputfont = new Font("Monospaced",Font.PLAIN,24);

    public Gui(){
        JFrame frame = new JFrame();
        frame.setLayout(new BorderLayout());
        JPanel panel = new JPanel();
        panel.setLayout(new GridBagLayout());
        gbc.insets = new Insets(10,25,10,25);

        //
        setGrid(0,1,1,1);
        inputA.setColumns(4);
        inputA.setFont(Inputfont);
        panel.add(inputA,gbc);
        // //
        setGrid(0,0,1,1);
        inputALabel.setFont(Labelfont);
        panel.add(inputALabel,gbc);
        // //
        setGrid(2,1,1,1);
        inputB.setColumns(10);
        inputB.setFont(Inputfont);
        panel.add(inputB,gbc);
        // //
        setGrid(2,0,1,1);
        inputBLabel.setFont(Labelfont);
        panel.add(inputBLabel,gbc);
        // //
        setGrid(0,4,3,5);
        gbc.fill = GridBagConstraints.VERTICAL;
        //JPanel resultPanel = new JPanel();
        //resultPanel.setBackground(Color.gray);
        resultLabel.setFont(Labelfont);
        resultLabel.setRows(5);
        //resultPanel.add(resultLabel);
        panel.add(resultLabel,gbc);
        //
        button.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent ae){
                buttonPressed();
            };
        });

        setGrid(0,3,3,1);
        gbc.fill = GridBagConstraints.HORIZONTAL;
        panel.add(button,gbc);
        //frame.setSize(width, height);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.add(panel,BorderLayout.CENTER);
        frame.pack();
        frame.setVisible(true);
    };

    private void setGrid(int x,int y,int w,int h){
        gbc.gridx = x;
        gbc.gridy = y;
        gbc.gridwidth = w;
        gbc.gridheight = h;
    };
    private void buttonPressed(){
        try{
            String str = inputA.getText()+" "+inputB.getText();
            Process p = Runtime.getRuntime().exec("./main "+str);
            BufferedReader in = new BufferedReader(new InputStreamReader(p.getInputStream()));
            BufferedReader inErr = new BufferedReader(new InputStreamReader(p.getErrorStream()));

            resultLabel.setText("");
            String output;
            while((output = in.readLine())!=null)
                resultLabel.append(output+"\n");
            while((output = inErr.readLine())!=null)
                inErr.close();
        }
        catch(Exception ex){
            ex.printStackTrace();
        }
    };

    public static void main(String[] args) {
        new Gui();
    }
}
