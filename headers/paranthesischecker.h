#ifndef PARANTHESISCHECKER_H
#define PARANTHESISCHECKER_H


#include <stack>
#include <QString>


class Checker
{
private :
  std::stack<QString> Stack;
  QString Exp;

public :
  bool HasBalancedParanthesis();

  Checker(QString expression)
  {
    Exp = expression;
  }
};
#endif // PARANTHESISCHECKER_H
