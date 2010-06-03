using System;
using System.Collections;
using aima.games;
using aima.basic;


namespace HexapawnSample
{
	/// <summary>
	/// Summary description for Octapawn.
	/// </summary>
	public class Octapawn : Game 
	{
		public Octapawn() 
		{
			ArrayList moves = new ArrayList();
			//first, add all possible moves from the initial state
			//assume white goes first
			//store moves as gameboards
			OctapawnBoard board = new OctapawnBoard();
			moves = board.getSuccessorBoards("W");

			//all the moves from the current state
			initialState.put("moves", moves);
			//the player whose move it is
			initialState.put("player", "W");

			initialState.put("utility", 0);
			//the board
			initialState.put("board", board);
			//the number of moves that have been made so far
			initialState.put("level", 0);
			presentState = initialState;
		}

		public OctapawnBoard getBoard(GameState state) 
		{

			return (OctapawnBoard) state.get("board");
		}

		//get all possible successors from the current state
		public override ArrayList getSuccessorStates(GameState state) 
		{
			GameState temp = presentState;
			ArrayList retVal = new ArrayList();
			int parentLevel = getLevel(state);
			for (int i = 0; i < getMoves(state).Count; i++) 
			{
				//XYLocation loc = (XYLocation) getMoves(state)[i];
				//for each move, actually make the move
				OctapawnBoard move = (OctapawnBoard) getMoves(state)[i];

				GameState aState = makeMove(state, move);
				aState.put("moveMade", move);
				aState.put("level", parentLevel + 1);
				retVal.Add(aState);

			}
			presentState = temp;
			return retVal;
		}

		public override GameState makeMove(GameState state, Object o) 
		{

			GameState retVal = new GameState();
			//a move is the board itself
			OctapawnBoard move = ((OctapawnBoard)o).cloneBoard();

			//we need to:
			//find out whose move it is
			string playerToMove = getPlayerToMove(state);
			
			ArrayList newMoves;
			//set the player whose move is next
			if (playerToMove.Equals("W"))
			{
				retVal.put("player", "B");
				//add the new moves
				newMoves = move.getSuccessorBoards("B");
			}
			else
			{
				retVal.put("player", "W");
				//add the new moves
				newMoves = move.getSuccessorBoards("W");
			}

			retVal.put("moves", newMoves);
			retVal.put("board", move);
			retVal.put("utility",computeUtility(move,
				getPlayerToMove(getState())));
			retVal.put("level", getLevel(state) + 1);
			//if (newMoves.Count != 0)
			presentState = retVal;

			return retVal;
		}

		public override int computeUtility(GameState state) 
		{
			int utility = computeUtility((OctapawnBoard) state.get("board"),
				(getPlayerToMove(state)));
			return utility;
		}

		private int computeUtility(OctapawnBoard aBoard, string playerToMove) 
		{
			//int retVal = 0;
			if (aBoard.gameLost("W")) 
			{
				if (playerToMove.Equals("W"))
					return -1;
			}
			else if (aBoard.gameLost("B"))
			{
				if (playerToMove.Equals("B"))
					return 1;
			}
			return 0;
		}

		public override bool terminalTest(GameState state) 
		{
			OctapawnBoard board = (OctapawnBoard) state.get("board");
			//			bool line = board.lineThroughBoard();
			//			bool filled = board.getNumberOfMarkedPositions() == 9;
			//			return (line || filled);
			return (board.gameLost("B") || board.gameLost("W"));
		}


		public override int getMiniMaxValue(GameState state) 
		{
			//statesSeen = new ArrayList();
			//  System.out.println("In get Minimax Value");
			// System.out.println("Received state ");
			//((TicTacToeBoard)state.get("board")).print();
			//if (getPlayerToMove(state).equalsIgnoreCase("X")) 
			if (getPlayerToMove(state).ToUpper().Equals("W")) 
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
		
			if (getPlayerToMove(state).ToUpper().Equals("W")) 
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
