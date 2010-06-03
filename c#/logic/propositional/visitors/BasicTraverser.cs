using System;
using System.Collections;
using aima.util;
using aima.logic.propositional.parsing.ast;
using aima.logic.propositional.parsing;

namespace aima.logic.propositional.visitors
{
	/// <summary>
	/// Summary description for BasicTraverser.
	/// </summary>
	public class BasicTraverser : PLVisitor 
	{

	
		public virtual Object visitSymbol(Symbol s, Object arg) 
		{
			return arg;
		}

	
		public virtual Object visitTrueSentence(TrueSentence ts, Object arg) 
		{
			return arg;
		}

	
		public virtual Object visitFalseSentence(FalseSentence fs, Object arg) 
		{
			return arg;
		}

	
		public virtual Object visitNotSentence(UnarySentence ns, Object arg) 
		{
			Hashtable s =(Hashtable)arg;
			return new SetOps().union(s,(Hashtable)ns.getNegated().accept(this,arg));
		}

	
		public virtual Object visitBinarySentence(BinarySentence bs, Object arg) 
		{
			Hashtable s =(Hashtable)arg;
			Hashtable termunion = new SetOps().union((Hashtable)bs.getFirst().accept(this,arg),(Hashtable)bs.getSecond().accept(this,arg));
			return new SetOps().union(s,termunion);
		}

	
		public virtual Object visitMultiSentence(MultiSentence fs, Object arg) 
		{
			throw new Exception("Can't handle MultiSentence");
		}

	}
}
