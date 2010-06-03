using System;
using aima.basic;

namespace aima.util
{
	/// <summary>
	/// Summary description for Calculator.
	/// </summary>
	public class Calculator 
	{

		public static int calculateSquareOfDistanceBetweenLocations(
			XYLocation loc1, XYLocation loc2) 
		{
			int xdifference = loc1.getXCoOrdinate() - loc2.getXCoOrdinate();
			int ydifference = loc1.getYCoOrdinate() - loc2.getYCoOrdinate();
			return (xdifference * xdifference) + (ydifference * ydifference);

		}
	}
}
