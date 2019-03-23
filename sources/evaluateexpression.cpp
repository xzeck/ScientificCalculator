#include "headers/evaluateexpression.h"
#include "headers/parser.h"

#include <stack>
#include <QString>
#include <QDebug>
#include <QList>
#include <math.h>


//FIXME : Expression evaluation neglects multi-digit numbers
QString Eval::FinalVal()
{
  std::stack<QString> EvaluationStack;
  QString x;
  QString op1, op2;
  QString Result;

  //unsigned long Siz = PostFixStack.size();
  //for(unsigned long i =0;i<Siz; i++)
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

            case '^':
              op2 = EvaluationStack.top();
              EvaluationStack.pop();
              op1 = EvaluationStack.top();
              EvaluationStack.pop();


              Result = QString::number(powf64(op1.toDouble(), op2.toDouble()));
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
