#ifndef PARSER_H
#define PARSER_H
#include <QString>
#include <stack>

extern std::stack<QString> ParsedStack;
extern std::stack<QString> TempPostFixStack;
extern std::stack<QString> OperatorHoldStack;
extern QList<QString> List;

class Parse
{
private :

  QString Expression;
public :
  void ParseFunction();

  void GeneratePostFix();

  Parse(QString Expression)
  {
    this->Expression = Expression;
  }
};

#endif // PARSER_H
