using System;
using System.Collections;

namespace aima.util
{
	/// <summary>
	/// Summary description for AbstractQueue.
	/// </summary>
	public class AbstractQueue : Queue 
	{
		protected ArrayList linkedList;

		public AbstractQueue() 
		{
			linkedList = new ArrayList();
		}

		public void addToFront(Object n) 
		{
			linkedList.Insert(0,n);
		}

		public void addToBack(Object n) 
		{
			linkedList.Add(n);
		}

		public void addToFront(ArrayList list) 
		{
			for (int i = 0; i < list.Count; i++) 
			{
				addToFront(list[list.Count - 1 - i]);
			}
		}

		public void addToBack(ArrayList list) 
		{
			for (int i = 0; i < list.Count; i++) 
			{
				addToBack(list[i]);
			}
		}

		public Object removeFirst() 
		{
			Object o = linkedList[0];
			linkedList.RemoveAt(0);
			return o;
		}

		public Object removeLast() 
		{
			Object o = linkedList[linkedList.Count - 1];
			linkedList.RemoveAt(linkedList.Count - 1);
			return o;
		}

		public Object getFirst() 
		{
			return (linkedList[0]);
		}

		public Object getLast() 
		{
			return (linkedList[linkedList.Count - 1]);
		}

		public bool isEmpty() 
		{
			return linkedList.Count == 0;
		}

		public int size() 
		{
			return linkedList.Count;
		}

		public ArrayList asList() 
		{
			return linkedList;
		}

		public void add(Object anItem) 
		{
			throw new Exception("must be implemented by subclasses");
		}

		public void add(ArrayList items) 
		{
			throw new Exception("must be implemented by subclasses");
		}

		public Object remove() 
		{
			throw new Exception("must be implemented by subclasses");
		}

		public Object get() 
		{
			throw new Exception("must be implemented by subclasses");
		}

	}
}
