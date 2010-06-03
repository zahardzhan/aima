using System;
using aima.search.framework;

namespace JugsSearchSample
{
	/// <summary>
	/// Summary description for Q2GoalTest.
	/// </summary>
	public class Q2GoalTest : aima.search.framework.GoalTest 
	{    
    
    
		public bool isGoalState(Object state) 
		{
			Q2State jstate = (Q2State) state;
        
			if (jstate.jugArray[0]==1 || jstate.jugArray[1]==1 || jstate.jugArray[2]==1)
				return true;
			else return false;
		}
}
}
