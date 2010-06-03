using System;
using System.Collections;
using aima.util;

namespace aima.games
{
	/// <summary>
	/// Summary description for Game.
	/// </summary>
	public abstract class Game 
	{
		protected GameState initialState = new GameState();

		protected GameState presentState = new GameState();

		public int getLevel(GameState g) 
		{
			return (((int) g.get("level")));
		}

		protected int level;

		public ArrayList getMoves(GameState state) 
		{
			return (ArrayList) state.get("moves");
		}

		public string getPlayerToMove(GameState state) 
		{
			return state.get("player").ToString();
		}

		public int getUtility(GameState h) 
		{
			return ((int) h.get("utility"));
		}

		public GameState getState() 
		{
			return presentState;
		}

		public abstract int computeUtility(GameState state);

		public abstract bool terminalTest(GameState state);

		public int maxValue(GameState state) 
		{
			int v = int.MinValue;
			if (terminalTest(state)) 
			{
				return computeUtility(state);
			} 
			else 
			{
				ArrayList successorList = getSuccessorStates(state);
				for (int i = 0; i < successorList.Count; i++) 
				{
					GameState successor = (GameState) successorList[i];
					int minimumValueOfSuccessor = minValue(successor);
					if (minimumValueOfSuccessor > v) 
					{
						v = minimumValueOfSuccessor;
						state.put("next", successor);
					}
				}
				return v;
			}

		}

		public int minValue(GameState state) 
		{

			int v = int.MaxValue;

			if (terminalTest(state)) 
			{
				return computeUtility(state);

			} 
			else 
			{
				ArrayList successorList = getSuccessorStates(state);
				for (int i = 0; i < successorList.Count; i++) 
				{
					GameState successor = (GameState) successorList[i];
					int maximumValueOfSuccessors = maxValue(successor);
					if (maximumValueOfSuccessors < v) 
					{
						v = maximumValueOfSuccessors;
						state.put("next", successor);
					}
				}
				return v;
			}

		}

		protected int maxValue(GameState state, AlphaBeta ab) 
		{
			int v = int.MinValue;
			if (terminalTest(state)) 
			{
				return computeUtility(state);
			} 
			else 
			{
				ArrayList successorList = getSuccessorStates(state);
				for (int i = 0; i < successorList.Count; i++) 
				{
					GameState successor = (GameState) successorList[i];
					int minimumValueOfSuccessor = minValue(successor, ab.copy());
					if (minimumValueOfSuccessor > v) 
					{
						v = minimumValueOfSuccessor;
						state.put("next", successor);
					}
					if (v >= ab.beta()) 
					{
						//System.out.println("pruning from max");
						return v;
					}
					//ab.setAlpha(Util.max(ab.alpha(), v));
					ab.setAlpha(System.Math.Max(ab.alpha(),v));
				}
				return v;
			}

		}

		public int minValue(GameState state, AlphaBeta ab) 
		{
			int v = int.MaxValue;

			if (terminalTest(state)) 
			{
				return (computeUtility(state));

			} 
			else 
			{
				ArrayList successorList = getSuccessorStates(state);
				for (int i = 0; i < successorList.Count; i++) 
				{
					GameState successor = (GameState) successorList[i];
					int maximumValueOfSuccessor = maxValue(successor, ab.copy());
					if (maximumValueOfSuccessor < v) 
					{
						v = maximumValueOfSuccessor;
						state.put("next", successor);
					}
					if (v <= ab.alpha()) 
					{
						//System.out.println("pruning from min");
						return v;
					}
					//ab.setBeta(Util.min(ab.beta(), v));
					ab.setBeta(System.Math.Min(ab.beta(),v));

				}
				return v;
			}

		}

		public void makeMiniMaxMove() 
		{
			getMiniMaxValue(presentState);
			GameState nextState = (GameState) presentState.get("next");
			if (nextState == null) 
			{
				throw new Exception("Mini Max Move failed");

			}
			makeMove(presentState, nextState.get("moveMade"));

		}

		public void makeAlphaBetaMove() 
		{
			
			getAlphaBetaValue(presentState);
		
			GameState nextState = (GameState) presentState.get("next");
			if (nextState == null) 
			{
				throw new Exception("Alpha Beta Move failed");
			}
			makeMove(presentState, nextState.get("moveMade"));

		}

		public abstract ArrayList getSuccessorStates(GameState state);

		public abstract GameState makeMove(GameState state, Object o);

		public bool hasEnded() 
		{
			return (terminalTest(getState()));
		}

		public Game() 
		{
		}

		public abstract int getMiniMaxValue(GameState state);

		public abstract int getAlphaBetaValue(GameState state);
	}
}
