using System;
using System.Collections;
using aima.search.nodestore;

namespace aima.search.framework
{
	/// <summary>
	/// Summary description for PrioritySearch.
	/// </summary>
	public abstract class PrioritySearch : Search 
	{
		protected QueueSearch _search;

		public ArrayList search(Problem p)  
		{
			return _search.search(p, new PriorityNodeStore(getComparator(p)));
		}

		protected abstract IComparer getComparator(Problem p);

		public Metrics getMetrics() 
		{
			return _search.getMetrics();
		}

	}
}
