using System;

namespace aima.search.framework
{
	/// <summary>
	/// Summary description for DefaultStepCostFunction.
	/// </summary>
	public class DefaultStepCostFunction : StepCostFunction 
	{

		public double calculateStepCost(Object fromState, Object toState,
								 string action) 
		{
			return 1;
		}

}
}
