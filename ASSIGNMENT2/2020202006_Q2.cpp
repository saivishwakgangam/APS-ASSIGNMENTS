#include <iostream>
#include <string>
#include <boost/lexical_cast.hpp>
using namespace std;
namespace std {
template <typename T1>
  string to_string(const T1& value) {
    return string(value);
  }
}
template<typename T1,typename T2>
class Node{
	public:T1 key;
	       T2 value;
	       Node<T1,T2>*next;
	       Node(T1 key,T2 val)
           {
           	   this->key=key;
               value=val;
               next=NULL;
           }
           ~Node()
           {
           	if(next!=NULL)
           	{
           		delete next;
           	}
           }
};

template<typename T1,typename T2>
class Hashtable
{
    public:Node<T1,T2>**tab;
	       int currsize;
	       int totalsize;
           Hashtable()
           {
           	 totalsize=7;
           	 tab=new Node<T1,T2>*[totalsize];
           	 currsize=0;
           	 for(int i=0;i<totalsize;i++)
           	 {
           	 	tab[i]=NULL;
           	 }

           }
           int hashfunction(T1 keyp)
           {
               //string key=boost::lexical_cast<std::string>(keyp);
               string key=to_string(keyp);
           	   int index=0;
           	   int power=1;
           	   for(int i=0;i<key.length();i++)
           	   {
           	   	 index=index+(power*key[i])%totalsize;
                 index=index%totalsize;
                 power=(power*27)%totalsize;

           	   }
           	   return index;
           }
           void rehash()
           {
           	Node<T1,T2>**oldtab=tab;
           	int oldtabsize=totalsize;
           	totalsize=2*totalsize;//next prime number
           	tab=new Node<T1,T2>*[totalsize];
           	for(int i=0;i<totalsize;i++)
           	{
           		tab[i]=NULL;
           	}
           	currsize=0;
           	//copy oldtab into tab
           	for(int i=0;i<oldtabsize;i++)
           	{
           		Node<T1,T2>*temp=oldtab[i];
           		while(temp!=NULL)
           		{
           			insert(temp->key,temp->value);
           			temp=temp->next;
           		}
           		if(oldtab[i]!=NULL)
           		{
           			delete oldtab[i];
           		}

           	}
           	delete [] oldtab;
           }
           void insert(T1 key,T2 value)
           {
               int index=hashfunction(key);
               Node<T1,T2>*node=new Node<T1,T2>(key,value);
               node->next=tab[index];
               tab[index]=node;
               currsize++;
              float loadfactor=(currsize)/(1.0*totalsize);
              if(loadfactor>0.7)
              {
                   rehash();
              }
                
           }
           bool find(T1 key)
           {
           	  int index=hashfunction(key);
           	  Node<T1,T2>*temp=tab[index];
           	  while(temp!=NULL)
           	  {
           	  	if(temp->key==key)
           	  	{
           	  		return true;
           	  	}
           	  }
           	  return false;
           }
           void erase(T1 key)
           {
           	  int index=hashfunction(key);
           	  Node<T1,T2>*temp=tab[index];
           	  Node<T1,T2>*temporary;
           	  if(temp==NULL)
           	  {
           	  	return;
           	  }
           	  if(temp->next==NULL)
           	  {
           	  	if(temp->key==key)
           	  	{
           	  		tab[index]=NULL;
           	  	}
           	  	return;

           	  }
           	  if(temp->key==key)
           	  {
           	     tab[index]=temp->next;
           	     return;
           	  }
           	  while(temp->next!=NULL&&temp->next->key!=key)
           	  {
           	  	temp=temp->next;
           	  }
           	  if(temp->next!=NULL)
           	  {
           	  	if(temp->next->next==NULL)
           	  	{
                     temporary=temp->next;
                     temp->next=NULL;
           	  	}
           	  	else
           	  	{
           	  		temporary=temp->next;
           	  		temp->next=temporary->next;
           	  	}
           	  }
      
           	  
           }
           void print()
           { 
           	  Node<T1,T2>*temp;
           	  for(int i=0;i<totalsize;i++)
           	  {
           	  	cout<<"Bucket No:"<<i;
           	  	temp=tab[i];
           	  	while(temp!=NULL)
           	  	{
           	  		cout<<temp->key<<" -> ";
           	  		temp=temp->next;
           	  	}
           	  	cout<<endl;
           	  }
             
                
           } 
           T2 operator[](T1 key)
           {
           	 int index=hashfunction(key);
           	 Node<T1,T2>*temp=tab[index];
           	 while(temp!=NULL)
           	 {
           	 	if(temp->key==key)
           	 	{
           	 		return temp->value;
           	 	}
           	 }
           }


};
int main()
{
	Hashtable<int,int>h;
	int key,value;
	int x;
	while(true)
	{
       cin>>x;
	   switch (x)
	   {
	      case 1:cin>>key>>value;
		         h.insert(key,value);
				 break;
		  case 2:cin>>key;
		         h.erase(key);
				 break;
		  case 3:cin>>key;
		         cout<<h.find(key)<<endl;
				 break;
		  case 4:cin>>key;
		         cout<<h[key]<<endl;break;
		  
	   }
	}
	
}