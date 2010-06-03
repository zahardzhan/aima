using System;
using System.Collections;
using aima.search.csp;

namespace ConstraintSample
{
	/// <summary>
	/// Summary description for HousesCSP.
	/// </summary>
	public class HousesCSP : CSP 
	{ 
		static private HousesCSP instance = null;
        
		private HousesCSP(ArrayList variables, Constraint constraints, Domain domains) : base(variables, constraints, domains)
		{
			//super ;
		}
        
		public static CSP getMap() 
		{    
			if (instance != null) return instance;
            
			ArrayList variables = new ArrayList();
			variables.Add("blue");
			variables.Add("green");
			variables.Add("ivory");
			variables.Add("red");
			variables.Add("yellow");
			variables.Add("coffee");
			variables.Add("milk");
			variables.Add("juice");
			variables.Add("tea");
			variables.Add("water");
			variables.Add("englishman");
			variables.Add("japanese");
			variables.Add("norwegian");
			variables.Add("spaniard");
			variables.Add("ukrainian");
			variables.Add("dog");
			variables.Add("fox");
			variables.Add("horse");
			variables.Add("snails");
			variables.Add("zebra");
			variables.Add("chesterfield");
			variables.Add("kools");
			variables.Add("lucky-strike");
			variables.Add("old-gold");
			variables.Add("parliament");

            
            
			Domain domains = new Domain(variables);
			for (int i = 0; i < variables.Count; i++) 
			{
				string variable = variables[i].ToString();
				domains.addToDomain(variable, "1");
				domains.addToDomain(variable, "2");
				domains.addToDomain(variable, "3");
				domains.addToDomain(variable, "4");
				domains.addToDomain(variable, "5");
			}

            
             
			Constraint housesConstraints = new HousesConstraint();

			instance = new HousesCSP(variables, housesConstraints, domains); 
			return instance;
		}
	}
}
