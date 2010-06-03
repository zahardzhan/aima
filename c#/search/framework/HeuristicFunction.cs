using System;

namespace aima.search.framework
{
	/// <summary>
	/// Summary description for HeuristicFunction.
	/// </summary>
	public interface HeuristicFunction 
	{

		int getHeuristicValue(Object state);

	}
}
