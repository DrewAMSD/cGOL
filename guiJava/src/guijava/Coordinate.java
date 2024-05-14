/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package guijava;


/**
 *
 * @author drewa
 */
public class Coordinate {
    private int row;
    private int col;
    
    public Coordinate(int row, int col) {
        this.row = row;
        this.col = col;
    }
    
    public int getRow() {
        return this.row;
    }
    
    public int getCol() {
        return this.col;
    }
    
    public void setRow(int newRow) {
        this.row = newRow;
    }
    
    public void setCol(int newCol) {
        this.col = newCol;
    }
    
    public void translate(Coordinate coord) {
        this.row += coord.getRow();
        this.col += coord.getCol();
    }
    
    public boolean isEqualTo(Coordinate coord) {
        return (this.row == coord.getRow() && this.col == coord.getCol());
    }
    
    public boolean isInsideBoard() {
        return (0 <= this.row 
                && this.row < Constants.ROWS 
                && 0 <= this.col 
                && this.col < Constants.COLS);
    }
    
    @Override
    public String toString() {
        return ""+row+","+col+"";
    }
}
