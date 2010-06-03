using System;

namespace aima.logic.propositional.parsing.ast
{
	/// <summary>
	/// Summary description for Symbol.
	/// </summary>
	public class Symbol : AtomicSentence 
	{
		private string value;

		public Symbol(String value) 
		{
			this.value = value;
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
			Symbol sym = (Symbol) o;
			return (sym.getValue().Equals(getValue()));

		}
		public override int GetHashCode()
		{
			int result = 17;
			result = 37 * result + value.GetHashCode();
			return result; 
		}


		public string getValue() 
		{
			return value;
		}

		public override string ToString() 
		{
			return getValue();
		}

		public override Object accept(PLVisitor plv, Object arg) 
		{
			return plv.visitSymbol(this, arg);
		}

	}
}
