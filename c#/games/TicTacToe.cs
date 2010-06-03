using System;
using System.Collections;
using aima.basic;

namespace aima.games
{
	/// <summary>
	/// Summary description for TicTacToe.
	/// </summary>
	public class TicTacToe : Game 
	{
		public TicTacToe() 
		{
			ArrayList moves = new ArrayList();
			for (int i = 0; i < 3; i++) 
			{
				for (int j = 0; j < 3; j++) 
				{
					XYLocation loc = new XYLocation(i, j);
					moves.Add(loc);
				}
			}
			initialState.put("moves", moves);
			initialState.put("player", "X");
			initialState.put("utility", 0);
			initialState.put("board", new TicTacToeBoard());
			initialState.put("level", 0);
			presentState = initialState;
		}

		public TicTacToeBoard getBoard(GameState state) 
		{

			return (TicTacToeBoard) state.get("board");
		}

		public override ArrayList getSuccessorStates(GameState state) 
		{
			GameState temp = presentState;
			ArrayList retVal = new ArrayList();
				int parentLevel = getLevel(state);
			for (int i = 0; i < getMoves(state).Count; i++) 
			{
				XYLocation loc = (XYLocation) getMoves(state)[i];

				GameState aState = makeMove(state, loc);
				aState.put("moveMade", loc);
				aState.put("level", parentLevel + 1);
				retVal.Add(aState);

			}
			presentState = temp;
			return retVal;
		}

		public override GameState makeMove(GameState state, Object o) 
		{
			XYLocation loc = (XYLocation) o;
			return makeMove(state, loc.getXCoOrdinate(), loc.getYCoOrdinate());
		}

		public GameState makeMove(GameState state, int x, int y) 
		{
			GameState temp = getMove(state, x, y);
			if (temp != null) 
			{
				presentState = temp;
			}
			return presentState;
		}

		public GameState makeMove(int x, int y) 
		{
			GameState state = presentState;
			GameState temp = getMove(state, x, y);
			if (temp != null) 
			{
				presentState = temp;
			}
			return presentState;
		}

		public GameState getMove(GameState state, int x, int y) 
		{
			GameState retVal = null;
			XYLocation loc = new XYLocation(x, y);
			ArrayList moves = getMoves(state);
			ArrayList newMoves = (ArrayList) moves.Clone();
			if (moves.Contains(loc)) 
			{
				//int index = newMoves.indexOf(loc);
				int index = newMoves.IndexOf(loc);
				//newMoves.Remove(index);
				//.remove function is not overloaded in .net like it is in java
				//in .NET .remove only removes the instance of the parameter, 
				//not the object at the index
				newMoves.RemoveAt(index);

				retVal = new GameState();

				retVal.put("moves", newMoves);
				TicTacToeBoard newBoard = getBoard(state).cloneBoard();
				if (getPlayerToMove(state) == "X") 
				{
					newBoard.markX(x, y);
					retVal.put("player", "O");

				} 
				else 
				{
					newBoard.markO(x, y);
					retVal.put("player", "X");

				}
				retVal.put("board", newBoard);
				retVal.put("utility",computeUtility(newBoard,
					getPlayerToMove(getState())));
				retVal.put("level", getLevel(state) + 1);
				//presentState = retVal;
			}
			return retVal;
		}

		public override int computeUtility(GameState state) 
		{
			int utility = computeUtility((TicTacToeBoard) state.get("board"),
				(getPlayerToMove(state)));
			return utility;
		}

		private int computeUtility(TicTacToeBoard aBoard, string playerToMove) 
		{
			int retVal = 0;
			if (aBoard.lineThroughBoard()) 
			{
				if (playerToMove.Equals("X")) 
				{
					retVal = -1;
				} 
				else 
				{
					retVal = 1;
				}

			}
			return retVal;
		}

		public override bool terminalTest(GameState state) 
		{
			TicTacToeBoard board = (TicTacToeBoard) state.get("board");
			bool line = board.lineThroughBoard();
			bool filled = board.getNumberOfMarkedPositions() == 9;
			return (line || filled);
		}

//		public void printPossibleMoves() 
//		{
//			System.out.println("Possible moves");
//
//			ArrayList moves = getMoves(presentState);
//			for (int i = 0; i < moves.size(); i++) 
//			{
//				XYLocation moveLoc = (XYLocation) moves.get(i);
//				GameState newState = getMove(presentState,
//					moveLoc.getXCoOrdinate(), moveLoc.getYCoOrdinate());
//				TicTacToeBoard board = (TicTacToeBoard) newState.get("board");
//				System.out.println("utility = " + computeUtility(newState));
//				System.out.println("");
//			}
//
//		}

		public override int getMiniMaxValue(GameState state) 
		{
			//statesSeen = new ArrayList();
			//  System.out.println("In get Minimax Value");
			// System.out.println("Received state ");
			//((TicTacToeBoard)state.get("board")).print();
			//if (getPlayerToMove(state).equalsIgnoreCase("X")) 
			if (getPlayerToMove(state).ToUpper().Equals("X")) 
			{
				return maxValue(state);

			} 
			else 
			{
				return minValue(state);
			}
		}

		public override int getAlphaBetaValue(GameState state) 
		{
		
			if (getPlayerToMove(state).ToUpper().Equals("X")) 
			{
				AlphaBeta initial = new AlphaBeta(int.MinValue, int.MaxValue);
				int max = maxValue(state, initial);
				return max;

			} 
			else 
			{
				//invert?
				AlphaBeta initial = new AlphaBeta(int.MinValue, int.MaxValue);
				return minValue(state, initial);
			}
		}
	}
}
