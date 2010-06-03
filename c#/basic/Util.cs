using System;
using System.Collections;


namespace aima.basic
{
	/// <summary>
	/// Summary description for Util.
	/// </summary>
	public class Util 
	{

		static Random r = new Random();

		public static int min(int i, int j) 
		{
			return (i > j ? j : i);
		}

		public static int max(int i, int j) 
		{
			return (i < j ? j : i);
		}

		public static ArrayList range(int start, int end) 
		{
			ArrayList retVal = new ArrayList();
			for (int i = start; i <= end; i++) 
			{
				retVal.Add(i);
			}
			return retVal;
		}

		public static ArrayList getFilledArrayList(int size, int value) 
		{
			ArrayList retVal = new ArrayList();
			for (int i = 0; i < size; i++) 
			{
				retVal.Add(value);
			}
			return retVal;
		}

//		public static ArrayList split(string sourceString, string delimiter) 
//		{
//
//			Tokenizer tokenizer = new Tokenizer(sourceString, delimiter);
//			int tokenCount = tokenizer.countTokens();
//			ArrayList result = new ArrayList();
//			for (int i = 0; i < tokenCount; i++) 
//			{
//				result.add(tokenizer.nextToken());
//			}
//			if (result.get(result.size() - 1).equals("")) 
//			{
//				result.remove(result.size() - 1);
//			} //weird extra space token at the end ... fix later
//			return result;
//
//		}

		public static ArrayList getKeysAsArrayList(Hashtable h) 
		{
			ArrayList retVal = new ArrayList();
			//Set s = h.keySet();
			//Iterator i = s.iterator();
			IEnumerator i = h.Keys.GetEnumerator();
			while (i.MoveNext()) 
			{
				retVal.Add(i.Current);
			}
			return retVal;
		}

//		public static void printHashtable(Hashtable h) 
//		{
//			Enumeration e = h.keys();
//			while (e.hasMoreElements()) 
//			{
//				Object key = e.nextElement();
//				String keyString = key.toString();
//				String valueString = h.get(key).toString();
//				System.out.println(keyString + " : " + valueString);
//
//			}
//
//		}

//		public Object first(ArrayList l) 
//		{
//			List temp = new ArrayList();
//			//copy l in totemp
//			for (int i = 0; i < l.size(); i++) 
//			{
//				temp.add(l.get(i));
//			}
//			Object retVal = temp.remove(0);
//			return retVal;
//
//		}

//		public List rest(List l) 
//		{
//			List temp = new ArrayList();
//			//copy l in totemp
//			for (int i = 0; i < l.size(); i++) 
//			{
//				temp.add(l.get(i));
//			}
//			Object retVal = temp.remove(0);
//			return temp;
//
//		}

		public static Object selectRandomlyFromList(ArrayList l) 
		{
			//System.out.println("size = " +l.size());
			int index = r.Next(l.Count);
			//System.out.println(index);
			return l[index];
		}

//		public static void printHashtableKeys(Hashtable h) 
//		{
//			Enumeration e = h.keys();
//			while (e.hasMoreElements()) 
//			{
//				Object key = e.nextElement();
//				String keyString = key.toString();
//
//				System.out.println(keyString);
//
//			}
//		}
	}
}
