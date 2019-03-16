#include "paranthesischecker.h"


bool Checker::HasBalancedParanthesis()
{

  //BUG : Need to go through testing, might causes a crash
  for(auto x : Checker::Exp)
    {
      if(x == '(')
        Checker::Stack.push(x);
      if(x == ')')
        Checker::Stack.pop();
    }

  if(Checker::Stack.empty())
    return true;
  else
     return false;
}


