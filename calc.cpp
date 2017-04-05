#include <cstring>
#include <iostream>
#include <stdlib.h>
#include <math.h>
using namespace std;

#ifdef __cplusplus
extern "C" {
  #endif
  double calc(const char * str, int * status);
  #ifdef __cplusplus
  }
class Steck {
	int size;
	char massiv[30];
  public:
	Steck(){
		size=0;
		for (int i = 0; i < 30; ++i)
			{
			massiv[i]=0;
			}
		}
	void Push(char simbol){
		massiv[size]=simbol;
		size++;
		}
	char Pop(){
		size--;
		return massiv[size];
		}
	int Size(){
		return size;
		}
	int Check_Steck(){
		return massiv[size-1];
		}
	};
int Check_Status(int stat)
	{
	int * status;
	*status+=stat;
	return *status;
	}
int Check_Simbol(char simbol)
	{
	if (simbol=='(')return 1;
	if (simbol=='+'||simbol=='-')return 2;
	if (simbol=='*'||simbol=='/')return 3;
	if (simbol=='^')return 4;
	if (simbol==')')return 5;
	else {return 0;} 
	}
double Math_Operations(char oper,Steck & operands){
	double result;
	double a,b;
	b=(operands.Pop());
	a=(operands.Pop());
	if (oper=='+') result=a+b;
	if (oper=='-') result=a-b;
	if (oper=='*') result=a*b;
	if (oper=='/') result=a/b;
	if (oper=='^') result=pow(a,b);
	return result;
	}
double calculation(const char * str){
	Steck operands;
	Steck operators;
	char * p;
	*p=*str;
	char op;
	double chislo=0.0;
	if(p==0)
		{
		Check_Status(1);
		return 1;
		}
	while(str!=0)
		{
	        chislo=atof(p);
		if(chislo!=0.0)
			{
			operands.Push(chislo);
			}
		p= strpbrk (p, "+-*/^()");
		op=*p;
		if (operators.Size()==0)
			{
			operators.Push(op);
			p++;
			continue;
			}
		if (Check_Simbol(op)!=5 && (Check_Simbol(op)>operators.Check_Steck()))
			{
			operators.Push(op);
			p++;
			continue;
			}
		if (Check_Simbol(op)<=operators.Check_Steck() && Check_Simbol(op)!=1)
			{
			operands.Push(Math_Operations(operators.Pop(), operators));
			continue;
			}
		if (Check_Simbol(op)==1)
				{
				operators.Push(op);
				p++;
				continue;
				}
		if (Check_Simbol(op)==5)
			{
			char a=0;
			while(1)
				{
				a=operators.Pop();
				if (a==')')break;
				operands.Push(Math_Operations(a, operators));
				}
			}
		}
	while(operators.Size()!=0)
		{
		operands.Push(Math_Operations(operators.Pop(), operators));
		}
	return operands.Check_Steck();
	}
double calc(const char * str, int * status) {
	double result=calculation(str);
	if(Check_Status(0)==1)
		{
		*status=1;
		}
	if(calculation(str)==0) 
		{
		*status=0;
		}
	return result;
}
int main(int argc , char argv[])
	{
	int * status;
	double result;
	result=calc(argv[1],status);
	if(*status==1)cout<<"Error"<<endl;
	if(*status==0)
		{
		cout<<"Calculation complete!"<<endl;
		cout<<result<<endl;
		}
	}
