using System;

namespace SearchSamples
{
	/// <summary>
	/// Summary description for Q1State.
	/// </summary>
	public class JocksNerdsState
	{
		/*
		* array contains:
		* # of nerds on left bank
		* # of jocks on left bank
		* turn count (boat on left for even, on right for odd)
		*
		*/
		public int[] locationArray = {3,3,0};
    
		public JocksNerdsState() {}
    

		

		public JocksNerdsState(JocksNerdsState state) 
		{
			for(int i=0; i<3; i++) 
				this.locationArray[i] = state.locationArray[i];
		}
    

		//when creating states, it's absolutely CRITICAL to override
		//Equals and GetHashCode or the application won't be able
		//to evaluate GraphSearch properly
		
		
		//if the number of nerds or jocks differs, or the boat is on the opposite side, return false
		public override bool Equals(object o)
		{
			JocksNerdsState state = (JocksNerdsState) o;
			for (int i=0; i<2; i++)
				if (this.locationArray[i] != state.locationArray[i])
					return false;
			if((this.locationArray[2] % 2) != (state.locationArray[2] % 2))
				return false;
        
			return true;
		}
    
		public override int GetHashCode()
		{
			return locationArray[0]*1000 + locationArray[1]*100 + locationArray[2] % 2;
		}    

	}
}
