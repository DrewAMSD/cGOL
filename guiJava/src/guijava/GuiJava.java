/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Main.java to edit this template
 */
package guijava;

import com.mrjaffesclass.apcs.messenger.*;
/**
 *
 * @author drewa
 */
public class GuiJava {
    private final Messenger mvcMessaging;
    
    public GuiJava() {
        this.mvcMessaging = new Messenger();
        
        View view = new View(this.mvcMessaging);
        view.init();
        view.setVisible(true);
        
        Model model = new Model(this.mvcMessaging);
        model.init();
    }
    
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        GuiJava app = new GuiJava();
    }
    
}
