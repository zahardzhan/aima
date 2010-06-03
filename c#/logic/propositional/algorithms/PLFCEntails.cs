using System;
using System.Collections;
using aima.logic.propositional.parsing.ast;
using aima.logic.propositional.visitors;
using aima.util;

namespace aima.logic.propositional.algorithms
{
	/// <summary>
	/// Summary description for PLFCEntails.
	/// </summary>
	public class PLFCEntails 
	{

		protected Hashtable _count;
		protected Hashtable _inferred;

		protected Stack _agenda;

		public PLFCEntails() 
		{
			
			_count = new Hashtable();
			_inferred = new Hashtable();
			_agenda = new Stack();
		}

		public bool plfcEntails(KnowledgeBase kb, string s) 
		{
			return plfcEntails(kb,new Symbol(s));
		}
		public bool plfcEntails(KnowledgeBase kb, Symbol q) 
		{
			ArrayList hornClauses = asHornClauses(kb.getSentences());
			while (_agenda.Count != 0) 
			{
				Symbol p = (Symbol) _agenda.Pop();
				while (!inferred(p)) 
				{
					if (_inferred.Contains(p))
						_inferred[p] = true;
					else
						_inferred.Add(p, true);

					for (int i = 0; i < hornClauses.Count; i++) 
					{
						HornClause hornClause = (HornClause) hornClauses[i];
						if (hornClause.premisesContainsSymbol(p)) 
						{
							decrementCount(hornClause);
							if (countisZero(hornClause)) 
							{
								if (hornClause.head().Equals(q)) 
								{
									return true;
								} 
								else 
								{
									_agenda.Push(hornClause.head());
								}
							}
						}
					}
				}
			}
			return false;
		}

		private ArrayList asHornClauses(ArrayList sentences) 
		{
			ArrayList hornClauses = new ArrayList();
			for (int i = 0; i < sentences.Count; i++) 
			{
				Sentence sentence = (Sentence) sentences[i];
				//TODO - don't know if i am supposed to pass in the agenda or stack
				//or whether the inner class is just supposed to create new ones
				//what does java do?
				HornClause clause = new HornClause(sentence, this._agenda,this._count, this._inferred);
				hornClauses.Add(clause);
			}
			return hornClauses;
		}

		private bool countisZero(HornClause hornClause) 
		{

			return (int.Parse(_count[hornClause].ToString()) == 0);
		}

		private void decrementCount(HornClause hornClause) 
		{
			int value = (int.Parse( _count[hornClause].ToString()));
			if (_count.Contains(hornClause))
				_count[hornClause] = value -1;
			else
				_count.Add(hornClause, value - 1);

		}

		private bool inferred(Symbol p) 
		{
			Object value = _inferred[p];
			return ((value == null) || value.Equals(true));
		}

		public class HornClause 
		{
			ArrayList premiseSymbols;

			Symbol _head;

			public HornClause(Sentence sentence, Stack _agenda, Hashtable _count, Hashtable _inferred) 
			{
				if (sentence is Symbol) 
				{
					_head = (Symbol) sentence;
					
					_agenda.Push(_head);
					premiseSymbols = new ArrayList();
					if (_count.Contains(this))
						_count[this] = 0;
					else
						_count.Add(this, 0);
					if (_inferred.Contains(_head))
						_inferred[_head] = false;
					else
						_inferred.Add(_head, false);
				} 
				else if (!isImpliedSentence(sentence)) 
				{
					throw new Exception("Sentence " + sentence
						+ " is not a horn clause");

				} 
				else 
				{
					BinarySentence bs = (BinarySentence) sentence;
					_head = (Symbol) bs.getSecond();
					if (_inferred.Contains(_head))
					{
						_inferred[_head] = false;
					}
					else
					{
						_inferred.Add(_head, false);
					}
					Hashtable symbolsInPremise = new SymbolCollector().getSymbolsIn(bs
						.getFirst());
//					Iterator iter = symbolsInPremise.iterator();
//					while (iter.hasNext()) 
					foreach (object iter in symbolsInPremise.Keys)
					{
						if (_inferred.Contains(iter))
							_inferred[iter] = false;
						else
							_inferred.Add(iter, false);
					}
					premiseSymbols = new Converter().setToList(symbolsInPremise);
					if (_count.Contains(this))
					{
						_count[this] = premiseSymbols.Count;
					}
					else
					{
						_count.Add(this, premiseSymbols.Count);
					}
				}

			}

			private bool isImpliedSentence(Sentence sentence) 
			{
				return ((sentence is BinarySentence) && ((BinarySentence) sentence)
					.getOperator().Equals("=>"));
			}

			public Symbol head() 
			{

				return _head;
			}

			public bool premisesContainsSymbol(Symbol q) 
			{
				return premiseSymbols.Contains(q);
			}

			public ArrayList getPremiseSymbols() 
			{
				return premiseSymbols;
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
				HornClause ohc = (HornClause) o;
				if (premiseSymbols.Count != ohc.premiseSymbols.Count)
				{
					return false;
				}
				//bool result = true;
				foreach (Symbol s in premiseSymbols)
				{
					if (!ohc.premiseSymbols.Contains(s))
					{
						return false;
					}
				}
			
				return true;

			}
		
		
			public override int GetHashCode() 
			{
				int result = 17;
				foreach (Symbol s in premiseSymbols)
				{
					result = 37 * result + s.GetHashCode();
				}
				return result;  
			}

			public override string ToString() 
			{
				return premiseSymbols.ToString() + " => " + _head;
			}
		}
	
	
	
	
	}
}
