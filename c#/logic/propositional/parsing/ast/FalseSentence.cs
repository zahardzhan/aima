using System;

namespace aima.logic.propositional.parsing.ast
{
	/// <summary>
	/// Summary description for FalseSentence.
	/// </summary>
	public class FalseSentence : AtomicSentence 
	{
		public override string ToString() 
		{
			return "FALSE";
		}

		public override Object accept(PLVisitor plv,Object arg) 
		{
			return plv.visitFalseSentence(this,arg);
		}
	}
}
