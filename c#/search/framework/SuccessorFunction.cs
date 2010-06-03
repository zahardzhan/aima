using System;
using System.Collections;

namespace aima.search.framework
{
	/// <summary>
	/// Summary description for SuccessorFunction.
	/// </summary>
	public interface SuccessorFunction 
	{

		ArrayList getSuccessors(Object state);

	}
}
