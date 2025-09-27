import java.awt.*;
import java.awt.event.*;
import java.util.Arrays;
import javax.swing.*;
import javax.swing.border.LineBorder;

public class Calc {
    int Height = 540;
    int Width = 360;

    Color customLightGray = new Color(212, 212, 210);
    Color customDarkGray = new Color(80, 80, 80);
    Color customBlack = new Color(28, 28, 28);
    Color customOrange = new Color(255, 149, 0);
    String[] buttonValues = {
        "AC", "+/-", "%", "÷", 
        "7", "8", "9", "×", 
        "4", "5", "6", "-",
        "1", "2", "3", "+",
        "0", ".", "√", "="
    };
    String[] rightSymbols = {"÷", "×", "-", "+", "="};
    String[] topSymbols = {"AC", "+/-", "%"};

    JFrame frame = new JFrame("Calc"); //struttura di base
    JLabel DisplayLabel = new JLabel(); //usato per fare display di scritte
    JPanel DisplayPanel = new JPanel(); //metti dentro questo il label e poi questo lo metti nel frame
    JPanel ButtonsPanel = new JPanel();
    
    //primo numero
    String A = "0";
    //operatore corrente
    String op = null;
    //secondo numero
    boolean B = false;


    Calc(){
        //creazione frame (calcolatrice)
        frame.setSize(Width, Height);
        frame.setLocationRelativeTo(null);
        frame.setResizable(false);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setLayout(new BorderLayout());

        //inizializzazione schermo sopra
        DisplayLabel.setBackground(customBlack);
        DisplayLabel.setForeground(Color.white);
        DisplayLabel.setFont(new Font("Arial", Font.PLAIN, 80));
        DisplayLabel.setHorizontalAlignment(JLabel.RIGHT);
        DisplayLabel.setText("0");
        DisplayLabel.setOpaque(true);

        //aggiunta dello schermo sopra
        DisplayPanel.setLayout(new BorderLayout());
        DisplayPanel.add(DisplayLabel);
        frame.add(DisplayPanel, BorderLayout.NORTH);

        //creazione griglia dei bottoni
        ButtonsPanel.setLayout(new GridLayout(5,4));
        ButtonsPanel.setBackground(customBlack);
        frame.add(ButtonsPanel);

        for(int i=0; i<buttonValues.length; i++){
            JButton button = new JButton();
            String buttonValue = buttonValues[i];
            button.setFont(new Font("Arial", Font.PLAIN, 30));
            button.setText(buttonValue);
            button.setFocusable(false);
            button.setBorder(new LineBorder(customBlack));
            if(Arrays.asList(topSymbols).contains(buttonValue)){
                button.setBackground(customLightGray);
                button.setForeground(customBlack);
            }else if(Arrays.asList(rightSymbols).contains(buttonValue)){
                button.setBackground(customOrange);
                button.setForeground(Color.white);
            }else{
                button.setBackground(customDarkGray);
                button.setForeground(Color.white);
            }
            ButtonsPanel.add(button);
            button.addActionListener(new ActionListener() {
                public void actionPerformed(ActionEvent e){
                    System.out.println(A);
                    JButton button = (JButton) e.getSource();
                    String buttonValue = button.getText();
                    if(Arrays.asList(rightSymbols).contains(buttonValue)){
                        //operazioni
                        defineOp(buttonValue);
                    }else if(Arrays.asList(topSymbols).contains(buttonValue)){
                        //bottoni speciali
                        if(buttonValue=="AC"){
                            clear();
                            DisplayLabel.setText("0");
                        }else if(buttonValue=="+/-"){
                            if(DisplayLabel.getText().charAt(0)=='-'){
                                DisplayLabel.setText(DisplayLabel.getText().substring(1));
                            }else{
                                DisplayLabel.setText("-"+DisplayLabel.getText());
                            }
                        }else if(buttonValue=="%"){
                            double x = Double.parseDouble(DisplayLabel.getText());
                            x/=100;
                            check(x);
                        }
                    }else{
                        //numeri
                        switch (buttonValue) {
                            case "√":
                                //da fare
                                break;
                            case ".":
                                if(!DisplayLabel.getText().contains(buttonValue)){
                                    DisplayLabel.setText(DisplayLabel.getText()+buttonValue);
                                }
                                break;
                            default:
                                if(DisplayLabel.getText()=="0"){
                                    DisplayLabel.setText(buttonValue);
                                }else{
                                    if(B){
                                        DisplayLabel.setText(buttonValue);
                                        B=false;
                                    }else{
                                        DisplayLabel.setText(DisplayLabel.getText()+buttonValue);
                                    }
                                }
                                break;
                        }
                    }
                }
            }); 
        }
        frame.setVisible(true);
    }
    void clear(){
        A="0";
        op=null;
        B=false;
    }
    void check(double x){
        if(x%1==0){
            DisplayLabel.setText(Integer.toString((int) x));
        }else{
            DisplayLabel.setText(Double.toString(x));
        }
    }
    void exec(){
        double a = Double.parseDouble(A);
        double b = Double.parseDouble(DisplayLabel.getText());
        double res = 0;
        switch(op){
            case "+":
                res=a+b;
                break;
            case "-":
                res=a-b;
                break;
            case "÷":
                res=a/b;
                break;
            case "×":
                res=a*b;
                break;
        }
        B=true;
        /*if(res%1==0){
            DisplayLabel.setText(Integer.toString((int) res));
            A=Integer.toString((int) res);
        }else{
            DisplayLabel.setText(Double.toString(res));
            A=Double.toString(res);
        } */
        check(res);
        A="0";
        op=null;
        //System.out.println(A);
    }
    void defineOp(String buttonValue){
        if((buttonValue=="=" && op!=null)){
            if(A=="0"){
                A=DisplayLabel.getText();
            }
            exec();
        }else if(op!=null && DisplayLabel.getText()!="0"){
            exec();
            A=DisplayLabel.getText();
            DisplayLabel.setText("0");
        }else{
            if(op==null){
                A=DisplayLabel.getText();
                DisplayLabel.setText("0");
            }
        }
        if(buttonValue!="="){
            op=buttonValue;
        }
    }
}

