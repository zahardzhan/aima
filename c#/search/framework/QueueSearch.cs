using System;
using System.Collections;

namespace aima.search.framework
{
	/// <summary>
	/// Summary description for QueueSearch.
	/// </summary>
	public abstract class QueueSearch : NodeExpander 
	{
		private static string QUEUE_SIZE = "queueSize";

		private static string MAX_QUEUE_SIZE = "maxQueueSize";

		public ArrayList search(Problem problem, NodeStore fringe) 
		{
			clearInstrumentation();
			fringe.add(new Node(problem.getInitialState()));
			setQueueSize(fringe.size());
			while (!(fringe.isEmpty())) 
			{
				Node node = (Node) fringe.remove();
				setQueueSize(fringe.size());
				if (problem.isGoalState(node.getState())) 
				{
					return SearchUtils.actionsFromNodes(node.getPathFromRoot());
				}
				addExpandedNodesToFringe(fringe, node, problem);
				setQueueSize(fringe.size());
			}
			return new ArrayList();//Empty List indicates Failure
		}

		public new void clearInstrumentation() 
		{
			base.clearInstrumentation();
			metrics.set(QUEUE_SIZE, 0);
			metrics.set(MAX_QUEUE_SIZE, 0);
		}

		public int getQueueSize() 
		{
			return metrics.getInt("queueSize");
		}

		public void setQueueSize(int queueSize) 
		{

			metrics.set(QUEUE_SIZE, queueSize);
			int maxQSize = metrics.getInt(MAX_QUEUE_SIZE);
			if (queueSize > maxQSize) 
			{
				metrics.set(MAX_QUEUE_SIZE, queueSize);
			}
		}

		public int getMaxQueueSize() 
		{
			return metrics.getInt("maxQueueSize");
		}

		protected abstract void addExpandedNodesToFringe(NodeStore fringe,
			Node node, Problem p);
	}
}
