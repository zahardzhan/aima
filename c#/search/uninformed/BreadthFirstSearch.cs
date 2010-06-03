using System;
using System.Collections;
using aima.search.framework;
using aima.search.nodestore;

namespace aima.search.uninformed
{
	/// <summary>
	/// Summary description for BreadthFirstSearch.
	/// </summary>
	public class BreadthFirstSearch : Search 
	{

		private QueueSearch _search;

		public BreadthFirstSearch(QueueSearch search) 
		{
			this._search = search;
		}

		public ArrayList search(Problem p) 
		{
			return _search.search(p, new FIFONodeStore());
		}

		public Metrics getMetrics() 
		{
			return _search.getMetrics();
		}

	}
}
