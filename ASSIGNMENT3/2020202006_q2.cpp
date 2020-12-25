#include<iostream>
using namespace std;
class node{

public:node *left;
	   node *right;
};
class Trie
{
	node *root;
public:Trie()
       {
       	root=new node();
       }
       void insert(long long int data)//ASSUME 32 bit
       {
       	   int msd;
       	   node *temp=root;
           for(int i=63;i>=0;i--)
           {
           	msd=(data>>i)&1;//to get right msd
           	if(msd==0)
           	{
               if(temp->left==NULL)
               {
               	 temp->left=new node();
               }
               temp=temp->left;
           	}
           	else
           	{
                 if(temp->right==NULL)
                 {
                 	temp->right=new node();
                 }
                 temp=temp->right;
           	}
           }
       }
       int maxxor(long long int data)
       {
       	 int msd;
       	 int ans=0;
       	 node *temp=root;
       	 for(int i=63;i>=0;i--)
       	 {
       	 	msd=(data>>i)&1;
       	 	if(msd==0)
       	 	{
       	 		if(temp->right!=NULL)
       	 		{
                   ans+=(1<<i);
                   temp=temp->right;
       	 		}
       	 		else
       	 		{
       	 			temp=temp->left;
       	 		}
       	 	}
       	 	else
       	 	{
       	 		if(temp->left!=NULL)
       	 		{
                    ans+=(1<<i);
                    temp=temp->left;
       	 		}
       	 		else
       	 		{
       	 			temp=temp->right;
       	 		}

       	 	}
       	 }
       	 return ans;
       }

};
int main()
{
   Trie t;
   int n,q;//number of elements in array
   cin>>n>>q;
   long long int arr[n],temp;
   for(int i=0;i<n;i++)
   {
   	cin>>arr[i];
   	t.insert(arr[i]);
   }
   while(q--)
   {
      cin>>temp;
      cout<<t.maxxor(temp)<<endl;
   }

}