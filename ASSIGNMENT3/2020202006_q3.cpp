#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <climits>
using namespace std;
struct node
{
	long int element;
    int arrindex;
};
void swap(node *left,node *right)
{
	node temp=*left;
	*left=*right;
	*right=temp;
}
class Minheap
{
	node *root;
	int hsize;
public:
void minheapify(int i)
{
	int left=2*i+1;
	int right=2*i+2;
	int minimum=i;
	if(left<hsize&&root[left].element<root[i].element)
	{
        minimum=left;
	}
	if(right<hsize&&root[right].element<root[minimum].element)
	{
		minimum=right;
	}
	if(minimum!=i)
	{
		swap(&root[minimum],&root[i]);
		minheapify(minimum);

	}

}
void changemin(node x)
{
  root[0]=x;
  minheapify(0);
}

Minheap(node arr[],int size)
      {
         hsize=size;
		 root=arr;
		 int i=(hsize-1)/2;
		 while(i>=0)
		 {
			 minheapify(i);
			 i--;
		 }
	  }
};
long int size(char *name)
{
   FILE *pointer=fopen(name,"r");
   fseek(pointer,0L,SEEK_END);
   long int res=ftell(pointer);
   return res;
}
long int partition(long int *arr,long int start,long int end)
{
	long int i=start-1;
	long int j=start;
	long int pivot=arr[end];
	for(;j<=(end-1);)
	{
		if(arr[j]<=pivot)
		{
			i++;
			swap(arr[i],arr[j]);
		}
		j++;
	}
	swap(arr[i+1],arr[end]);
	return (i+1);


}
void quicksort(long int *arr,long int s,long int e)
{
	if(s>=e)
	{
		return;
	}
	long int p=partition(arr,s,e);
	quicksort(arr,s,p-1);
	quicksort(arr,p+1,e);
}


void divide(char *inputfile,int partitions,long int ramsize)
{
	FILE *input=fopen(inputfile,"r");
	if(input==NULL)
	{
		cout<<"error in opening file";
		exit(0);
	}
	FILE *output[partitions];
	char filename[9];
	for(int i=0;i<partitions;i++)
	{
		snprintf(filename,sizeof(filename),"OUTPUT%d",i+1);
		output[i]=fopen(filename,"w");
		if(output[i]==NULL)
		{
			cout<<"error in opening file";
			exit(0);
		}

	}
	//now all the output files havebeen openened so we need to write the contents in to it
	bool moredata=true;
	int presentfile=0;
	long int *data=(long int *)malloc(ramsize*sizeof(long int));
	long int currsize;
	while(moredata)
	{
		//write the data into present file
		for(currsize=0;currsize<ramsize;currsize++)
		{
			if(fscanf(input,"%ld,",&data[currsize])!=1)
			{
				moredata=false;
				break;
			}
		}
		//now apply quick sort to all the data present
        quicksort(data,0,currsize-1);
		
		//now write the sorted content into file
		for(long int j=0;j<currsize;j++)
		{
			fprintf(output[presentfile],"%ld,",data[j]);

		}
		presentfile++;

	}
	for(int j=0;j<partitions;j++)
	{
		fclose(output[j]);
	}
	fclose(input);
}
void merge(char *outputfile,int partitions,long int ramsize)
{
	FILE *chunks[partitions];
	for(int i=0;i<partitions;i++)
	{
		char filename[9];
		snprintf(filename,sizeof(filename),"OUTPUT%d",i+1);
		chunks[i]=fopen(filename,"r");
	}
	FILE *output=fopen(outputfile,"w");
	if(output==NULL)
	{
		cout<<"cannot open output file";
		exit(0);
	}
	node* data=new node[partitions];
	int currpartition=0;
	for(;currpartition<partitions;currpartition++)
	{
		if(fscanf(chunks[currpartition],"%ld,",&data[currpartition].element)!=1)
		{
			break;
		}
		data[currpartition].arrindex=currpartition;
	}
	Minheap heap(data,currpartition);
	int cntr=0;
	long int min;
	while(cntr!=currpartition)
	{
       min=data[0].element;
	   fprintf(output,"%ld,",min);
	   if(fscanf(chunks[data[0].arrindex],"%ld,",&data[0].element)!=1)
	   {
		   data[0].element=LONG_MAX;
		   cntr++;
	   }
	   heap.changemin(data[0]);
	}
	for(int i=0;i<partitions;i++)
	{
		fclose(chunks[i]);
	}
	fclose(output);
}
void externalsort(char *inputfile,char *outputfile,int partitions,long int ramsize)
{
    //divide the input file into chunks of ramsize and sort them using merge sort
	divide(inputfile,partitions,ramsize);

	//after dividing we should merge all chunk files
	merge(outputfile,partitions,ramsize);

}
int main(int argc,char **argv)
{
    char *inputfile=argv[1];
    char *outputfile=argv[2];
	long int inputsize=100000000;//number of words in input file
    long int ramsize=10000000;//number of words that can fit in ram
    int partitions=inputsize/ramsize;
    externalsort(inputfile,outputfile,partitions,ramsize);
    
}