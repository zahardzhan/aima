using System;
using System.Collections;
using aima.search.framework;
using aima.datastructures;

namespace aima.search.nodestore
{
	/// <summary>
	/// Summary description for LIFONodeStore.
	/// </summary>
	public class LIFONodeStore : NodeStore 
	{
		LIFOQueue queue;

		public LIFONodeStore() 
		{
			queue = new LIFOQueue();
		}

		public void add(Node anItem) 
		{
			queue.add(anItem);

		}

		public Node remove() 
		{
			return (Node) queue.remove();
		}

		public void add(ArrayList nodes) 
		{
			queue.add(nodes);

		}

		public bool isEmpty() 
		{
			return queue.isEmpty();
		}

		public int size() 
		{
			return queue.size();
		}

	}
}
