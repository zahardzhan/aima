using System;
using System.Collections;

namespace aima.search.csp
{
	/// <summary>
	/// Summary description for MapCSP.
	/// </summary>
	public class MapCSP : CSP 
	{
		public static string WA = "WA";

		public static string NT = "NT";

		public static string SA = "SA";

		public static string Q = "Q";

		public static string NSW = "NSW";

		public static string V = "V";

		public static string T = "T";

		public static string RED = "RED";

		public static string BLUE = "BLUE";

		public static string GREEN = "GREEN";

//		private MapCSP(ArrayList variables, Constraint constraints): this(variables, constraints)
//		{
//			//super(variables, constraints);
//			
//		}

		public static CSP getMap() 
		{
			ArrayList variables = new ArrayList();
			variables.Add(WA);
			variables.Add(NT);
			variables.Add(SA);
			variables.Add(Q);
			variables.Add(NSW);
			variables.Add(V);
			variables.Add(T);

			ArrayList colors = new ArrayList();
				colors.Add(RED);
			colors.Add(BLUE);
			colors.Add(GREEN);

			Domain domains = new Domain(variables);
			for (int i = 0; i < variables.Count; i++) 
			{
				string variable = variables[i].ToString();
				domains.addToDomain(variable, colors);
			}

			Hashtable neighbors = new Hashtable();
			addToNeighbors(neighbors, T);
			addToNeighbors(neighbors, WA, NT, SA);
			addToNeighbors(neighbors, NT, WA, SA, Q);
			addToNeighbors(neighbors, SA, WA, NT, Q, NSW, V);
			addToNeighbors(neighbors, Q, NT, SA, NSW);
			addToNeighbors(neighbors, NSW, SA, Q, V);
			addToNeighbors(neighbors, V, SA, NSW);
			Constraint mapConstraints = new MapColoringConstraint(neighbors);

			return new CSP(variables, mapConstraints, domains);
		}

		public static void addToNeighbors(Hashtable neighbors, string whose) 
		{
			ArrayList l = new ArrayList();
			neighbors.Add(whose, l);
		}

		public static void addToNeighbors(Hashtable neighbors, string whose,
			string one) 
		{
			ArrayList l = new ArrayList();
			l.Add(one);
			neighbors.Add(whose, l);
		}

		public static void addToNeighbors(Hashtable neighbors, string whose,
			string one, string two) 
		{
			ArrayList l = new ArrayList();
			l.Add(one);
			l.Add(two);
			neighbors.Add(whose, l);
		}

		public static void addToNeighbors(Hashtable neighbors, string whose,
			string one, string two, string three) 
		{
			ArrayList l = new ArrayList();
			l.Add(one);
			l.Add(two);
			l.Add(three);
			neighbors.Add(whose, l);
		}

		public static void addToNeighbors(Hashtable neighbors, string whose,
			string one, string two, string three, string four) 
		{
			ArrayList l = new ArrayList();
			l.Add(one);
			l.Add(two);
			l.Add(three);
			l.Add(four);
			neighbors.Add(whose, l);
		}

		public static void addToNeighbors(Hashtable neighbors, string whose,
			string one, string two, string three, string four, string five) 
		{
			ArrayList l = new ArrayList();
			l.Add(one);
			l.Add(two);
			l.Add(three);
			l.Add(four);
			l.Add(five);
			neighbors.Add(whose, l);
		}
	}
}
