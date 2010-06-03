using System;
using aima.search.framework;

namespace BucharestSearchSample
{
	/// <summary>
	/// Summary description for Q3HeuristicFunction.
	/// </summary>
	public class Q4HeuristicFunction : HeuristicFunction 
	{   
		public int getHeuristicValue(Object state) 
		{

			Q4State Q4FromState = (Q4State)state;
			string from = Q4FromState.location;

			if (from.Equals("Oradea"))
			{
				return 380;
			}
			else if (from.Equals("Zerind") )
			{
				return 374;
			}
			else if (from.Equals("Arad"))
			{
				return 366;
			}
			else if (from.Equals("Timisoara"))
			{
				return 329;
			}
			else if (from.Equals("Lugoj"))
			{
				return 244;
			}
			else if (from.Equals("Mehadia"))
			{
				return 241;
			}
			else if (from.Equals("Dobreta"))
			{
				return 242;
			}
			else if (from.Equals("Craiova"))
			{
				return 160;
			}
			else if (from.Equals("Rimnicu Vilcea"))
			{
				return 193;
			}
			else if (from.Equals("Sibiu"))
			{
				return 253;
			}
			else if (from.Equals("Fagaras"))
			{
				return 176;
			}
			else if (from.Equals("Pitesti"))
			{
				return 100;
			}
			else if (from.Equals("Bucharest"))
			{
				return 0;
			}
			else if (from.Equals("Giurgiu"))
			{
				return 77;
			}
			else if (from.Equals("Urziceni"))
			{
				return 80;
			}
			else if (from.Equals("Vaslui"))
			{
				return 199;
			}
			else if (from.Equals("Iasi"))
			{
				return 226;
			}
			else if (from.Equals("Neamt"))
			{
				return 234;
			}
			else if (from.Equals("Hirsova"))
			{
				return 151;
			}
			else if (from.Equals("Eforie"))
			{
				return 161;
			}
			return 0;
		}
	}
}
