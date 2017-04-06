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
  #endif
class Operators {
	double result;
	int size;
	char massiv[30];
  public:
	Operators(){
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
	int Check_Simbol(char simbol)
		{
		if (simbol=='(')return 1;
		if (simbol=='+'||simbol=='-')return 2;
		if (simbol=='*'||simbol=='/')return 3;
		if (simbol=='^')return 4;
		if (simbol==')')return 5;
		else {return 0;} 
		}
	double Math_Operations(char oper,double b,double a){
		if (oper=='+') result=a+b;
		if (oper=='-') result=a-b;
		if (oper=='*') result=a*b;
		if (oper=='/') result=a/b;
		if (oper=='^') result=pow(a,b);
		return result;
		}
	};
class Operands {
	char * p;
	int size;
	double massiv[30];
	int * status;
	char op;
	char simb;
	double chislo;
  public:
	Operands(){
		simb=0;
		status=new int;
		chislo=0.0;
		size=0;
		for (int i = 0; i < 30; ++i)
			{
			massiv[i]=0.0;
			}
		}
	void Push(double simbol){
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
	int Check_Status(int stat)
		{
		*status+=stat;
		return *status;
		}
	double calculation(const char * str,Operators & operators){
		*p=*str;
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
				Push(chislo);
				}
			p= strpbrk (p, "+-*/^()");
			op=*p;
			if (operators.Size()==0)
				{
				operators.Push(op);
				p++;
				continue;
				}
			if (operators.Check_Simbol(op)!=5 && (operators.Check_Simbol(op)>operators.Check_Steck()))
				{
				operators.Push(op);
				p++;
				continue;
				}
			if (operators.Check_Simbol(op)<=operators.Check_Steck() && operators.Check_Simbol(op)!=1)
				{
				Push(operators.Math_Operations(operators.Pop(), Pop(),Pop()));
				p++;
				continue;
				}
			if (operators.Check_Simbol(op)==1)
					{
					operators.Push(op);
					p++;
					continue;
					}
			if (operators.Check_Simbol(op)==5)
				{
				while(1)
					{
					simb=operators.Pop();
					if (simb==')')break;
					Push(operators.Math_Operations(simb, Pop(),Pop()));
					}
				p++;
				}
			}
		while(operators.Size()!=0)
			{
			Push(operators.Math_Operations(operators.Pop(), Pop(),Pop()));
			}
		return Check_Steck();
		}
	};
double calc(const char * str, int * status) {
	Operators operators;
	Operands operands;
	double result=operands.calculation(str,operators);
	if(operands.Check_Status(0)==1)
		{
		*status=1;
		}
	if(operands.Check_Status(0)==0) 
		{
		*status=0;
		}
	return result;
}
int main(int argc ,char *argv[])
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
