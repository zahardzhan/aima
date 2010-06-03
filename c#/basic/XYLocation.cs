using System;

namespace aima.basic
{
	/// <summary>
	/// Summary description for XYLocation.
	/// </summary>
	public class XYLocation 
	{
		int xCoOrdinate, yCoOrdinate;

		public XYLocation(int x, int y) 
		{
			xCoOrdinate = x;
			yCoOrdinate = y;
		}

		public int getXCoOrdinate() 
		{
			return xCoOrdinate;
		}

		public override bool Equals(Object o) 
		{
			XYLocation anotherLoc = (XYLocation) o;
			return ((anotherLoc.getXCoOrdinate() == xCoOrdinate) && (anotherLoc
				.getYCoOrdinate() == yCoOrdinate));
		}

		public int getYCoOrdinate() 
		{
			return yCoOrdinate;
		}

		public XYLocation west() 
		{
			return new XYLocation(xCoOrdinate - 1, yCoOrdinate);
		}

		public XYLocation east() 
		{
			return new XYLocation(xCoOrdinate + 1, yCoOrdinate);
		}

		public XYLocation north() 
		{
			return new XYLocation(xCoOrdinate, yCoOrdinate - 1);
		}
		public XYLocation northwest() 
		{
			return new XYLocation(xCoOrdinate - 1, yCoOrdinate - 1);
		}
		public XYLocation northeast() 
		{
			return new XYLocation(xCoOrdinate + 1, yCoOrdinate - 1);
		}

		public XYLocation south() 
		{
			return new XYLocation(xCoOrdinate, yCoOrdinate + 1);
		}
		public XYLocation southwest() 
		{
			return new XYLocation(xCoOrdinate - 1, yCoOrdinate + 1);
		}
		public XYLocation southeast() 
		{
			return new XYLocation(xCoOrdinate + 1, yCoOrdinate + 1);
		}

		public XYLocation right() 
		{
			return east();
		}

		public XYLocation left() 
		{
			return west();
		}

		public XYLocation up() 
		{
			return north();
		}

		public XYLocation down() 
		{
			return south();
		}

		public XYLocation locationAt(String direction) 
		{
			if (direction.Equals("North")) 
			{
				return north();
			}
			if (direction.Equals("South")) 
			{
				return south();
			}
			if (direction.Equals("East")) 
			{
				return east();
			}
			if (direction.Equals("West")) 
			{
				return west();
			} 
			else 
			{
				throw new Exception("Unknown direction " + direction);
			}
		}

		public override string ToString() 
		{
			return " ( " + xCoOrdinate + " , " + yCoOrdinate + " ) ";
		}
	
		public override int GetHashCode()
		{
			int result = 17;
			result = 37 * result +  xCoOrdinate;
			result = result +  yCoOrdinate;
			return result;
		}

	}
}
