using System;

namespace aima.logic.propositional.parsing.ast
{
	/// <summary>
	/// Summary description for BinarySentence.
	/// </summary>
	public class BinarySentence : ComplexSentence 
	{
		private string oper;

		private Sentence first;

		private Sentence second;

		public BinarySentence(string oper, Sentence first, Sentence second) 
		{
			this.oper = oper;
			this.first = first;
			this.second = second;

		}

		public Sentence getFirst() 
		{
			return first;
		}

		public String getOperator() 
		{
			return oper;
		}

		public Sentence getSecond() 
		{
			return second;
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
			BinarySentence bs = (BinarySentence) o;
			return ((bs.getOperator().Equals(getOperator()))
				&& (bs.getFirst().Equals(first)) && (bs.getSecond()
				.Equals(second)));

		}
		public override int GetHashCode()
		{
			int result = 17;
			result = 37 * result + first.GetHashCode();
			result = 37 * result + second.GetHashCode();
			return result; 
		}

		public override string ToString() 
		{
			return " ( " + first.ToString() + " " + oper + " "
				+ second.ToString() + " )";
		}

		public override Object accept(PLVisitor plv, Object arg) 
		{
			return plv.visitBinarySentence(this, arg);
		}

		public bool isOrSentence() 
		{
			return (getOperator().Equals("OR"));
		}

		public bool isAndSentence() 
		{
			return (getOperator().Equals("AND"));
		}

		public bool isImplication() 
		{
			return (getOperator().Equals("=>"));
		}

		public bool isBiconditional() 
		{
			return (getOperator().Equals("<=>"));
		}

		public bool firstTermIsAndSentence() 
		{
			return (getFirst() is BinarySentence)
				&& (((BinarySentence) getFirst()).isAndSentence());
		}

		public bool secondTermIsAndSentence() 
		{
			return (getSecond() is BinarySentence)
				&& (((BinarySentence) getSecond()).isAndSentence());
		}
	}
}
