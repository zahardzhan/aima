using System;

namespace aima.learning.framework
{
	/// <summary>
	/// Summary description for Learner.
	/// </summary>
	public interface Learner 
	{
		void train(DataSet ds);
		string predict(Example e);
		int[] test(DataSet ds);
	}
}
