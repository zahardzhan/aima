using System;

namespace aima.learning.framework
{
	/// <summary>
	/// Summary description for NumericAttribute.
	/// </summary>
	public class NumericAttribute : Attribute 
	{
		double value;
		private NumericAttributeSpecification spec;
		public NumericAttribute(double rawvalue ,NumericAttributeSpecification spec)
		{
			this.value = rawvalue;
			this.spec =  spec;
		}
		public string valueAsString() 
		{
			return value.ToString();
		}

		public string name() 
		{
			return spec.getAttributeName().Trim();
		}
	
		public double valueAsDouble() 
		{
			return value;
		}

	}
}
