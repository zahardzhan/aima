using System;

namespace aima.logic.common
{
	/// <summary>
	/// Summary description for LogicTokenTypes.
	/// </summary>
	public abstract class LogicTokenTypes 
	{
		public static  int SYMBOL = 1;

		public static  int LPAREN = 2;

		public static  int RPAREN = 3;

		public static  int COMMA = 4;

		public static  int CONNECTOR = 5;

		public static  int QUANTIFIER = 6;

		public static  int PREDICATE = 7;

		public static  int FUNCTION = 8;
		public static  int VARIABLE = 9;

		public static  int CONSTANT = 10;

		public static  int TRUE = 11;

		public static  int FALSE = 12;

		public static  int EQUALS = 13;

		public static  int WHITESPACE = 1000;

		public static  int EOI = 9999;

	}
}
