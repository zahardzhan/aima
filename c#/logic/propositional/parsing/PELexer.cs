using System;
using System.Collections;
using aima.logic.common;
using System.Text;

namespace aima.logic.propositional.parsing
{
	/// <summary>
	/// Summary description for PELexer.
	/// </summary>
	public class PELexer : Lexer 
	{

		Hashtable connectors;

		public PELexer() 
		{
			connectors = new Hashtable();
			
			connectors.Add("NOT",null);
			connectors.Add("AND",null);
			connectors.Add("OR",null);
			connectors.Add("=>",null);
			connectors.Add("<=>",null);
		}

		public PELexer(String inputString) : this()
		{
			//this();
			setInput(inputString);
		}

		public override Token nextToken() 
		{
//			Token result = null;
//			int tokenType;
//			string tokenContent;

			if (lookAhead(1) == '(') 
			{
				consume();
				return new Token(LogicTokenTypes.LPAREN, "(");

			} 
			else if (lookAhead(1) == ')') 
			{
				consume();
				return new Token(LogicTokenTypes.RPAREN, ")");
			} 
			else if (identifierDetected()) 
			{
				return symbol();

			} 
			//else if (Character.isWhitespace(lookAhead(1))) 
			else if (char.IsWhiteSpace(lookAhead(1))) 
			{
				consume();
				return nextToken();
				//return whiteSpace();
			} 
			else if (lookAhead(1) == (unchecked((char) -1)) )
			{
				return new Token(LogicTokenTypes.EOI, "EOI");
			} 
			else 
			{
//				throw new Exception("Lexing error on character "
//					+ lookAhead(0));//this itself throws an error!
				throw new Exception("Lexing error on character "
					+ lookAhead(1));
			}

		}
		private bool identifierDetected() 
		{
			
			return (char.IsLetterOrDigit((char)lookAheadBuffer[0])) || partOfConnector();
		}
//		private bool identifierDetected() 
//		{
//			
//			return (Character.isJavaIdentifierStart((char) lookAheadBuffer[0]))
//				|| partOfConnector();
//		}

		private bool partOfConnector() 
		{
			return (lookAhead(1) == '=') || (lookAhead(1) == '<')
				|| (lookAhead(1) == '>');
		}

		private Token symbol() 
		{
			StringBuilder sbuf = new StringBuilder();
			while ((char.IsLetterOrDigit(lookAhead(1)))
				|| (lookAhead(1) == '=') || (lookAhead(1) == '<')
				|| (lookAhead(1) == '>')) 
			{
				sbuf.Append(lookAhead(1));
				consume();
			}
			string symbol = sbuf.ToString();
			if (isConnector(symbol)) 
			{
				return new Token(LogicTokenTypes.CONNECTOR, sbuf.ToString());
			} 
			else if (symbol.ToLower().Equals("true")) 
			{
				return new Token(LogicTokenTypes.TRUE, "TRUE");
			} 
			else if (symbol.ToLower().Equals("false")) 
			{
				return new Token(LogicTokenTypes.FALSE, "FALSE");
			} 
			else 
			{
				return new Token(LogicTokenTypes.SYMBOL, sbuf.ToString());
			}

		}

		private Token connector() 
		{
			StringBuilder sbuf = new StringBuilder();
			while (char.IsLetterOrDigit(lookAhead(1))) 
			{
				sbuf.Append(lookAhead(1));
				consume();
			}
			return new Token(LogicTokenTypes.CONNECTOR, sbuf.ToString());
		}

		private Token whiteSpace() 
		{
			StringBuilder sbuf = new StringBuilder();
			while (char.IsWhiteSpace(lookAhead(1))) 
			{
				sbuf.Append(lookAhead(1));
				consume();
			}
			return new Token(LogicTokenTypes.WHITESPACE, sbuf.ToString());

		}

		private bool isConnector(string aSymbol) 
		{
			return (connectors.Contains(aSymbol));
		}

	}
}
