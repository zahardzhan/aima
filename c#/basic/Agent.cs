using System;
using System.Collections;

namespace aima.basic
{
	/// <summary>
	/// Summary description for Agent.
	/// </summary>
	public abstract class Agent : ObjectWithDynamicAttributes 
	{
		protected AgentProgram program;

		protected bool _isAlive;

		protected Hashtable enviromentSpecificAttributes;

		protected Agent() 
		{
			live();

		}

		public Agent(AgentProgram aProgram)  : this()
		{
			program = aProgram;
		}

		public string execute(Percept p) 
		{
			return program.execute(p);
		}

		public void live() 
		{
			_isAlive = true;
		}

		public void die() 
		{
			_isAlive = false;
		}

		public bool isAlive() 
		{
			return _isAlive;
		}

	}
}
