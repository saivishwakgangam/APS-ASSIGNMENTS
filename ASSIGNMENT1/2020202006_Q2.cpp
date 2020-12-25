#include <bits/stdc++.h>
using namespace std;
bool smaller(string str1, string str2) 
{ 
    int n1 = str1.length();
    int n2 = str2.length();
    if(n1 < n2)
    {
    	return true;
    }
    else if(n1>n2)
    {
    	return false;
    }
    else
    {
    	for(int i=0;i<n1;i++)

    	{
    		if(str1[i]<str2[i])
    		{
    			return true;
    		}
    		if(str1[i]>str2[i])
    		{
    			return false;
    		}
    	}
    }
    return false;

} 
string add(string a,string b)
{
	if(a.length()>b.length())
	{
		swap(a,b);
	}
	int n1=a.length();
	int n2=b.length();
	string res="";
	int sum,carry=0;
	reverse(a.begin(),a.end());
	reverse(b.begin(),b.end());
	for(int i=0;i<n1;i++)
	{
         sum=((a[i]-'0')+(b[i]-'0')+carry);
         res.push_back(sum%10+'0');
         carry=sum/10;
	}
	for(int i=n1;i<n2;i++)
	{
		sum=((b[i]-'0')+carry);
		res.push_back(sum%10+'0');
        carry=sum/10;
	}
	if(carry)
	{
		res.push_back(carry+'0');
	}
	reverse(res.begin(),res.end());
    res.erase(0, min(res.find_first_not_of('0'), res.size()-1));   
    return res;

}
string difference(string a,string b)
{
	string res="";
    int n1=a.length();
    int n2=b.length();
    reverse(a.begin(),a.end());
    reverse(b.begin(),b.end());
    int carry=0,sub;
    for(int i=0;i<n2;i++)
    {
         sub=((a[i]-'0')-(b[i]-'0')-carry);
         if(sub<0)
         {
         	sub=sub+10;
         	carry=1;
         }
         else
         {
         	carry=0;
         }
         res.push_back(sub +'0');
    }
    for(int i=n2;i<n1;i++)
    {
    	sub=((a[i]-'0')-carry);
    	if(sub<0)
    	{
    		sub=sub+10;
    		carry=1;
    	}
    	else
    	{
    		carry=0;
    	}
    	res.push_back(sub + '0');
    }
    reverse(res.begin(),res.end());
    res.erase(0, min(res.find_first_not_of('0'), res.size()-1));
    return res;
}
std::string multiply(string a,string b)
{
   string res="";
   int result,sum;
	int l1=a.length();
	int l2=b.length();
	char ch;
	//cout<<l1<<l2;
	int arr[l1+l2]={0};
	for(int i=l1-1;i>=0;i--)
	{
		for(int j=l2-1;j>=0;j--)
		{
            result=(b[j]-'0')*(a[i]-'0');
            sum=arr[i+j+1]+result;
            arr[i+j]+=sum/10;
            arr[i+j+1]=sum%10;

		}
	}
	for(int i=0;i<(l1+l2);i++)
	{
		res.push_back(arr[i]+'0');
	}
	res.erase(0, min(res.find_first_not_of('0'), res.size()-1));
	return res;
}
string divide(string a,int b)
{
	string res="";
	int index=0;
	int temp=a[index]-'0';
	while(temp<b)
	{
		temp=temp*10+(a[++index]-'0');
	}
	while(a.length()>index)
	{
		res.push_back((temp/b)+'0');
		temp=((temp%b)*10)+(a[++index]-'0');
	}
	if(res.length()==0)
	{
		return "0";
	}
	else
	{
		return res;
	}

} 
string mod(string a,string b)
{
	string left="0";
	string right=a;
	string m;
	while(smaller(left,right))
	{
       m=divide((add(left,right)),2);
       if(!(smaller(a,multiply(m,b))))
       {
       	if(!(smaller(difference(a,multiply(m,b)),b)))
       	{

       	left=add(m,"1");
        }
        else
        {
        	right=m;
        }
       }
       else
       {
       	 right=m;
       }
	}
	return difference(a,multiply(left,b));
}
string gcd(string a,string b)
{
	if(b.compare("0")==0)
	{
		return a;
	}
	else
	{
		return gcd(b,mod(a,b));
	}
}

void fastexponentiation(string a,int b)
{
	string res="1";
	while(b)
	{
		if(b&1)
		{
			res=multiply(res,a);
		}
		b=b/2;
		a=multiply(a,a);
	}
	cout<<res<<endl;
}
void fact(int n)
{
	int arr[1000000]={-1};
    int end=0,carry=0,res;
    arr[0]=1;
    for(int i=2;i<=n;i++)
    {
    	for(int j=0;j<=end;j++)
    	{
    		res=i*arr[j]+carry;
    		arr[j]=res%10;
    		carry=res/10;

    	}
    	while(carry)
    	{
    		arr[++end]=carry%10;
    		carry=carry/10;
    	}
    }
    for(int i=end;i>=0;i--)
    {
    	cout<<arr[i];
    }
    cout<<endl;   

}
int main()
{
	string a,b;
	int num;
	int q,qno;
	cin>>q;
	while(q--)
	{
		cin>>qno;
		switch(qno)
		{
			case 1:cin>>a;
			       cin>>num;
			       fastexponentiation(a,num);break;
			case 2:cin>>a;
			       cin>>b;
			       if(smaller(a,b))
			       {
			       	swap(a,b);
			       }
			       cout<<gcd(a,b)<<endl;
			       break;
			case 3:cin>>num;
			       fact(num);
			       break;
		}
	}
}