using System;
using aima.logic.propositional.parsing.ast;
using System.Collections;

namespace aima.util
{
	/// <summary>
	/// Summary description for LogicUtils.
	/// </summary>
	public class LogicUtils 
	{

		public static Sentence chainWith(string connector, ArrayList sentences) 
		{
			if (sentences.Count == 0) 
			{
				return null;
			} 
			else if (sentences.Count == 1) 
			{
				return (Sentence) sentences[0];
			} 
			else 
			{
				Sentence soFar = (Sentence) sentences[0];
				for (int i = 1; i < sentences.Count; i++) 
				{
					Sentence next = (Sentence) sentences[i];
					soFar = new BinarySentence(connector, soFar, next);
				}
				return soFar;
			}
		}
		//
		//		public static Sentence reorderCNFTransform(Set<Symbol> positiveSymbols,
		//		Set<Symbol> negativeSymbols) 
		//	{
		//		List<Symbol> plusList = new Converter<Symbol>().setToList(positiveSymbols);
		//		List<Symbol> minusList = new Converter<Symbol>().setToList(negativeSymbols);
		//		Collections.sort(plusList, new SymbolComparator());
		//		Collections.sort(minusList, new SymbolComparator());
		//
		//		List<Sentence> sentences = new ArrayList<Sentence>();
		//		for (int i = 0; i < positiveSymbols.size(); i++) 
		//	{
		//		sentences.add(plusList.get(i));
		//	}
		//	for (int i = 0; i < negativeSymbols.size(); i++) 
		//{
		//	sentences.add(new UnarySentence((Symbol) minusList.get(i)));
		//}
		//	if (sentences.size() == 0) 
		//{
		//	return new Symbol("EMPTY_CLAUSE"); // == empty clause
		//} 
		//	else 
		//{
		//	return LogicUtils.chainWith("OR", sentences);
		//}
		//}
		//	
		//public static Set<Variable> stringsToVariables(Set<String> strings)
		//{
		//Set<Variable> vars =  new HashSet<Variable>();
		//for(String str :strings)
		//{
		//vars.add(new Variable(str));
		//}
		//return vars;
		//}

	}
}
