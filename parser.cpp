#include "parser.h"
#include <QDebug>
#include <QString>
#include <stack>
#include <QList>
#include <utility>


//Function prototypes
bool IsOperator(QString); //Used to check if a given input is an operator
bool IsOperand(const QString&); //User to check if a given input is an operand
bool HasHigherPrecedence(QString, QString ); //Checks if first input has higher precedence than second
int  OperatorWeight(const QString&); //Returns the operator weight

//Some stacks
std::stack<QString> ParsedStack; //Used to store the parsed stack
std::stack<QString> TempPostFixStack; //Used to store the Reversed Post Fix Stack
std::stack<QString> PostFixStack; //Stores the actucal Post Fix in RPN
std::stack<QString> OperatorHoldStack; // Temporary stack to hold the operators while performing shunting yard algorithm
std::stack<QString> TemporaryParsedStack; //Holds the temporary parsed value


void Parse::ParseFunction()
{
  QString Exp = Parse::Expression; //Make a copy of the Expression
  Exp += ")"; //Add an end backet so that the final brackets would also be popped out


  QString GeneratedParseString; //Used to store the entire digits from start till a new operator is reached
  bool IsParsedStringFull = false; //Checks is a parsed string has hit an operator or not

  //This part is required so that the calculator can handle double digits when it generates its postfix expression
  for(auto x : Exp)
    {

      if(!List.contains(x) && x != ")" && x != "(") //Enter if its a number
        {
          GeneratedParseString += x; //Generate number until it hits a token which is either an operator or a bracket
          IsParsedStringFull = true; //Indicates that the parsed string is generated
        }
      else if(x == "(" || x == ")" || List.contains(x)) //Enter is its an operator or bracket
        {
          if(IsParsedStringFull) //Push the generated string to a stack
            TemporaryParsedStack.push(GeneratedParseString);

          TemporaryParsedStack.push(x); // push the token to the stack
          GeneratedParseString = ""; //set generated parse string to empty
          IsParsedStringFull = false; // Parsed string is false
        }
    }


  unsigned long Size = TemporaryParsedStack.size(); //Get Size of the Stack;

  //Reversing the parsed stack
  for(unsigned long i =0; i<Size; i++)
    {
      //qDebug() << TemporaryParsedStack.top();
      ParsedStack.push(TemporaryParsedStack.top());
      TemporaryParsedStack.pop();
    }

  GeneratePostFix(); //Gets RPN

  unsigned long Size_Post = TempPostFixStack.size(); //Get Size again cause brackets are removed nad the size now is not the same

  //push the Postfix generated into another stack because the initial generated postfix is reverse of what is required
  for(unsigned long i =0; i<Size_Post; i++)
    {
      //qDebug() << TempPostFixStack.top();
      PostFixStack.push(TempPostFixStack.top());
      TempPostFixStack.pop();
    }

}

//Generates Post Fix Notation
void Parse::GeneratePostFix()
{
  QString x;
  while(!ParsedStack.empty()) // Run till ParsedStack is empty
    {
      x = ParsedStack.top(); //Get the top of the parsed stack
      ParsedStack.pop(); //Pop the top of the stack

      if(x == ' ' || x == ',') continue; //If user inputs a space or a comma in between the strings

      else if(List.contains(x)) // If its an operator
        {
          //qDebug() << "Precedence Vallue : " << OperatorHoldStack.top();

          while(!OperatorHoldStack.empty() && OperatorHoldStack.top() != '(') //Push in the stack to the postfix string
            {
              if(HasHigherPrecedence(OperatorHoldStack.top(), x))
                {
                  TempPostFixStack.push(OperatorHoldStack.top());
                  OperatorHoldStack.pop();
                }
            }
          OperatorHoldStack.push(x);
        }
      else if(x == '(')  //Push the brackets
        {
          OperatorHoldStack.push(x);
        }
      else if(x == ')') //If a close bracket appears, push everything in the stack to postfix string
        {
          while(!OperatorHoldStack.empty() && OperatorHoldStack.top()!= '(')
            {
              TempPostFixStack.push(OperatorHoldStack.top());
              OperatorHoldStack.pop();
            }
        }
      else if (IsOperand(x)) //Check if operand, if true push to the postfix string
        {
          TempPostFixStack.push(x);
        }
    }
  while(!OperatorHoldStack.empty()) //Once done, push the reamining values in the stack to the postfix string
    {
      TempPostFixStack.push(OperatorHoldStack.top());
      OperatorHoldStack.pop();
    }
}

bool IsOperand(const QString& op)
{
  QRegExp re("[+-]?([0-9]*[.])?[0-9]+"); //Regular Expression to check if input is a number or not

  if(re.exactMatch(op)) return true;

  //qDebug() << op << ": Return false";
  return false;
}

bool HasHigherPrecedence(QString op1, QString op2)
{
  //std::move used becasuse op1 will soon be destroyed as there's no need for it further down the code
  int op1wt = OperatorWeight(std::move(op1)); //Get op1 weight
  int op2wt = OperatorWeight(std::move(op2)); //Get op2 weight

  //qDebug() << "op1 wt : " << op1wt << "op2 wt : " << op2wt;

  return op1wt >= op2wt; // return true or false
}

//Return the operator weight
int OperatorWeight(const QString& op)
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
