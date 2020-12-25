#include<iostream>
#include<algorithm>
using namespace std;
template <class T> struct Less 
{
bool operator()(const T &l, const T &r)
{
   return l<r;
}	
};
template<typename T>
class node
{
public:T data;
    int count;
    int rcount;
    int lcount;
    int height;
	node *left;
	node *right;
	node(T d)
	{
		height=1;
		rcount=0;
		lcount=0;
		count=1;
		data=d;
		left=NULL;
		right=NULL;
	}
};
template<class T,class Compare = Less<T>>
class BST
{
public: node<T>* root;
        T upperbound;
        T lowerbound;
        Compare cmp;
        int size;
  BST() : root(NULL), cmp(Compare()){size=0;}
  int height(node<T> *root)
  {
  	if(root==NULL)
  	{
  		return 0;
  	}
  	return (root->height);
  }
  int balancefactor(node<T> *root)
  {
     if(root==NULL)
     {
     	return 0;
     }
     return (height(root->left)-height(root->right));

  }
  node<T>* rightRotate(node<T> *root)
  {
  	node<T>* newroot = root->left; 
    node<T>* newroot1 = newroot->right; 
    int rightchildren=(newroot == NULL)?0:newroot->rcount;
    root->lcount=rightchildren;
    if(newroot!=NULL)
    {
    	newroot->rcount=newroot->rcount+root->rcount+1;
    }
    newroot->right = root; 
    root->left = newroot1;  
    root->height = max(height(root->left), height(root->right))+1; 
    newroot->height = max(height(newroot->left), height(newroot->right))+1; 
    return newroot;
  }
  node<T>* leftRotate(node<T> *root)
  {
    node<T>* newroot = root->right; 
    node<T>* newroot1 = newroot->left; 
    int leftchildren=(newroot==NULL)?0:newroot->lcount;
    root->rcount=leftchildren;
    if(newroot!=NULL)
    {
    	newroot->lcount=newroot->lcount+root->lcount+1;
    }
    newroot->left = root; 
    root->right = newroot1;  
    root->height = max(height(root->left), height(root->right))+1; 
    newroot->height = max(height(newroot->left), height(newroot->right))+1; 
    return newroot;
  }
  void insert(T data)
  {
  	root=insertInBST(root,data);
  	size++;

  }
  void deleteBST(T data)
  {
  	root=deleteInBST(root,data);
  	size--;
  }
  node<T>* deleteInBST(node<T> *root,T data)
  {

        if(root==NULL)
        {
        	return root;
        }
        else if(cmp(data,root->data))
        {
        	root->left=deleteInBST(root->left,data);
        	root->lcount--;
        	
        }
        else if(cmp(root->data,data))
        {
        	
        	root->right=deleteInBST(root->right,data);
        	root->rcount--;
        	
        }
        else
        {
        	if(root->count>1)
        	{
        		(root->count)--;
        	}
        	else if(root->left==NULL||root->right==NULL)
        	{

               node<T> *temp = root->left ? root->left : root->right;  
  
	            
	            if (temp == NULL)  
	            {  
	                temp = root;  
	                root = NULL;  
	            }  
	            else 
	            {  

	              *root = *temp;
	            }
	                           
	            free(temp);  
                 
        	}
            else 
            {
            	node<T> *rep=root->right;
            	while(rep->left!=NULL)
            	{
            		rep=rep->left;
            	}
            	root->data=rep->data;
            	root->right=deleteInBST(root->right,rep->data);
            }

        		
        }
        if(root==NULL)
        {
        	return root;
        }
        
        root->height=max(height(root->left),height(root->right))+1;
  	    int balance=balancefactor(root);
	  	if(balance>1&&cmp(data,root->left->data))
	  	{ 
	        return rightRotate(root);
	    }  
	    if(balance<-1&&cmp(root->right->data,data))
	    { 
	        return leftRotate(root);
	    } 
	    if(balance>1 && cmp(root->left->data,data)) { 
	        root->left = leftRotate(root->left); 
	        return rightRotate(root); 
	    } 
	    if(balance<-1&&cmp(data,root->right->data)) { 
	        root->right = rightRotate(root->right); 
	        return leftRotate(root); 
	    } 

        return root;
        
  }
  bool search(T data)
  {
  	return searchinBST(root,data);
  }
  bool searchinBST(node<T> *root,T data)
  {
  	if(root==NULL)
  	{
  		return false;
  	}
  	if(data==root->data)
  	{
  		return true;
  	}
  	if(cmp(data,root->data))
  	{
        return searchinBST(root->left,data);
    }
  	else
  	{
  		return searchinBST(root->right,data);
  	}
  }
  node<T>* insertInBST(node<T> *root,T data)
  {
  	if(root==NULL)
  	{
  		return new node<T>(data);
  	}
    if(data==root->data)
    {
    	(root->count)++;
        return root;
    }
  	else if(cmp(data,root->data))
  	{
  		root->left=insertInBST(root->left,data);
  		root->lcount++;
  	}
  	else if(cmp(root->data,data))
  	{
  		root->right=insertInBST(root->right,data);
  		root->rcount++;
  	}
  	root->height=max(height(root->left),height(root->right))+1;
  	int balance=balancefactor(root);
  	if(balance>1&&cmp(data,root->left->data))
  	{ 
        return rightRotate(root);
    }  
    if(balance<-1&&cmp(root->right->data,data))
    { 
        return leftRotate(root);
    } 
    if(balance>1 && cmp(root->left->data,data)) { 
        root->left = leftRotate(root->left); 
        return rightRotate(root); 
    } 
    if(balance<-1&&cmp(data,root->right->data)) { 
        root->right = rightRotate(root->right); 
        return leftRotate(root); 
    } 

  	return root;
  }
  int count(T data)
  {
  	return countBST(root,data);
  }
  int countBST(node<T>* root,T data)
  {
  	if(root==NULL)
  	{
  		return 0;
  	}
  	if(root->data==data)
  	{
  		return (root->count);
  	}
  	if(cmp(data,root->data))
  	{
  		return countBST(root->left,data); 
  	}
  	if(cmp(root->data,data))
  	{
         return countBST(root->right,data);
  	}
  }
  T lowerBound(T data)
  {
  	 lowerBoundBST(root,data);
  	 return lowerbound;
  }
  void lowerBoundBST(node<T>* root,T data)
  {
  	if(root==NULL)
  	{
  		return;
  	}
  	if(root->data>=data)
  	{
  		lowerbound=root->data;
  		lowerBoundBST(root->left,data);
  	}
  	else if(root->data<data)
  	{
  		lowerBoundBST(root->right,data);
  	}
  	
  }
  T upperBound(T data)
  {
  	 upperBoundBST(root,data);
  	 return upperbound;
  }
  void upperBoundBST(node<T> *root,T data)
  {
  	 if(root==NULL)
  	{
  		return;
  	}
  	if(root->data>data)
  	{
  		upperbound=root->data;
  		upperBoundBST(root->left,data);
  	}
  	else if(root->data<=data)
  	{
  		upperBoundBST(root->right,data);
  	}
  }
  T closest(T data)
  {
  	return closestBST(root,data);
  }
  T closestBST(node<T> *root,T data)
  {
    if(root->data==data)
    {
      return (root->data);
      
    }
    if(root->data>data)
    {
      if(root->left==NULL)
      {
      	  return (root->data);
      }
      if(data>root->left->data)
      {
        node<T> *temp=root->left;
        while(temp->right)
        {
        	temp=temp->right;
        }
        return ((data-temp->data)<(root->data-data))?(temp->data):(root->data);
      }
      else
      {
      	return closestBST(root->left,data);
      }
    }
    if(root->data<data)
    {
    	if(root->right==NULL)
    	{
    		return (root->data);
    	}
    	if(data<root->right->data)
    	{
    		node<T> *temp=root->right;
    		while(temp->left)
    		{
    			temp=temp->left;
    		}
    	   return ((temp->data-data)<(data-root->data))?(temp->data):(root->data);
    	}
    	else
    	{
    		return closestBST(root->right,data);
    	}


    }

   }
 
};
int main()
{
	BST<int,Less<int>> h;
	int x;
	int temp;
	while(true)
	{
		cin>>x;
		switch(x)
		{
			case 1:cin>>temp;
			       h.insert(temp);
				   break;
			case 2:cin>>temp;
			       h.deleteBST(temp);
				   break;
			case 3:cin>>temp;
			       cout<<h.search(temp);break;
			case 4:cin>>temp;
			       cout<<h.count(temp)<<endl;break;
			case 5:cin>>temp;
			       cout<<h.lowerBound(temp)<<endl;break;
			case 6:cin>>temp;
			       cout<<h.upperBound(temp)<<endl;break;
			case 7:cin>>temp;
			       cout<<h.closest(temp)<<endl;
		}
	}
	

}