using System;
using System.Collections;
using aima.search.framework;
using aima.search.nodestore;

namespace aima.search.uninformed
{
	/// <summary>
	/// Summary description for DepthLimitedSearch.
	/// </summary>
	public class DepthLimitedSearch : NodeExpander , Search 
	{

		private int limit;

		public DepthLimitedSearch(int limit) 
		{
			this.limit = limit;

		}

		public ArrayList search(Problem p) 
		{
			clearInstrumentation();
			return recursiveDLS(new Node(p.getInitialState()), p, limit);
		}

		private ArrayList recursiveDLS(Node node, Problem problem, int limit) 
		{
			bool cutOffOccured = false;
			if (problem.isGoalState(node.getState())) 
			{
				return SearchUtils.actionsFromNodes(node.getPathFromRoot());
			} 
			else if (node.getDepth() == limit) 
			{
				return createCutOffResult();
			} 
			else 
			{
				ArrayList children = expandNode(node, problem);
				for (int i = 0; i < children.Count; i++) 
				{
					Node child = (Node) children[i];
					ArrayList result = recursiveDLS(child, problem, limit);
					if (cutoffResult(result)) 
					{
						cutOffOccured = true;
					} 
					else if (!(failure(result))) 
					{
						return result;
					}
				}
				if (cutOffOccured) 
				{
					return createCutOffResult();
				} 
				else 
				{
					return new ArrayList();
				}

			}

		}

		private bool failure(ArrayList result) 
		{

			return result.Count == 0;
		}

		private bool cutoffResult(ArrayList result) 
		{

			return result.Count == 1 && result[0].ToString().Equals("cutoff");
		}

		private ArrayList createCutOffResult() 
		{
			ArrayList result = new ArrayList();
			result.Add("cutoff");
			return result;
		}

	}
}
