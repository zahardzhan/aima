using System;
using System.Collections;
using aima.logic.propositional.parsing;
using aima.logic.propositional.parsing.ast;
using aima.util;

namespace aima.logic.propositional.algorithms
{
	/// <summary>
	/// Summary description for KnowledgeBase.
	/// </summary>
	public class KnowledgeBase 
	{
		private ArrayList sentences;

		private PEParser parser;

		public KnowledgeBase() 
		{
			sentences = new ArrayList();
			parser = new PEParser();
		}

		public void tell(string aSentence) 
		{
			Sentence sentence = (Sentence) parser.parse(aSentence);
			if (!(sentences.Contains(sentence))) 
			{
				sentences.Add(sentence);
			}
		}

		public void tellAll(String[] percepts) 
		{
			for (int i = 0; i < percepts.Length; i++) 
			{
				tell(percepts[i]);
			}

		}

		public int size() 
		{
			return sentences.Count;
		}

		public Sentence asSentence() 
		{
			return LogicUtils.chainWith("AND", sentences);
		}

//		public boolean askWithDpll(string queryString) 
//		{
//			Sentence query = null, cnfForm = null;
//			try 
//			{
//				//just a check to see that the query is well formed
//				query = (Sentence) parser.parse(queryString);
//			} 
//			catch (Exception e) 
//			{
//				//System.out.println("error parsing query" + e.getMessage());
//			}
//
//			Sentence kbSentence = asSentence();
//			Sentence kbPlusQuery = null;
//			if (kbSentence != null) 
//			{
//				kbPlusQuery = (Sentence) parser.parse(" ( " + kbSentence.toString()
//					+ " AND " + queryString + " )");
//			} 
//			else 
//			{
//				kbPlusQuery = query;
//			}
//			try 
//			{
//				cnfForm = new CNFTransformer().transform(kbPlusQuery);
//				//System.out.println(cnfForm.toString());
//			} 
//			catch (Exception e) 
//			{
//				//				System.out.println("error converting kb +  query to CNF"
//				//						   + e.getMessage());
//
//			}
//			return new DPLL().dpllSatisfiable(cnfForm);
//		}

		public bool askWithTTEntails(string queryString) 
		{

			return new TTEntails().ttEntails(this, queryString);
		}

		public override String ToString() 
		{
			if (sentences.Count == 0) 
			{
				return "";
			} 
			else
				return asSentence().ToString();
		}

		public ArrayList getSentences() 
		{
			return sentences;
		}
	}
}
