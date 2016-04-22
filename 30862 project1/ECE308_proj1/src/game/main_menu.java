package game;
import javax.swing.*;
import java.awt.Color;
import java.awt.FlowLayout;
import java.awt.Font;

import java.awt.Color;
import java.awt.event.*;


public class main_menu {
	 public static int type(){
   	  // Create a "clickable" image icon
   	
   	int i =0;
   	Color c = new Color (0,0,0);
       ImageIcon icon = new ImageIcon("images/mike_main.png");
       JLabel label = new JLabel(icon);
       ImageIcon icon1 = new ImageIcon("images/igal_main.png");
       JLabel label1 = new JLabel(icon1);
       JPanel contentPane = new JPanel();
       
       JLabel label3 = new JLabel("Choose your character!");
       JLabel mike_l = new JLabel("Mike");
       JLabel mike_info = new JLabel("<html>Speed: 10<br>Range: 7</html>");
       JLabel igal_l = new JLabel("Igal");
       JLabel igal_info = new JLabel("<html>Speed: 7<br>Range: 10</html>");
       
       
       label3.setBounds(600,100,2000,100);
       label3.setFont(new Font("Serif", Font.BOLD, 56));
       label3.setForeground(Color.WHITE);
       
       
       contentPane.setOpaque(true);
       contentPane.setBackground(c);
       contentPane.setLayout(null);
       final JFrame frame = new JFrame("My Window");
       frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
       frame.getContentPane().add(label);
       frame.setTitle("The Ultimate Game");
       frame.setExtendedState(frame.MAXIMIZED_BOTH);
       frame.pack();
       frame.setVisible(true);
       label.setBounds(400,400,300,600);
       mike_l.setBounds(500,330,1000,100);
       mike_info.setBounds(750,500,1000,100);
       //label.setLocation(50, 50);
       label1.setBounds(1200,400,300,600);
       igal_l.setBounds(1300,330,1000,100);
       igal_info.setBounds(1550,500,1000,100);
       //label1.setLocation(250, 250);
       mike_l.setFont(new Font("Serif", Font.BOLD, 26));
       mike_l.setForeground(Color.WHITE);
       mike_info.setFont(new Font("Serif", Font.BOLD, 26));
       mike_info.setForeground(Color.WHITE);
       igal_l.setFont(new Font("Serif", Font.BOLD, 26));
       igal_l.setForeground(Color.WHITE);
       igal_info.setFont(new Font("Serif", Font.BOLD, 26));
       igal_info.setForeground(Color.WHITE);
       contentPane.add(label);
       contentPane.add(label1);
       contentPane.add(label3);
       contentPane.add(mike_l);
       contentPane.add(mike_info);
       contentPane.add(igal_l);
       contentPane.add(igal_info);
       
       frame.setContentPane(contentPane);
       label.addMouseListener(new MouseAdapter() {
           public void mouseClicked(MouseEvent me) {
             System.out.println("CLICKED");
             frame.setTitle("Mike");
           }
         });
       label1.addMouseListener(new MouseAdapter() {
           public void mouseClicked(MouseEvent me) {
             System.out.println("CLICKED");
             frame.setTitle("Igal");
           }
         });
       while (i==0){
       //System.out.println("I am here");
       
       String s = frame.getTitle();
       System.out.println(s);
       if (s.equals("Mike")){
       	i =1;
       }
       else if(s.equals("Igal")){
       	i = 2;
       }
       // Add it to a frame.
       
       
   	}
       System.out.println("im out");
       frame.setVisible(false);
       return i;
       
   }
}
