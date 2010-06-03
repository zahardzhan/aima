using System;
using aima.search.framework;

namespace JugsSearchSample
{
	/// <summary>
	/// Summary description for Q2StepCostFunction.
	/// </summary>
	public class Q2StepCostFunction :  
		aima.search.framework.StepCostFunction 
	{
    
     
		public Q2StepCostFunction() 
		{
		}
 
		//the step cost is the amount of water that's been transfered. To get it just sum up the absolute val of the differences
		//in each jug from one state to the next, and divide it by the number of jugs that had a change
		public double calculateStepCost(Object fromState, Object toState, String action) 
		{
        
			Q2State q2FromState = (Q2State)fromState;
			Q2State q2ToState = (Q2State)toState;
        
			int difference = Math.Abs(q2FromState.jugArray[0] - q2ToState.jugArray[0])
				+ Math.Abs(q2FromState.jugArray[1] - q2ToState.jugArray[1])
				+ Math.Abs(q2FromState.jugArray[2] - q2ToState.jugArray[2]);
        
			//now find out how many jugs were changed (should only ever be 1 or 2)
			int count = 0;
        
			if (Math.Abs(q2FromState.jugArray[0] - q2ToState.jugArray[0]) > 0)
				count += 1;
        
			if (Math.Abs(q2FromState.jugArray[1] - q2ToState.jugArray[1]) > 0)
				count += 1;
        
			if (Math.Abs(q2FromState.jugArray[2] - q2ToState.jugArray[2]) > 0)
				count += 1;
        
			return (double) (difference / count);
        
		}    
    
	}
}
