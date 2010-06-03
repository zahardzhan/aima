using System;
using aima.search.framework;
using aima.basic;

namespace aima.search.eightpuzzle
{
	/// <summary>
	/// Summary description for MisplacedTileHeuristicFunction.
	/// </summary>
	public class MisplacedTilleHeuristicFunction : HeuristicFunction 
	{

		public int getHeuristicValue(Object state) 
		{
			EightPuzzleBoard board = (EightPuzzleBoard) state;
			return getNumberOfMisplacedTiles(board);

		}

		private int getNumberOfMisplacedTiles(EightPuzzleBoard board) 
		{
			int numberOfMisplacedTiles = 0;
			if (!(board.getLocationOf(0).Equals(new XYLocation(0, 0)))) 
			{
				numberOfMisplacedTiles++;
			}
			if (!(board.getLocationOf(1).Equals(new XYLocation(0, 1)))) 
			{
				numberOfMisplacedTiles++;
			}
			if (!(board.getLocationOf(2).Equals(new XYLocation(0, 2)))) 
			{
				numberOfMisplacedTiles++;
			}
			if (!(board.getLocationOf(3).Equals(new XYLocation(1, 0)))) 
			{
				numberOfMisplacedTiles++;
			}
			if (!(board.getLocationOf(4).Equals(new XYLocation(1, 1)))) 
			{
				numberOfMisplacedTiles++;
			}
			if (!(board.getLocationOf(5).Equals(new XYLocation(1, 2)))) 
			{
				numberOfMisplacedTiles++;
			}
			if (!(board.getLocationOf(6).Equals(new XYLocation(2, 0)))) 
			{
				numberOfMisplacedTiles++;
			}
			if (!(board.getLocationOf(7).Equals(new XYLocation(2, 1)))) 
			{
				numberOfMisplacedTiles++;
			}
			if (!(board.getLocationOf(8).Equals(new XYLocation(2, 2)))) 
			{
				numberOfMisplacedTiles++;
			}
			return numberOfMisplacedTiles;
		}

	}
}
