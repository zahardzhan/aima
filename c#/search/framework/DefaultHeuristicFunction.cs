using System;

namespace aima.search.framework
{
	/// <summary>
	/// Summary description for DefaultHeuristicFunction.
	/// </summary>
	public class DefaultHeuristicFunction : HeuristicFunction 
	{

			public int getHeuristicValue(Object state) 
			{
				return 1;
			}

	}
}
