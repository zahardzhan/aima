using System;
using System.Collections;

namespace aima.search.framework
{
	/// <summary>
	/// Summary description for Search.
	/// </summary>
	public interface Search 
	{
		ArrayList search(Problem p); //throws exception

		Metrics getMetrics();
	}
}
