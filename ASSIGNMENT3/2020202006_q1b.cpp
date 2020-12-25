//minimum lexicographic rotation
#include<iostream>
#include<cstring>
#include<algorithm>
#include<deque>
#include<climits>
using namespace std;
struct suffix{
    int index;
    int placevalue[2];
};
bool compare(struct suffix a,struct suffix b)
{
    if(a.placevalue[0]<b.placevalue[0])
    {
        return true;
    }
    else if(a.placevalue[0]==b.placevalue[0])
    {
        if(a.placevalue[1]<b.placevalue[1])
        {
            return true;
        }
        return false;
    }
    return false;
}
int lengthoflongestsubstr(string word,int length,int k)
{
   if(k==1)
   {
       return length;
   }
   struct suffix suffixes[length];
   //get rank and next rank for each suffix and sort them
   for(int i=0;i<length;i++)
   {
        suffixes[i].index=i;
        suffixes[i].placevalue[0]=word[i]-'a';
        suffixes[i].placevalue[1]=((i+1)<length)?(word[i+1]-'a'):(-1);
   }
   sort(suffixes,suffixes+length,compare);
   //now sorting the contents based on 2 power n characters
   for(int j=4;j<2*length;j=2*j)
   {
      int newrank[length];
      int rankcntr=0;
      int mapindex[length];
      //now we need to update rank and then next rank
      for(int i=0;i<length;i++)
      {
          if(i==0)
          {
             newrank[i]=rankcntr;
             
        
          }
          else
          {
              if(suffixes[i-1].placevalue[0]==suffixes[i].placevalue[0]&&suffixes[i-1].placevalue[1]==suffixes[i].placevalue[1])
              {
                 newrank[i]=rankcntr;
              }
              else
              {
                  rankcntr++;
                  newrank[i]=rankcntr;
              }
              
          }
          mapindex[suffixes[i].index]=i;
          
      }
      //now update ranks
      for(int i=0;i<length;i++)
      {
          suffixes[i].placevalue[0]=newrank[i];
      }
      //now update next character rank
      for(int i=0;i<length;i++)
      {
          int next=suffixes[i].index+(j/2);
          if(next<length)
          {
              suffixes[i].placevalue[1]=suffixes[mapindex[next]].placevalue[0];
          }
          else
          {
              suffixes[i].placevalue[1]=-1;
          }
          
      }
      sort(suffixes,suffixes+length,compare);
   }
   //Apply KASAI ALGO
   //buidling position array
   int position[length];
   for(int i=0;i<length;i++)
   {
       position[i]=suffixes[i].index;
   }
   int rank[length];
   for(int i=0;i<length;i++)
   {
        rank[position[i]]=i;
   }
   int cntr=0,temporary;
   int lcparray[length];
   for(int i=0;i<length;i++)
   {
         if(rank[i])
         {
             temporary=position[rank[i]-1];
             while(word[i+cntr]==word[temporary+cntr])
             {
                 cntr++;
             }
             lcparray[rank[i]]=cntr;
             if(cntr>0)
             {
                 cntr=cntr-1;
             }

         }
         else
         {
             lcparray[rank[i]]=-1;
         }
         
   }
   int finallcparray[length];
   for(int i=1;i<length;i++)
   { 
       finallcparray[i-1]=lcparray[i];
    
   }
   finallcparray[length-1]=-1;
   int finalk=k-1;
   int result=INT_MIN;
   deque<int>d(finalk);
   int i;
   for( i=0;i<finalk;i++)
   {
       while((!d.empty())&&(finallcparray[i]<=finallcparray[d.back()]))
       {
           d.pop_back();
       }
       d.push_back(i);
   }
   for(;i<length-1;i++)
   {
       result=max(result,finallcparray[d.front()]);
       while((!d.empty())&&(d.front()<=i-finalk))
       {
           d.pop_front();
       }
       
       while((!d.empty())&&(finallcparray[i]<=finallcparray[d.back()]))
       {
           d.pop_back();
       }
       d.push_back(i);

   }
   result=max(result,finallcparray[d.front()]);
   if(result==0)
   {
       return -1;
   }
   return result;
   
  
  
}

int main()
{
    
    string ch;
    getline(cin,ch);
    int n=ch.length();
    int k;
    cin>>k;
    cout<<lengthoflongestsubstr(ch,n,k);
    return 0;
    
}