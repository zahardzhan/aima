using System;

namespace aima.search.csp
{
	/// <summary>
	/// Summary description for Constraint.
	/// </summary>
	public interface Constraint 
	{
		bool isSatisfiedWith(Assignment assignment, string variable, Object value);

	}
}
