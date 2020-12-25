#include<iostream>
#define TIME  cout<<"\nTime elapsed:"<<1000*clock()/CLOCKS_PER_SEC<<"ms\n";
using namespace std;
template<typename T>
class Deque
{
	long int currsize;
	long int maxsize;
	long int fr,rear;
	T *arr;
	public:void deque()
	       {
	       	  currsize=0;
	       	  maxsize=10000000;
	       	  rear=maxsize/2;
	       	  fr=rear;
              arr=new T[maxsize];
	       } 
           void deque(long int n,T x)
           {
           	currsize=0;
           	maxsize=10000000;
            rear=maxsize/2;
            fr=rear;
           	arr=new T[maxsize];
           	int cntr=0;
           	while(cntr<n)
           	{
           		push_back(x);
           		cntr++;
           	}
           }
	       void push_back(T d)
	       { 
	       	  if(rear==maxsize)
	       	  {
	       	  	T *oldArr=arr;
	       	  	arr=new T[2*maxsize];
	       	  	maxsize=2*maxsize;
	       	  	for(long int i=fr;i<=rear;i++)
	       	  	{
	       	  		arr[i]=oldArr[i];
	       	  	}
	       	  	delete [] oldArr;
	       	  }
	       	  arr[rear]=d;
	       	  rear++;

	       }
	       void push_front(T d)
	       {
	       	/*if(fr<=0)
	       	{
	       		T *oldArr=arr;
	       		arr=new T[2*maxsize];
	       		maxsize=2*maxsize;
	       		for(long int i=fr;i<=rear;i++)
	       		{
                    arr[i+(maxsize/2)]=oldArr[i];
	       		}
	       		delete [] oldArr;

	       	}*/
	       	arr[--fr]=d;
	       }
	       void pop_back()
	       {
	       	rear--;
	       }
	       void pop_front()
	       {
	       	fr++;
	       }
	       T front()
	       {
	       	return arr[fr];
	       }
	       T back()
	       {
	       	return arr[rear-1];
	       }
	       T operator[](const int i)
	       { 
	       	  return arr[fr+i];
           }
           int size()
           {
           	return (rear-fr);
           }
           bool empty()
           {
           	if(rear==fr)
           	{
           		return true;
           	}
           	else
           	{
           		return false;
           	}
           }
           void clear()
           {
               rear=fr;
            
           }
           void resize(long int n,T d)
           {
           	      int s=size();

                  if(s<n)
                  {
                      for(long int i=0;i<n-s;i++)
                      {
                      	arr[rear++]=d;
                      }


                  }
                  else
                  {
                       for(long int i=0;i<s-n;i++)
                       {
                       	  pop_back();
                       }

                  }
               
                
                 
           }
           void display()
           {
           	 int i=0;
           	 while(i<size())
           	 {
           	 	cout<<arr[fr+i]<<" ";
           	 	
           	 	i++;
           	 }
           	 cout<<endl;
           }



};
int main()
{
	Deque<int>d;
	int x,n;
	int queries,qno;
	cin>>queries;
	while(queries--)
	{
		cin>>qno;
		switch(qno)
		{
			case 1:cin>>x;
			       d.push_front(x);
			       d.display();break;
			case 2:d.pop_front();d.display();break;
			case 3:cin>>x;
			       d.push_back(x);
			       d.display();
			       break;
			case 4:d.pop_back();
			       d.display();break;
			case 5:d.deque();
			case 6:cin>>n;
			       cin>>x;
			       d.deque(n,x);break;
			case 7:cout<<d.front()<<endl;break;
			case 8:cout<<d.back()<<endl;break;
			case 9:cout<<d.empty()<<endl;break;
			case 10:cout<<d.size()<<endl;break;
			case 11:cin>>n;
			        cin>>x;
			        d.resize(n,x);
			        d.display();break;
			case 12:d.clear();
			        d.display();break;
			case 13:cin>>n;
			        cout<<d[n];break;
			case 14:d.display();break;


		}

	}

	


}