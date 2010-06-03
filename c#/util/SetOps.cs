using System;
using System.Collections;

namespace aima.util
{
	/// <summary>
	/// Summary description for SetOps.
	/// </summary>
	public class SetOps 
	{
		public Hashtable union(Hashtable one, Hashtable two) 
		{
			Hashtable union = new Hashtable();
			//union.addAll(two);
			foreach (object key in one.Keys)
			{
				union.Add(key,null);
			}
			foreach (object key in two.Keys)
			{
				if (!union.Contains(key))
					union.Add(key,null);
			}
			return union;
		}
		public Hashtable intersection(Hashtable one, Hashtable two) 
		{
			Hashtable intersection = new Hashtable();
			//intersection.retainAll(two);
			foreach (object key in one.Keys)
			{
				if (two.Contains(key))
					intersection.Add(key,null);
			}
			return intersection;
		}
	
		public Hashtable difference(Hashtable one, Hashtable two) 
		{
			
			Hashtable three = new Hashtable();
			//Iterator iteratorOne = one.iterator();
//			while (iteratorOne.hasNext()) 
//			{
//				T sym = iteratorOne.next();
//				if (!(In(two, sym))) 
//				{
//					three.add(sym);
//				}
//			}
			foreach (object key in one.Keys)
			{
				if (!(this.In(two,key)))
					three.Add(key,null);
			}
			return three;
		}
	
		public bool In(Hashtable s, object o) 
		{
			foreach (object key in s.Keys)
			{
				if (key.Equals(o))
					return true;
			}
//			IEnumerator i = s.iterator();
//			while (i.hasNext()) 
//			{
//				Object obj = i.next();
//				if (obj.equals(o)) 
//				{
//					return true;
//				}
//			}
			return false;
		}

	}
}
