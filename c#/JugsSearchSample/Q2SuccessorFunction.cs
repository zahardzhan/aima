using System;
using aima.search.framework;
using System.Collections;

namespace JugsSearchSample
{
	/// <summary>
	/// Summary description for Q2SuccessorFunction.
	/// </summary>
	public class Q2SuccessorFunction 
		: aima.search.framework.SuccessorFunction 
	{   
		public ArrayList getSuccessors(Object state)
		{
			ArrayList list = new ArrayList(20);
			Q2State jstate = (Q2State) state;
        
			//By filling
			for(int i=0; i<3; i++) 
			{
				if (jstate.jugArray[i] < Q2State.capacityArray[i]) 
				{
					Q2State successor_state = new Q2State(jstate);
					successor_state.jugArray[i] = Q2State.capacityArray[i];
					Successor s = new Successor("fill " + i, successor_state);
					list.Add(s);
				}
			}
			//By emptying
			for(int i=0; i<3; i++) 
			{
				if (jstate.jugArray[i] > 0) 
				{
					Q2State successor_state = new Q2State(jstate);
					successor_state.jugArray[i] = 0;
					Successor s = new Successor("empty " + i, successor_state);
					list.Add(s);
				}
			}                   
			//By pouring j to i
			for(int i=0; i<3; i++) 
			{
				for(int j=0; j<3; j++) 
				{
					if (j != i) 
					{
						int newjug_i = min(jstate.jugArray[i] + jstate.jugArray[j], Q2State.capacityArray[i]);
						int juginc_i = newjug_i - jstate.jugArray[i];
						if (juginc_i > 0) 
						{
							Q2State successor_state = new Q2State(jstate);
							successor_state.jugArray[i] += juginc_i;
							successor_state.jugArray[j] -= juginc_i;
							Successor s = new Successor("pouring " + j + " to " + i, successor_state);
							list.Add(s);
						}
					}
				}
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
