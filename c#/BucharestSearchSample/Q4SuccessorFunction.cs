using System;
using System.Collections;
using aima.search.framework;

namespace BucharestSearchSample
{
	/// <summary>
	/// Summary description for Q4SuccessorFunction.
	/// </summary>
	public class Q4SuccessorFunction 
		: aima.search.framework.SuccessorFunction 
	{   
		public ArrayList getSuccessors(Object state)
		{
			ArrayList list = new ArrayList(20);
			Q4State jstate = (Q4State) state;
        
			string location = jstate.location;
        
			Successor s;
			Q4State successor_state ;
        
        
			//these functions are used to track the expanded nodes step/heuristic costs
			//Q4StepCostFunction sn = new Q4StepCostFunction();
			//Q4HeuristicFunction hn = new Q4HeuristicFunction();
        
			//System.out.println("Expanding " + location);
         
			if (location.Equals("Oradea"))
			{
				successor_state = new Q4State("Zerind");
				s = new Successor("go to  Zerind", successor_state);
				list.Add(s);
            
				successor_state = new Q4State("Sibiu");
				s = new Successor("go to  Sibiu", successor_state);
				list.Add(s);
			}
			else if (location.Equals("Zerind"))
			{
				successor_state = new Q4State("Oradea");
				s = new Successor("go to  Oradea", successor_state);
				list.Add(s);
            
				successor_state = new Q4State("Arad");
				s = new Successor("go to Arad", successor_state);
				list.Add(s);
			}
			else if (location.Equals("Arad"))
			{
				successor_state = new Q4State("Zerind");
				s = new Successor("go to Zerind", successor_state);
				list.Add(s);
            
				successor_state = new Q4State("Timisoara");
				s = new Successor("go to Timisoara", successor_state);
				list.Add(s);
			}
			else if (location.Equals("Timisoara"))
			{
				successor_state = new Q4State("Arad");
				s = new Successor("go to Arad", successor_state);
				list.Add(s);
            
				successor_state = new Q4State("Lugoj");
				s = new Successor("go to  Lugoj", successor_state);
				list.Add(s);
			}
			else if (location.Equals("Lugoj"))
			{
				successor_state = new Q4State("Timisoara");
				s = new Successor("go to Timisoara", successor_state);
				list.Add(s);
            
				successor_state = new Q4State("Mehadia");
				s = new Successor("go to Mehadia", successor_state);
				list.Add(s);
			}
			else if (location.Equals("Mehadia"))
			{
				successor_state = new Q4State("Dobreta");
				s = new Successor("go to Dobreta", successor_state);
				list.Add(s);
            
				successor_state = new Q4State("Lugoj");
				s = new Successor("go to Lugoj", successor_state);
				list.Add(s);
			}
			else if (location.Equals("Dobreta"))
			{
				successor_state = new Q4State("Mehadia");
				s = new Successor("go to Mehadia", successor_state);
				list.Add(s);
            
				successor_state = new Q4State("Craiova");
				s = new Successor("go to Craiova", successor_state);
				list.Add(s);
			}
			else if (location.Equals("Sibiu"))
			{
				successor_state = new Q4State("Arad");
				s = new Successor("go to Arad", successor_state);
				list.Add(s);
            
				successor_state = new Q4State("Oradea");
				s = new Successor("go to Oradea", successor_state);
				list.Add(s);
            
				successor_state = new Q4State("Fagaras");
				s = new Successor("go to Fagaras", successor_state);
				list.Add(s);
            
				successor_state = new Q4State("Rimnicu Vilcea");
				s = new Successor("go to Rimnicu Vilcea", successor_state);
				list.Add(s);
			}
			else if (location.Equals("Rimnicu Vilcea"))
			{
				successor_state = new Q4State("Sibiu");
				s = new Successor("go to Sibiu", successor_state);
				list.Add(s);
            
				successor_state = new Q4State("Pitesti");
				s = new Successor("go to Pitesti", successor_state);
				list.Add(s);
            
				successor_state = new Q4State("Craiova");
				s = new Successor("go to Craiova", successor_state);
				list.Add(s);
			}
			else if (location.Equals("Craiova"))
			{
				successor_state = new Q4State("Rimnicu Vilcea");
				s = new Successor("go to Rimnicu Vilcea", successor_state);
				list.Add(s);
            
				successor_state = new Q4State("Dobreta");
				s = new Successor("go to Dobreta", successor_state);
				list.Add(s);
            
				successor_state = new Q4State("Pitesti");
				s = new Successor("go to Pitesti", successor_state);
				list.Add(s);
			}
			else if (location.Equals("Pitesti"))
			{
				successor_state = new Q4State("Rimnicu Vilcea");
				s = new Successor("go to Rimnicu Vilcea", successor_state);
				list.Add(s);
            
				successor_state = new Q4State("Craiova");
				s = new Successor("go to Craiova", successor_state);
				list.Add(s);
            
				successor_state = new Q4State("Bucharest");
				s = new Successor("go to Bucharest", successor_state);
				list.Add(s);
			}
			else if (location.Equals("Fagaras"))
			{
				successor_state = new Q4State("Sibiu");
				s = new Successor("go to Sibiu", successor_state);
				list.Add(s);
            
				successor_state = new Q4State("Bucharest");
				s = new Successor("go to Bucharest", successor_state);
				list.Add(s);
			}
			else if (location.Equals("Bucharest"))
			{
				successor_state = new Q4State("Fagaras");
				s = new Successor("go to Fagaras", successor_state);
				list.Add(s);
            
				successor_state = new Q4State("Pitesti");
				s = new Successor("go to Pitesti", successor_state);
				list.Add(s);
            
				successor_state = new Q4State("Giurgiu");
				s = new Successor("go to Giurgiu", successor_state);
				list.Add(s);
            
				successor_state = new Q4State("Urziceni");
				s = new Successor("go to Urziceni", successor_state);
				list.Add(s);
			}
			else if (location.Equals("Giurgiu"))
			{
				successor_state = new Q4State("Bucharest");
				s = new Successor("go to Bucharest", successor_state);
				list.Add(s);
			}
			else if (location.Equals("Urziceni"))
			{
				successor_state = new Q4State("Bucharest");
				s = new Successor("go to Bucharest", successor_state);
				list.Add(s);
            
				successor_state = new Q4State("Vaslui");
				s = new Successor("go to Vaslui", successor_state);
				list.Add(s);
            
				successor_state = new Q4State("Hirsova");
				s = new Successor("go to Hirsova", successor_state);
				list.Add(s);
			}
			else if (location.Equals("Vaslui"))
			{
				successor_state = new Q4State("Urziceni");
				s = new Successor("go to Urziceni", successor_state);
				list.Add(s);
            
				successor_state = new Q4State("Iasi");
				s = new Successor("go to Iasi", successor_state);
				list.Add(s);
			}
			else if (location.Equals("Iasi"))
			{
				successor_state = new Q4State("Vaslui");
				s = new Successor("go to Vaslui", successor_state);
				list.Add(s);
            
				successor_state = new Q4State("Neamt");
				s = new Successor("go to Neamt", successor_state);
				list.Add(s);
			}
			else if (location.Equals("Neamt"))
			{
				successor_state = new Q4State("Iasi");
				s = new Successor("go to Iasi", successor_state);
				list.Add(s);
			}
			else if (location.Equals("Hirsova"))
			{
				successor_state = new Q4State("Urziceni");
				s = new Successor("go to Urziceni", successor_state);
				list.Add(s);
            
				successor_state = new Q4State("Eforie");
				s = new Successor("go to Eforie", successor_state);
				list.Add(s);
			}
			else if (location.Equals("Eforie"))
			{
				successor_state = new Q4State("Hirsova");
				s = new Successor("go to Hirsova", successor_state);
				list.Add(s);
			}
       
               
            
        
			return list;
		}
    
    
		private int min(int x, int y) 
		{
			if (x < y) return x;
			return y;
		}
	}

}
