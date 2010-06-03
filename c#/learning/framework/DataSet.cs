using System;
using aima.util;
using System.Collections;

namespace aima.learning.framework
{
	/// <summary>
	/// Summary description for DataSet.
	/// </summary>
	public class DataSet 
	{
		protected DataSet() 
		{

		}

		public ArrayList examples;

		public DataSetSpecification specification;

		public DataSet(DataSetSpecification spec) 
		{
			examples = new ArrayList();
			this.specification = spec;
		}

		public void add(Example e) 
		{
			examples.Add(e);
		}

		public int size() 
		{
			return examples.Count;
		}

		public Example getExample(int number) 
		{
			return (Example)examples[number];
		}

		public DataSet removeExample(Example e) 
		{
			DataSet ds = new DataSet(specification);
			foreach (Example eg in examples) 
			{
				if (!(e.Equals(eg))) 
				{
					ds.add(eg);
				}
			}
			return ds;
		}

		public double getInformationFor() 
		{
			String attributeName = specification.getTarget();
			Hashtable counts = new Hashtable();
			foreach (Example e in examples) 
			{

				String val = e.getAttributeValueAsString(attributeName);
				if (counts.Contains(val)) 
				{
					counts[val] = (((int)counts[val]) + 1);
				} 
				else 
				{
					counts.Add(val, 1);
				}
			}

			//double totalTargetAttributeCount = 0; not used

			double[] data = new double[counts.Keys.Count];
			IEnumerator iter = counts.Values.GetEnumerator();
			for (int i = 0; i < data.Length; i++) 
			{
				iter.MoveNext();
				data[i] = double.Parse(iter.Current.ToString());
			}
			data = Util.normalize(data);

			return Util.information(data);
		}

		public Hashtable splitByAttribute(string attributeName) 
		{
			Hashtable results = new Hashtable();
			foreach (Example e in examples) 
			{
				string val = e.getAttributeValueAsString(attributeName);
				if (results.Contains(val)) 
				{
					//results.get(val).add(e);
					((DataSet)results[val]).add(e);
				} 
				else 
				{
					DataSet ds = new DataSet(specification);
					ds.add(e);
					//results.put(val, ds);
					results.Add(val,ds);
				}
			}
			return results;
		}

		public double calculateGainFor(string parameterName) 
		{
			Hashtable hash = splitByAttribute(parameterName);
			double totalSize = examples.Count;
			double remainder = 0.0;
			foreach (string parameterValue in hash.Keys) 
			{
				double reducedDataSetSize = ((DataSet)hash[parameterValue]).examples.Count;
//				double reducedDataSetSize = hash.get(parameterValue).examples
//					.size();
				remainder += (reducedDataSetSize / totalSize)
					* ((DataSet)hash[parameterValue]).getInformationFor();
			}
			return getInformationFor() - remainder;
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
			DataSet other = (DataSet) o;
			return examples.Equals(other.examples);
		}

		public override int GetHashCode()
		{
			return 0;
		}

		public IEnumerator GetEnumerator() 
		{
			return examples.GetEnumerator();
		}

		public DataSet copy() 
		{
			DataSet ds = new DataSet(specification);
			foreach (Example e in examples) 
			{
				ds.add(e);
			}
			return ds;
		}

		public ArrayList getAttributeNames() 
		{
			return specification.getAttributeNames();
		}

		public string getTargetAttributeName() 
		{
			return specification.getTarget();
		}

		public DataSet emptyDataSet() 
		{
			return new DataSet(specification);
		}

		/**
		 * @param specification
		 *            The specification to set. USE SPARINGLY for testing etc ..
		 *            makes no semantic sense
		 */
		public void setSpecification(DataSetSpecification specification) 
		{
			this.specification = specification;
		}

		public ArrayList getPossibleAttributeValues(string attributeName) 
		{
			return specification.getPossibleAttributeValues(attributeName);
		}

		public DataSet matchingDataSet(string attributeName, string attributeValue) 
		{
			DataSet ds = new DataSet(specification);
			foreach (Example e in examples) 
			{
				if (e.getAttributeValueAsString(attributeName).Equals(attributeValue)) 
				{
					ds.add(e);
				}
			}
			return ds;
		}

		public ArrayList getNonTargetAttributes() 
		{
			return Util.removeFrom(getAttributeNames(), getTargetAttributeName());
		}

	
	}
}
