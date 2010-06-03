using System;
using System.Collections;
using aima.util;

namespace aima.search.framework
{
	/// <summary>
	/// Summary description for Node.
	/// </summary>
	public class Node 
	{

		private Object state;

		private Node parent;

		private Hashtable actionStateMap;

		private string action;

		private int depth;

		private double stepCost, pathCost;

		public Node(Object state) 
		{

			this.state = state;
			this.actionStateMap = new Hashtable();
			this.depth = 0;
			this.stepCost = 0;
			this.pathCost = 0;
		}

		public Node(Node parent, Object state) : this(state)
		{
			//this(state);
			this.parent = parent;
			this.depth = parent.getDepth() + 1;
		}

		public int getDepth() 
		{

			return depth;
		}

		public bool isRootNode() 
		{
			return parent == null;
		}

		public Node getParent() 
		{
			return parent;
		}

		public ArrayList getPathFromRoot() 
		{
			Node current = this;
			AbstractQueue queue = new AbstractQueue();
			while (!(current.isRootNode())) 
			{
				queue.addToFront(current);
				current = current.getParent();
			}
			queue.addToFront(current); // take care of root node
			return queue.asList();
		}

		public Object getState() 
		{
			return state;
		}

		public void setAction(string action) 
		{
			//actionStateMap.Add("action", action);
			this.action = action;
		}

		public string getAction() 
		{
			return action;
			//this.action = action
			//return actionStateMap["action"].ToString();
		}

		public void setStepCost(double stepCost) 
		{

			this.stepCost = stepCost;

		}

		public void addToPathCost(double stepCost) 
		{
			this.pathCost = parent.pathCost
				+ stepCost;

		}

		/**
		 * @return Returns the pathCost.
		 */
		public double getPathCost() 
		{
			
			return pathCost;
		}

		/**
		 * @return Returns the stepCost.
		 */
		public double getStepCost() 
		{

			return stepCost;
		}

		public override string ToString()
		{
			return getState().ToString();
		}
	}
}
