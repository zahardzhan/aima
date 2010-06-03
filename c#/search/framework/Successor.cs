using System;

namespace aima.search.framework
{
	/// <summary>
	/// Summary description for Successor.
	/// </summary>
	public class Successor 
	{

		private string action;

		private Object state;

		public Successor(string action, Object state) 
		{
			this.action = action;
			this.state = state;
		}

		public string getAction() 
		{
			return action;
		}

		public Object getState() 
		{
			return state;
		}
	}
}
