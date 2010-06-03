using System;

namespace aima.learning.framework
{
	/// <summary>
	/// Summary description for AttributeSpecification.
	/// </summary>
	public interface AttributeSpecification 
	{

		bool isValid(string str);

		string getAttributeName();
	
		Attribute createAttribute(string rawValue);

	}
}
