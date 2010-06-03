using System;
using System.Collections;

namespace aima.learning.framework
{
	/// <summary>
	/// Summary description for StringAttributeSpecification.
	/// </summary>
	public class StringAttributeSpecification : AttributeSpecification
	{
		String attributeName;

		ArrayList attributePossibleValues;

		public StringAttributeSpecification(string attributeName,
			ArrayList attributePossibleValues) 
		{
			this.attributeName = attributeName;
			this.attributePossibleValues = attributePossibleValues;
		}

		public StringAttributeSpecification(string attributeName,
			String[] attributePossibleValues) 
		{
			//this(attributeName, Arrays.asList(attributePossibleValues));
			
			//StringAttributeSpecification(attributeName, attributePossibleValues);
			this.attributeName = attributeName;
			//this.attributePossibleValues = System.Array.attributePossibleValues.;
			foreach (string str in attributePossibleValues)
			{
				this.attributePossibleValues.Add(str);
			}
		}

		public bool isValid(string value) 
		{
			return (attributePossibleValues.Contains(value));
		}

		/**
		 * @return Returns the attributeName.
		 */
		public string getAttributeName() 
		{
			return attributeName;
		}

		public ArrayList possibleAttributeValues() 
		{
			return attributePossibleValues;
		}

		public Attribute createAttribute(string rawValue) 
		{
			return (Attribute)(new StringAttribute(rawValue,this));
		}
	}
}
