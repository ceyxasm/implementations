#include <bits/stdc++.h>
using namespace std;


int solver(const char* equ, int n)
{
	int op=0;
	char opr;
	string opr1="", opr2="";
	for(int i=0; i<n; i++)
	{
		if( equ[i]=='+' || equ[i]=='-' || equ[i]=='/' || equ[i]=='*' ) 
		{
			op=1; 
			opr= equ[i];
			continue;
		}
		else if( op==0)
			opr1+= equ[i];
		else 
		{
			opr2+=equ[i];
		}
	}

	int oprd1= stoi(opr1);
	int oprd2= stoi(opr2);

	switch (opr){
		case '+':
			return oprd1+oprd2;
		case '-':
			return oprd1-oprd2;
		case '/':
			return oprd1/oprd2;
		case '*':
			return oprd1*oprd2;
	}
	return 0;
}
int main()
{

	char equ[]="100*4";
	int sol= solver( equ, sizeof(equ)/sizeof(char));
	cout<<sol<<endl;
	return 0;
}
