using System;
using System.Collections;

namespace aima.search.csp
{
	/// <summary>
	/// Summary description for Domain.
	/// </summary>
	public class Domain
	{
		private Hashtable hash;

		//a hash Of Lists { variable: ListOfDomainValues
		public Domain(ArrayList variables) 
		{
			this.hash = new Hashtable();
			IEnumerator varIter = variables.GetEnumerator();
			while (varIter.MoveNext()) 
			{
				hash.Add(varIter.Current, new ArrayList());
			}
		}

		public ArrayList getDomainOf(string variable) 
		{
			return (ArrayList) hash[variable];
		}

		public void addToDomain(string variable, Object value) 
		{
			ArrayList varDomains = (ArrayList) hash[variable];

			//if (!(varDomains.contains(value))) 
			if (!(varDomains.Contains(value)))
			{
				varDomains.Add(value);
			}
		}

		public void addToDomain(string variable, ArrayList values) 
		{
			ArrayList varDomains = (ArrayList) hash[variable];
			for (int i = 0; i < values.Count; i++) 
			{
				addToDomain(variable, values[i]);
			}

		}

		public void removeFromDomain(string variable, Object value) 
		{
			ArrayList varDomains = (ArrayList) hash[variable];
			varDomains.Remove(value);
		}

		public override string ToString() 
		{
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

	}
}
