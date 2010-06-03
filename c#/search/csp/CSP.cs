using System;
using System.Collections;
using aima.basic;

namespace aima.search.csp
{
	/// <summary>
	/// Summary description for CSP.
	/// </summary>
	public class CSP 
	{

		//private Assignment assignment;

		private Domain domains;

		private Constraint constraints;

		private ArrayList variables;

		public CSP(){}
		public CSP(ArrayList variables, Constraint constraints) 
		{
			this.variables = variables;
			//this.assignment = new Assignment(variables);
			this.domains = new Domain(variables);
			this.constraints = constraints;
		}

		public CSP(ArrayList variables, Constraint constraints, Domain domains) 
		{
			this.variables = variables;
			//this.assignment = new Assignment(variables);
			this.domains = domains;
			this.constraints = constraints;
		}

		public ArrayList defaultOrderDomainOf(string variable) 
		{
			return domains.getDomainOf(variable);
		}

		public Assignment backTrackingSearch() 
		{
			return recursiveBackTrackingSearch(new Assignment(variables));
		}

		private Assignment recursiveBackTrackingSearch(Assignment anAssignment) 
		{
			if (anAssignment.isComplete()) 
			{
				return anAssignment;
			}
			string variable = anAssignment.selectFirstUnassignedVariable();
			ArrayList domainValues = defaultOrderDomainOf(variable);
			for (int i = 0; i < domainValues.Count; i++) 
			{
				Object value = domainValues[i];

				if (constraints.isSatisfiedWith(anAssignment, variable, value)) 
				{
					anAssignment.setAssignment(variable, value);
					Assignment result = recursiveBackTrackingSearch(anAssignment);
					if (result != null) 
					{
						return result;
					}
					anAssignment.remove(variable);
				}
			}
			return null;//failure
		}

		public Assignment mcSearch(int maxSteps) 
		{
			Assignment randomAssignment = generateRandomAssignment();

			for (int i = 0; i < maxSteps; i++) 
			{

				if (randomAssignment.satisfies(constraints)) 
				{
					return randomAssignment;
				} 
				else 
				{
					string conflictedVariable = Util
						.selectRandomlyFromList(randomAssignment.getConflictedVariables(constraints)).ToString();
					Object minConflictValue = randomAssignment
						.getMinimumConflictingValueFor(conflictedVariable,
						domains.getDomainOf(conflictedVariable),
						constraints);
					randomAssignment.setAssignment(conflictedVariable,
						minConflictValue);
				}
			}
			return null;

		}

		private Assignment generateRandomAssignment() 
		{
			ArrayList vars = new ArrayList();
			for (int i = 0; i < variables.Count; i++) 
			{
				vars.Add(variables[i]);
			}
			Assignment assignment = new Assignment(vars);
			for (int i = 0; i < variables.Count; i++) 
			{
				string variable = variables[i].ToString();
				Object randomValue = Util.selectRandomlyFromList(domains
					.getDomainOf(variable));
				//System.out.println("in generate Assignment setting");
				assignment.setAssignment(variable, randomValue);
			}
			return assignment;
		}

	}
}
