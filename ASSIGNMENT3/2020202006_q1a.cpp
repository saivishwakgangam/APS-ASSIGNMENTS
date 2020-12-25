//minimum lexicographic rotation
#include<iostream>
#include<cstring>
#include<algorithm>
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
string minimumlexicographic(string word,int length)
{
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
  //find minimum lexicographic rotation
  //first find rank of the word 
  int rank[length];
  for(int i=0;i<length;i++)
  {
      rank[suffixes[i].index]=i;
  }
  //find minimumindex
  int minindex=0;
  int newlength=length/2;
  for(int i=1;i<newlength;i++)
  {
      if(rank[i]<rank[minindex])
      {
          minindex=i;
      }
  }
  string result=word.substr(minindex,newlength);
  return result;
  

  

  
  
  
}

int main()
{
    
    string ch;
    getline(cin,ch);
    ch=ch+ch;//appending the string with itself
    int n=ch.length();
    cout<<minimumlexicographic(ch,n);
    return 0;
    
}