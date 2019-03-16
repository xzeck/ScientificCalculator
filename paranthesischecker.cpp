#include "paranthesischecker.h"


bool Checker::HasBalancedParanthesis()
{
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


