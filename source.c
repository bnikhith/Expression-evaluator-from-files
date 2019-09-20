#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
int top1=-1;
char postfix[200];
char stack1[30];
int top2=-1;
char stack2[30];
void push1(char symbol)
{
	stack1[++top1]=symbol;
}
char pop1()
{
	char ch;
	ch=stack1[top1];
	top1--;
	return ch;
}
void push2(char symbol)
{
	stack2[++top2]=symbol;
}
char pop2()
{
	char ch;
	ch=stack2[top2];
	top2--;
	return ch;
}
int PostfixEval(char postfix[])
{
	char ch;
	int op2,op1;
	int i=0;
	while(postfix[i]!='\0')
	{
		ch=postfix[i];
		if(isdigit(ch))
		push2(ch-'0');
		else
		{
			op1=pop2();
			op2=pop2();
			switch(ch)
			{
				case '+':
					push2(op2+op1);
					break;
				case '-':
					push2(op2-op1);
					break;
				case '/':
					push2(op2/op1);
					break;
				case '*':
					push2(op2*op1);
					break;
				case '^':
					push2(pow(op2,op1));
					break;
				default:
					printf("operator is not handled");
			}
			
		}
		i++;
	}
	//printf("result is    %d",
	return stack2[top2];
}

int precedence(char symbol)
{
	char ch;
	ch=symbol;
	if(ch=='^')
	return 3;
	else if(ch=='/'||ch=='*')
	return 2;
	else if(ch=='+'||ch=='-')
	return 1;
	else
	return 0;
	
}

int infix_postfix(char infix[])
{
	char symbol;
	int i=0,j=0;
	while(infix[i]!='\0')
	{
		char temp;
		symbol=infix[i];
		char nextsymbol=infix[i+1];
		switch(symbol)
		{
			case '+':
			case '/':
			case '-':
					while(top1!=-1&&precedence(symbol)<=precedence(stack1[top1]))
					{
					 temp=pop1();
						postfix[j]=temp;
						j++;
					}
					push1(symbol);
					break;
			case '*':
				if(nextsymbol!='*')
				{
					while(top1!=-1&&precedence(symbol)<=precedence(stack1[top1]))
					{
						temp=pop1();
						postfix[j]=temp;
						j++;
					}
					push1(symbol);
					
				}
				if(nextsymbol=='*')
				{
					symbol='^';
					
					while(top1!=-1&&precedence(symbol)<=precedence(stack1[top1]))
					{
						temp=pop1();
						postfix[j]=temp;
						j++;
					}
					push1(symbol);
					i++;
					
				}
				break;
			default:
				postfix[j]=symbol;
				j++;
		
		}
		i++;
	}
	while(top1>=0)
	{
		postfix[j]=pop1();
		j++;
	}
	postfix[j]='\0';
		//	printf("postfix expression is  %s\n",postfix );
			return PostfixEval(postfix);

}

void AppendToFile(char* expression){
	FILE *pFile;
	pFile=fopen("myfile.txt", "a");
	if(pFile==NULL) {
    	perror("Error opening file.");
	}
	else {
   	   	 fprintf(pFile, "%s", expression);
	}
	fclose(pFile);
	//printf("%s\n",expression);
}

void Separator(char expr[200]){
	char str[50];
	char* ans;
	char* equate;
	int solution=0;
	equate="=";
	AppendToFile(expr);
	AppendToFile(equate);
	solution=infix_postfix(expr);
	itoa(solution,ans,10);
	AppendToFile(ans);	
	AppendToFile("\n");
}

void Expression_extractor(char* filename){
	//This function will separate each epression and send it to expression_evaluator
	FILE *fptr;
    char ch[200];
    int i=0,line_num=1;
    //  open the file for reading 
    fptr = fopen(filename, "r");
    if (fptr == NULL)
    {
        printf("Cannot open file \n");
        exit(0);
    }
    char c = fgetc(fptr);
    while (c != EOF)
    {
    	//if '\n' then that exprn is sent to evaluate
    	while(c != '\n'){
    	ch[i++]=c;
        c = fgetc(fptr);
        }
    	ch[i]='\0';
    	Separator(ch);
   	    i=0;
    	c=fgetc(fptr);
    }
    fclose(fptr);
}
void final_result(){
	FILE *fp1, *fp2;
   char ch;
 
   fp1 = fopen("HELPER_FILE", "r");//should delete this file at the end.
   fp2 = fopen("FILE_NAME", "w");
 
   while (1) {
      ch = fgetc(fp1);
 
      if (ch == EOF)
         break;
      else
         putc(ch, fp2);
   }
 
   printf("File copied Successfully!");
   fclose(fp1);
   fclose(fp2);
   int status = remove(HELPER_FILE);
     
    if( status == 0 )
    printf("%s file deleted successfully.\n",HELPER_FILE);
    else
    {
        printf("Unable to delete the file\n");
        perror("Error");
    }
}
int main(){
	//Send the file to a function which will extract each expression individually
    Expression_extractor("FILE_NAME");
    final_result();
	return 0;
}
