#include "evaluateexpression.h"

#include <stack>
#include <QString>
#include <QDebug>

//FIXME : Expression evaluation neglects multi-digit numbers
QString Eval::FinalVal()
{
   std::stack<QString> ExpressionStack;
   QString x;
   QString op1;
   QString op2;
   double Result = 0.0;

   QList<QString> List;
   List.append("+");
   List.append("-");
   List.append("*");
   List.append("/");

   /*for(auto x : postfix)
     {
       ExpressionStack.push(x);
     }

   //qDebug() <<  ExpressionStack.size();

  for(unsigned long i = 0; i<ExpressionStack.size(); i++)
    {
      x = ExpressionStack.top();
      ExpressionStack.pop();

      if(List.contains(x))
        {
          op1 = ExpressionStack.top();
          ExpressionStack.pop();
          op2 = ExpressionStack.top();
          ExpressionStack.pop();
          QString temp = static_cast<QString>(x);
          QByteArray QB = temp.toLocal8Bit();

          char *oper = QB.data();

          switch(*oper)
           {
            case '+':
              Result += op1.toDouble() + op2.toDouble();
              break;

            case '-':
              Result += op1.toDouble() - op2.toDouble();
              break;

            case '*':
              Result += op1.toDouble() * op2.toDouble();
              break;

            case '/':
              Result += op1.toDouble() / op2.toDouble();
              break;
           }
        }


    }
  return QString::number(Result);*/
}
