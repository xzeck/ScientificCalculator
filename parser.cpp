#include "parser.h"
#include <QDebug>
#include <QString>
#include <stack>
#include <QList>


bool ParserIsOperator(QString);
bool ParserIsOperand(QString);
bool ParserHasHigherPrecedence(QString, QString );
bool ParserIsRightAssociative(QString);
int  ParserOperatorWeight(QString);



std::stack<QString> ParsedStack;
std::stack<QString> TempPostFixStack;
std::stack<QString> OperatorHoldStack;
QList<QString> List;

void Parse::ParseFunction()
{
  QString Exp = Parse::Expression;
  std::stack<QString> TemporaryParsedStack;
  QString GeneratedParseString = "(";
  bool IsParsedStringFull = false;
  Exp += ")";
  List.append("+");
  List.append("-");
  List.append("*");
  List.append("/");

  qDebug() << "Parsing";
  for(auto x : Exp)
    {
      if(!List.contains(x) && x != ")" && x != "(")
        {
          GeneratedParseString += x;
          IsParsedStringFull = true;
        }
      else if(x == "(" || x == ")" || List.contains(x))
        {
          if(IsParsedStringFull == true)
            TemporaryParsedStack.push(GeneratedParseString);

          TemporaryParsedStack.push(x);
          GeneratedParseString = "";
          IsParsedStringFull = false;
        }
    }

  unsigned long Size = TemporaryParsedStack.size();

  for(unsigned long i =0; i<Size; i++)
    {
      ParsedStack.push(TemporaryParsedStack.top());
      TemporaryParsedStack.pop();
    }
  qDebug() << "Calling PostFix";
  GeneratePostFix();

  qDebug() << "PostFix Stack : ";

  unsigned long Size_Post = TempPostFixStack.size();

  for(unsigned long i =0; i<Size_Post; i++)
    {
      qDebug() << TempPostFixStack.top();
      TempPostFixStack.pop();
    }

}


void Parse::GeneratePostFix()
{
  QString x;
  while(!ParsedStack.empty())
    {
      x = ParsedStack.top();
      ParsedStack.pop();

      if(x == ' ' || x == ',') continue;

      else if(List.contains(x))
        {
          //qDebug() << "Precedence Vallue : " << OperatorHoldStack.top();

          while(!OperatorHoldStack.empty() && OperatorHoldStack.top() != '(')
            {
              if(ParserHasHigherPrecedence(OperatorHoldStack.top(), x))
                {
                  TempPostFixStack.push(OperatorHoldStack.top());
                  OperatorHoldStack.pop();
                }
            }
          OperatorHoldStack.push(x);
        }
      else if(x == '(')
        {
          OperatorHoldStack.push(x);
        }
      else if(x == ')')
        {
          while(!OperatorHoldStack.empty() && OperatorHoldStack.top()!= '(')
            {
              TempPostFixStack.push(OperatorHoldStack.top());
              OperatorHoldStack.pop();
            }
          //OperatorHoldStack.pop();
        }
      else if (ParserIsOperand(x))
        {
          TempPostFixStack.push(x);
        }
    }
  while(!OperatorHoldStack.empty())
    {
      TempPostFixStack.push(OperatorHoldStack.top());
      OperatorHoldStack.pop();
    }
}

bool ParserIsOperand(QString op)
{
  QRegExp re("\\d*");
  if(re.exactMatch(op)) return true;
  return false;
}

bool ParserHasHigherPrecedence(QString op1, QString op2)
{
  int op1wt = ParserOperatorWeight(op1);
  int op2wt = ParserOperatorWeight(op2);

  //qDebug() << "op1 wt : " << op1wt << "op2 wt : " << op2wt;

  return op1wt > op2wt ? true : false;
}

int ParserOperatorWeight(QString op)
{
  int weight = -1;
  qDebug() << "op : " << op;
  if( op == "+" || op == "-")
    weight = 1;
  else if(op == "*" || op == "/")
    weight = 2;
  else if(op == "^")
    weight = 3;


  return weight;
}
