package OrologioMerda;
import java.awt.*;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import javax.swing.*;

public class Orologio {
    int Height = 200;
    int Width = 350;

    JFrame frame = new JFrame();
    JLabel Hours = new JLabel();
    JLabel Day = new JLabel();
    JLabel Date = new JLabel();
    Calendar calendar;
    SimpleDateFormat timeFormat=new SimpleDateFormat("hh:mm:ss a");
    SimpleDateFormat dayFormat=new SimpleDateFormat("EEEE");
    SimpleDateFormat dateFormat=new SimpleDateFormat("MMMMM dd, yyyy");

    Orologio(){
        frame.setSize(Width, Height);
        frame.setLocationRelativeTo(null);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setLayout(new FlowLayout());

        Hours.setBackground(Color.black);
        Hours.setForeground(new Color(0x00FF00));
        Hours.setFont(new Font("Arial", Font.PLAIN, 50));
        Hours.setOpaque(true);

        Day.setFont(new Font("Arial", Font.PLAIN, 35));
        Date.setFont(new Font("Arial", Font.PLAIN, 20));
        frame.add(Hours);
        frame.add(Day);
        frame.add(Date);
        frame.setVisible(true);
        frame.setFocusable(false);
        setTime();
    }   
    public void setTime(){
        while(true){
            Hours.setText(timeFormat.format(calendar.getInstance().getTime()));
            Day.setText(dayFormat.format(calendar.getInstance().getTime()));
            Date.setText(dateFormat.format(calendar.getInstance().getTime()));
        }
    }
}
