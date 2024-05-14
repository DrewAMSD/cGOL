/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package guijava;

import java.awt.Color;
/**
 *
 * @author drewa
 */
public class Constants {
    //board size
    public static final int ROWS = 15;
    public static final int COLS = 25;

    //cell states
    public static final boolean DEAD = false;
    public static final boolean ALIVE = true;
    
    //background for cells
    public static final Color COLOR_DEAD = Color.BLACK;
    public static final Color COLOR_ALIVE = Color.YELLOW;
    
    //time between each generation being displayed;
    public static final int DELAY = 1000;
}
