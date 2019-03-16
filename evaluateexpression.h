#ifndef EVALUATEEXPRESSION_H
#define EVALUATEEXPRESSION_H


#include "InfixToPostfix.h"

#include <QString>

class Eval
{
private :
  QString PostfixExpression = postfix;

public :

  QString FinalVal();


};


#endif // EVALUATEEXPRESSION_H
