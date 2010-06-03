using System;
using System.Collections;
using aima.logic.propositional.parsing;
using aima.logic.propositional.parsing.ast;

namespace aima.logic.propositional.algorithms
{
	/// <summary>
	/// Summary description for Model.
	/// </summary>
	public class Model : PLVisitor 
	{

		Hashtable h = new Hashtable();

		public bool getStatus(Symbol symbol) 
		{
			Object status = h[symbol.getValue()];
			if (status != null) 
			{
				return (bool) status;
			}
			return false;//TODO: is this right?  it was null in the java source
		}
		public bool isTrue(Symbol symbol) 
		{
			Object status = h[symbol.getValue()];
			if (status != null) 
			{
				return ((Boolean) status);
			}
			return false;
		}
		public bool isFalse(Symbol symbol) 
		{
			Object status = h[symbol.getValue()];
			if (status != null) 
			{
				return !((bool) status);
			}
			return false;
		}

		private bool isUnknown(Symbol s) 
		{
			Object o = h[s.getValue()];
			return (o == null);

		}

		public Model extend(Symbol symbol, bool b) 
		{
			Model m = new Model();
			return extend(symbol.getValue(),b);
		}
		public Model extend(string s, bool b) 
		{
			Model m = new Model();
			//iterator i = this.h.keySet().iterator();
			//while (i.hasNext()) 
			foreach (string key in this.h.Keys)
			{
				//String key = i.next();
				bool value = (bool)h[key];
				string newKey = new string(((string) key).ToCharArray());
//				if (value == null) 
//				{
//					throw new Exception();
//				}
				m.h.Add(key, value);
			}
			m.h.Add(s, b);
			return m;
		}


		//		public void print() 
		//		{
		//			Iterator i = h.keySet().iterator();
		//			while (i.hasNext()) 
		//			{
		//				Object key = i.next();
		//				Object value = h.get(key);
		//				System.out.print(key + " = " + value + " ");
		//				//System.out.print (key +" = " +((Boolean)value).booleanValue());
		//			}
		//			System.out.println();
		//		}

		public bool isTrue(Sentence clause) 
		{		
			Object result = clause.accept(this,null);
			return (result == null) ? false : ((bool) result)==true;
		}
	
		public bool isFalse(Sentence clause) 
		{		
			Object o = clause.accept(this,null);
			return (o != null) ? ((bool) o)==false : false;
		}
	
		public bool isUnknown(Sentence clause) 
		{		//TODO TEST WELL
			Object o = clause.accept(this,null);
			return (o == null) ;
		}

		public Model flip(Symbol s) 
		{
			if (isTrue(s)) 
			{
				return extend(s, false);
			}
			if (isFalse(s)) 
			{
				return extend(s, true);
			}
			return this;
		}

		public override string ToString() 
		{
			return h.ToString();
		}



		// VISITOR METHODS
		public Object visitSymbol(Symbol s, Object arg) 
		{
			return getStatus(s);
		}

		public Object visitTrueSentence(TrueSentence ts, Object arg) 
		{
			return true;
		}

		public Object visitFalseSentence(FalseSentence fs, Object arg) 
		{
			return false;
		}

		public Object visitNotSentence(UnarySentence fs, Object arg) 
		{
			Object negatedValue = fs.getNegated().accept(this,null);
			if (negatedValue != null) 
			{
				return (!((bool) negatedValue));
			} 
			else 
			{
				return null;
			}
		}

		public Object visitBinarySentence(BinarySentence bs, Object arg) 
		{
			Object firstValue = bs.getFirst().accept(this,null);
			Object secondValue = bs.getSecond().accept(this,null);
			if ((firstValue == null) || (secondValue == null)) 
			{ //strictly not
				// true for or/and
				// -FIX later
				return null;
			} 
			else 
			{
				string oper = bs.getOperator();
				if (oper.Equals("AND")) 
				{
					return evaluateAnd((bool) firstValue, (bool) secondValue);
				}
				if (oper.Equals("OR")) 
				{
					return evaluateOr((bool) firstValue, (bool) secondValue);
				}
				if (oper.Equals("=>")) 
				{
					return evaluateImplied((bool) firstValue,
						(bool) secondValue);
				}
				if (oper.Equals("<=>")) 
				{
					return evaluateBiConditional((bool) firstValue,
						(bool) secondValue);
				}
				return null;
			}
		}

		public Object visitMultiSentence(MultiSentence fs, Object argd) 
		{
			// TODO remove this? 
			return null;
		}
	
	
		private bool evaluateAnd(bool firstValue, bool secondValue) 
		{
			if ((firstValue.Equals(true))
				&& (secondValue.Equals(true))) 
			{
				return true;
			} 
			else 
			{
				return false;
			}
		}

		private bool evaluateOr(bool firstValue, bool secondValue) 
		{
			if ((firstValue.Equals(true))
				|| (secondValue.Equals(true))) 
			{
				return true;
			} 
			else 
			{
				return false;
			}
		}

		private bool evaluateImplied(bool firstValue, bool secondValue) 
		{
			if ((firstValue.Equals(true))
				&& (secondValue.Equals(false))) 
			{
				return false;
			} 
			else 
			{
				return true;
			}
		}

		private bool evaluateBiConditional(bool firstValue, bool secondValue) 
		{
			if (firstValue.Equals(secondValue)) 
			{
				return true;
			} 
			else 
			{
				return false;
			}
		}
		public Hashtable getAssignedSymbols() 
		{
			Hashtable _set= new Hashtable();
			//Iterator i = this.h.keySet().iterator();
			//while (i.hasNext()) 
			foreach (string i in this.h.Keys)
			{
				Symbol key = new Symbol(i);
				if (!(isUnknown(key)))
				{
					_set.Add(key,null);
				}
			}
			return _set;
		}
		public bool matches(string variable, bool value) 
		{
			if (value)
			{
				return isTrue(new Symbol(variable));
			}
			else if (!(value))
			{
				return isFalse(new Symbol(variable));
			}
			return false;
		}

	}
}
