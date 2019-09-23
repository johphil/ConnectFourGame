package Class;
import java.io.IOException;

public class Board implements Runnable {
	int BOARD_COLS = 7;
	int BOARD_ROWS = 6;
	
	@Override
	public void run() {
		// TODO Auto-generated method stub
		
	}
	
	public void printBoard(char[] board)
	{
		int col;
		clearScreen();
		System.out.println("\n    ****Connect Four****\n");
		for(int row = 0; row < BOARD_ROWS; row++)
	    {
	        for(col = 0; col < BOARD_COLS; col++)
	        {
	        	System.out.print(String.format("| %c ",  board[BOARD_COLS * row + col]));
	        }
	        System.out.println("|");
	        System.out.println("-----------------------------");
	    }
		System.out.println("  1   2   3   4   5   6   7\n");
	}
	
	public void clearScreen()
	{
		System.out.println("\u000c");
	}
}	
