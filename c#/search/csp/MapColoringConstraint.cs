using System;
using System.Collections;

namespace aima.search.csp
{
	/// <summary>
	/// Summary description for MapColoringConstraint.
	/// </summary>
	public class MapColoringConstraint : Constraint 
	{
		private Hashtable neighbors;

		public MapColoringConstraint(Hashtable neighbors) 
		{
			this.neighbors = neighbors;
		}

		public bool isSatisfiedWith(Assignment assignment, string variable,
			Object value) 
		{
			ArrayList variableNeighbors = (ArrayList) neighbors[variable];
			for (int i = 0; i < variableNeighbors.Count; i++) 
			{
				string neighbor = variableNeighbors[i].ToString();
				if (assignment.hasAssignmentFor(neighbor)) 
				{
					string neighborColor = assignment.getAssignment(neighbor).ToString();
					if (neighborColor.Equals(value)) 
					{

						return false;
					}
				}
			}
			return true;
		}

	}
}
