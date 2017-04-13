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
		cout<<simbol<<"\t"<<"упал на вершину стека операторов"<<endl;
		size_operators++;
		}
	void Push_operands(double chislo){
		operands[size_operands]=chislo;
		cout<<chislo<<"\t"<<"упал на вершину стека чилел"<<endl;
		size_operands++;
		}
	char Pop_operators(){
		size_operators--;
		cout<<operators[size_operators]<<"\t"<<"вытолкнут из стека операторов"<<endl;
		return operators[size_operators];
		}
	double Pop_operands(){
		size_operands--;
		cout<<operands[size_operands]<<"\t"<<"вытолкнуто из стека чисел"<<endl;
		return operands[size_operands];
		}
	int Size_operators(){
		return size_operators;
		}
	int Size_operands(){
		return size_operands;
		}
	int Check_operators(){
		if (operators[size_operators-1]=='+'||operators[size_operators-1]=='-')return 1;
		if (operators[size_operators-1]=='*'||operators[size_operators-1]=='/')return 2;
		if (operators[size_operators-1]=='^')return 3;
		else{return 0;}
		}
	double Check_operands(){
		return operands[size_operands-1];
		}
	};
class Calculator{
	Steck steck;
	int * status;
	double result,chislo;
	char op,oper;
	int simb;
	double a ,b;
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
		if (simbol=='+'||simbol=='-')return 1;
		if (simbol=='*'||simbol=='/')return 2;
		if (simbol=='^')return 3;
		}
	double Math_Operations(){
		oper=steck.Pop_operators();
		a=steck.Pop_operands();
		b=steck.Pop_operands();
		if (oper=='+') result=a+b;
		if (oper=='-') result=a-b;
		if (oper=='*') result=a*b;
		if (oper=='/') result=b/a;
		if (oper=='^') result=pow(b,a);
		steck.Push_operands(result);
		}
	int Check_Status(int stat)
		{
		*status+=stat;
		return *status;
		}
	int Skobki()
		{
			if (op=='(')
					{
					steck.Push_operators(op);
					return 1;
					}
			if (op==')')
				{
				while(1)
					{
					simb=steck.Check_operators();
					if (simb==0){steck.Pop_operators();break;}
					Math_Operations();
					}
				return 1;
				}
		return 0;
		}
	double calculation(const char * str){
		if(str==NULL)
			{
			Check_Status(1);
			return 1;
			}
		while(str!=NULL)
			{
			if(*str=='0'||*str=='1'||*str=='2'||*str=='3'||*str=='4'||*str=='5'||*str=='6'||*str=='7'||*str=='8'||*str=='9')
		        	{
				chislo=atof(str);
				steck.Push_operands(chislo);
				}
			if((*str=='-')&&(*(str-1)!='0'||*(str-1)!='1'||*(str-1)!='2'||*(str-1)!='3'||*(str-1)!='4'||*(str-1)!='5'||*(str-1)!='6'||*(str-1)!='7'||*(str-1)!='8'||*(str-1)!='9'))
				{
				chislo=atof(str);
				steck.Push_operands(chislo);
				str++;
				}
			str= strpbrk (str, "+-*/^()");
			if (str == NULL){
				break;
				}
			op=*str;
			if(Skobki()==1)
				{
				str++;
				continue;
				}
			if (steck.Size_operators()==0)
				{
				steck.Push_operators(op);
				str++;
				continue;
				}
			if (Check_Simbol(op)>steck.Check_operators())
				{
				steck.Push_operators(op);
				str++;
				continue;
				}
			if (Check_Simbol(op)<=steck.Check_operators())
				{
				Math_Operations();
				continue;
				}
			}
		while(steck.Size_operators()!=0)
			{
			Math_Operations();
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
