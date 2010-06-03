using System;
using System.Collections;
using aima.basic;
using aima.search.framework;

namespace aima.search.nqueens
{
	/// <summary>
	/// Summary description for NQueensSuccessorFunction.
	/// </summary>
	public class NQueensSuccessorFunction : SuccessorFunction 
	{

		public ArrayList getSuccessors(Object state) 
		{
			ArrayList successors = new ArrayList();
			NQueensBoard board = (NQueensBoard) state;
			int numQueens = board.getNumberOfQueensOnBoard();
			int boardSize = board.getSize();
			for (int i = 0; i < boardSize; i++) 
			{
				if (!(board.isSquareUnderAttack(new XYLocation(numQueens, i)))) 
				{
					NQueensBoard child = placeQueenAt(numQueens, i, board);
					successors.Add(new Successor("placeQueenAt " + numQueens + "  "
						+ i, child));

				}

			}

			return successors;
		}

		private NQueensBoard placeQueenAt(int row, int column,
			NQueensBoard parentBoard) 
		{

			NQueensBoard newBoard = new NQueensBoard(parentBoard.getSize());
			ArrayList queenPositionsOnParentBoard = parentBoard.getQueenPositions();
			queenPositionsOnParentBoard.Add(new XYLocation(row, column));
			newBoard.setBoard(queenPositionsOnParentBoard);
			return newBoard;
		}

	}
}
