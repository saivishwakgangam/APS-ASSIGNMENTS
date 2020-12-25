//construct suffix array and lcp array
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
bool palindrome(string s)
{
    string temp=s;
    reverse(temp.begin(),temp.end());
    if(temp==s)
    {
        return true;
    }
    return false;
}
string longestpalindrome(string word,int length,int actuallength)
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
   //Apply KASAI ALGO
   //buidling position array
   int position[length];
   for(int i=0;i<length;i++)
   {
       position[i]=suffixes[i].index;
   }
   int rank[length];
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
             lcparray[rank[i]]=0;
         }
         
         
   }
    int temp_longest=0;
    int temp_pos=0;
    int longest=0;
    int pos=0;
    string tempstr="";
    for(int i=1;i<length;i++)
    {
        if(lcparray[i]>longest)
        {
            if((position[i-1]<actuallength&&position[i]>actuallength)||(position[i-1]>actuallength&&position[i]<actuallength))
            {
                temp_longest=lcparray[i];
                temp_pos=position[i];
                tempstr.clear();
                tempstr=word.substr(temp_pos,temp_longest);
                if(palindrome(tempstr))
                {
                   longest=temp_longest;
                   pos=temp_pos;
                }

            }
        }
    }
    return word.substr(pos,longest);

  
   
   
  
  
}

int main()
{
    
    string orginal;
    getline(cin,orginal);
    string rev=orginal;
    reverse(rev.begin(),rev.end());
    string finalstr=orginal+"#"+rev;
    int n=finalstr.length();
    int alen=orginal.length();
    cout<<longestpalindrome(finalstr,n,alen);
    return 0;
    
}