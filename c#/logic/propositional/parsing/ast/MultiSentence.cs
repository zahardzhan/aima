using System;
using System.Collections;

namespace aima.logic.propositional.parsing.ast
{
	/// <summary>
	/// Summary description for MultiSentence.
	/// </summary>
	public class MultiSentence : ComplexSentence 
	{
		private string oper;

		private ArrayList sentences;

		public MultiSentence(string oper, ArrayList sentences) 
		{
			this.oper = oper;
			this.sentences = sentences;
		}

		public string getOperator() 
		{
			return oper;
		}

		public ArrayList getSentences() 
		{
			return sentences;
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
			MultiSentence sen = (MultiSentence) o;
			return ((sen.getOperator().Equals(getOperator())) && (sen
				.getSentences().Equals(getSentences())));

		}
		public override int GetHashCode()
		{
			int result = 17;
			foreach (Sentence s in sentences)
			{
				result = 37 * result + s.GetHashCode();
			}
			return result;  
		}

		public override string ToString() 
		{
			String part1 = "( " + getOperator() + " ";
			for (int i = 0; i < getSentences().Count; i++) 
			{
				part1 = part1 + sentences[i].ToString() + " ";
			}
			return part1 + " ) ";
		}

		public override Object accept(PLVisitor plv, Object arg) 
		{
			return plv.visitMultiSentence(this, arg);
		}

	}
}
