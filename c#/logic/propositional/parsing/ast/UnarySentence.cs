using System;

namespace aima.logic.propositional.parsing.ast
{
	/// <summary>
	/// Summary description for UnarySentence.
	/// </summary>
	public class UnarySentence : ComplexSentence 
	{
		private Sentence negated;

		public Sentence getNegated() 
		{
			return negated;
		}

		public UnarySentence(Sentence negated) 
		{
			this.negated = negated;
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
			UnarySentence ns = (UnarySentence) o;
			return (ns.negated.Equals(negated));

		}
	
		public override int GetHashCode()
		{
			int result = 17;
			result = 37 * result + negated.GetHashCode();
			return result; 
		}

		public override string ToString() 
		{
			return " ( NOT " + negated.ToString() + " ) ";
		}

		public override Object accept(PLVisitor plv, Object arg) 
		{
			return plv.visitNotSentence(this, arg);
		}
	}
}
