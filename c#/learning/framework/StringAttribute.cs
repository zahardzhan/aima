using System;

namespace aima.learning.framework
{
	/// <summary>
	/// Summary description for StringAttribute.
	/// </summary>
	public class StringAttribute : Attribute 
	{
		private StringAttributeSpecification spec;
		private string value;

		public StringAttribute(string value,StringAttributeSpecification spec) 
		{
			this.spec = spec;
			this.value = value;
		}
		public string valueAsString()
		{
			return value.Trim();
		}
	
		public string name()
		{
			return spec.getAttributeName().Trim();
		}

	}
}
