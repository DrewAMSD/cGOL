/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package guijava;

import com.mrjaffesclass.apcs.messenger.*;
import java.util.concurrent.TimeUnit;
/**
 *
 * @author drewa
 */
public class Model implements MessageHandler {
    private final Messenger mvcMessaging;
    private boolean[][] grid;
 
    public Model(Messenger messages) {
        this.mvcMessaging = messages;
        
        this.grid = new boolean[Constants.ROWS][Constants.COLS];
    }
    
    public void init() {
        //subscribe to messages here
        this.mvcMessaging.subscribe("view:cellClicked", this);
        this.mvcMessaging.subscribe("view:clearBtnClicked", this);
        this.mvcMessaging.subscribe("view:nextGenBtnClicked", this);
        
        //other initializations
        clear();
    }
    
    public void clear() {
        for (int row = 0; row < Constants.ROWS; row++) {
            for (int col = 0; col < Constants.COLS; col++) {
                this.grid[row][col] = Constants.DEAD;
            }
        }
        this.mvcMessaging.notify("model:gridChanged", this.grid);
    }
    
    private void cellClicked(Coordinate cellClicked) {
        int curRow = cellClicked.getRow();
        int curCol = cellClicked.getCol();
        boolean curCellState = this.grid[curRow][curCol];
        this.grid[curRow][curCol] = !curCellState;
        this.mvcMessaging.notify("model:gridChanged", this.grid);
    }
    
    private int countNeighbors(int r, int c) {
        int count = 0;
        for (int i = r - 1; i <= r + 1; i++) {
        for (int j = c - 1; j <= c + 1; j++) {
            if ((i != r || j != c) && i < Constants.ROWS && i >= 0 && j < Constants.COLS && j >= 0) {
            if (grid[i][j]) {
                count = count + 1;
            }
            }
        }
        }
        return count;
    }
    
    private boolean[][] getNextGen() {
        boolean[][] nextGen = new boolean[Constants.ROWS][Constants.COLS];
        for (int row = 0; row < Constants.ROWS; row++) {
            for (int col = 0; col < Constants.COLS; col++) {
                nextGen[row][col] = this.grid[row][col];
                int count = countNeighbors(row, col);
                if (grid[row][col]) {
                    //cell is alive and doesn't have num of neighbors to survive
                    if (count != 2 && count != 3) {
                        nextGen[row][col] = false;
                    }
                } else {
                    //cell is dead and has 3 neighbors to become alive
                    if (count == 3) {
                        nextGen[row][col] = true;
                    }
                }
            }
        }
        return nextGen;
    }
    
    private void nextGen() {
        this.grid = getNextGen();
        this.mvcMessaging.notify("model:gridChanged", this.grid);
    }
    
    @Override
    public void messageHandler(String messageName, Object messagePayload) {
        //notify that the message was received
        if (messagePayload != null) {
            System.out.println("MSG: received by view: "+messageName+" | "+messagePayload.toString());
        } else {
            System.out.println("MSG: received by view: "+messageName+" | No data sent");
        }
        
        switch (messageName) {
            case "view:cellClicked":
                Coordinate coord = (Coordinate) messagePayload;
                cellClicked(coord);
                break;
            case "view:clearBtnClicked":
                clear();
                break;
            case "view:nextGenBtnClicked":
                nextGen();
                break;
            default:
                break;
        }
    }
}