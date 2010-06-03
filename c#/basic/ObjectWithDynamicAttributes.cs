using System;
using System.Collections;

namespace aima.basic
{
	/// <summary>
	/// Summary description for ObjectWithDynamicAttributes.
	/// </summary>
	public class ObjectWithDynamicAttributes 
	{
		private Hashtable attributes = new Hashtable();

		public void setAttribute(Object key, Object value) 
		{
			attributes.Add(key, value);
		}

		public Object getAttribute(Object key) 
		{
			return attributes[key];
		}
	}
}
