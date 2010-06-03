using System;
using aima.search.framework;

namespace aima.search.nqueens
{
	/// <summary>
	/// Summary description for QueensToBePlacedHeuristic.
	/// </summary>
	public class QueensToBePlacedHeuristic : HeuristicFunction 
	{
		public int getHeuristicValue(Object state) 
		{
			NQueensBoard board = (NQueensBoard) state;
			return board.getSize() - board.getNumberOfQueensOnBoard();
		}

	}
}
