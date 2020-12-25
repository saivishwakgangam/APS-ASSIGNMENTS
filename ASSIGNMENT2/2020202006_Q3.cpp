#include<iostream>
#include<algorithm>
using namespace std;
template <class T1> struct Less 
{
bool operator()(const T1 &l, const T1 &r)
{
   return l<r;
}	
};
template<typename T1,typename T2>
class node
{
public:T1 key;
	T2 data;
    int height;
	node *left;
	node *right;
	node(T1 k,T2 d)
	{
		height=1;
		key=k;
		data=d;
		left=NULL;
		right=NULL;
	}
};
template<typename T1,typename T2,class Compare = Less<T1>>
class MAP
{
public: node<T1,T2>* root;
        Compare cmp;
        int currelements;
        MAP() : root(NULL),cmp(Compare()),currelements(0){}
        int height(node<T1,T2> *root)
        {
  	       if(root==NULL)
  	       {
  		      return 0;
  	       }
  	       return (root->height);
        }
         int balancefactor(node<T1,T2> *root)
		 
		  {
		     if(root==NULL)
		     {
		     	return 0;
		     }
		     return (height(root->left)-height(root->right));

		  }
		 
        node<T1,T2>* rightRotate(node<T1,T2> *root)
       	{
  	       	node<T1,T2>* newroot = root->left; 
           	node<T1,T2>* newroot1 = newroot->right; 
           	newroot->right = root; 
            root->left = newroot1;  
            root->height = max(height(root->left), height(root->right))+1; 
            newroot->height = max(height(newroot->left), height(newroot->right))+1; 
    		return newroot;
       	}
       	node<T1,T2>* leftRotate(node<T1,T2> *root)
       	{
       		    node<T1,T2>* newroot = root->right; 
			    node<T1,T2>* newroot1 = newroot->left; 
			    newroot->left = root; 
			    root->right = newroot1;  
			    root->height = max(height(root->left), height(root->right))+1; 
			    newroot->height = max(height(newroot->left), height(newroot->right))+1; 
			    return newroot;
       	}
          void insert(T1 key,T2 data)
		  {
		  	currelements++;
		  	root=insertInBST(root,key,data);
		  	//print(root);
		  	//cout<<endl;

		  }
		  node<T1,T2>* insertInBST(node<T1,T2> *root,T1 key,T2 data)
		  {
		  	if(root==NULL)
		  	{
		  		return new node<T1,T2>(key,data);
		  	}
		    if(key==root->key)
		    {
		    	currelements--;
		    	root->data=data;
		        return root;
		    }
		  	else if(cmp(key,root->key))
		  	{
		  		root->left=insertInBST(root->left,key,data);
		  	}
		  	else if(cmp(root->key,key))
		  	{
		  		root->right=insertInBST(root->right,key,data);
		  	}
		  	root->height=max(height(root->left),height(root->right))+1;
		  	int balance=balancefactor(root);
		  	if(balance>1&&cmp(key,root->left->key))
		  	{ 
		        return rightRotate(root);
		    }  
		    if(balance<-1&&cmp(root->right->key,key))
		    { 
		        return leftRotate(root);
		    } 
		    if(balance>1 && cmp(root->left->key,key)) { 
		        root->left = leftRotate(root->left); 
		        return rightRotate(root); 
		    } 
		    if(balance<-1&&cmp(key,root->right->key)) { 
		        root->right = rightRotate(root->right); 
		        return leftRotate(root); 
		    } 

		  	return root;
		  }
		  void erase(T1 key)
		  {
		  	currelements--;
		  	root=deleteInBST(root,key);
		  	//print(root);
		  	//cout<<endl;
		  }
		  node<T1,T2>* deleteInBST(node<T1,T2> *root,T1 key)
		  {
		        if(root==NULL)
		        {
		        	return NULL;
		        }
		        if(cmp(key,root->key))
		        {
		        	root->left=deleteInBST(root->left,key);
		        	return root;
		        }
		        if(key==root->key)
		        {
		        	//if root is leaf node
		        	if(root->left==NULL&&root->right==NULL)
		        	{
		        		delete root;
		        		return NULL;
		        	}
		        	//if root has a single child
		        	if((root->left!=NULL&&root->right==NULL))
		            {
		            	node<T1,T2>* temp=root->left;
		            	
		            	delete root;
		            	return temp;

		            }
		            if((root->left==NULL&&root->right!=NULL))
		            {
		            	node<T1,T2>* temp=root->right;
		            	delete root;
		            	return temp;
		            }
		            //if root has two children
		            if((root->left!=NULL&&root->right!=NULL))
		            {
		            	node<T1,T2> *rep=root->right;
		            	while(rep->left!=NULL)
		            	{
		            		rep=rep->left;
		            	}
		            	root->key=rep->key;
		            	root->data=rep->data;
		            	root->right=deleteInBST(root->right,rep->key);
		            	return root;            }
		        }
		        if(cmp(root->key,key))
		        {
		        	root->right=deleteInBST(root->right,key);
		        	return root;
		        }
		        
		    }
	      bool find(T1 key)
		  {
		  	return searchinBST(root,key);
		  }
		  bool searchinBST(node<T1,T2> *root,T1 key)
		  {
		  	if(root==NULL)
		  	{
		  		return false;
		  	}
		  	if(key==root->key)
		  	{
		  		return true;
		  	}
		  	if(cmp(key,root->key))
		  	{
		        return searchinBST(root->left,key);
		    }
		  	else
		  	{
		  		return searchinBST(root->right,key);
		  	}
		  }
		  int size()
		  {
		  	return currelements;
		  }
          void clear()
          {
          	node<T1,T2> *rl=root->left;
            node<T1,T2> *rr=root->right;
            clearMap(rl);
            clearMap(rr);
            root=NULL;
            currelements=0;
          }
          void clearMap(node<T1,T2> *root)
          {
               if(root)
               {
               	  clearMap(root->left);
               	  clearMap(root->right);
               	  delete root;
               }
          }
          T2 operator[](T1 key)
          {
          	return value(root,key);
          }
          T2 value(node<T1,T2> *root,T1 key)
          {
          	if(root->key==key)
          	{
          		return (root->data);
          	}
          	if(cmp(key,root->key))
          	{
          		return value(root->left,key);
          	}
          	if(cmp(root->key,key))
          	{
          		return value(root->right,key); 
          	}
          }
          
         void print(node<T1,T2> *root)
         {
         	if(root)
         	{
         		print(root->left);
         		cout<<root->key<<"->"<<root->data<<" ";
         		print(root->right);
         	}
         }



};
int main()
{
  MAP<int,int>h;
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
		  case 5:cout<<h.size()<<endl;break;
		  case 6:h.clear();
		
		  
	   }
	}
  
}