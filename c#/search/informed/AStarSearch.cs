using System;
using aima.search.framework;
using System.Collections;


namespace aima.search.informed
{
	/// <summary>
	/// Summary description for AStarSearch.
	/// </summary>
	public class AStarSearch : PrioritySearch 
	{

		public AStarSearch(QueueSearch search) 
		{
			this._search = search;
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
				double g1 = one.getPathCost();
				int h2 = problem.getHeuristicFunction().getHeuristicValue(
					two.getState());
				double g2 = two.getPathCost();

				double s1 = g1 + h1;
				double s2 = g2 + h2;
				if (s1 == s2) 
				{
					return 0;
				} 
				else if (s1 < s2) 
				{
					return -1;
				} 
				else 
				{
					return 1;//
				}
			}
		}

		public new Metrics getMetrics() 
		{
			return _search.getMetrics();
		}

		protected override IComparer getComparator(Problem p) 
		{

			return new NodeComparator(p);
		}

	}
	
}
