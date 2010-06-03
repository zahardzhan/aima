using System;

namespace BucharestSearchSample
{
	/// <summary>
	/// Summary description for Q3State.
	/// </summary>
	public class Q4State 
	{

		public string location = "";
    
		public Q4State() {}
    
		public Q4State(string location)
		{
			this.location = location + "";
		}
    
		public Q4State(Q4State state) 
		{
			this.location = state.location;
		}
    
		public override bool Equals(object obj)
		{
			Q4State state = (Q4State) obj;
			return location.ToLower().Equals(state.location.ToLower());
		}
    
		public override int GetHashCode()
		{
			return location.GetHashCode();
		}
  
	}

}
