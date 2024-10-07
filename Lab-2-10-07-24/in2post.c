#include <stdio.h>
#include <stdbool.h>
#include <string.h>
int top=-1, size=25;

int prec(char c){
	return (c=='^')?3:(c=='/'||c=='*')?2:(c=='+'||c=='-')?1:-1;
}


char Top(char s[]){return s[top];}

bool isEmpty(){return (top==-1);}
bool isFull(){return (top==size-1);}
bool isRtoL(char op){return (op=='^');}
void push(char s[], char x)
{
	if(!isFull()){
		++top;
		s[top]=x;
	}
}

char pop(char s[]){
	if(!isEmpty()){
		char temp=s[top];
		top--;
		return temp;
	}
}

void in2post(char s[], char req[]){
	printf("Enter exp:");
	fgets(req,sizeof(req),stdin);

	int len=strlen(req);
	size=strlen(s);
	char res[len+1];
	int resIndex=0;

	for(int i=0;i<len;i++){
		char c=req[i];
		if((c>='a'&&c<='z')||(c>='A'&&c<='Z')||(c>='0'&&c<='9'))
			res[resIndex++]=c;
		else if (c=='(')
			push(s,c);
		else if (c==')')
		{
			while(Top(s)!='(')
				res[resIndex++]=pop(s);
			pop(s);
		}
		else if(prec(c)>prec(Top(s))){
			push(s,c);
		}
		else{
			while( (prec(c)<prec(Top(s)) && !isEmpty() ) || ( prec(c)==prec(Top(s)) && !isRtoL(c) ) ){
				res[resIndex++]=pop(s);
			}
			push(s,c);
		}
	}//end of for
	
	//clear stack
	while(top!=-1)
		res[resIndex++]=pop(s);
	res[resIndex]=='\0';

	printf("Result:%s\n",res);
}

void main()
{
	char req[25];
	char s[25];
	in2post(s,req);
}

