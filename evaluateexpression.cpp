#include "evaluateexpression.h"
#include "parser.h"

#include <stack>
#include <QString>
#include <QDebug>
#include <QList>


//FIXME : Expression evaluation neglects multi-digit numbers
QString Eval::FinalVal()
{
  std::stack<QString> EvaluationStack;
  QList<QString> List;
  QString x;
  QString op1, op2;
  QString Result;

  List.append("+");
  List.append("-");
  List.append("*");
  List.append("/");
  //unsigned long Size = PostFixStack.size();
  //for(unsigned long i =0;i<Size; i++)
  //  {
  //    qDebug() << PostFixStack.top();
  //    PostFixStack.pop();
  //  }
  //
  //return "Something" ;

  while(!PostFixStack.empty())
    {
      x = PostFixStack.top();
      PostFixStack.pop();
      /*if(x == '(')
        {
          x = TempPostFixStack.top();
          TempPostFixStack.pop();
        }*/

      if(List.contains(x))
        {
          char *oper = x.toLocal8Bit().data();
          switch (*oper)
            {
             case '+':
              op2 = EvaluationStack.top();
              EvaluationStack.pop();
              op1 = EvaluationStack.top();
              EvaluationStack.pop();

              Result = QString::number(op1.toDouble() + op2.toDouble());
              EvaluationStack.push(Result);
              break;

            case '-':
              op2 = EvaluationStack.top();
              EvaluationStack.pop();
              op1 = EvaluationStack.top();
              EvaluationStack.pop();


              Result = QString::number(op1.toDouble() - op2.toDouble());
              EvaluationStack.push(Result);
              break;

            case '*':
              op2 = EvaluationStack.top();
              EvaluationStack.pop();
              op1 = EvaluationStack.top();
              EvaluationStack.pop();

              Result = QString::number(op1.toDouble() * op2.toDouble());
              EvaluationStack.push(Result);
              break;

            case '/':
              op2 = EvaluationStack.top();
              EvaluationStack.pop();
              op1 = EvaluationStack.top();
              EvaluationStack.pop();


              Result = QString::number(op1.toDouble() / op2.toDouble());
              EvaluationStack.push(Result);
              break;
            }
        }else
        {
          EvaluationStack.push(x);
        }
    }
  unsigned long Size = EvaluationStack.size();
  std::stack<QString> RevStack;

  for(unsigned long i =0; i<Size; i++)
    {
      RevStack.push(EvaluationStack.top());
      EvaluationStack.pop();
    }
  return RevStack.top();
}
