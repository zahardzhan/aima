using System;
using aima.logic.common;
using aima.logic.propositional.parsing.ast;
using System.Collections;

namespace aima.logic.propositional.parsing
{
	/// <summary>
	/// Summary description for PEParser.
	/// </summary>
	public class PEParser : Parser 
	{

		public PEParser() 
		{
			lookAheadBuffer = new Token[_lookAhead];
		}

		public override ParseTreeNode parse(string inputString) 
		{
			lexer = new PELexer(inputString);
			fillLookAheadBuffer();
			return parseSentence();
		}

		private TrueSentence parseTrue() 
		{

			consume();
			return new TrueSentence();

		}

		private FalseSentence parseFalse() 
		{
			consume();
			return new FalseSentence();

		}

		private Symbol parseSymbol() 
		{
			string sym = lookAhead(1).getText();
			consume();
			return new Symbol(sym);
		}

		private AtomicSentence parseAtomicSentence() 
		{
			Token t = lookAhead(1);
			if (t.getType() == LogicTokenTypes.TRUE) 
			{
				return parseTrue();
			} 
			else if (t.getType() == LogicTokenTypes.FALSE) 
			{
				return parseFalse();
			} 
			else if (t.getType() == LogicTokenTypes.SYMBOL) 
			{
				return parseSymbol();
			} 
			else 
			{
				throw new Exception(
					"Error in parseAtomicSentence with Token " + lookAhead(1));
			}
		}

		private UnarySentence parseNotSentence() 
		{
			match("NOT");
			Sentence sen = parseSentence();
			return new UnarySentence(sen);
		}

		private MultiSentence parseMultiSentence() 
		{
			consume();
			string connector = lookAhead(1).getText();
			consume();
			ArrayList sentences = new ArrayList();
			while (lookAhead(1).getType() != LogicTokenTypes.RPAREN) 
			{
				Sentence sen = parseSentence();
				//consume();
				sentences.Add(sen);
			}
			match(")");
			return new MultiSentence(connector, sentences);
		}

		private Sentence parseSentence() 
		{
			if (detectAtomicSentence()) 
			{
				return parseAtomicSentence();
			} 
			else if (detectBracket()) 
			{
				return parseBracketedSentence();
			} 
			else if (detectNOT()) 
			{
				return parseNotSentence();
			} 
			else 
			{

				throw new Exception("Parser Error Token = " + lookAhead(1));
			}
		}

		private bool detectNOT() 
		{
			return (lookAhead(1).getType() == LogicTokenTypes.CONNECTOR)
				&& (lookAhead(1).getText().Equals("NOT"));
		}

		private Sentence parseBracketedSentence() 
		{

			if (detectMultiOperator()) 
			{
				return parseMultiSentence();
			} 
			else 
			{
				match("(");
				Sentence one = parseSentence();
				if (lookAhead(1).getType() == LogicTokenTypes.RPAREN) 
				{
					match(")");
					return one;
				} 
				else if ((lookAhead(1).getType() == LogicTokenTypes.CONNECTOR)
					&& (!(lookAhead(1).getText().Equals("Not")))) 
				{
					String connector = lookAhead(1).getText();
					consume(); //connector
					Sentence two = parseSentence();
					match(")");
					return new BinarySentence(connector, one, two);
				}

			}
			throw new Exception(
				" Runtime Exception at Bracketed Expression with token "
				+ lookAhead(1));
		}

		private bool detectMultiOperator() 
		{
			return (lookAhead(1).getType() == LogicTokenTypes.LPAREN)
				&& ((lookAhead(2).getText().Equals("AND")) || (lookAhead(2)
				.getText().Equals("OR")));
		}

		private bool detectBracket() 
		{
			return lookAhead(1).getType() == LogicTokenTypes.LPAREN;
		}

		private bool detectAtomicSentence() 
		{
			int type = lookAhead(1).getType();
			return (type == LogicTokenTypes.TRUE)
				|| (type == LogicTokenTypes.FALSE)
				|| (type == LogicTokenTypes.SYMBOL);
		}
	}
}
