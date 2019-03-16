#ifndef PARSER_H
#define PARSER_H

#include <QString>
#include <stack>
#include <QCharRef>

using namespace std;

extern QString postfix;
extern stack<QCharRef> Stack;

class InfixToPostFix
{
public :

  void RPN(QString);

  bool ParanthesisChecker();

};

#endif // PARSER_H
