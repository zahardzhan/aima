using System;
using System.Collections;

namespace aima.search.framework
{
	/// <summary>
	/// Summary description for NodeStore.
	/// </summary>
	public interface NodeStore 
	{
		 void add(Node anItem);

		 Node remove();

		 void add(ArrayList nodes);

		 bool isEmpty();

		 int size();
	}
}
