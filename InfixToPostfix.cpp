#include<iostream>
#include<stack>
#include<string>
#include "InfixToPostfix.h"
#include <QString>
#include <QDebug>


using namespace std;

QString postfix;
stack<QCharRef> Stack;

// Function to convert Infix expression to postfix
QString InfixToPostfix(QString expression);

// Function to verify whether an operator has higher precedence over other
int HasHigherPrecedence(QCharRef operator1, QCharRef operator2);

// Function to verify whether a character is operator symbol or not.
bool IsOperator(QCharRef C);

// Function to verify whether a character is alphanumeric chanaracter (letter or numeric digit) or not.
bool IsOperand(QCharRef C);

void InfixToPostFix::RPN(QString Input)
{

  postfix = InfixToPostfix(Input);
  qDebug() << postfix;
}

// Function to evaluate Postfix expression and return output
QString InfixToPostfix(QString exp)
{


  postfix = "";
  for(int i = 0;i< exp.length();i++)
    {

      if(exp[i] == ' ' || exp[i] == ',') continue;

      else if(IsOperator(exp[i]))
        {
          while(!Stack.empty() && Stack.top() != '(' && HasHigherPrecedence(Stack.top(),exp[i]))
            {
              postfix+= Stack.top();
              Stack.pop();
            }
          Stack.push(exp[i]);
        }
      // Else if character is an operand
      else if(IsOperand(exp[i]))
        {
          postfix +=exp[i];
        }

      else if (exp[i] == '(')
        {
          Stack.push(exp[i]);
        }

      else if(exp[i] == ')')
        {
          while(!Stack.empty() && Stack.top() !=  '(')
            {
              postfix += Stack.top();
              Stack.pop();
            }
          Stack.pop();
        }
    }

  while(!Stack.empty())
    {
      postfix += Stack.top();
      Stack.pop();
    }

  return postfix;
}

// Function to verify whether a character is english letter or numeric digit.
// We are assuming in this solution that operand will be a single character
bool IsOperand(QCharRef C)
{
  if(C >= '0' && C <= '9') return true;
  return false;
}

// Function to verify whether a character is operator symbol or not.
bool IsOperator(QCharRef C)
{
  if(C == '+' || C == '-' || C == '*' || C == '/' || C== '$')
    return true;

  return false;
}

// Function to verify whether an operator is right associative or not.
int IsRightAssociative(QCharRef op)
{
  if(op == '$') return true;
  return false;
}

// Function to get weight of an operator. An operator with higher weight will have higher precedence.
int GetOperatorWeight(QCharRef op)
{
  int weight = -1;
  QString x = static_cast<QChar>(op);
  QByteArray exp = x.toLocal8Bit();
  char *operand = exp.data();

  switch(*operand)
    {
    case '+':
    case '-':
      weight = 1;
    case '*':
    case '/':
      weight = 2;
    case '$':
      weight = 3;
    }
  return weight;
}

// Function to perform an operation and return output.
int HasHigherPrecedence(QCharRef op1, QCharRef op2)
{
  int op1Weight = GetOperatorWeight(op1);
  int op2Weight = GetOperatorWeight(op2);

  if(op1Weight == op2Weight)
    {
      if(IsRightAssociative(op1)) return false;
      else return true;
    }
  return op1Weight > op2Weight ?  true: false;
}
