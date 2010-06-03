using System;
using System.Text;
using System.IO;



namespace aima.logic.common
{
	/// <summary>
	/// Summary description for Lexer.
	/// </summary>
	public abstract class Lexer 
	{
		public abstract Token nextToken();

		//protected Reader input;
		protected System.IO.TextReader input;

		protected int _lookAhead = 1;

		protected int[] lookAheadBuffer;

		public void setInput(string inputString) 
		{
			lookAheadBuffer = new int[_lookAhead];
			//this.input = new StringReader(inputString);
			this.input = new StringReader(inputString);
			fillLookAheadBuffer();
		}

		protected void fillLookAheadBuffer() 
		{
			try 
			{
				lookAheadBuffer[0] = (char) input.Read();
			} 
			catch (Exception e) 
			{
				//e.printStackTrace();
				
			}

		}

		protected char lookAhead(int position) 
		{
			return (char) lookAheadBuffer[position - 1];
		}

		protected bool isEndOfFile(int i) 
		{
			return (-1 == i);
		}

		protected void loadNextCharacterFromInput() 
		{

			bool eofEncountered = false;
			for (int i = 0; i < _lookAhead - 1; i++) 
			{

				lookAheadBuffer[i] = lookAheadBuffer[i + 1];
				if (isEndOfFile(lookAheadBuffer[i])) 
				{
					eofEncountered = true;
					break;
				}
			}
			if (!eofEncountered) 
			{
				try 
				{
					lookAheadBuffer[_lookAhead - 1] = input.Read();
				} 
				catch (Exception e) 
				{
					//e.printStackTrace();
				}
			}

		}

		protected void consume() 
		{
			loadNextCharacterFromInput();
		}

		public void clear() 
		{
			this.input = null;
			lookAheadBuffer = null;

		}

	}
}
