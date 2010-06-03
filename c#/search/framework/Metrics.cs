using System;
using System.Collections;

namespace aima.search.framework
{
	/// <summary>
	/// Summary description for Metrics.
	/// </summary>
	public class Metrics 
	{
		private Hashtable hash;

		public Metrics() 
		{
			this.hash = new Hashtable();
		}

		public void set(string name, int i) 
		{
			if (!hash.Contains(name))
				hash.Add(name, i.ToString());
			else
				hash[name] = i;//should i replace the value here?
		}

		public int getInt(String name) 
		{
			return int.Parse(hash[name].ToString());
		}

		public void set(string name, Object val) 
		{
			hash.Add(name, val);
		}

//		public Object get(string name) 
//		{
//			return hash[name];
//		}

		public ICollection keySet() 
		{
			return hash.Keys;
		}

		public string get(String key) 
		{
			return hash[key].ToString();
		}

	}
}
