using System;
using System.Collections;
using System.Text;


namespace aima.util
{
	/// <summary>
	/// Summary description for Util.
	/// </summary>
	/// 

	public class Util 
	{
		public static string NO = "No";

		public static string YES = "Yes";

		private static Random r = new Random();

		public static object first(ArrayList l) 
		{

			ArrayList newList = new ArrayList();
			foreach(object element in l)
			{
				newList.Add(element);
			}
			return newList[0];
		}

		public static ArrayList rest(ArrayList l) 
		{
			ArrayList newList = new ArrayList();
			foreach(object element in l)
			{
				newList.Add(element);
			}
			newList.RemoveAt(0);
			return newList;
		}

//		public static bool randomBoolean() 
//		{
//			int trueOrFalse = r.Next(2);//should this be 1?
//			return (!(trueOrFalse == 0));
//		}

		public static double[] normalize(double[] probDist) 
		{
			int len = probDist.Length;
			double total = 0.0;
			foreach (double d in probDist) 
			{
				total = total + d;
			}

			double[] normalized = new double[len];
			if (total != 0) 
			{
				for (int i = 0; i < len; i++) 
				{
					normalized[i] = probDist[i] / total;
				}
			}
			double totalN = 0.0;
			foreach (double d in normalized) 
			{
				totalN = totalN + d;
			}

			return normalized;
		}
	
		public static ArrayList normalize(ArrayList values) 
		{
			double[] valuesAsArray = new double[values.Count];
			for (int i=0;i<valuesAsArray.Length;i++)
			{
				valuesAsArray[i] = (double)values[i];
			}
			double[] normalized =  normalize(valuesAsArray);
			ArrayList results = new ArrayList();
			for (int i=0;i<normalized.Length;i++)
			{
				results.Add(normalized[i]);
			}
			return results;
		}

		public static int min(int i, int j) 
		{
			return (i > j ? j : i);
		}

		public static int max(int i, int j) 
		{
			return (i < j ? j : i);
		}
		public static int max(int i, int j,int k) 
		{
			return max (max(i,j),k);
		}
		public static int min(int i, int j,int k) 
		{
			return min (min(i,j),k);
		}

//		public static T selectRandomlyFromList(List l) 
//		{
//			int index = r.nextInt(l.size());
//			return l.get(index);
//		}

//		public static T mode(List l) 
//		{
//			Hashtable hash = new Hashtable();
//			foreach (T obj in l) 
//			{
//				if (hash.containsKey(obj)) 
//				{
//					hash.put(obj, hash.get(obj).intValue() + 1);
//				} 
//				else 
//				{
//					hash.put(obj, 1);
//				}
//			}
//		 
//			T maxkey = hash.keySet().iterator().next();
//			foreach (T key in hash.keySet()) 
//			{
//				if (hash.get(key) > hash.get(maxkey)) 
//				{
//					maxkey = key;
//				}
//			}
//			return maxkey;
//		}
//
		public static string[] yesno() 
		{
			return new string[] { YES, NO };
		}
//
//		public static double log2(double d) 
//		{
//			return Math.log(d) / Math.log(2);
//		}

		public static double information(double[] probabilities) 
		{
			double total = 0.0;
			foreach (double d in probabilities) 
			{
				total += (-1.0 * Math.Log(d,2) * d);
			}
			return total;
		}

		public static ArrayList removeFrom(ArrayList list,
			object member) 
		{
			ArrayList newList = new ArrayList();
			foreach (object s in list) 
			{
				if (!(s.Equals(member))) 
				{
					newList.Add(s);
				}
			}
			return newList;
		}

		public static double sumOfSquares(ArrayList list) 
		{
			double accum =0;
			foreach (object item in list)
			{
				accum = accum + ((double)item * (double)item);
			}
			return accum;
		}
	
		public static string ntimes(string s,int n)
		{
			StringBuilder buf = new StringBuilder();
			for (int i = 0; i < n; i++) 
			{
				buf.Append(s);
			}
			return buf.ToString();
		}

	}
}
