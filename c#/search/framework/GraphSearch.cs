using System;
using System.Collections;

namespace aima.search.framework
{
	/// <summary>
	/// Summary description for GraphSearch.
	/// </summary>
	public class GraphSearch : QueueSearch 
	{
		//Set closed = new HashSet();
		//hashset = hashtable with nulls for values
		Hashtable closed = new Hashtable();

		protected override void addExpandedNodesToFringe(NodeStore fringe, Node node,
			Problem problem) 
		{

			if (!(alreadySeen(node))) 
			{
				//it is critical here put the hashcode of the object
				//into the hashtable!!
				closed.Add(node.getState().GetHashCode(),"");
				fringe.add(expandNode(node,problem));

			}
		}

		private bool alreadySeen(Node node) 
		{
			//return closed.contains(node.getState());
			//you must compare hashcode values, or they will never
			//evaluate to true!
			return closed.Contains(node.getState().GetHashCode());
		}

	}
}
