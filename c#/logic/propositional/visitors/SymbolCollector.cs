using System;
using System.Collections;
using aima.logic.propositional.parsing.ast;

namespace aima.logic.propositional.visitors
{
	/// <summary>
	/// Summary description for SymbolCollector.
	/// </summary>
	public class SymbolCollector : BasicTraverser 
	{
	
		public override Object visitSymbol(Symbol s, Object arg) 
		{
			Hashtable symbolsCollectedSoFar = (Hashtable)arg;
			symbolsCollectedSoFar.Add(new Symbol(s.getValue()),null);
			return symbolsCollectedSoFar;
		}

		public Hashtable getSymbolsIn(Sentence s)
		{
			if (s == null)
			{//empty knowledge bases  == null fix this later
				return new Hashtable();
			}
			object o = s.accept(this,new Hashtable());
			Hashtable h = (Hashtable)o;
			return (Hashtable)s.accept(this, new Hashtable());
		}
	
	}
}
