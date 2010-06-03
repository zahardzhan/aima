using System;
using System.Collections;
using aima.search.framework;

namespace aima.search.informed
{
	/// <summary>
	/// Summary description for GreedyBestFirstSearch.
	/// </summary>
	public class GreedyBestFirstSearch : PrioritySearch 
	{

		public GreedyBestFirstSearch(QueueSearch search) 
		{
			this._search = search;
		}

		protected override IComparer getComparator(Problem p) 
		{
			return new NodeComparator(p);
		}

		public class NodeComparator : IComparer 
		{
			private Problem problem;

			public NodeComparator(Problem problem) 
			{
				this.problem = problem;
			}

			public int Compare(Object aNode, Object anotherNode) 
			{
				Node one = (Node) aNode;
				Node two = (Node) anotherNode;

				int h1 = problem.getHeuristicFunction().getHeuristicValue(
					one.getState());
				int h2 = problem.getHeuristicFunction().getHeuristicValue(
					two.getState());
				if (h1 == h2) 
				{
					return 0;
				} 
				else if (h1 < h2) 
				{
					return -1;
				} 
				else 
				{
					return +1;
				}
			}

		}
	}
}
