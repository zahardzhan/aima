using System;
using System.Collections;
using aima.basic;

namespace aima.search.framework
{
	/// <summary>
	/// Summary description for SearchAgent.
	/// </summary>
	public class SearchAgent : Agent 
	{
		ArrayList actionList;

		private IEnumerator actionIterator;

		private Metrics searchMetrics;

		public SearchAgent(Problem p, Search search) 
		{
			actionList = search.search(p);
			actionIterator = actionList.GetEnumerator();
			searchMetrics = search.getMetrics();

		}

		public string execute(Percept p) 
		{
			if (actionIterator.MoveNext()) 
			{
				return actionIterator.Current.ToString();
			} 
			else 
			{
				return "NoOp";
			}
		}

		public ArrayList getActions() 
		{
			return actionList;
		}

		public Hashtable getInstrumentation() 
		{
		
			Hashtable retVal = new Hashtable();
			IEnumerator iter = searchMetrics.keySet().GetEnumerator();
			while (iter.MoveNext()) 
			{
				string key = iter.Current.ToString();
				string value = searchMetrics.get(key);
				//retVal.setProperty(key, value);
				retVal.Add(key,value);
				
			}
			return retVal;
		}

	}
}
