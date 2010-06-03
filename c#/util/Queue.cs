using System;
using System.Collections;

namespace aima.util
{
	/// <summary>
	/// Summary description for Queue.
	/// </summary>
	public interface Queue 
	{
		void add(Object anItem);

		void add(ArrayList items);

		Object remove();

		Object get();
	}
}
