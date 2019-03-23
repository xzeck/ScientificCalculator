#ifndef PARSER_H
#define PARSER_H
#include <QString>
#include <stack>
#include <QList>

extern std::stack<QString> ParsedStack;
extern std::stack<QString> TempPostFixStack;
extern std::stack<QString> OperatorHoldStack;
extern std::stack<QString> PostFixStack;
extern std::stack<QString> TemporaryParsedStack;
static QList<QString> List = {"+", "-", "*", "/", "^"};


class Parse
{
private :

  QString Expression;

  void GeneratePostFix();
public :
  void ParseFunction();

  Parse(QString Expression)
  {
    this->Expression = Expression;
  }
};

#endif // PARSER_H
