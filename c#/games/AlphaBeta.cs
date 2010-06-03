using System;

namespace aima.games
{
	/// <summary>
	/// Summary description for AlphaBeta.
	/// </summary>
	public class AlphaBeta
	{
			private int _alpha;
			private int _beta;

			public AlphaBeta(int alpha,int beta)
			{
				this._alpha = alpha;
				this._beta = beta;
			}

			public int alpha() 
			{
				return _alpha;
			}

			public void setAlpha(int alpha) 
			{
				this._alpha = alpha;
			}

			public int beta() 
			{
				return _beta;
			}

			public void setBeta(int beta) 
			{
				this._beta = beta;
			}

			public AlphaBeta copy() 
			{
				return new AlphaBeta(_alpha,_beta);
			}
		}
	
}
