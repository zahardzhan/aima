using System;
using System.Collections;
using aima.search.framework;

namespace SearchSamples
{
	/// <summary>
	/// Summary description for JocksNerdsSuccessorFunction.
	/// </summary>
	public class JocksNerdsSuccessorFunction : aima.search.framework.SuccessorFunction 
	{   
		public ArrayList getSuccessors(Object state)
		{
			ArrayList list = new ArrayList(20);
			JocksNerdsState jocksNerdsState = (JocksNerdsState) state;
        
			int numberNerdsLeft = jocksNerdsState.locationArray[0];
			int numberJocksLeft = jocksNerdsState.locationArray[1];
			int numberNerdsRight = 3 - jocksNerdsState.locationArray[0];
			int numberJocksRight = 3 - jocksNerdsState.locationArray[1];
			int turnCount = jocksNerdsState.locationArray[2];
        
			/*
        
			 if the turn count for the current state is even the boat is on on the left bank,
			 otherwise it's on the right side
			 try moving every combination of nerds and jocks to the opposite bank.
			 Also need to make sure that the # of jocks on one side never outnumbers the
			 number of nerds on that side.
         
			 */
        
			if(jocksNerdsState.locationArray[2] % 2 == 0)
			{
				//the boat's on the left so move people to the right
				JocksNerdsState successor_state;
             
             
             
				//move 1 nerd to the right if the Nerds won't be eaten as a result
				if (numberNerdsLeft > 0)
				{
					successor_state = new JocksNerdsState(jocksNerdsState);
					successor_state.locationArray[0] -= 1;
					successor_state.locationArray[1] = numberJocksLeft;
					successor_state.locationArray[2] = turnCount + 1;
					if(isValidState(successor_state))
					{
						Successor s = new Successor("move 1 nerd right (array = " + successor_state.locationArray[0] + ", " + successor_state.locationArray[1] + ", "  + successor_state.locationArray[2] + ")\n", successor_state);
						list.Add(s);
					}
                 
				}
            
            
				//move 2 Nerds right if the Nerds won't be eaten as a result
				if (numberNerdsLeft > 1)
				{
					successor_state = new JocksNerdsState(jocksNerdsState);
					successor_state.locationArray[0] -= 2;
					successor_state.locationArray[1] = numberJocksLeft;
					successor_state.locationArray[2] = turnCount + 1;
					if(isValidState(successor_state))
					{
						Successor s = new Successor("move 2 Nerds right (array = " + successor_state.locationArray[0] + ", " + successor_state.locationArray[1] + ", "  + successor_state.locationArray[2] + ")\n", successor_state);
						list.Add(s);
					}
                 
				}
            
            
				//move 1 Jock right if the Nerds won't be eaten as a result
				if (numberJocksLeft > 0)
				{
					successor_state = new JocksNerdsState(jocksNerdsState);
					successor_state.locationArray[0] = numberNerdsLeft;
					successor_state.locationArray[1] -= 1;
					successor_state.locationArray[2] = turnCount + 1;
					if(isValidState(successor_state))
					{
						Successor s = new Successor("move 1 Jock right (array = " + successor_state.locationArray[0] + ", " + successor_state.locationArray[1] + ", "  + successor_state.locationArray[2] + ")\n", successor_state);
						list.Add(s);
					}
                 
				}
            
				//move 2 Jocks right if the Nerds won't be eaten as a result
				if (numberJocksLeft > 1)
				{
					successor_state = new JocksNerdsState(jocksNerdsState);
					successor_state.locationArray[0] = numberNerdsLeft;
					successor_state.locationArray[1] -= 2;
					successor_state.locationArray[2] = turnCount + 1;
					if(isValidState(successor_state))
					{
						Successor s = new Successor("move 2 Jocks right (array = " + successor_state.locationArray[0] + ", " + successor_state.locationArray[1] + ", "  + successor_state.locationArray[2] + ")\n", successor_state);
						list.Add(s);
					}
                 
				}
            
				//move a Jock and a nerd right
				if (numberJocksLeft > 0 && numberNerdsLeft > 0)
				{
					successor_state = new JocksNerdsState(jocksNerdsState);
					successor_state.locationArray[0] -= 1;
					successor_state.locationArray[1] -= 1;
					successor_state.locationArray[2] = turnCount + 1;
					if(isValidState(successor_state))
					{
						Successor s = new Successor("move a nerd and Jock right (array = " + successor_state.locationArray[0] + ", " + successor_state.locationArray[1] + ", "  + successor_state.locationArray[2] + ")\n", successor_state);
						list.Add(s);
					}
                 
				}
            
			}   
			else
			{   
				//the boat is on the right so try moving people to the left
            
				//the boat is on the left so move people to the right
				JocksNerdsState successor_state;
             
             
             
				//move 1 nerd to the left if the Nerds won't be eaten as a result
				if (numberNerdsRight > 0)
				{
					successor_state = new JocksNerdsState(jocksNerdsState);
					successor_state.locationArray[0] += 1;
					successor_state.locationArray[1] = numberJocksLeft;
					successor_state.locationArray[2] = turnCount + 1;
					if(isValidState(successor_state))
					{
						Successor s = new Successor("move 1 nerd left (array = " + successor_state.locationArray[0] + ", " + successor_state.locationArray[1] + ", "  + successor_state.locationArray[2] + ")\n", successor_state);
						list.Add(s);
					}
                 
				}
            
            
				//move 2 Nerds left if the Nerds won't be eaten as a result
				if (numberNerdsRight> 1)
				{
					successor_state = new JocksNerdsState(jocksNerdsState);
					successor_state.locationArray[0] += 2;
					successor_state.locationArray[1] = numberJocksLeft;
					successor_state.locationArray[2] = turnCount + 1;
					if(isValidState(successor_state))
					{
						Successor s = new Successor("move 2 Nerds left (array = " + successor_state.locationArray[0] + ", " + successor_state.locationArray[1] + ", "  + successor_state.locationArray[2] + ")\n", successor_state);
						list.Add(s);
					}
                 
				}
            
            
				//move 1 Jock left if the Nerds won't be eaten as a result
				if (numberJocksRight > 0)
				{
					successor_state = new JocksNerdsState(jocksNerdsState);
					successor_state.locationArray[0] = numberNerdsLeft;
					successor_state.locationArray[1] += 1;
					successor_state.locationArray[2] = turnCount + 1;
					if(isValidState(successor_state))
					{
						Successor s = new Successor("move 1 Jock left (array = " + successor_state.locationArray[0] + ", " + successor_state.locationArray[1] + ", "  + successor_state.locationArray[2] + ")\n", successor_state);
						list.Add(s);
					}
                 
				}
            
				//move 2 Jocks left if the Nerds won't be eaten as a result
				if (numberJocksRight > 1)
				{
					successor_state = new JocksNerdsState(jocksNerdsState);
					successor_state.locationArray[0] = numberNerdsLeft;
					successor_state.locationArray[1] += 2;
					successor_state.locationArray[2] = turnCount + 1;
					if(isValidState(successor_state))
					{
						Successor s = new Successor("move 2 Jocks left (array = " + successor_state.locationArray[0] + ", " + successor_state.locationArray[1] + ", "  + successor_state.locationArray[2] + ")\n", successor_state);
						list.Add(s);
					}
                 
				}
            
				//move a Jock and a nerd left
				if (numberJocksRight > 0 && numberNerdsRight > 0)
				{
					successor_state = new JocksNerdsState(jocksNerdsState);
					successor_state.locationArray[0] += 1;
					successor_state.locationArray[1] += 1;
					successor_state.locationArray[2] = turnCount + 1;
					if(isValidState(successor_state))
					{
						Successor s = new Successor("move a nerd and Jock left (array = " + successor_state.locationArray[0] + ", " + successor_state.locationArray[1] + ", "  + successor_state.locationArray[2] + ")\n", successor_state);
						list.Add(s);
					}
                 
				}
            
        
			}
        
       
        
			return list;
		}
    
    
		//if the # of Jocks on a side is > the number of Nerds and there's at least one nerd 
		//on that side then the state is invalid
		private bool isValidState(JocksNerdsState state)
		{
        
			if ((state.locationArray[1] > state.locationArray[0] && state.locationArray[0] > 0) || ((3 - state.locationArray[1]) > (3 - state.locationArray[0]) && (3 - state.locationArray[0]) > 0))
			{
				return false;
			}
			return true;
		}
    
   
	}
}
