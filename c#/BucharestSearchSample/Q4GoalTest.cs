using System;

namespace BucharestSearchSample
{
	/// <summary>
	/// Summary description for Q3GoalTest.
	/// </summary>
	public class Q4GoalTest : aima.search.framework.GoalTest 
	{    
		public bool isGoalState(Object state) 
		{
			Q4State jstate = (Q4State) state;
        
			if (jstate.location.ToLower().Equals("bucharest"))
				return true;
			else return false;
		}
	}
}
