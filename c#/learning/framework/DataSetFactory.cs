using System;
using aima.util;
using System.Collections;

namespace aima.learning.framework
{
	/// <summary>
	/// Summary description for DataSetFactory.
	/// </summary>
	public class DataSetFactory 
	{
	
		public  DataSet fromFile(string filename,DataSetSpecification spec,string separator)
		{
			// assumed file in data directory and ends in .csv
			DataSet ds = new DataSet(spec);
//			BufferedReader reader = new BufferedReader(new InputStreamReader(
//				this.getClass().getResourceAsStream("../data/" + filename + ".csv")));
//			string line;
//			while ((line = reader.readLine()) != null) 
//			{
//				ds.add(exampleFromString(line,spec,separator));
//			}
		
			return ds;

		}
	
		public static Example exampleFromString(string data,DataSetSpecification dataSetSpec,string separator)
		{
			Hashtable attributes = new Hashtable();
			//ArrayList attributeValues = Arrays.asList(data.Split(separator.ToCharArray()[0]));
			string[] splitData = data.Split(separator.ToCharArray()[0]);
			ArrayList attributeValues = new ArrayList();
			foreach (string str in splitData)
			{
				attributeValues.Add(str);
			}
			if (dataSetSpec.isValid(attributeValues))
			{
				ArrayList names = dataSetSpec.getAttributeNames();
				IEnumerator nameiter = names.GetEnumerator();
				IEnumerator valueiter = attributeValues.GetEnumerator();
				while(nameiter.MoveNext() && valueiter.MoveNext())
				{
					string name = nameiter.Current.ToString();
					AttributeSpecification attributeSpec = dataSetSpec.getAttributeSpecFor(name);
					Attribute attribute =  attributeSpec.createAttribute(valueiter.Current.ToString());
					//attributes.put(name,attribute);
					if (attributes.Contains(name))
						attributes[name] = attribute;
					else
						attributes.Add(name,attribute);
				}
				string targetAttributeName = dataSetSpec.getTarget();
				//AttributeSpecification attributeSpec =dataSetSpec.getAttributeSpecFor(targetAttributeName );
				AttributeSpecification _attributeSpec =dataSetSpec.getAttributeSpecFor(targetAttributeName );
				return new Example(attributes,(Attribute)attributes[targetAttributeName]);
			}
			else
			{
				throw new Exception("Unable to construct Example from " + data);
			}
		}
	
		public static DataSet getRestaurantDataSet()
		{
			DataSetSpecification spec = createRestaurantDataSetSpec();
			return new DataSetFactory().fromFile("restaurant",spec,"\\s+");
		}
	
	
	
		public static DataSetSpecification createRestaurantDataSetSpec() 
		{
			DataSetSpecification dss =  new DataSetSpecification();
			dss.defineStringAttribute("alternate",Util.yesno());
			dss.defineStringAttribute("bar",Util.yesno());
			dss.defineStringAttribute("fri/sat",Util.yesno());
			dss.defineStringAttribute("hungry",Util.yesno());
			dss.defineStringAttribute("patrons",new String[]{"None","Some","Full"});
			dss.defineStringAttribute("price",new String[]{"$","$$","$$$"});
			dss.defineStringAttribute("raining",Util.yesno());
			dss.defineStringAttribute("reservation",Util.yesno());
			dss.defineStringAttribute("type",new String[]{"French","Italian","Thai","Burger"});
			dss.defineStringAttribute("wait_estimate",new String[]{"0-10","10-30","30-60",">60"});
			dss.defineStringAttribute("will_wait",Util.yesno());
			//last attribute is the target attribute unless the target is explicitly reset with dss.setTarget(name)

			return dss;
		}
	
		public static DataSet getIrisDataSet()
		{
			DataSetSpecification spec = createIrisDataSetSpec();
			return new DataSetFactory().fromFile("iris",spec,",");
		}
		public static DataSetSpecification createIrisDataSetSpec() 
		{
			DataSetSpecification dss =  new DataSetSpecification();
			dss.defineNumericAttribute("sepal_length");
			dss.defineNumericAttribute("sepal_width");
			dss.defineNumericAttribute("petal_length");
			dss.defineNumericAttribute("petal_width");
			dss.defineStringAttribute("plant_category",new String[]{"setosa","versicolor","virginica"});
			return dss;
		}
	


	}
}
