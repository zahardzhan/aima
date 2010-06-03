using System;
using System.Collections;
using aima.util;
namespace aima.datastructures
{
	/// <summary>
	/// Summary description for PriorityQueue.
	/// </summary>
	public class PriorityQueue : AbstractQueue 
	{
		private IComparer comparator;

		public PriorityQueue(IComparer comparator) 
		{
			this.comparator = comparator;
		}

		public new void add(Object anItem) 
		{
			base.addToFront(anItem);
			//Collections.sort(linkedList, comparator);
			linkedList.Sort(comparator);
		}

		public new void add(ArrayList items) 
		{

			for (int i = items.Count - 1; i > -1; i--) 
			{
				add(items[i]);
			}

		}

		public new Object remove() 
		{
			return base.removeFirst();
		}

		public new Object get() 
		{
			return base.getFirst();
		}

	}
}
