using System;
using System.Collections;
using aima.search.csp;

namespace ConstraintSample
{
	/// <summary>
	/// Summary description for HousesConstraint.
	/// </summary>
	public class HousesConstraint : Constraint 
	{

		public bool isSatisfiedWith( Assignment assignment, 
			string variable,
			Object value) 
		{
			//Checking constraints
		
			int intVal = int.Parse(value.ToString());
		
			Assignment a2 = assignment.copy();
			a2.setAssignment(variable, value);

			//uniqueness constraints
			//colours
			if (!passesUniqueClass("blue","yellow","red","green","ivory",a2))return false;
	    
			//drinks
			if (!passesUniqueClass("coffee","tea","milk","juice","water",a2))return false;
	    
			//nationality
			if (!passesUniqueClass("norwegian","englishman","japanese","ukrainian","spaniard",a2))return false;
	    
			//	    pets
			if (!passesUniqueClass("fox","horse","dog","snails","zebra",a2))return false;
	    
			//	    cigarettes
			if (!passesUniqueClass("parliament","kools","lucky-strike","chesterfield","old-gold",a2))return false;
		
			//14 constraints:
			//1
			if (a2.hasAssignmentFor("englishman") && a2.hasAssignmentFor("red"))
				if (!a2.getAssignment("englishman").Equals(a2.getAssignment("red")))
					return false;
	     
			//2
			if (a2.hasAssignmentFor("spaniard") && a2.hasAssignmentFor("dog"))
				if (!a2.getAssignment("spaniard").Equals(a2.getAssignment("dog")))
					return false;
	     
			//3
			if (a2.hasAssignmentFor("coffee") && a2.hasAssignmentFor("green"))
				if (!a2.getAssignment("coffee").Equals(a2.getAssignment("green")))
					return false;
	     
			//4
			if (a2.hasAssignmentFor("ukrainian") && a2.hasAssignmentFor("tea"))
				if (!a2.getAssignment("ukrainian").Equals(a2.getAssignment("tea")))
					return false;
	     
			//5
			if (a2.hasAssignmentFor("green") && a2.hasAssignmentFor("ivory"))
			{
				//green must be directly to the right of ivory
				int intGreen = int.Parse(a2.getAssignment("green").ToString());
				int intIvory = int.Parse(a2.getAssignment("ivory").ToString());
	    	
				if ((intGreen - intIvory) != 1)
					return false;
			}
			
			//6
			if (a2.hasAssignmentFor("old-gold") && a2.hasAssignmentFor("snails"))
				if (!a2.getAssignment("old-gold").Equals(a2.getAssignment("snails")))
					return false;
		    
			//7
			if (a2.hasAssignmentFor("kools") && a2.hasAssignmentFor("yellow"))
				if (!a2.getAssignment("kools").Equals(a2.getAssignment("yellow")))
					return false;
        
			//8
        
			if (a2.hasAssignmentFor("milk"))
			{
				int intMilk = int.Parse(a2.getAssignment("milk").ToString());
				if (intMilk != 3)
					return false;
			}
                            
        
        
			//9
			if (a2.hasAssignmentFor("norwegian"))
			{
				int intNorwegian = int.Parse(a2.getAssignment("norwegian").ToString());
				if (intNorwegian != 1)
					return false;
			}

			
			//10.
			if (a2.hasAssignmentFor("chesterfield") && a2.hasAssignmentFor("fox"))
			{
				int int1 = int.Parse( a2.getAssignment("chesterfield").ToString());
				int int2 = int.Parse(a2.getAssignment("fox").ToString());
				
				if (System.Math.Abs(int1 - int2) != 1)
					return false;
			}
		    
			//11.
			if (a2.hasAssignmentFor("kools") && a2.hasAssignmentFor("horse"))
			{
				int int1 = int.Parse((String) a2.getAssignment("kools").ToString());
				int int2 = int.Parse((String) a2.getAssignment("horse").ToString());
				if (System.Math.Abs(int1 - int2) != 1)
					return false;
			}
		    
			//12
			if (a2.hasAssignmentFor("lucky-strike") && a2.hasAssignmentFor("juice"))
				if (!a2.getAssignment("lucky-strike").Equals(a2.getAssignment("juice")))
					return false;
		    
			//13.
			if (a2.hasAssignmentFor("japanese") && a2.hasAssignmentFor("parliament"))
				if (!a2.getAssignment("japanese").Equals(a2.getAssignment("parliament")))
					return false;
		    
			//14.
			if (a2.hasAssignmentFor("norwegian") && a2.hasAssignmentFor("blue"))
			{
				int int1 = int.Parse(a2.getAssignment("norwegian").ToString());
				int int2 = int.Parse(a2.getAssignment("blue").ToString());
				if (System.Math.Abs(int1 - int2) != 1)
					return false;
			}
        
			return true;
		}    

		/*
		 * returns false if the assignment has more than one of each class assigned to it
		 * (ie color, cigarette, drink, etc)
		 */
		private bool passesUniqueClass(string s1, string s2,string s3, string s4, string s5, Assignment assignment)
		{

			if (!passesUnique(s1,s2,assignment))return false;

			if (!passesUnique(s1,s3,assignment))return false;

			if (!passesUnique(s1,s4,assignment))return false;

			if (!passesUnique(s1,s5,assignment))return false;

			if (!passesUnique(s2,s3,assignment))return false;

			if (!passesUnique(s2,s4,assignment))return false;

			if (!passesUnique(s2,s5,assignment))return false;

			if (!passesUnique(s3,s4,assignment))return false;

			if (!passesUnique(s3,s5,assignment))return false;

			if (!passesUnique(s4,s5,assignment))return false;
	    
			return true;
		}
		private bool passesUnique(string s1, string s2, Assignment a2)
		{
			if (a2.hasAssignmentFor(s1) && a2.hasAssignmentFor(s2))
				if (a2.getAssignment(s1).Equals(a2.getAssignment(s2)))
					return false;
			return true;
		}
	}
}
