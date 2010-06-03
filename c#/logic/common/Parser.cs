using System;

namespace aima.logic.common
{
	/// <summary>
	/// Summary description for Parser.
	/// </summary>
	public abstract class Parser 
	{

		protected Lexer lexer;

		protected Token[] lookAheadBuffer;

		protected int _lookAhead = 3;

		protected void fillLookAheadBuffer() 
		{
			for (int i = 0; i < _lookAhead; i++) 
			{
				lookAheadBuffer[i] = lexer.nextToken();
			}
		}

		protected Token lookAhead(int i) 
		{
			return lookAheadBuffer[i - 1];
		}

		protected void consume() 
		{
			loadNextTokenFromInput();
		}

		protected void loadNextTokenFromInput() 
		{

			bool eoiEncountered = false;
			for (int i = 0; i < _lookAhead - 1; i++) 
			{

				lookAheadBuffer[i] = lookAheadBuffer[i + 1];
				if (isEndOfInput(lookAheadBuffer[i])) 
				{
					eoiEncountered = true;
					break;
				}
			}
			if (!eoiEncountered) 
			{
				try 
				{
					lookAheadBuffer[_lookAhead - 1] = lexer.nextToken();
				} 
				catch (Exception e) 
				{
					//e.printStackTrace();
				}
			}

		}

		protected bool isEndOfInput(Token t) 
		{
			return (t.getType() == LogicTokenTypes.EOI);
		}

		protected void match(String terminalSymbol) 
		{
			if (lookAhead(1).getText().Equals(terminalSymbol)) 
			{
				consume();
			} 
			else 
			{
				throw new Exception(
					"Syntax error detected at match. Expected "
					+ terminalSymbol + " but got "
					+ lookAhead(1).getText());
			}

		}

		public abstract ParseTreeNode parse(string input);

	}
}
