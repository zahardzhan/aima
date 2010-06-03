using System;
using System.Collections;
using aima.basic;
using aima.search.framework;

namespace aima.search.nqueens
{
	/// <summary>
	/// Summary description for NQueensGoalTest.
	/// </summary>
	public class NQueensGoalTest : GoalTest 
	{
		NQueensBoard board;

		public bool isGoalState(Object state) 
		{

			board = (NQueensBoard) state;
			return (allQueensPlaced() && allQueenPositionsHaveZeroAttacks(board
				.getQueenPositions()));
		}

		private bool allQueensPlaced() 
		{
			return board.getNumberOfQueensOnBoard() == board.getSize();
		}

		private bool allQueenPositionsHaveZeroAttacks(ArrayList positions) 
		{
		
			for (int i = 0; i < positions.Count; i++) 
			{
				XYLocation location = (XYLocation) positions[i];
				if (board.getNumberOfAttacksOn(location) != 0) 
				{
					return false;
				}
			}
			return true;
		}
	}
}
