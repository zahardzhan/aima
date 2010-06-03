using System;
using System.Collections;

namespace aima.util
{
	/// <summary>
	/// Summary description for Converter.
	/// </summary>
	public  class Converter 
	{
	
		public ArrayList  setToList(Hashtable Set)
		{
			ArrayList retVal = new ArrayList();
			foreach (object o in Set.Keys)
			{
				//string str = o.ToString();
				retVal.Add(o);
			}
			return retVal;
		}
	
		public Hashtable listToSet(ArrayList l) 
		{

			Hashtable retVal = new Hashtable();
			foreach (object o in l)
			{
				retVal.Add(o,null);
			}
			return retVal;

		}

	}
}
