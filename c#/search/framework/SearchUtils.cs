using System;
using System.Collections;

namespace aima.search.framework
{
	/// <summary>
	/// Summary description for SearchUtils.
	/// </summary>
	public class SearchUtils 
	{

		public static ArrayList actionsFromNodes(ArrayList nodeList) 
		{
			ArrayList stateList = new ArrayList();
			for (int i = 1; i < nodeList.Count; i++) 
			{ //ignore root node this has
				// no action hence 1 not
				// zero
				Node node = (Node) nodeList[i];
				stateList.Add(node.getAction());
			}
			return stateList;
		}

		public static ArrayList stringToList(string str) 
		{

			ArrayList list = new ArrayList();
			list.Add(str);
			return list;

		}

		public static bool listMatches(ArrayList list, string str) 
		{
			return ((list.Count == 1) && ((list[0].ToString()).Equals(str)));
		}

	}
}
