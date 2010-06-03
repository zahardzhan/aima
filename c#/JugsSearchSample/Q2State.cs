using System;

namespace JugsSearchSample
{
	/// <summary>
	/// Summary description for Q2State.
	/// </summary>
	public class Q2State 
	{
		public static int[] capacityArray = {12, 8, 3};
    
		public int[] jugArray = {0,0,0};
    
		public Q2State() {}
    
		public Q2State(Q2State state) 
		{
			for(int i=0; i<3; i++) 
				this.jugArray[i] = state.jugArray[i];
		}
		public override bool Equals(object obj)
		{
			Q2State state = (Q2State) obj;
        
			for (int i=0; i<3; i++)
				if (this.jugArray[i] != state.jugArray[i])
					return false;
        
			return true;
		}

		public override int GetHashCode()
		{
			return jugArray[0]*100 + jugArray[1]*10 + jugArray[2];
		}
  
	}
}
