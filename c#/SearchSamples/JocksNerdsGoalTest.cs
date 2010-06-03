using System;

namespace SearchSamples
{
	/// <summary>
	/// Summary description for Q1GoalTest.
	/// </summary>
	public class JocksNerdsGoalTest : aima.search.framework.GoalTest 
	{    
    
		public bool isGoalState(Object state) 
		{
			JocksNerdsState jstate = (JocksNerdsState) state;

			//if there's no one left on the left bank and the boat is on the right side then it's over
			if (jstate.locationArray[0]==0 && jstate.locationArray[1]==0 && jstate.locationArray[2] % 2 == 1)
				return true;
			else return false;
		}
	}
}
