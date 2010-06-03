using System;
using System.Collections;

namespace aima.search.csp
{
	/// <summary>
	/// Summary description for Assignment.
	/// </summary>
	public class Assignment 
	{
		Hashtable hash;

		ArrayList variables;

		public Assignment() : this(new ArrayList())
		{
			
		}

		public Assignment(ArrayList variables) 
		{
			hash = new Hashtable();
			this.variables = variables;
		}

		public void setAssignment(string variable, Object value) 
		{
			if (hash.ContainsKey(variable) == false)
				hash.Add(variable,value);
		}

		public Object getAssignment(string variable) 
		{
			return hash[variable];
		}

		public bool isComplete() 
		{

			return everyVariableIsAKeyAndHasAValue();
		}

		private bool everyVariableIsAKeyAndHasAValue() 
		{
			IEnumerator iter = variables.GetEnumerator();
			while (iter.MoveNext()) 
			{
				string variable = iter.Current.ToString();
				if (!hash.ContainsKey(variable))
				{
					return false;
				} 
				else 
				{
					if (hash[variable] == null) 
					{
						return false;
					}
				}
			}
			return true;
		}

		public void remove(string variable) 
		{
			if (hash.ContainsKey(variable))
			{
				hash.Remove(variable);
			}
		}

		public string selectFirstUnassignedVariable() 
		{
			//Iterator iter = variables.iterator();
			IEnumerator iter = variables.GetEnumerator();
			while (iter.MoveNext()) 
			{
				string variable = iter.Current.ToString();
				if (!hash.ContainsKey(variable))
				{
					return variable;
				}
			}
			return null;

		}

		public bool hasAssignmentFor(string variable) 
		{
			return hash.ContainsKey(variable);
		}

		public override string ToString() 
		{
			//return hash.ToString();
			//the intention is to output the key/value pairs of the
			//hashtable to a string
			string tmp = "";
			IEnumerator m = hash.Keys.GetEnumerator();
			while (m.MoveNext())
			{
				tmp += m.Current.ToString() + "=" + hash[m.Current].ToString() + " ";
			}
			return tmp.Trim();
		}

		public Assignment copy() 
		{
			Assignment _copy = new Assignment();
			for (int i = 0; i < variables.Count; i++) 
			{
				_copy.variables.Add(variables[i]);
			}
			//Iterator iter = hash.keySet().iterator();
			IEnumerator iter = hash.Keys.GetEnumerator();
			while (iter.MoveNext()) 
			{
				Object key = iter.Current;
				//copy.hash.put(key, hash.get(key));
				_copy.hash.Add(key,hash[key]);
			}
			return _copy;
		}

		public int getNumberOfConflictsFor(string conflictedVariable, Object value,
			Constraint constraint) 
		{
			Assignment duplicate = copy();
			duplicate.setAssignment(conflictedVariable, value);
			return duplicate.getConflictedVariables(constraint).Count;
		}

		public ArrayList getConflictedVariables(Constraint constraint) 
		{
			ArrayList conflictedVariables = new ArrayList();
			for (int j = 0; j < getVariables().Count; j++) 
			{
				string variable = getVariables()[j].ToString();
				Object value = getAssignment(variable);
				if (!(constraint.isSatisfiedWith(this, variable, value))) 
				{
					conflictedVariables.Add(variable);
				}
			}
			return conflictedVariables;
		}

		public Object getMinimumConflictingValueFor(string conflictedVariable,
			ArrayList domain, Constraint constraint) 
		{
			int minConflict = int.MaxValue;//an arbitrarily large number
			Object minConflictValue = null;

			for (int i = 0; i < domain.Count; i++) 
			{
				Object value = domain[i];
				if (getNumberOfConflictsFor(conflictedVariable, value, constraint) < minConflict) 
				{
					minConflict = getNumberOfConflictsFor(conflictedVariable,
						value, constraint);
					minConflictValue = value;
				}
			}
			return minConflictValue;
		}

		public bool satisfies(Constraint constraint) 
		{
			if (isComplete()) 
			{
				for (int j = 0; j < getVariables().Count; j++) 
				{
					string variable = getVariables()[j].ToString();
					Object value = getAssignment(variable);
					if (!(constraint.isSatisfiedWith(this, variable, value))) 
					{
						return false;
					}
				}
				return true;
			} 
			else 
			{
				return false;
			}
		}

		public ArrayList getVariables() 
		{
			return variables;
		}
	}
}
