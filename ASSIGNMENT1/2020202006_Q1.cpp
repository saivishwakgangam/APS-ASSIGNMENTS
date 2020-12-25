#include <iostream>
#include <bits/stdc++.h>
#include <string>
using namespace std;
template<typename T>
class Stack
{
 int currsize;
 int maxsize;
 T *arr;
public:
	Stack()
	{
		currsize=0;
		maxsize=10000;
		arr=new T[maxsize];
	}
	void push(T d)
	{
		if(currsize==maxsize)
		{
			T *oldArr=arr;
			arr=new T[2*maxsize];
			maxsize=2*maxsize;
			for(int i=0;i<currsize;i++)
			{
				arr[i]=oldArr[i];
			}
			delete [] oldArr;
		}
		arr[currsize]=d;
		currsize++;
	}
	bool empty()
	{
		return (currsize==0);
	}
	void pop()
	{
		if(!empty())
		{
			currsize--;
		}
	}
	T top()
	{
		return arr[currsize-1];
	}


};
int precedence(char ch)
{
   if(ch=='*'||ch=='/'||ch=='%')
   {
   	return 3;
   }
   else if(ch=='+'||ch=='-')
   {
   	return 2;
   }
   return 0;
}
void infixtopostfix(string &s,string &res)
{
	Stack<char>st;
	st.push('N');
	char ch;
	for(int i=0;s[i]!='\0';i++)
	{
		if(s[i]>=48&&s[i]<=57)
		{
             ch=s[i];
		     res=res+ch;
		     while((s[i+1]>=48&&s[i+1]<=57||s[i+1]=='.')&&s[i+1]!='\0')
		     {
		     	ch=s[i+1];
		     	res=res+ch;
		     	i++;
		     }
		     res+=" ";
		}
		else if(s[i]=='(')
		{
		   	  ch=s[i];
		   	 st.push(ch);
		 }  
		 else if(s[i]==')')
		 {
		   	while(st.top()!='('&&st.top()!='N')
		   	{
		   		ch=st.top();
               res=res+ch;
               res=res+" ";
               st.pop();
            }
            if(st.top()=='(')
            {
            	st.pop();
            }
		  }
		  else
		   {

                  while((st.top()!='N')&&precedence(s[i])<=precedence(st.top()))
                  {
                  		ch=st.top();
                       res=res+ch;
                       res+=" ";
                       st.pop();
                  }
                  	ch=s[i];
                    st.push(ch);
                  
		   	}

	}	
	while(st.top()!='N')
	{
		ch=st.top();
		res=res+ch;
		res+=" ";
		st.pop();
	}

}
void postfixevaluation(string &ref)
{
	Stack<double>st;
	double num,res1,res2;
	int mod1,mod2;
	string res="";
	for(int i=0;i<ref.size();i++)
	{
		if(ref[i]>=48&&ref[i]<=57)
		{
           while(ref[i]!=' '&&i<ref.size())
           {
           	res+=ref[i];
           	i++;
           }
           num=stod(res);
           st.push(num);
           res.clear();

		}
		else if(ref[i]=='+')
		{
           res1=st.top();
           st.pop();
           res2=st.top();
           st.pop();
           st.push(res2+res1);
		}
		else if(ref[i]=='-')
		{
           res1=st.top();
           st.pop();
           res2=st.top();
           st.pop();
           st.push(res2-res1);
		}
		else if(ref[i]=='*')
		{
           res1=st.top();
           st.pop();
           res2=st.top();
           st.pop();
           st.push(res2*res1);
		}
		else if(ref[i]=='/')
		{
           res1=st.top();
           st.pop();
           res2=st.top();
           st.pop();
           st.push(res2/res1);
		}
		else if(ref[i]=='%')
		{
           res1=st.top();
           mod1=int(res1);    
           st.pop();
           res2=st.top();
           mod2=int(res2);
           st.pop();
           st.push(mod2%mod1);
		}
       

	}
	std::cout.precision(10);
	cout<<std::fixed<<st.top();
	st.pop();
}
int main()
{
	string s;
	string ref="";
	getline(cin,s);
	infixtopostfix(s,ref);
	postfixevaluation(ref);
	cout<<endl;
}