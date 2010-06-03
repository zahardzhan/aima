using System;
using System.Collections;
using aima.util;
namespace aima.datastructures
{
	/// <summary>
	/// Summary description for FIFOQueue.
	/// </summary>
	public class FIFOQueue : AbstractQueue 
	{
		public new void add(Object anItem) 
		{
			base.addToFront(anItem);
		}

		public new void add(ArrayList items) 
		{
			ArrayList reversed = new ArrayList();
			for (int i = items.Count - 1; i > -1; i--) 
			{
				reversed.Add(items[i]);
			}
			base.addToFront(reversed);
		}

		public new Object remove() 
		{
			return base.removeLast();
		}

		public new Object get() 
		{
			return base.getLast();
		}

	}
}
