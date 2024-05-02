import java.awt.*;
import java.awt.event.*;
import src.WierszTrojkatPascala;



public class Gui extends Frame{
    private int width;
    private int height;

    private TextField tf;
    private Button btn;
    private Container labelContainer;

    Gui(int _width,int _height){
        width = _width;
        height = _height;
        setSize(width, height);
        setLayout(new BorderLayout());
        setVisible(true);

        btn = new Button("Uruchom");
        btn.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent ae){
                try{
                    int n = Integer.parseInt(tf.getText());
                    buttonPressed(n);
                }
                catch(NumberFormatException ex){
                    labelContainer.removeAll();
                    Label temp = new Label("Prosze wprowadzić liczbę naturalną");
                    labelContainer.add(temp);
                    labelContainer.revalidate();
                }
            }
        });
        btn.setFont(new Font("arial",Font.BOLD,24));
        btn.setBackground(new Color(200,200,180));


        tf = new TextField();
        tf.setFont(new Font("arial",Font.PLAIN,24));
        tf.setBackground(new Color(200,180,200));

        addWindowListener(new WindowAdapter() {
            public void windowClosing(WindowEvent we) {
                dispose();
             }
         }
        );
        Container con = new Container();
        labelContainer = new Container();
        labelContainer.setBackground(new Color(190,210,210));
        labelContainer.setLayout(new GridLayout(labelContainer.getComponentCount()+1,1));
        labelContainer.add(new Label(""));
        con.setLayout(new GridLayout(1,2));
        con.add(btn);
        con.add(tf);
        add(con,BorderLayout.NORTH);
        add(labelContainer,BorderLayout.CENTER);
    };
    Gui(){
        this(640,480);
    };

    private void buttonPressed(int n){
        labelContainer.setFont(new Font("arial",Font.PLAIN,6+(40-n)/2));
        labelContainer.removeAll();
        labelContainer.setLayout(new GridLayout(n,1));
        for(int i=0; i<n; i++){
            WierszTrojkatPascala wtp = new WierszTrojkatPascala(i);
            Container con = new Container();
            con.setLayout(new GridLayout(1,n));
            for(int j=i; j<n; j++)
                con.add(new Label(""));
            for(int j=0; j<=i; j++){
                con.add(new Label(String.valueOf(wtp.Wspolczynnik(j))));
            }            
            for(int j=i; j<n; j++)
            con.add(new Label(""));
            labelContainer.add(con);
        }
        labelContainer.revalidate();
    };

    public static void main(String[] args) {
        Gui gui = new Gui();
    }
}