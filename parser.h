#ifndef PARSER_H
#define PARSER_H
#include <QString>

#endif // PARSER_H

#define BRAC_L '('
#define BRAC_R ')'


class Parse
{
private :

  QString Expression;
public :
  void ParseFunction();

  Parse(QString Expression)
  {
    this->Expression = Expression;
  }
};
