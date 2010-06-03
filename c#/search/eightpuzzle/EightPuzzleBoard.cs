using System;
using System.Collections;
using aima.basic;

namespace aima.search.eightpuzzle
{
	/// <summary>
	/// Summary description for EightPuzzleBoard.
	/// </summary>
	public class EightPuzzleBoard 
	{

		public static string LEFT = "Left";

		public static string RIGHT = "Right";

		public static string UP = "Up";

		public static string DOWN = "Down";

		public int[] getBoard() 
		{
			return board;
		}

		int[] board;

		public EightPuzzleBoard() 
		{
			board = new int[] { 5, 4, 0, 6, 1, 8, 7, 3, 2 };

		}

		public EightPuzzleBoard(int[] aBoard) 
		{
			board = aBoard;
		}

		private int[] xycoordinatesFromAbsoluteCoordinate(int x) 
		{
			int[] retVal = null;
			switch (x) 
			{
				case 0:
					retVal = new int[] { 0, 0 };
					break;
				case 1:
					retVal = new int[] { 0, 1 };
					break;
				case 2:
					retVal = new int[] { 0, 2 };
					break;
				case 3:
					retVal = new int[] { 1, 0 };
					break;
				case 4:
					retVal = new int[] { 1, 1 };
					break;
				case 5:
					retVal = new int[] { 1, 2 };
					break;
				case 6:
					retVal = new int[] { 2, 0 };
					break;
				case 7:
					retVal = new int[] { 2, 1 };
					break;
				case 8:
					retVal = new int[] { 2, 2 };
					break;

			}
			return retVal;
		}

		private int absoluteCoordinatesFromXYCoordinates(int x, int y) 
		{
			return x * 3 + y;
		}

		private int getValueAt(int x, int y) 
		{
			//refactor this use either case or a div/mod soln
			return board[absoluteCoordinatesFromXYCoordinates(x, y)];
		}

		private int getGapPosition() 
		{

			return getPositionOf(0);
		}

		private int getPositionOf(int val) 
		{
			int retVal = -1;
			for (int i = 0; i < 9; i++) 
			{
				if (board[i] == val) 
				{
					retVal = i;
				}
			}
			return retVal;
		}

		public XYLocation getLocationOf(int val) 
		{
			int abspos = getPositionOf(val);
			int xpos = xycoordinatesFromAbsoluteCoordinate(abspos)[0];
			int ypos = xycoordinatesFromAbsoluteCoordinate(abspos)[1];
			return new XYLocation(xpos, ypos);
		}

		private void setValue(int xPos, int yPos, int val) 
		{
			int abscoord = absoluteCoordinatesFromXYCoordinates(xPos, yPos);
			board[abscoord] = val;

		}

		public int getValueAt(XYLocation loc) 
		{
			return getValueAt(loc.getXCoOrdinate(), loc.getYCoOrdinate());
		}

		public void moveGapRight() 
		{
			int gapPosition = getGapPosition();
			int xpos = xycoordinatesFromAbsoluteCoordinate(gapPosition)[0];
			int ypos = xycoordinatesFromAbsoluteCoordinate(gapPosition)[1];
			if (!(ypos == 2)) 
			{
				int valueOnRight = getValueAt(xpos, ypos + 1);
				setValue(xpos, ypos, valueOnRight);
				setValue(xpos, ypos + 1, 0);
			}

		}

		public void moveGapLeft() 
		{
			int gapPosition = getGapPosition();
			int xpos = xycoordinatesFromAbsoluteCoordinate(gapPosition)[0];
			int ypos = xycoordinatesFromAbsoluteCoordinate(getGapPosition())[1];
			if (!(ypos == 0)) 
			{
				int valueOnLeft = getValueAt(xpos, ypos - 1);
				setValue(xpos, ypos, valueOnLeft);
				setValue(xpos, ypos - 1, 0);
			}

		}

		public void moveGapDown() 
		{
			int gapPosition = getGapPosition();
			int xpos = xycoordinatesFromAbsoluteCoordinate(gapPosition)[0];
			int ypos = xycoordinatesFromAbsoluteCoordinate(gapPosition)[1];
			if (!(xpos == 2)) 
			{
				int valueOnBottom = getValueAt(xpos + 1, ypos);
				setValue(xpos, ypos, valueOnBottom);
				setValue(xpos + 1, ypos, 0);
			}

		}

		public void moveGapUp() 
		{
			int gapPosition = getGapPosition();
			int xpos = xycoordinatesFromAbsoluteCoordinate(gapPosition)[0];
			int ypos = xycoordinatesFromAbsoluteCoordinate(gapPosition)[1];
			if (!(xpos == 0)) 
			{
				int valueOnTop = getValueAt(xpos - 1, ypos);
				setValue(xpos, ypos, valueOnTop);
				setValue(xpos - 1, ypos, 0);
			}

		}

		public override bool Equals(Object o) 
		{

			if( this == o ) 
			{
				return true;
			}
			if((o == null) || (this.GetType() != o.GetType()))
			{
				return false;
			}
			EightPuzzleBoard aBoard = (EightPuzzleBoard) o;

			for (int i = 0; i < 8; i++) 
			{
				if (this.getPositionOf(i) != aBoard.getPositionOf(i)) 
				{
					return false;
				}
			}
			return true;
		}

		public override int GetHashCode() 
		{
			int result = 17;
			for (int i = 0; i < 8; i++) 
			{
				int position = this.getPositionOf(i);
				result = 37 * result+ position;
			}
			return result;  
		}

		public ArrayList getPositions() 
		{
			ArrayList retVal = new ArrayList();
			for (int i = 0; i < 9; i++) 
			{
				int[] res = xycoordinatesFromAbsoluteCoordinate(getPositionOf(i));
				XYLocation loc = new XYLocation(res[0], res[1]);
				retVal.Add(loc);

			}
			return retVal;
		}

		public void setBoard(ArrayList locs) 
		{

			int count = 0;

			for (int i = 0; i < locs.Count; i++) 
			{
				XYLocation loc = (XYLocation) locs[i];
				this.setValue(loc.getXCoOrdinate(), loc.getYCoOrdinate(), count);
				count = count + 1;
			}
		}

		public bool canMoveGap(string where) 
		{
			bool retVal = true;
			int absPos = getPositionOf(0);
			if (where.Equals(LEFT)) 
			{
				if ((absPos == 0) || (absPos == 3) || (absPos == 6)) 
				{
					retVal = false;
				}
			}
			if (where.Equals(RIGHT)) 
			{
				if ((absPos == 2) || (absPos == 5) || (absPos == 8)) 
				{
					retVal = false;
				}
			}
			if (where.Equals(UP)) 
			{
				if ((absPos == 0) || (absPos == 1) || (absPos == 2)) 
				{
					retVal = false;
				}
			}
			if (where.Equals(DOWN)) 
			{
				if ((absPos == 6) || (absPos == 7) || (absPos == 8)) 
				{
					retVal = false;
				}
			}

			return retVal;
		}

		public override string ToString() 
		{
			string retVal = board[0] + " " + board[1] + " " + board[2] + "\n"
				+ board[3] + " " + board[4] + " " + board[5] + " " + "\n"
				+ board[6] + " " + board[7] + " " + board[8];
			return retVal;
		}

	}
}
