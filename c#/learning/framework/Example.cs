using System;
using System.Collections;

namespace aima.learning.framework
{
	/// <summary>
	/// Summary description for Example.
	/// </summary>
	public class Example 
	{
		Hashtable attributes;

		private Attribute targetAttribute;

		public Example(Hashtable attributes,
			Attribute targetAttribute) 
		{
			this.attributes = attributes;
			this.targetAttribute = targetAttribute;
		}

		public string getAttributeValueAsString(string attributeName) 
		{
			//return attributes[attributeName].valueAsString();
			return ((Attribute)(attributes[attributeName])).valueAsString();
		}
	
		public double getAttributeValueAsDouble(string attributeName) 
		{
			Attribute attribute =  (Attribute)attributes[attributeName];
			if(attribute == null || !(attribute is NumericAttribute) )
			{
				throw new Exception("cannot return numerical value for non numeric attribute");
			}
			
			return ((NumericAttribute)attribute).valueAsDouble();;
		}
		public override string ToString() 
		{
			return attributes.ToString();
		}

		public string targetValue() 
		{
			return getAttributeValueAsString(targetAttribute.name());
		}

		public override bool Equals(Object o) 
		{
			if (this == o) 
			{
				return true;
			}
			if ((o == null) || (this.GetType() != o.GetType()))
			{
				return false;
			}
			Example other = (Example) o;
			return attributes.Equals(other.attributes);
		}

		public override int GetHashCode() 
		{
			return attributes.GetHashCode();
		}

		public Example numerize(Hashtable attrValueToNumber) 
		{
			Hashtable numerizedExampleData = new Hashtable();
			foreach (string key in attributes.Keys)
			{
				Attribute attribute = (Attribute)attributes[key];
				if ( attribute is StringAttribute)
				{
					int correspondingNumber = int.Parse(((Hashtable)(attrValueToNumber[key]))[attribute.valueAsString()].ToString());
					NumericAttributeSpecification spec = new NumericAttributeSpecification(key);
					if (numerizedExampleData.Contains(key))
						numerizedExampleData[key] = new NumericAttribute((double)correspondingNumber,spec);
					else
						numerizedExampleData.Add(key,new NumericAttribute((double)correspondingNumber,spec));
					
				}
				else 
				{//Numeric Attribute
					if (numerizedExampleData.Contains(key))
						numerizedExampleData[key] = attribute;
					else
						numerizedExampleData.Add(key,attribute);
				}
			}
			return new Example(numerizedExampleData,(Attribute)numerizedExampleData[targetAttribute.name()]);
		}
	}
}
