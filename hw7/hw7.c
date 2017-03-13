/**********
Student Number: F74045018
Name: Cayon Liow Keei Yann
Way of Compiling: gcc -o hw7 hw7.c
Way of Executing: ./hw7
Function of the Program: A program that able to input or output the data into or from the file. the program also did the works of compressing and mapping data.
Updated Date: 2015.12.30
**********/

#include<stdio.h>
#include<stdlib.h>
#include<string.h> 

//defined global value
int num[400][400];
int newmapping[400][400];
int compress[400][400];
int n;
int map1[400];
int map2[400];

//function new_mapping
int new_mapping(int i,int size)
{
		int h,j,k,jj;
		for(h=0;h<=n;h++)
		{	
			int times[400]={0};
			int bbb=0;
			for(j=0;j<=size;j++)
			{	
				for(k=0;k<=n;k++)
				{
					if(num[i][h]==compress[j][k]&&num[i][h]!=0)
					{	
						times[j]++;
					}
				}		
				if(times[j]>bbb)
				{
					bbb=times[j];
					jj=j;	
				}
						
			
			}
			
			int kk,hh;
			for(hh=0;num[i][hh]!=0;hh++)
			{
				for(kk=0;kk<n;kk++)	
				{
					if(num[i][hh]==compress[jj][kk]&&num[i][h]!=0&&compress[jj][kk]!=0)
					{
						newmapping[i][kk]=1;
						if(newmapping[i][kk]!=1)
						{	
							newmapping[i][kk]=0;
							
						}
					}
				}
			}
			return jj;
		}
			
}
//structure
struct II1
{
	unsigned unit;
};

//function bucket_union
int bucket_union(int n)
{
	if(n==1)
		return 1;
	if(n==0)
		return 0;			
	}

//function print_result
void print_result(int bucket)
{
	printf("Successfully Done\n");
	printf("There are %d buckets.",bucket);
}

int main()
{
	struct II1 SS;
	SS.unit=1;
	FILE *fptrinput,*fptroutput,*fptrindex;

	char tmp;
	int i,j,h,k,b,*max,g,mm,a,remainder;
	int record;
	int yy[400];//the array used to record the numbers of buckets have
	int totalrow; //how many row the bucket have
	
	//file open
	fptrinput=fopen("buckets.in","r");
	fptroutput=fopen("mapping.out","w");
	fptrindex=fopen("buckets.out","w");
	if(fptrinput==NULL)
		{
			printf("Failed to open file bucket.in.");
			SS.unit=0;
		}
	if(fptroutput==NULL)
		printf("Failed to open file bucket.out.");
		
	for(i=0;i<400;i++)
		{
			yy[i]=0;
		}

	for(i=0;i<400;i++)
		{
			for(h=0;h<38;h++)
			{
				num[i][h]=0;	
			}
		}
	
	totalrow=0;//control row
	k=0;//which have how many number 
	i=0;//control column	
	
	//read the data into program from the buckets.in file
	while(bucket_union(SS.unit)==1)
	{
		fscanf(fptrinput,"%d",&num[totalrow][i]);
		fscanf(fptrinput,"%c",&tmp);	//the spacing between two numbers is input with the form of character
		i++;
			if((int)tmp!=32)	//32 is the DEC of space in ASCII code
			{
			totalrow++;
				yy[k]=i;
				i=0;
				k++;
			}	
			
		if(feof(fptrinput)) 
			{
		totalrow++;
				yy[k]=i;
				i=0;
				k++;
				
			break;}
	}totalrow--;
	
	//number insert
	int w=0;
	while(w==0)
	{
		w=1;
		printf("Insert a number equal or larger than 38: ");
		scanf("%d",&n);
		if(n<38)
		w=0;
	}
	
	for(i=0;i<=totalrow;i++)
		{
			for(h=0;h<n;h++)
			{
				compress[i][h]=0;	
			}
		}	
	
int size,samesame,controlinputcolumn,controloutputcolumn,flag,list;
flag=1;
list=totalrow;
controlinputcolumn=0;
controloutputcolumn=0;

//the original space of the array 'compress' is 'n'
int spaceleft[totalrow];
for (i=0;i<totalrow;i++)
	spaceleft[i] = n;

//compressing the data into the array 'compress'
int mark;
size=0;
while(controlinputcolumn<totalrow) 
{
mark=0;
	for (i=0;i<yy[controlinputcolumn];i++)	
		for (j=0;j<n;j++){

		if ( num[controlinputcolumn][i] == compress[controloutputcolumn][j])
			{
			samesame++;
			}
		}		
		if (samesame == yy[controlinputcolumn])
			{
			mark=1;
			samesame=0;
			controlinputcolumn++;
			controloutputcolumn = 0;
			}
	if (mark == 0)
	{
	if (yy[controlinputcolumn] - samesame <= spaceleft[controloutputcolumn])
		{
		for (i=0;i<yy[controlinputcolumn];i++)
			{
			flag = 1;
			for (j=0;j<n;j++)
				{
				if (flag != 0)
			            if (num[controlinputcolumn][i] != compress[controloutputcolumn][j])
					{
					if (compress[controloutputcolumn][j] == 0)
						{
						compress[controloutputcolumn][j] = num[controlinputcolumn][i];
						flag = 0;
						spaceleft[controloutputcolumn]--;
						}
					}				   
				    else
				       {
				       flag = 0;
				       }	
				       
				}
			}
		list--;

		controlinputcolumn++;
		samesame = 0;
		controloutputcolumn = 0;
		}
	else
		{
		controloutputcolumn++;
		if (size<controloutputcolumn)
                   	size = controloutputcolumn;
		samesame = 0;
		}
	}
}

	//write the compressed data array into the buckets.out file
	for (i=0;i<=size;i++)
	{
	for (j=0;j<n;j++)
		fprintf(fptrindex,"%d ",compress[i][j]);
	fprintf(fptrindex,"\n");
	}

	//mapping
	for(i=0;i<=totalrow;i++)
	{
		map1[i]=i;
		map2[i]=new_mapping(i,size);
	}
	
	//write the mapped data into the mapping.out file
	for(i=0;i<=totalrow;i++)
	{
		fprintf(fptroutput,"row=%d",map1[i]);
		fprintf(fptroutput,"---->goto=%d--",map2[i]);
		for(h=0;h<n;h++)
		{
			fprintf(fptroutput,"%d",newmapping[i][h]);
		}
	fprintf(fptroutput,"\n");
	}

//output the result on the screen
if(fprintf(fptroutput,"\n")==1)
	print_result(size+1);
	
//close file completely
fclose(fptrinput);
fclose(fptroutput);
fclose(fptrindex);
return 0;	
}


