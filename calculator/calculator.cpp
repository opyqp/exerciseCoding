#include "string"
#include "stack"
#include "iostream"
#include "vector"
#include "math.h"
using namespace std;

bool isOper(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')' ? true : false;
}

bool isNum(char c)
{
    return (c >= '0' && c <= '9');
}

bool isNumOrDot(char c)
{
    return isNum(c) || c == '.';
}
double cal(double a, char op, double b)
{
    double res = 0;
    switch (op)
    {
        case '+':
        res = a + b;
        break;
        case '-':
        res = a - b;
        break;
        case '*':
        res = a * b;
        break;
        case '/':
        res = a / b;
        break;
        default:
        break;
    }
    return res;
}

vector<string> split(string str)
{
    double tmp = 0;
    int flag = -1;
    vector<string> res;
    char LastOp = 0;
    for (int i = 0; i < str.size(); ++i)
    {
        char p = str.at(i);
        if (p == '.')
        {
            flag = 1;
        }
        else if (isNum(p))
        {
            if (flag > 0)
            {
                tmp = tmp + (p - '0') * pow(0.1, flag++);
            }
            else
            {
                tmp = tmp * 10 + p - '0';
            }
        }
        else if (isOper(p))
        {
            if (LastOp != ')' && p != '(')
            {
                res.push_back(to_string(tmp));
                tmp = 0;
                flag = -1;
            }
            string t(1, p);
            res.push_back(t);
            LastOp = p;
        }
    }
	res.push_back(to_string(tmp));
    return res;
}

int getpri(char a)
{
    switch (a)
    {
        case ')':
        return 1;
        break;
        case '+':
        return 2;
        break;
        case '-':
        return 3;
        break;
        case '*':
        return 4;
        break;
        case '/':
        return 5;
        break;
        case '(':
        return 6;
        break;
        default:
        return 0;
        break;
    }
}

double gt(vector<string> str)
{
    stack<double> operand;
    stack<char> operato;
    char op = 0;
    char LastOp = 0;
    for(vector<string>::iterator it = str.begin(); it != str.end(); ++it)
    {
        char * optmp = (char*)(*it).data();
        if(isNum(*optmp))
        {
            operand.push(stod(optmp));
        }
        else if(isOper(*optmp))
        {
            char tmp = *optmp;
            if(operato.empty())
            {
                operato.push(tmp);
                LastOp = tmp;
            }
            else
            {
                while(!operato.empty())
                {
                    char tp = operato.top();
                    if(getpri(tp) >= getpri(tmp))
                    {
                        if(tp == '(')
                        {
                            if(tmp ==')')
                            {
                                operato.pop();
                                break;
                            }
                            else
                            {
                                break;
                            }
                        }
                        else
                        {
                            operato.pop();
                            double b = operand.top();
                            operand.pop();
                            double a = operand.top();
                            operand.pop();
                            operand.push(cal(a, tp, b));
                            LastOp = tp;
                        }
                    }
                    else
                    {
                        break;
                    }
                }
                if(tmp != ')')
                {
                    operato.push(tmp);
                }
                LastOp = tmp;
            }
        }
    }
   while (!operato.empty())
   {
       double b = operand.top();
       operand.pop();
       double a = operand.top();
       operand.pop();
       char optmp = operato.top();
       operato.pop();
       operand.push(cal(a, optmp, b));

   }
   return operand.top();
}

int main()
{
	string str;
	cin>>str;
    vector<string> result = split(str);
    cout<<gt(result)<<endl;
    cin.get();
    return 0;
}

