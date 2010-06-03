using System;
using System.Collections;
using aima.search.framework;


namespace aima.search.informed
{
	/// <summary>
	/// Summary description for HillClimbingSearch.
	/// </summary>
	public class HillClimbingSearch : NodeExpander , Search 
	{

		public ArrayList search(Problem p) 
		{
			clearInstrumentation();
			Node current = new Node(p.getInitialState());
			Node neighbor = null;
			while (true) 
			{
				ArrayList children = expandNode(current, p);
				neighbor = getHighestValuedNodeFrom(children, p);

				if ((neighbor == null)
					|| (getValue(neighbor, p) <= getValue(current, p))) 
				{
					return SearchUtils.actionsFromNodes(current.getPathFromRoot());
				}
				current = neighbor;
			}

		}

		private Node getHighestValuedNodeFrom(ArrayList children, Problem p) 
		{
			int highestValue = int.MinValue;
			Node nodeWithHighestValue = null;
			for (int i = 0; i < children.Count; i++) 
			{
				Node child = (Node) children[i];
				int value = getValue(child, p);
				if (value > highestValue) 
				{
					highestValue = value;
					nodeWithHighestValue = child;
				}
			}
			return nodeWithHighestValue;
		}

		private int getHeuristic(Node aNode, Problem p) 
		{

			return p.getHeuristicFunction().getHeuristicValue(aNode.getState());
		}

		private int getValue(Node n, Problem p) 
		{

			return -1 * getHeuristic(n, p); //assumption greater heuristic value =>
			// HIGHER on hill; 0 == goal state;
		}

	}
}
