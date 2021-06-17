#include<iostream> 
#include <sstream>  // for string streams 
#include <string>  // for string 
#include<fstream> //stream class to both read and write from  files
#include <bits/stdc++.h> //for precompiling  ( reduce time wasted)
#define d 256  // d is the number of characters in the input alphabet
#define q 11
using namespace std;

void naive(string p,string text)
{
	int m=p.length();  //m=pattern length
	int n=text.length();  //n=text length
	int i;                  //shift numbers      
	int j;             
	for(i=0;i<=n-m;i++)  
	{
        for(j=0;j<m;j++)   //for current index i and check for pattern match
        {
        	if (text[i+j]!=p[j])  //pattern  and text are not matched
			break; 
		}
		if (j==m)   // pattern match
			cout << "Pattern found at index: "<< i << endl; 
			
	}
	
} 


void preFixFn(string p,int* lps)    //pre computing- compute LPS array   ( for kmp algorithm )
{   
    int len = 0;   //keep length 0
    lps[0] = 0; // in LPS array lps[0] is alaways 0.   
    int m = p.length();   // length  pattern
    int i = 1;    //iterator
    while (i<m)    
	{ 
        if (p[i]==p[len])
		{ 
            len++;   
            lps[i] = len;   // for current index i, length value assign lps[i]
            i++; 
        } 
        else     // pattern[i]  not equal to pattern length
		{ 
            if(len!=0)    // in this case we don't increment i
			{ 
                len = lps[len-1]; 
            } 
            else      //for length ==0
			{ 
                lps[i] = 0; 
                i++; 
            } 
        } 
    } 
}  


void kmp(string p,string text)
{
	int m=p.length();
	int n=text.length();
	int lps[m];  // lps mean hold the longest prefix suffix value for pattern
    preFixFn(p,lps);  //calculate lps[] (preprocess the pattern)
	int i=0;              //index for text[]
	int j=0;             //index for pattern []
	while(i<n)   
	{ 
		if (p[j]==text[i])
		{ 
			j++; 
			i++; 
		} 
		else             //mismatch after j match
		{ 
			if(j!= 0) 
				j=lps[j-1]; 
			else
				i=i+1; 
		} 
		if(j==m) { 
			cout << "Pattern found at index: "<<i-j<< endl; //printf("Found pattern at index =%d \n",i-j); 
			j=lps[j-1]; 
		} 
		
	
 	}
}




void rabinKarp(string p,string text)
{
	int m=p.length();
	int n=text.length();
	int i, j; 
	int pH= 0; // hash value for pattern 
	int tH= 0; // hash value for txt 
	int h = 1; 
	for(i=0;i<m-1;i++) 
	{
		h=(h*d)%q;              //calculate hash value of pattern
	}
	for(i=0;i<m;i++) 
	{ 
		pH = (d*pH+p[i])%q; 
		tH = (d*tH+text[i])%q; 
	} 

	
	for(i=0;i<=n-m;i++) 
	{ 
		if ( pH == tH )         //check hash values
		{ 
			for (j = 0; j < m; j++)         
			{ 
				if(text[i+j]!=p[j]) 
					break; 
			} 
			if (j == m) 
				cout<<"Pattern found at Index :"<< i<<endl;  
		} 
		if (i<n-m) 
		{ 
			tH=(d*(tH-text[i]*h)+text[i+m])%q; 
			if (tH < 0)           //hash value of text value negative, converting it to positive
			tH = (tH + q); 
		} 
	} 
	
	
}



