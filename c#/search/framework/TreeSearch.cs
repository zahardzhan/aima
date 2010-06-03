using System;

namespace aima.search.framework
{
	/// <summary>
	/// Summary description for TreeSearch.
	/// </summary>
	public class TreeSearch : QueueSearch 
	{

		protected override void addExpandedNodesToFringe(NodeStore fringe, Node node,
			Problem problem) 
		{
			fringe.add(expandNode(node, problem));
		}

	}
}
