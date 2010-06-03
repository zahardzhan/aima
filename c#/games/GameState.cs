using System;
using System.Collections;

namespace aima.games
{
	/// <summary>
	/// Summary description for GameState.
	/// </summary>
	public class GameState 
	{
		private Hashtable state;

		// extends Hashtable{
		public GameState() 
		{
			state = new Hashtable();
		}

		public override bool Equals(Object anotherState) 
		{

			if( this == anotherState ) 
			{
				return true;
			}
			if((anotherState == null) || (this.GetType() != anotherState.GetType()))
			{
				return false;
			}
			GameState another = (GameState) anotherState;
			//Set keySet1 = state.keySet();
			//Iterator i = keySet1.iterator();
			IEnumerator i = state.Keys.GetEnumerator();
			//Iterator j = another.state.keySet().iterator();
			IEnumerator j = another.state.Keys.GetEnumerator();
			while (i.MoveNext()) 
			{
				string key = i.Current.ToString();
				bool keymatched = false;
				bool valueMatched = false;
				while (j.MoveNext()) 
				{
					string key2 = j.Current.ToString();
					if (key.Equals(key2)) 
					{
						keymatched = true;
						if (state[key].Equals(another.state[key2])) 
						{
							valueMatched = true;
						}
						break;
					}
				}
				if (!((keymatched) && valueMatched)) 
				{
					return false;
				}
			}
			return true;
		}
		public override int GetHashCode()
		{
			int result =17;
			IEnumerator i = state.Keys.GetEnumerator();
			while (i.MoveNext())
			{
				string s = i.Current.ToString();
				result = 37 * result + s.GetHashCode();
				result = 37 * result + state[s].GetHashCode();
			}
		
			return result;
		}

		public Object get(string key) 
		{
			return state[key];
		}

		public void put(string key,Object value) 
		{
			//state.Add(key,value);
			if (!state.Contains(key))
				state.Add(key, value);
			else
				state[key] = value;//not sure if i should be replacing this value here?
		
		}
	}
}
