using System;
using System.Collections;
using aima.search.framework;
using aima.basic;

namespace aima.search.informed
{
	/// <summary>
	/// Summary description for SimulatedAnnealingSearch.
	/// </summary>
	public class SimulatedAnnealingSearch : NodeExpander , Search 
	{

		//private int steps; not used?

		private Scheduler scheduler;

		public SimulatedAnnealingSearch() 
		{
			//this.steps = 10000;
			this.scheduler = new Scheduler();
		}

		public ArrayList search(Problem p)
		{
			clearInstrumentation();
			Node current = new Node(p.getInitialState());
			Node next = null;
			ArrayList ret = new ArrayList();
			for (int step = 0; step < 1000; step = step + 1) 
			{
				double temp = scheduler.getTemp(step);
				if (temp == 0.0) 
				{
					String status = "not completed";
					if (p.isGoalState(current.getState())) 
					{
						status = "success";
					}
					//System.out.println(current.getState());
					ret = SearchUtils.actionsFromNodes(current.getPathFromRoot());
					ret.Add(status + "\nFinal state = \n" + current.getState());
					break;
				}
				ArrayList children = expandNode(current, p);
				//expansions++;
				//System.out.println("step = "+step+" expansions = "+expansions);
				if (children.Count > 0) 
				{
					//TODO take care of no possible expansion situation?
					next = (Node) Util.selectRandomlyFromList(children);
					int deltaE = getValue(next, p) - getValue(current, p);
					//System.out.print("deltaE = "+deltaE+"\n");
					if ((deltaE > 0.0)
						|| (new Random().NextDouble() > Math.Exp(deltaE / temp))) 
					{
						current = next;
					}
				}

			}
			//System.out.println("Number of expansions = "+expansions);
			return ret;//Total Failure
		}

		private int getHeuristic(Node aNode, Problem p) 
		{
			return p.getHeuristicFunction().getHeuristicValue(aNode.getState());
		}

		private int getValue(Node n, Problem p) 
		{
			return -1 * getHeuristic(n, p); //assumption greater heuristic value =>
			// HIGHER on hill; 0 == goal state;
			//SA deals with gardient DESCENT
		}

	}
}
