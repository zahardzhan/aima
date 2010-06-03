using System;
using System.Collections;
using System.Text;
using aima.basic;

namespace HexapawnSample
{
	/// <summary>
	/// Summary description for HexapawnBoard.
	/// </summary>
	public class HexapawnBoard
	{
		private static string B = "B";

		private static string W = "W";

		private int boardSize = 3;

		string[] topRow = { "B", "B", "B" };

		string[] midRow = { " ", " ", " " };

		string[] bottomRow = { "W", "W", "W" };

		public HexapawnBoard()
		{
			//
			// TODO: Add constructor logic here
			//
		}
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
		private bool isEmpty(XYLocation loc)
		{
			string[] _whichRow = whichRow(loc.getYCoOrdinate());

			return (_whichRow[loc.getXCoOrdinate()] == " ");
		}
		private bool isEmpty(int row, int col) 
		{
			string[] _whichRow = whichRow(row);

			return (_whichRow[col] == " ");
		}
		private bool isPlayer(string whichPlayer, XYLocation loc) 
		{
			string[] _whichRow = whichRow(loc.getYCoOrdinate());

			return (_whichRow[loc.getXCoOrdinate()].Equals(whichPlayer));
		}
		private bool isPlayer(string whichPlayer, int row, int col) 
		{
			string[] _whichRow = whichRow(row);

			return (_whichRow[col].Equals(whichPlayer));
		}
		private string whichPlayer(XYLocation loc)
		{
			string[] _whichRow = whichRow(loc.getYCoOrdinate());

			return (_whichRow[loc.getXCoOrdinate()]);
		}
		public void movePiece(XYLocation from, XYLocation to)
		{
			mark(to,whichPlayer(from));
			mark(from," ");
		}
//		public void markB(int row, int col) 
//		{
//			mark(row, col, B);
//		}
//
//		public void markW(int row, int col) 
//		{
//			mark(row, col, W);
//		}

		public void mark(XYLocation loc, string symbol) 
		{
			string[] _whichRow = null;
			_whichRow = whichRow(loc.getYCoOrdinate());

			_whichRow[loc.getXCoOrdinate()] = symbol;
		}

		public bool gameLost(string whoseMove)
		{
			if (whoseMove.Equals(B))
			{
				//check if top row has a white piece
				for (int col = 0; col < 3; col++) 
				{
					string[] _whichRow = whichRow(0);
					if ((_whichRow[col].Equals(W))) 
					{
						return true;
					}
				}
				//check if black can't move
				bool blackHasMoves = false;
				ArrayList blackPieces = this.getPieces(B);
				foreach (XYLocation loc in blackPieces)
				{
					ArrayList moves = this.getMoves(loc);
					if (moves.Count > 0)
					{
						blackHasMoves = true;
						break;
					}
				}
				return !blackHasMoves;
			}
			else
			{
				//check if bottom row has a black piece
				for (int i = 0; i < 3; i++) 
				{
					string[] _whichRow = whichRow(2);
					if ((_whichRow[i].Equals(B))) 
					{
						return true;
					}
				}
				//check if white can't move
				bool whiteHasMoves = false;
				ArrayList whitePieces = this.getPieces(W);
				foreach (XYLocation loc in whitePieces)
				{
					ArrayList moves = this.getMoves(loc);
					if (moves.Count > 0)
					{
						whiteHasMoves = true;
						break;
					}
				}
				return !whiteHasMoves;
			}
			
		}

		private string getValue(int row, int col) 
		{
			string[] _whichRow = whichRow(row);
			return _whichRow[col];
		}

		private void setValue(int row, int col, string val) 
		{
			string[] _whichRow = whichRow(row);
			_whichRow[col] = val;
		}

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

		public HexapawnBoard cloneBoard() 
		{
			return (HexapawnBoard) clone();
		}

		public Object clone() 
		{
			HexapawnBoard newBoard = new HexapawnBoard();
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

		private ArrayList getPieces(string forPlayer) 
		{
			ArrayList retVal = new ArrayList();
				for (int row = 0; row < 3; row++) 
				{
					for (int col = 0; col < 3; col++) 
					{
						if (this.isPlayer(forPlayer, row, col)) 
						{
							retVal.Add(new XYLocation(col, row));
						}
					}

				}
			return retVal;
		}
		private bool isLegalPlace(XYLocation forPlace) 
		{
			if (forPlace.getXCoOrdinate() >= 0 && forPlace.getXCoOrdinate() < this.boardSize && forPlace.getYCoOrdinate() >= 0 && forPlace.getYCoOrdinate() < this.boardSize)
				return true;
			else return false;
		}
		public ArrayList getSuccessorBoards(string whoMoves)
		{
			ArrayList retVal = new ArrayList();
			if (whoMoves.Equals(W))
			{
				ArrayList whitePieces = this.getPieces(W);
				foreach (XYLocation fromloc in whitePieces)
				{
					ArrayList moves = this.getMoves(fromloc);
					foreach (XYLocation toloc in moves)
					{
						HexapawnBoard board = this.cloneBoard();
						board.movePiece(fromloc,toloc);
						retVal.Add(board);
					}
				}
			}
			else
			{
				ArrayList blackPieces = this.getPieces(B);
				foreach (XYLocation fromloc in blackPieces)
				{
					ArrayList moves = this.getMoves(fromloc);
					foreach (XYLocation toloc in moves)
					{
						HexapawnBoard board = this.cloneBoard();
						board.movePiece(fromloc,toloc);
						retVal.Add(board);
					}
				}
			}
			return retVal;
		}
		private ArrayList getMoves(XYLocation forPiece) 
		{
			ArrayList retVal = new ArrayList();

			if (this.isPlayer(B,forPiece))
			{
				//if the piece below is empty, add it
				if (this.isLegalPlace(forPiece.south()) && this.isEmpty(forPiece.south()))
					retVal.Add(forPiece.south());
				//if the south diagonals are white, add them
				if (this.isLegalPlace(forPiece.southwest()) && this.isPlayer(W,forPiece.southwest()))
					retVal.Add(forPiece.southwest());
				if (this.isLegalPlace(forPiece.southeast()) && this.isPlayer(W,forPiece.southeast()))
					retVal.Add(forPiece.southeast());
			}
			else
			{
				//if the piece above is empty, add it
				if (this.isLegalPlace(forPiece.north()) && this.isEmpty(forPiece.north()))
					retVal.Add(forPiece.north());
				//if the north diagonals are black, add them
				if (this.isLegalPlace(forPiece.northwest()) && this.isPlayer(B,forPiece.northwest()))
					retVal.Add(forPiece.northwest());
				if (this.isLegalPlace(forPiece.northeast()) && this.isPlayer(B,forPiece.northeast()))
					retVal.Add(forPiece.northeast());
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
			HexapawnBoard anotherBoard = (HexapawnBoard) anObj;
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
	}
}
