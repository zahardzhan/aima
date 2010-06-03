/****************************************************************/
/*    NAME: Konstantinos Roussos                                */
/*    ACCT: knr                                                 */
/*    FILE: Searches.H                                          */
/*    ASGN: Final                                               */
/*    DATE: Wed Jun 22 15:04:54 1994                            */
/****************************************************************/


#ifndef SEARCHES_HEADER
#define SEARCHES_HEADER

class State;
class Comparator;
#include <SortedQueue.H>
State* best(State* current, State* goal, Comparator* heuristic);
State* bfs(State* current, State* goal);
State* dfs(State* current, State* goal);
State* dfs_fd(State* current, State* goal, int current_depth, 
              int fixed_depth);
State* ids(State* current,
           State* goal);


#endif
