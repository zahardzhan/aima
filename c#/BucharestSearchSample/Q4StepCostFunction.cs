using System;

namespace BucharestSearchSample
{
	/// <summary>
	/// Summary description for Q4StepCostFunction.
	/// </summary>
	public class Q4StepCostFunction :  
		aima.search.framework.StepCostFunction 
	{
    
     
		public Q4StepCostFunction() 
		{
		}
 
		//the step cost is the amount of water that's been transfered. To get it just sum up the absolute val of the differences
		//in each jug from one state to the next
		public double calculateStepCost(Object fromState, Object toState, string action) 
		{
        

			Q4State Q4FromState = (Q4State)fromState;
			Q4State Q4ToState = (Q4State)toState;
        
     
			string from = Q4FromState.location;
			string to = Q4ToState.location;
        
			if ((from.Equals("Oradea") && to.Equals("Zerind"))
				|| (from.Equals("Zerind") && to.Equals("Oradea")))
			{
				return 71;
			}
			else if ((from.Equals("Oradea") && to.Equals("Sibiu"))
				|| (from.Equals("Sibiu") && to.Equals("Oradea")))
			{
				return 151;
			}
			else if ((from.Equals("Zerind") && to.Equals("Arad"))
				|| (from.Equals("Arad") && to.Equals("Zerind")))
			{
				return 75;
			}
			else if ((from.Equals("Arad") && to.Equals("Sibiu"))
				|| (from.Equals("Sibiu") && to.Equals("Arad")))
			{
				return 140;
			}
			else if ((from.Equals("Arad") && to.Equals("Timisoara"))
				|| (from.Equals("Timisoara") && to.Equals("Arad")))
			{
				return 118;
			}
			else if ((from.Equals("Timisoara") && to.Equals("Lugoj"))
				|| (from.Equals("Lugoj") && to.Equals("Timisoara")))
			{
				return 111;
			}
			else if ((from.Equals("Lugoj") && to.Equals("Mehadia"))
				|| (from.Equals("Mehadia") && to.Equals("Lugoj")))
			{
				return 70;
			}
			else if ((from.Equals("Mehadia") && to.Equals("Dobreta"))
				|| (from.Equals("Dobreta") && to.Equals("Mehadia")))
			{
				return 75;
			}
			else if ((from.Equals("Dobreta") && to.Equals("Craiova"))
				|| (from.Equals("Craiova") && to.Equals("Dobreta")))
			{
				return 120;
			}
			else if ((from.Equals("Craiova") && to.Equals("Rimnicu Vilcea"))
				|| (from.Equals("Rimnicu Vilcea") && to.Equals("Craiova")))
			{
				return 146;
			}
			else if ((from.Equals("Craiova") && to.Equals("Pitesti"))
				|| (from.Equals("Pitesti") && to.Equals("Craiova")))
			{
				return 138;
			}
			else if ((from.Equals("Rimnicu Vilcea") && to.Equals("Sibiu"))
				|| (from.Equals("Sibiu") && to.Equals("Rimnicu Vilcea")))
			{
				return 80;
			}
			else if ((from.Equals("Rimnicu Vilcea") && to.Equals("Pitesti"))
				|| (from.Equals("Pitesti") && to.Equals("Rimnicu Vilcea")))
			{
				return 97;
			}
			else if ((from.Equals("Sibiu") && to.Equals("Fagaras"))
				|| (from.Equals("Fagaras") && to.Equals("Sibiu")))
			{
				return 99;
			}
			else if ((from.Equals("Fagaras") && to.Equals("Bucharest"))
				|| (from.Equals("Bucharest") && to.Equals("Fagaras")))
			{
				return 211;
			}
			else if ((from.Equals("Pitesti") && to.Equals("Bucharest"))
				|| (from.Equals("Bucharest") && to.Equals("Pitesti")))
			{
				return 101;
			}
			else if ((from.Equals("Bucharest") && to.Equals("Giurgiu"))
				|| (from.Equals("Giurgiu") && to.Equals("Bucharest")))
			{
				return 90;
			}
			else if ((from.Equals("Bucharest") && to.Equals("Urziceni"))
				|| (from.Equals("Urziceni") && to.Equals("Bucharest")))
			{
				return 85;
			}
			else if ((from.Equals("Urziceni") && to.Equals("Vaslui"))
				|| (from.Equals("Vaslui") && to.Equals("Urziceni")))
			{
				return 142;
			}
			else if ((from.Equals("Vaslui") && to.Equals("Iasi"))
				|| (from.Equals("Iasi") && to.Equals("Vaslui")))
			{
				return 92;
			}
			else if ((from.Equals("Iasi") && to.Equals("Neamt"))
				|| (from.Equals("Neamt") && to.Equals("Iasi")))
			{
				return 87;
			}
			else if ((from.Equals("Urziceni") && to.Equals("Hirsova"))
				|| (from.Equals("Hirsova") && to.Equals("Urziceni")))
			{
				return  98;
			}
			else if ((from.Equals("Hirsova") && to.Equals("Eforie"))
				|| (from.Equals("Eforie") && to.Equals("Hirsova")))
			{
				return  86;
			}
       
			return 0;
        
       
		}    
    
	}
}