void badChar(string p,int size,int badchar[d])
{ 
	int i; 
	for(i=0;i<d;i++)
	{
		badchar[i]=-1;                // all the occurrence are -1
	} 
	for (i = 0; i < size; i++)
	{
		badchar[(int) p[i]] = i;
	} 
	 
} 
void boyerMoore(string p,string text)
{
	int m=p.length();
	int n=text.length();
	int badchar[d]; 
	badChar(p,m,badchar);      //call preprocessing function  badChar()
	int s=0; 
	while(s<= n-m)			
	{ 
		int j=m-1; 
		while(j>=0 && p[j]==text[s+j])
		{
			j--;                //pattern is in current shift , then j will become -1
		 } 
		if (j<0) 
		{ 
			cout<<"pattern found at Index: " <<s<<endl; 
			s+=(s+m<n)? m-badchar[text[s+m]]:1; 

		} 

		else
			s += max(1,j-badchar[text[s+j]]); 
	} 
	
}



 
int main() 
{   
    int year,m,date;
    //int len=ceil(log10(year));
    cout<<"Enter your Birth Year:"<<endl;
	cin>>year;
	int y=year%100;  //last two number of the given number
	cout<<year<<"-------------->"<<y<<endl;
	
	do{
		cout<<"Enter your Birth Month:"<<endl;
		cin>>m;
		if(m>12 || m<0)                  // month must be between 1 and 12
			cout<<"------Invalid Month-----\nAgain"<<endl;
	}while(m>12 || m<0);
	
	
	do{
		cout<<"Enter your Birth Date:"<<endl;
		cin>>date;
		if(date>31 || date<0)                         //date must be less than 31 and must be positive number
			cout<<"-----Invalid Date----\nAgain"<<endl;
	}while(date>31 || date<0);
	
	int num=(y*10000)+(m*100)+date;
	cout<<num<<endl;
	
    ostringstream str0; //declare out put string
    str0 << num; //sending number as a stream into out put
    string p = str0.str(); // convert number in to string by usinng str
    cout << "Now your birthday string is : "; 
    cout << p << endl;     //display the string  
	 
    
    fstream myFile;
    myFile.open("pi.txt");   //open text file
    int line=0; //keep lines
    string read="";
    string str1="";  //keep every partial string  as a one string 
    if(myFile.is_open())   //chech whether file is open or not
    {
    	//cout<<"File is open";
    	while(getline(myFile,read))  //read file
    	{ 
    	    ++line;
    		if(line>=22)  //start to read line number 22
    		{
    			if(read!="")
    			{
    				static string a[5];      //for split parts
	                string s = "";
	                int i = 0;
	                stringstream ssin(read);  //used for breaking words
	                while(ssin.good() && i<5)
					{
		                ssin>>a[i];
		                s=s+a[i];
		                ++i;
	                }
	
    				str1.append(s);    // 
				}
				else
					--line;
				
			}
    		
    	   
		}
		myFile.close();
	}
	else        //if file doesn't exist
	{
		cout<<"File doesn't open";
	}
    
    int option;
    while(1){
    	cout<<endl<<"------ Enter string matching algorithm  to search your birthday string Index------"<<endl<<endl;  
		cout<<endl<<"1. Naive String Matching Algorithm";
		cout<<endl<<"2. Knuth-Morris-Pratt Algorithm";
		cout<<endl<<"3. Rabin Karp Algorithm";
		cout<<endl<<"4. Boyer-Moore Algorithm";
		cout<<endl<<"5. Exit"<<endl<<endl;
		cout<<endl<<"Enter an option:";  //put your choice 
		cin>>option;
		bool ignore=false;
		while(!cin)   //check whether option is integer or not  . otherwise we enter string as a option ,loop wiil be run infinitely
		{
			if(!ignore)   
			{
				cout<<"it's not an integer....."<<endl;
				cout<<"Option must be 1, 2, 3, 4 or 5\n"<<endl;
				ignore=true;
				
			}
			
			cin.clear(); 
			cin.ignore();
			cin>>option;
		}
		
		switch(option){
			case 1: 
				naive(p,str1);   //call  naive string matching algorithms
				break;
			case 2:
				kmp(p,str1);    //call kmp algorithm
				break;
			case 3:
			    rabinKarp(p,str1);    //call rabin karp algorithm
				break;
			case 4:
				boyerMoore(p,str1);     //call boyer moore algorithm
				break;
			case 5:
				exit(0);             //terminate execute
				break;
			default:    
				cout<<endl<<"Wrong option ";    //   if enter invalid option
				break;
				
			
		}
	}
    
    return 0; 
}
