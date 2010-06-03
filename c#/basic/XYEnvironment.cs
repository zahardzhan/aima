using System;
using System.Collections;
using aima.util;

namespace aima.basic
{
	/// <summary>
	/// Summary description for XYEnvironment.
	/// </summary>
	public class XYEnvironment : Environment 
	{
		public static string LOCATION = "location";

		int width;

		int height;

		XYLocation defaultLocation;

		public XYEnvironment() 
		{

		}

		public XYEnvironment(int width, int height) 
		{

			this.width = width;
			this.height = height;
			this.defaultLocation = new XYLocation(1, 1);
		}

		public void addObject(EnvironmentObject o, XYLocation loc) 
		{

			base.addObject(o, LOCATION, loc);
		}

		public void addAgent(Agent a, XYLocation loc) 
		{
			base.addAgent(a, LOCATION, loc);
		}

		public void moveObjectToAbsoluteLocation(Agent a, XYLocation loc) 
		{

			a.setAttribute(LOCATION, loc);

		}

		public void moveObject(Agent a, String direction) 
		{
			XYLocation presentLocation = (XYLocation) a.getAttribute(LOCATION);
			XYLocation locationToMoveTo = presentLocation.locationAt(direction);

			if (!(isBlocked(locationToMoveTo))) 
			{
				moveObjectToAbsoluteLocation(a, locationToMoveTo);
			}

		}

		public ArrayList getObjectsAt(XYLocation loc) 
		{

			ArrayList retval = new ArrayList();

			ArrayList all = getAllObjects();
			foreach (ObjectWithDynamicAttributes obj in all) 
			{
				XYLocation objLoc = (XYLocation) obj.getAttribute(LOCATION);
				if (objLoc.Equals(loc)) 
				{
					retval.Add(obj);
				}

			}
			return retval;
		}

		public ArrayList getObjectsNear(Agent agent, int radius) 
		{
			ArrayList retval = new ArrayList();

				XYLocation agentLocation = (XYLocation) agent.getAttribute(LOCATION);

			ArrayList all = getAllObjects();
			foreach (ObjectWithDynamicAttributes a in all) 
			{
				if (!(a.Equals(agent))) 
				{
					XYLocation otherAgentLocation = (XYLocation) a
						.getAttribute(LOCATION);
					if (withinRadius(radius, agentLocation, otherAgentLocation)) 
					{
						retval.Add(a);
					}
				}
			}
			return retval;
		}

		private bool withinRadius(int radius, XYLocation agentLocation,
			XYLocation objectLocation) 
		{
			int dist = Calculator.calculateSquareOfDistanceBetweenLocations(
				agentLocation, objectLocation);
			int radiusSquared = radius * radius;
			bool withinRadius = (dist <= radiusSquared);
			return withinRadius;
		}

		public override void executeAction(Agent a, String Action) 
		{

		}

		public override Percept getPerceptSeenBy(Agent anAgent) 
		{
			return new Percept();
		}

		public bool isBlocked(XYLocation loc) 
		{
			bool retval = false;
			ArrayList objs = this.getObjectsAt(loc);

			for (int i = 0; i < objs.Count; i++) 
			{
				EnvironmentObject eo = (EnvironmentObject) objs[i];
				//if (eo instanceof Wall) 
				if (eo is Wall)
				{
					retval = true;
				}
			}
			return retval;
		}

		public void makePerimeter() 
		{
			for (int i = 0; i < width; i++) 
			{
				XYLocation loc = new XYLocation(i, 0);
				XYLocation loc2 = new XYLocation(i, height - 1);
				addObject(new Wall(), loc);
				addObject(new Wall(), loc2);
			}

			for (int i = 0; i < height; i++) 
			{
				XYLocation loc = new XYLocation(0, i);
				XYLocation loc2 = new XYLocation(width - 1, i);
				addObject(new Wall(), loc);
				addObject(new Wall(), loc2);
			}

		}

	}
}
