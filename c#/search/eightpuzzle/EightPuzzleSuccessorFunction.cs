using System;
using System.Collections;
using aima.search.framework;

namespace aima.search.eightpuzzle
{
	/// <summary>
	/// Summary description for EightPuzzleSuccessorFunction.
	/// </summary>
	public class EightPuzzleSuccessorFunction : SuccessorFunction 
	{

		public ArrayList getSuccessors(Object state) 
		{
			EightPuzzleBoard board = (EightPuzzleBoard) state;
			ArrayList successors = new ArrayList();
			if (board.canMoveGap(EightPuzzleBoard.UP)) 
			{
				EightPuzzleBoard newBoard = copyOf(board);
				newBoard.moveGapUp();
				successors.Add(new Successor(EightPuzzleBoard.UP, newBoard));
			}
			if (board.canMoveGap(EightPuzzleBoard.DOWN)) 
			{
				EightPuzzleBoard newBoard = copyOf(board);
				newBoard.moveGapDown();
				successors.Add(new Successor(EightPuzzleBoard.DOWN, newBoard));
			}
			if (board.canMoveGap(EightPuzzleBoard.LEFT)) 
			{
				EightPuzzleBoard newBoard = copyOf(board);
				newBoard.moveGapLeft();
				successors.Add(new Successor(EightPuzzleBoard.LEFT, newBoard));
			}
			if (board.canMoveGap(EightPuzzleBoard.RIGHT)) 
			{
				EightPuzzleBoard newBoard = copyOf(board);
				newBoard.moveGapRight();
				successors.Add(new Successor(EightPuzzleBoard.RIGHT, newBoard));
			}
			return successors;
		}

		private EightPuzzleBoard copyOf(EightPuzzleBoard board) 
		{
			EightPuzzleBoard newBoard = new EightPuzzleBoard();
			newBoard.setBoard(board.getPositions());
			return newBoard;
		}

	}
}
