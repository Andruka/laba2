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
class Steck {
	char operators[30];
	int size_operators;
	double operands[30];
	int size_operands;	
	
  public:
	Steck(){
		size_operators=0;
		size_operands=0;
		for (int i = 0; i < 30; ++i)
			{
			operators[i]=0;
			operands[i]=0.0;
			}
		}
	void Push_operators(char simbol){
		operators[size_operators]=simbol;
		size_operators++;
		}
	void Push_operands(double chislo){
		operands[size_operands]=chislo;
		size_operands++;
		}
	char Pop_operators(){
		size_operators--;
		return operators[size_operators];
		}
	char Pop_operands(){
		size_operands--;
		return operands[size_operands];
		}
	int Size_operators(){
		return size_operators;
		}
	int Size_operands(){
		return size_operands;
		}
	int Check_operators(){
		return operators[size_operators-1];
		}
	int Check_operands(){
		return operands[size_operands-1];
		}
	};
class Calculator{
	Steck steck;
	int * status;
	double result,chislo;
	char op;
	char simb;
  public:
	Calculator(){
		status=new int;
		result=0.0;
		chislo=0.0;
		op=0;
		simb=0;
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
	int Check_Status(int stat)
		{
		*status+=stat;
		return *status;
		}
	double calculation(const char * str){
		if(str==0)
			{
			Check_Status(1);
			return 1;
			}
		while(str!=0)
			{
		        chislo=atof(str);
			if(chislo!=0.0)
				{
				steck.Push_operands(chislo);
				}
			str= strpbrk (str, "+-*/^()");
			op=*str;
			if (steck.Size_operators()==0)
				{
				steck.Push_operators(op);
				str++;
				continue;
				}
			if (Check_Simbol(op)!=5 && (Check_Simbol(op)>steck.Check_operators()))
				{
				steck.Push_operators(op);
				str++;
				continue;
				}
			if (Check_Simbol(op)<=steck.Check_operators() && Check_Simbol(op)!=1)
				{
				steck.Push_operands(Math_Operations(steck.Pop_operators(), steck.Pop_operands(),steck.Pop_operands()));
				str++;
				continue;
				}
			if (Check_Simbol(op)==1)
					{
					steck.Push_operators(op);
					str++;
					continue;
					}
			if (Check_Simbol(op)==5)
				{
				while(1)
					{
					simb=steck.Pop_operators();
					if (simb==')')break;
					steck.Push_operands(Math_Operations(simb, steck.Pop_operands(),steck.Pop_operands()));
					}
				str++;
				}
			}
		while(steck.Size_operators()!=0)
			{
			steck.Push_operands(Math_Operations(steck.Pop_operators(), steck.Pop_operands(),steck.Pop_operands()));
			}
		return steck.Check_operands();
		}	
	};
double calc(const char * str, int * status) {
	Calculator calculator;
	double result=calculator.calculation(str);
	if(calculator.Check_Status(0)==1)
		{
		*status=1;
		}
	if(calculator.Check_Status(0)==0) 
		{
		*status=0;
		}
	return result;
}
int main(int argc ,char *argv[])
	{
	int * status=new int;
	double result;
	result=calc(argv[1],status);
	if(*status==1)cout<<"Error"<<endl;
	if(*status==0)
		{
		cout<<"Calculation complete!"<<endl;
		cout<<result<<endl;
		}
	}
