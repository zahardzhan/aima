using System;
using aima.logic.common;

namespace aima.logic.propositional.parsing.ast
{
	/// <summary>
	/// Summary description for Sentence.
	/// </summary>
	public abstract class Sentence : ParseTreeNode 
	{

		public abstract Object accept(PLVisitor plv,Object arg);

	}
}
