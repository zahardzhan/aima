using System;
using System.Collections;

namespace aima.basic
{
	/// <summary>
	/// Summary description for Environment.
	/// </summary>
	public abstract class Environment 
	{

		protected ArrayList objects;

		protected ArrayList agents;

		protected ArrayList views;

		public abstract void executeAction(Agent a, String act);

		public abstract Percept getPerceptSeenBy(Agent anAgent);

		protected Environment() 
		{
			agents = new ArrayList();
			objects = new ArrayList();
			views = new ArrayList();
		}

		public void registerView(BasicEnvironmentView bev) 
		{
			views.Add(bev);
		}

		public void updateViews(string command) 
		{

//			for (BasicEnvironmentView view : views) 
//			{
//				view.envChanged(command);
//			}
			foreach(BasicEnvironmentView view in views)
			{
				view.envChanged(command);
			}
		}

		public bool isDone() 
		{

			foreach (Agent agent in agents) 
			{
				if (agent.isAlive()) 
				{
					return false;
				}
			}

			return true;
		}

		public void createExogenousChange() 
		{

		}

		public void step() 
		{
			if (!(this.isDone())) 
			{

				foreach (Agent agent in agents) 
				{

					String anAction = agent.execute(this.getPerceptSeenBy(agent));

					updateViews(anAction);
					this.executeAction(agent, anAction);
				}
				this.createExogenousChange();
			}
		}

		public void step(int n) 
		{

			for (int i = 0; i < n; i++) 
			{

				step();

			}
		}

		public void stepUntilNoOp() 
		{
			while (!(this.isDone())) 
			{
				step();
			}
		}

		public ArrayList getAgents() 
		{
			return agents;
		}

		public ArrayList getObjects() 
		{
			return objects;
		}

		public bool alreadyContains(EnvironmentObject o) 
		{

			bool retval = false;

			foreach (EnvironmentObject eo in objects) 
			{
				if (eo.Equals(o)) 
				{
					retval = true;
				}
			}

			return retval;
		}

		public bool alreadyContains(Agent anAgent) 
		{
			bool retval = false;
			foreach (Agent agent in agents) 
			{
				//if (agent.equals(anAgent)) 
				if (agent.Equals(anAgent)) 
				{
					retval = true;
				}
			}
			return retval;
		}

		public void addAgent(Agent a, string attributeName, Object attributeValue) 
		{
			if (!(alreadyContains(a))) 
			{
				a.setAttribute(attributeName, attributeValue);
				agents.Add(a);
			}
		}

		public void addObject(EnvironmentObject o, string attributeName,
			Object attributeValue) 
		{
			if (!(alreadyContains(o))) 
			{
				o.setAttribute(attributeName, attributeValue);
				objects.Add(o);
			}
		}

		public void addObject(EnvironmentObject o) 
		{
			if (!(alreadyContains(o))) 
			{
				objects.Add(o);
			}
		}

		public void addAgent(Agent a) 
		{
			if (!(alreadyContains(a))) 
			{
				agents.Add(a);
			}
		}

//		public List getAllObjects() 
//		{
//			ArrayList l = new ArrayList();
//				l.addAll(objects);
//			l.addAll(agents);
//			return l;
//		}
		public ArrayList getAllObjects() 
		{
			ArrayList l = new ArrayList();
			//l.a
				//l.addAll(objects);
			//l.addAll(agents);

			foreach (Object o in objects)
			{
				l.Add(o);
			}
			foreach (Object o in agents)
			{
				l.Add(o);
			}
			return l;
		}

	}
}
