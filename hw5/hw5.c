/**********
Student Number: F74045018
Name: Cayon Liow Keei Yann
Way of Compiling: gcc -o hw5 hw5.c
Way of Executing: ./hw5 N P
Function of the Program: A program designed to play the game MASTER MIND with respect to hw3 automictically,computer itself will ramdomly generate 'P'number to guess the answer until the addtion 'H' and 'X' is equal to 'P',which mean all the number are correct but some of them are with wrong position,then rearrange the number into the correct position in order to obtain the correct answer.**********/

#include<stdio.h>
#include<stdlib.h>
#include<time.h> //to set a random number
#include<string.h> //to check the length of the input integer
#include<math.h>
	void functionA(int t[],int a,int n )//to set the answer ramdomly and also make sure that the integer of the answer didn't repeat
   	{
        if(t[a]!=0) return;
		t[a]=((rand()%n)+1);
		functionA(t,a,n);//recursion
	}

	void functionB(int g[],int b, int c)// to separate a N-digit number to 'N' number ans put into array
	{
		g[b]=c%10;//take the remainder and put into the array
	}

	int functionC(int q,int r,int s)//function of showing the result to player
	{
		if (q!=r)
		{
			s=0;
			printf("_____________________________________________________________________");
			printf("\n");
			//printf("YOUR ANSWER:");
		}
		
		if (q==r)
		{
			s=1;//markings of there are 'N' of 'H' and the answer is correct
			printf("_____________________________________________________________________");
			printf("\n");
			printf("BINGO!!!!!!");
			printf("\n");
			return 0;
		}
	}

	int repeat(int n,int p,int a[])//make sure that the integer of the answer didn't repeat
	{
		int i,j,t;
		for (i=0;i<p;i++)
		{	
			t=0;	
     	 	while (t==0)
      		{
				t=1;
        		for (j=0;j<p;j++)
        		{
						
					if (i!=j)
        			{
						if (a[i]==a[j])
            			{
                			a[i]++;//when there are numbers repeated, number in array 'answer[i]'will plus to make it different from others
							t=0;
           				}
					
						if (a[i]>n)//if a[i] is larger than N after adding 1, a[i] reset to 1 then do the while again
           			 	{
							a[i]=1;
                			t=0;
						}
					}
	  			}	
			}
    	}
	}

	void funD(int GUESS,int guess[],int i)//to allocate the random number generated to guess to array guess[]
	{
		if(i==0)return;
		guess[i]=GUESS%10;
		GUESS=GUESS/10;	
		funD(GUESS,guess,i-1);//recursion
	}	

int main(int argc,char *argv[])
{
	int H,X,N,P,Lp,Ln,i,j,t,x,y,k,d;
	Ln=strlen(argv[1]); //Ln=the length of input N
	Lp=strlen(argv[2]); //Lp=the length of input P
		if (Lp!=1||Ln!=1) //to check that if the command agrument list is not single digit
		{
			printf("the command argument list is larger than 1-9.\n");
			return 0;
		}
	//to typecast the strings to integer
	N=atoi(argv[1]);
	P=atoi(argv[2]);

	if(N==0||P==0) //the integer '0' is not accepted
	{
		printf("The input of N or P is not valid.\n");
		return 0;
	}

	if (P>N) //the number of positions can't larger than the number of integer to play with
	{	
		printf("since P>N,the program is not work,plaese input correctly.\n");
		return 0;
	}
	printf("The number of integer to play with:%d\nThe number of positions: %d\n",N,P);

	//to initialise the array to 0
	int answer[100]={0};
	int yo[100]={0};
	
	//to set the answer ramdomly and also make sure that the integer of the answer didn't repeat
	srand((unsigned)time(NULL));
	for(i=0;i<P;i++)
		functionA(answer,i,N);

	repeat(N,P,answer);
   
	printf("ANSWER:");
	for (i=0;i<P;i++)
		printf("%d",answer[i]);
	
	//the making of table
	printf("\n");
	printf("_____________________________________________________________________");
	printf("\n");
	printf("|YOUR ANSWER");	
	printf("\t|\t");
	printf("'H'\t|\t'X'\t|\tCOUNT	|");
	printf("\n");
	printf("_____________________________________________________________________");
	printf("\n");
	
	int guess[100]={0};
	int times=1;//recording the times of executing
	int g=0;//When the answer of user guess is not exactly correct, there is a marking that let the loop to continue and use
	int f=0;//marking for there are not all the number are correct
		while(g==0)
		{
			if(f==0)
			{
				int GUESS;
				int ww[P];
				int w=1;
				for(i=0;i<P;i++)
					ww[i]=10; 
				for(i=0;i<P;i++)
					w=w*ww[i];
				//int w=pow(10,P);
				GUESS=rand()%w+1; 
				funD(GUESS,guess,P-1);
				for(i=0;i<P;i++)
					if(guess[i]==0)
						functionA(guess,i,N);
	
				repeat(N,P,guess);

				printf("|");
				for(d=0;d<P;d++)
					printf("%d",guess[d]);
				
				printf("\t\t|\t");
			
				H=0,X=0;//to initialise the variables to 0
				for(i=0;i<P;i++) //process to calculate the 
				{
					y=0; //marking that 'i'th arrays have a 'H'
					if(answer[i]==guess[i]) //to calculate H by determing the number of 'i' in both array are the same
					{
						y=1;
						H=H+1;
					}
						
					for(j=1;j<P;j++)
					{
						if (answer[i]==guess[j] && y==0)//to calculate X by determining that the 'i'th of both arrays have no marking 'y'
								X=X+1; 	
					}
				}
				
				printf("%d\t|	%d\t|\t%d\t|\n",H,X,times);//the number of 'H's and 'X's calculated is shown
				
				functionC(H,P,g);
				
				if(H+X!=P)//generate a random number again
					f=0;
					
				if (H+X==P)//that's means all the number are correct but some of them are with wrong position
					f=1;
					
				if (H==P)// the guess is exactly correct, directly end the program
					return 0;
			
				if(f==1)//this step starts when when all the number are correct but some of them are with wrong position
			{
				int ss[P];//the temporary array to store guess[]
				int s,tt;
				for (s=0;s<P;s++) 
					ss[s]=guess[s];
				
				int pp;
				int temporary[P];
				for(pp=0;pp<=P;pp++)//initialization of array
					temporary[pp]=0;
						
				int gguess[P];
				printf("|");
				for(y=0;y<P;y++) //process to find out the actual position of every number
				{
					for(i=0;i<P;i++)	
					{
						if(answer[y]==guess[i]&&y==i) //to fix the correct position
							temporary[y]=guess[i];
								
						if(answer[y]==guess[i]&&y!=i)//to put the number into the correct position
							temporary[y]=guess[i];
					}
							
					gguess[y]=temporary[y];
					printf("%d",gguess[y]);
					
				}
				printf("\t\t|\t%d\t\t0\t\t%d\t|",P,++times);
				printf("\n");
				
				H=0,X=0;
				for(i=0;i<P;i++)//process of verifying to the answer again
				{
					if(answer[i]==gguess[i])
					H=H+1;		
				}
				functionC(H,P,g);
				if(H==P)
				return 0;
			
			}
			}times=times+1;
		}
return 0;//the program end
}

