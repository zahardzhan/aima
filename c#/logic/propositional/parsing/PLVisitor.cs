using System;
using aima.logic.common;
using aima.logic.propositional.parsing.ast;

namespace aima.logic.propositional.parsing
{
	/// <summary>
	/// Summary description for PLVisitor.
	/// </summary>
	public interface PLVisitor : Visitor 
	{
		Object visitSymbol(Symbol s,Object arg);

		Object visitTrueSentence(TrueSentence ts,Object arg);

		Object visitFalseSentence(FalseSentence fs,Object arg);

		Object visitNotSentence(UnarySentence fs,Object arg);

		Object visitBinarySentence(BinarySentence fs,Object arg);

		Object visitMultiSentence(MultiSentence fs,Object arg);
	}
}
