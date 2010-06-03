using System;

namespace aima.logic.propositional.parsing.ast
{
	/// <summary>
	/// Summary description for TrueSentence.
	/// </summary>
	public class TrueSentence : AtomicSentence 
	{

		public override string ToString() 
		{
			return "TRUE";
		}

		public override Object accept(PLVisitor plv,Object arg) 
		{
			return plv.visitTrueSentence(this,arg);
		}
	}
}
