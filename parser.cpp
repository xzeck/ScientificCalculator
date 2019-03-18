#include "parser.h"
#include <QDebug>
#include <QString>
#include <stack>
#include <QList>

void Parse::ParseFunction()
{
  QString Exp = Parse::Expression;
  std::stack<QString> ParsedStack;
  QList<QString> List;
  QString GeneratedParseString = "";
  bool IsParsedStringFull = false;
  Exp += ")";
  List.append("+");
  List.append("-");
  List.append("*");
  List.append("/");

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
            ParsedStack.push(GeneratedParseString);

          ParsedStack.push(x);
          GeneratedParseString = "";
          IsParsedStringFull = false;
        }

    }
  unsigned long Size = ParsedStack.size();
  qDebug() << "Parsed Stack";
  for(unsigned long i = 0; i<Size; i++)
    {
      qDebug() << ParsedStack.top();
      ParsedStack.pop();
    }
}
