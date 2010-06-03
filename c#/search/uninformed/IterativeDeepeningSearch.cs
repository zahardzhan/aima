using System;
using System.Collections;
using aima.search.framework;
using aima.search.nodestore;

namespace aima.search.uninformed
{
	/// <summary>
	/// Summary description for IterativeDeepeningSearch.
	/// </summary>
public class IterativeDeepeningSearch : NodeExpander , Search {

	private int limit;

	private Metrics iterationMetrics;

	public IterativeDeepeningSearch() {
		this.limit = 32000;//define an arbitrarily large default integer, or it will just keep on going....
		iterationMetrics = new Metrics();
		iterationMetrics.set(NODES_EXPANDED, 0);
	}

	public ArrayList search(Problem p)  {
		for (int i = 1; i <= limit; i++) {
			DepthLimitedSearch dls = new DepthLimitedSearch(i);
			ArrayList result = dls.search(p);
			iterationMetrics.set(NODES_EXPANDED, iterationMetrics
					.getInt(NODES_EXPANDED)
					+ dls.getMetrics().getInt(NODES_EXPANDED));
			if (!cutOffResult(result)) {
				return result;
			}
		}
		return new ArrayList();//failure
	}

	private bool cutOffResult(ArrayList result) { //TODO remove this duplication

		return result.Count == 1 && result[0].ToString().Equals("cutoff");
	}

	public new Metrics getMetrics() {
		return iterationMetrics;
	}

}
}
