using System;
using System.Collections;
using aima.games;
using aima.basic;


namespace HexapawnSample
{
	/// <summary>
	/// Summary description for Decapawn.
	/// </summary>
	public class Decapawn : Game 
	{
		public long computeUtilityCalls = 0;
		public long computeUtilityCallsThisMove = 0;
		public long MaxMovesToConsider = 500000;
		public int MaxSearchDepth = 8;
		public bool UseBetterCompute = false;
		public string FirstPlayer = "W";
		public Decapawn() 
		{
			ArrayList moves = new ArrayList();
			//first, add all possible moves from the initial state
			//assume white goes first
			//store moves as gameboards
			DecapawnBoard board = new DecapawnBoard();
			moves = board.getSuccessorBoards(FirstPlayer);

			//all the moves from the current state
			initialState.put("moves", moves);
			//the player whose move it is
			initialState.put("player", FirstPlayer);

			initialState.put("utility", 0);
			//the board
			initialState.put("board", board);
			//the number of moves that have been made so far
			initialState.put("level", 0);
			presentState = initialState;
		}

		public DecapawnBoard getBoard(GameState state) 
		{

			return (DecapawnBoard) state.get("board");
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
				DecapawnBoard move = (DecapawnBoard) getMoves(state)[i];

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
			DecapawnBoard move = ((DecapawnBoard)o).cloneBoard();

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

			int parentLevel = getLevel(state);
//			if (parentLevel <= this.MaxSearchDepth && this.computeUtilityCallsThisMove < this.MaxMovesToConsider)
//			{
				retVal.put("moves", newMoves);
				retVal.put("utility",computeUtility(move,
					getPlayerToMove(getState())));
//			}
//			else
//			{
//				for (int i = 1; i < newMoves.Count; i++)
//				{
//					newMoves.RemoveAt(i);
//				}
//				
//				retVal.put("moves",newMoves);
//				retVal.put("utility",0);
//			}
			retVal.put("board", move);
			
			retVal.put("level", parentLevel + 1);
			//if (newMoves.Count != 0)
			presentState = retVal;

			return retVal;
		}

		public override int computeUtility(GameState state) 
		{
			computeUtilityCalls++;
			this.computeUtilityCallsThisMove++;

			if (this.UseBetterCompute)
			{
				int thisLevel = getLevel(state);
				int utility = computeUtilityBetter((DecapawnBoard) state.get("board"),
					(getPlayerToMove(state)),thisLevel);
				return utility;
			}
			else
			{
				int utility = computeUtility((DecapawnBoard) state.get("board"),
					(getPlayerToMove(state)));
				return utility;
			}
				

		}


		private int computeUtilityBetter(DecapawnBoard aBoard, string playerToMove,int thisLevel) 
		{
			//int thisLevel = getLevel(state);
			if (aBoard.gameLost("W")) 
			{
				if (playerToMove.Equals("W"))
					return -100/thisLevel;
			}
			else if (aBoard.gameLost("B"))
			{
				if (playerToMove.Equals("B"))
					return 100/thisLevel;
			}
			return 0;
		}

		private int computeUtility(DecapawnBoard aBoard, string playerToMove) 
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
			DecapawnBoard board = (DecapawnBoard) state.get("board");
			//			bool line = board.lineThroughBoard();
			//			bool filled = board.getNumberOfMarkedPositions() == 9;
			//			return (line || filled);
			int thisLevel = getLevel(state);
			bool bailOut = false;
			if (thisLevel >= this.MaxSearchDepth && this.computeUtilityCallsThisMove > this.MaxMovesToConsider)
				bailOut = true;
			return (board.gameLost("B") || board.gameLost("W") || bailOut);
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
			this.computeUtilityCallsThisMove = 0;
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
