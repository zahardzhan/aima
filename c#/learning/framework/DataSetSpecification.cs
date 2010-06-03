using System;
using System.Collections;

namespace aima.learning.framework
{
	/// <summary>
	/// Summary description for DataSetSpecification.
	/// </summary>
	public class DataSetSpecification 
	{
		ArrayList attributeSpecifications;

		private string targetAttribute;

		public DataSetSpecification() 
		{
			this.attributeSpecifications = new ArrayList();
		}

		public bool isValid(ArrayList uncheckedAttributes) 
		{
			if (attributeSpecifications.Count != uncheckedAttributes.Count) 
			{
				throw new Exception("size mismatch specsize = "
					+ attributeSpecifications.Count + " attrbutes size = "
					+ uncheckedAttributes.Count);
			}
			IEnumerator attributeSpecIter = attributeSpecifications.GetEnumerator();
			IEnumerator valueIter = uncheckedAttributes.GetEnumerator();
			while (valueIter.MoveNext() && attributeSpecIter.MoveNext()) 
			{
				if (!(((AttributeSpecification)(attributeSpecIter.Current)).isValid(valueIter.Current.ToString()))) 
				{
					return false;
				}
			}
			return true;
		}

		/**
		 * @return Returns the targetAttribute.
		 */
		public string getTarget() 
		{
			return targetAttribute;
		}

		public ArrayList getPossibleAttributeValues(string attributeName) 
		{
			foreach (AttributeSpecification asp in attributeSpecifications) 
			{
				if (asp.getAttributeName().Equals(attributeName)) 
				{
					return ((StringAttributeSpecification) asp)
						.possibleAttributeValues();
				}
			}
			throw new Exception("No such attribute" + attributeName);
		}

		public ArrayList getAttributeNames() 
		{
			ArrayList names = new ArrayList();
			foreach (AttributeSpecification asp in attributeSpecifications) 
			{
				names.Add(asp.getAttributeName());
			}
			return names;
		}

		public void defineStringAttribute(string name, string[] attributeValues) 
		{
			attributeSpecifications.Add(new StringAttributeSpecification(name,
				attributeValues));
			setTarget(name);// target defaults to last column added
		}

		/**
		 * @param targetAttribute
		 *            The targetAttribute to set.
		 */
		public void setTarget(string target) 
		{
			this.targetAttribute = target;
		}

		public AttributeSpecification getAttributeSpecFor(string name) 
		{
			foreach (AttributeSpecification spec in attributeSpecifications) 
			{
				if (spec.getAttributeName().Equals(name)) 
				{
					return spec;
				}
			}
			throw new Exception("no attribute spec for  " + name);
		}

		public void defineNumericAttribute(string name) 
		{
			attributeSpecifications.Add(new NumericAttributeSpecification(name));
		}

		public ArrayList getNamesOfStringAttributes() 
		{
			ArrayList names = new ArrayList();
			foreach (AttributeSpecification spec in attributeSpecifications)
			{
				if (spec is StringAttributeSpecification)
				{
					names.Add(spec.getAttributeName());
				}
			}
			return names;
		}

	}
}
