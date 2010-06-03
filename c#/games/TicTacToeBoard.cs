using System;
using System.Collections;
using System.Text;
using aima.basic;

namespace aima.games
{
	/// <summary>
	/// Summary description for TicTacToeBoard.
	/// </summary>
	public class TicTacToeBoard 
	{
		private static string O = "O";

		private static string X = "X";

		string[] topRow = { " ", " ", " " };

		string[] midRow = { " ", " ", " " };

		string[] bottomRow = { " ", " ", " " };

		private string[] whichRow(int rowNumber) 
		{
			string[] _whichRow = null;
			if (rowNumber == 0) 
			{
				_whichRow = topRow;
			} 
			else if (rowNumber == 1) 
			{
				_whichRow = midRow;
			} 
			else if (rowNumber == 2) 
			{
				_whichRow = bottomRow;
			}
			return _whichRow;

		}

		public bool isEmpty(int row, int col) 
		{
			string[] _whichRow = whichRow(row);

			return (_whichRow[col] == " ");
		}

		public void markX(int row, int col) 
		{
			mark(row, col, X);
		}

		public void markO(int row, int col) 
		{
			mark(row, col, O);
		}

		public void mark(int row, int col, string symbol) 
		{
			String[] _whichRow = null;
			_whichRow = whichRow(row);

			_whichRow[col] = symbol;
		}

		public bool isAnyRowComplete() 
		{
			bool retVal = false;
			for (int i = 0; i < 3; i++) 
			{
				string[] _whichRow = whichRow(i);
				if ((_whichRow[0] != " ") && (_whichRow[0] == _whichRow[1])
					&& (_whichRow[1] == _whichRow[2])) 
				{
					retVal = true;
					break;
				}
			}
			return retVal;
		}

		public bool isAnyColumnComplete() 
		{
			bool retVal = false;
			for (int i = 0; i < 3; i++) 
			{

				if ((topRow[i] != " ") && (topRow[i] == midRow[i])
					&& (midRow[i] == bottomRow[i])) 
				{
					retVal = true;
					break;
				}
			}
			return retVal;
		}

		public bool isAnyDiagonalComplete() 
		{
			bool retVal = false;
			//check diagonal 1
			if ((topRow[0] != " ") && (topRow[0] == midRow[1])
				&& (midRow[1] == bottomRow[2])) 
			{
				retVal = true;
			} 
			else if ((topRow[2] != " ") && (topRow[2] == midRow[1])
				&& (midRow[1] == bottomRow[0])) 
			{
				retVal = true;
			}

			return retVal;
		}

		public bool lineThroughBoard() 
		{
			return ((isAnyRowComplete()) || (isAnyColumnComplete()) || (isAnyDiagonalComplete()));
		}

		public string getValue(int row, int col) 
		{
			string[] _whichRow = whichRow(row);
			return _whichRow[col];
		}

		private void setValue(int row, int col, string val) 
		{
			string[] _whichRow = whichRow(row);
			_whichRow[col] = val;
		}

//		public void print() 
//		{
//			for (int i = 0; i < 3; i++) 
//			{
//				for (int j = 0; j < 3; j++) 
//				{
//					string value = getValue(i, j);
//					string printValue;
//					if (value == " ") 
//					{
//						printValue = "-";
//					} 
//					else 
//					{
//						printValue = value;
//					}
//					//System.out.print(printValue + " ");
//				}
//				//System.out.println();
//			}
//		}

		public override string ToString() 
		{
			//StringBuffer buf = new StringBuffer();
			StringBuilder buf = new StringBuilder();
			
			for (int i = 0; i < 3; i++) 
			{
				for (int j = 0; j < 3; j++) 
				{
					String value = getValue(i, j);
					String printValue;
					if (value == " ") 
					{
						printValue = "-";
					} 
					else 
					{
						printValue = value;
					}
					//buf.append(printValue + " ");
					buf.Append(printValue + " ");
				}
				buf.Append(System.Environment.NewLine);
			}
			return buf.ToString();
		}

		public TicTacToeBoard cloneBoard() 
		{
			return (TicTacToeBoard) clone();
		}

		public Object clone() 
		{
			TicTacToeBoard newBoard = new TicTacToeBoard();
			for (int i = 0; i < 3; i++) 
			{
				for (int j = 0; j < 3; j++) 
				{
					String s = getValue(i, j);
					newBoard.setValue(i, j, s);
				}
			}
			return newBoard;
		}

		public int getNumberOfMarkedPositions() 
		{
			int retVal = 0;
			for (int i = 0; i < 3; i++) 
			{
				for (int j = 0; j < 3; j++) 
				{
					if (!(isEmpty(i, j))) 
					{
						retVal++;
					}
				}

			}
			return retVal;
		}

		
		public override int GetHashCode()
		{
			return base.GetHashCode ();
		}

		public override bool Equals(Object anObj) 
		{
			bool retVal = true;
			TicTacToeBoard anotherBoard = (TicTacToeBoard) anObj;
			bool secondBreak = false;
			for (int i = 0; i < 3; i++) 
			{
				for (int j = 0; j < 3; j++) 
				{
					if (anotherBoard.getValue(i, j) != getValue(i, j)) 
					{
						retVal = false;
						secondBreak = true;
						break;
					}

				}
				if (secondBreak == false) 
				{
					break;
				}

			}
			return retVal;
		}

		public bool isMarked(string str, int i, int j) 
		{
			return getValue(i, j).Equals(str);
		}
	}
}
