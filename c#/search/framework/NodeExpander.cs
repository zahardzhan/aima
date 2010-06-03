using System;
using System.Collections;

namespace aima.search.framework
{
	/// <summary>
	/// Summary description for NodeExpander.
	/// </summary>
	public class NodeExpander 
	{
		protected Metrics metrics;

		protected static string NODES_EXPANDED = "nodesExpanded";

		public NodeExpander() 
		{
			metrics = new Metrics();
		}

		public void clearInstrumentation() 
		{
			metrics.set(NODES_EXPANDED, 0);
			
		}

		public ArrayList expandNode(Node node, Problem problem) 
		{
			int heuristic = problem.getHeuristicFunction().getHeuristicValue(
				node.getState());
			//System.out.println("Expanding\n"+node.getState()+"\n"+"heuristic =
			// "+heuristic+"\n");

			ArrayList nodes = new ArrayList();
			ArrayList successors = problem.getSuccessorFunction().getSuccessors(
				node.getState());
			for (int i = 0; i < successors.Count; i++) 
			{
				Successor successor = (Successor) successors[i];
				Node aNode = new Node(node, successor.getState());
				aNode.setAction(successor.getAction());
				double stepCost = problem.getStepCostFunction().calculateStepCost(
					node.getState(), successor.getState(),
					successor.getAction());
				aNode.setStepCost(stepCost);
				aNode.addToPathCost(stepCost);
				nodes.Add(aNode);

			}
			metrics.set(NODES_EXPANDED, metrics.getInt(NODES_EXPANDED) + 1);
			//System.out.println("Nodes expanded = " +
			// metrics.getInt(NODES_EXPANDED));
			return nodes;
		}

		public int getNodesExpanded() 
		{
			return metrics.getInt("nodesExpanded");
		}

		public void setNodesExpanded(int nodesExpanded) 
		{
			metrics.set(NODES_EXPANDED, nodesExpanded);
		}

		public void setSearchMetric(String name, Object value) 
		{
			metrics.set(name, value);
		}

		public Object getSearchMetric(String name) 
		{
			return metrics.get(name);
		}

		public Metrics getMetrics() 
		{
			return metrics;
		}
	}
}
