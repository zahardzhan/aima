using System;
using System.Collections;
using aima.util;
using aima.logic.propositional.parsing;
using aima.logic.propositional.visitors;
using aima.logic.propositional.parsing.ast;

namespace aima.logic.propositional.algorithms
{
	/// <summary>
	/// Summary description for TTEntails.
	/// </summary>
	public class TTEntails 
	{
		public bool ttEntails(KnowledgeBase kb, string alpha) 
		{
			Sentence kbSentence = kb.asSentence();
			Sentence querySentence = (Sentence) new PEParser().parse(alpha);
			SymbolCollector collector = new SymbolCollector();
			Hashtable kbSymbols= collector.getSymbolsIn(kbSentence);
			Hashtable querySymbols= collector.getSymbolsIn(querySentence);
			Hashtable symbols = new SetOps().union(kbSymbols,querySymbols);
			ArrayList symbolList = new Converter().setToList(symbols);
			return ttCheckAll(kbSentence, querySentence, symbolList, new Model());
		}

		public bool ttCheckAll(Sentence kbSentence, Sentence querySentence,
			ArrayList symbols, Model model) 
		{
			if (symbols.Count == 0) 
			{
				if (model.isTrue(kbSentence)) 
				{
					//System.out.println("#");
					return model.isTrue(querySentence);
				} 
				else 
				{
					//System.out.println("0");
					return true;
				}
			} 
			else 
			{
				Symbol symbol = (Symbol)Util.first(symbols);
				ArrayList rest = Util.rest(symbols);

				Model trueModel = model.extend(new Symbol(symbol.getValue()), true);
				Model falseModel = model.extend(new Symbol(symbol.getValue()),
					false);
				return (ttCheckAll(kbSentence, querySentence, rest, trueModel) && (ttCheckAll(
					kbSentence, querySentence, rest, falseModel)));
			}
		}
	}
}
