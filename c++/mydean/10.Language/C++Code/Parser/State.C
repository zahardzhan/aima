#include <State.H>

State::State() {
   marked_ = NOT_MARKED;
}

State::State(int label)
{
  label_ = label;
  marked_ = NOT_MARKED;
}

State::Marked State::isMarked(){
   return marked_;
}

void State::mark(){
   marked_ = MARKED;
}

void State::unMark(){
   marked_ = NOT_MARKED;
}

/****************************************************************/
/*                                                              */
/* Function Name: setLabel                                      */
/* Parameters:    (int) label                                   */
/* Returns:       none                                          */
/* Effects:       sets the label_ of the state                  */
/*                                                              */
/****************************************************************/

void
State::setLabel(int label)
{
  label_ = label;
}


/****************************************************************/
/*                                                              */
/* Function Name: getLabel                                      */
/* Parameters:    none                                          */
/* Returns:       (int) label_                                  */
/* Effects:       none                                          */
/*                                                              */
/****************************************************************/

int
State::getLabel()
{
  return label_;
}
