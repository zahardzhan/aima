using System;

namespace aima.learning.framework
{
	/// <summary>
	/// Summary description for NumericAttributeSpecification.
	/// </summary>
	public class NumericAttributeSpecification : AttributeSpecification 
	{

		// a simple attribute representing a number reprsented as a double .
		private string name;

		public NumericAttributeSpecification (string name)
		{
			this.name = name;
		}
		public bool isValid(string str) 
		{
			try
			{
				double.Parse(str);
				return true;
			}
			catch 
			{
				return false;
			}
		}

		public string getAttributeName() 
		{
			return name;
		}

		public Attribute createAttribute(string rawValue) 
		{
			return (Attribute)(new NumericAttribute(double.Parse(rawValue),this));
		}
	}
}
