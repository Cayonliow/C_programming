#include <stdio.h>
#include <stdlib.h>

typedef struct NODE
{
	int value[5];
	struct NODE* next;
}node;

	FILE *fourk, *searchk, *insertk, *deletek, *resultk;
	int prefix[5];
	node *group1[256];
	node *group2[4096];
	node *group3[4096];
	node *tail1[256];
	node *tail2[4096];
	node *tail3[4096];		
	
unsigned long long int rdtsc()
        {
            unsigned long long int x;
            __asm__ __volatile__ ("rdtsc" : "=A" (x));
            return x;
        }			
node* newNode()
{
	node* p=malloc(sizeof(node));
	if(p==NULL)
	{
		printf("failed to create a new node\n");
		return p;
	}
	int i;
	for(i=0;i<4;i++)
	p->value[i]=0;
	p->next=NULL;
	return p;

}

int check_open_file(FILE *file)
{
	if(file==NULL)
	{
		printf("failed to open file\n");
		
		return 0;
	}
			
	return 1;
}

int changetobit(int number,int shift)
{
	int bit;
	int tmp;
	tmp=1;
	number>>=shift;
	bit=(number&tmp==1?1:0);	
	return bit;
}

int changetoint(int number[],int bit)
{
	int i;
	int tmp_int=0;
	for ( i = 0; i < bit; i++) 
	{
		if (number[i] == 1) 
		tmp_int= tmp_int+ pow(2,bit-1 - i);
	}
return tmp_int;
}
void build_table(FILE *file)
{
	int i,j;
	int bitpattern_of_ip[32];
	int free;
	while(!feof(file))
	{
		fscanf(file,"%d%*[.]%d%*[.]%d%*[.]%d%*[/]%d%*[^\n]",&prefix[0],&prefix[1],&prefix[2],&prefix[3],&prefix[4]);

for(i=0;i<8;i++)
		{
			bitpattern_of_ip[7-i]=changetobit(prefix[0],i);
			bitpattern_of_ip[15-i]=changetobit(prefix[1],i);
			bitpattern_of_ip[23-i]=changetobit(prefix[2],i);
			bitpattern_of_ip[31-i]=changetobit(prefix[3],i);
		}
		
		
		if(prefix[4]>=8&&prefix[4]<=15)
		{
			 free=changetoint(bitpattern_of_ip,8);
			
			for(i=0;i<5;i++)
			{
				tail1[free]->value[i]=prefix[i];
			
			}
			
			tail1[free]->next=newNode(); 
			tail1[free]=tail1[free]->next;
			
		}
	
		if(prefix[4]>=16&&prefix[4]<=24)
		{
			free=changetoint(bitpattern_of_ip,12);
			
			for(i=0;i<5;i++)
			{
				tail2[free]->value[i]=prefix[i];
			
			}
			
			tail2[free]->next=newNode(); 
			tail2[free]=tail2[free]->next;
		}
	
		if(prefix[4]>=25&&prefix[4]<=32)
		{
			free=changetoint(bitpattern_of_ip,12);
			//printf("%d\n",free);
			for(i=0;i<5;i++)
			{
				tail3[free]->value[i]=prefix[i];
			
			}
			
			tail3[free]->next=newNode(); 
			tail3[free]=tail3[free]->next;
		}
	
	}

} 
int match(int bit1[],int bit2[],int length)
{
	int i;
	//int match=0;
	int matchnumber=0;
	for(i=0;i<length;i++)
		{
			if(bit1[i]==bit2[i])
			{
				matchnumber++;
			}
	
		}
		if(matchnumber==length)
		return 1;
				
	else
		return 0;
	}

node* findPrevious(node* head,int array[])
{
	if(head->value==array)
	return head;
	node *previous=head;
	
	while(previous->next!=NULL)
	{
		if(previous->next->value==array)
			return previous;
			
		previous=previous->next;
	}
	
	return NULL;
}

int main()
{
	int i,j,k,h;
	//node *ppp;
		int search[4];
	
	fourk=fopen("IPv4_400k.txt","r");
	if(check_open_file(fourk)==0)
		return 0;
	for(i=0;i<256;i++)
		{
		group1[i]=newNode();	
		tail1[i]=group1[i];
		}
	
	for(i=0;i<4096;i++)
		{
		group2[i]=newNode();	
		tail2[i]=group2[i];
		
		group3[i]=newNode();
		tail3[i]=group3[i];
		}
	
	build_table(fourk);
	
	searchk=fopen("IPv4_search.txt","r");
	if(check_open_file(searchk)==0)
	{	
		return 0;
	}
	
	fourk=fopen("IPv4_400k.txt","r");
	if(check_open_file(fourk)==0)
		return 0;
	for(i=0;i<256;i++)
		{
		group1[i]=newNode();	
		tail1[i]=group1[i];
		}
	
	for(i=0;i<4096;i++)
		{
		group2[i]=newNode();	
		tail2[i]=group2[i];
		
		group3[i]=newNode();
		tail3[i]=group3[i];
		}
	
	build_table(fourk);

	searchk=fopen("IPv4_search.txt","r");
	if(check_open_file(searchk)==0)
	{	
		return 0;
	}


	resultk=fopen("result.txt","w");
	if(check_open_file(resultk)==0)
	{
		return 0;
	}

	FILE *print_search;
	print_search=fopen("Search.txt","w");
	if(check_open_file(print_search)==0)
	{
		return 0;
	}
unsigned long long int begin1,end1,result1=0;
while(!feof(searchk))
{
    begin1=rdtsc();
	fscanf(searchk,"%d%*[.]%d%*[.]%d%*[.]%d%*[^\n]",&search[0],&search[1],&search[2],&search[3]);
	int i,j,k;
	node *one;
	node *two;
	node *three;
	int bitpattern_of_search[32];
	int bitpattern_of_group[32];
	
	for(i=0;i<8;i++)
		{
			bitpattern_of_search[7-i]=changetobit(search[0],i);
			bitpattern_of_search[15-i]=changetobit(search[1],i);
			bitpattern_of_search[23-i]=changetobit(search[2],i);
			bitpattern_of_search[31-i]=changetobit(search[3],i);
		}
	int flag=0;
	int flag1;
	int flag2;
	int opop3=changetoint(bitpattern_of_search,12);
	int opop2=changetoint(bitpattern_of_search,12);
	int opop1=changetoint(bitpattern_of_search,8);
	three=group3[opop3];
	int search_linklist[5]={0};

	while(three->next!=NULL)		
	{	
		for(k=0;k<8;k++)
		{
			bitpattern_of_group[7-k]=changetobit(three->value[0],k);
			bitpattern_of_group[15-k]=changetobit(three->value[1],k);
			bitpattern_of_group[23-k]=changetobit(three->value[2],k);
			bitpattern_of_group[31-k]=changetobit(three->value[3],k);
		}

		if(match(bitpattern_of_search,bitpattern_of_group,three->value[4])==1)
		{
			if(three->value[4]>search_linklist[4])
			{
				for(i=0;i<5;i++)
				{
					search_linklist[i]=three->value[i];
				}
						
			flag++;
			}

		}

		three=three->next;
	}
	
	if(flag != 0) 
	{
		fprintf(resultk,"%d.%d.%d.%d/%d\n",search_linklist[0], search_linklist[1], search_linklist[2], search_linklist[3], search_linklist[4]);
	}
	flag = 0;

	if(flag==0);
	{
		two=group2[opop2];
		flag1=0;
		while(two->next!=NULL)		
		{
			for(k=0;k<8;k++)
			{
				bitpattern_of_group[7-k]=changetobit(two->value[0],k);
				bitpattern_of_group[15-k]=changetobit(two->value[1],k);
				bitpattern_of_group[23-k]=changetobit(two->value[2],k);
				bitpattern_of_group[31-k]=changetobit(two->value[3],k);
			}

			if(match(bitpattern_of_search,bitpattern_of_group,two->value[4])==1)
			{			
				if(two->value[4]>search_linklist[4])
				{
           			for(i=0;i<5;i++)
					{
						search_linklist[i]=two->value[i];
					}
						
					flag1++;
				}

			}

			two=two->next;
		}
					
	if (flag1 != 0) 
	{
		fprintf(resultk,"%d.%d.%d.%d/%d\n",search_linklist[0], search_linklist[1], search_linklist[2], search_linklist[3], search_linklist[4]);
	}			
	flag1 = 0;
	
	if(flag1==0)
	{
		one=group1[opop1];
		flag2=0;
		while(one->next!=NULL)		
		{
			for(k=0;k<8;k++)
			{
				bitpattern_of_group[7-k]=changetobit(one->value[0],k);
				bitpattern_of_group[15-k]=changetobit(one->value[1],k);
				bitpattern_of_group[23-k]=changetobit(one->value[2],k);
				bitpattern_of_group[31-k]=changetobit(one->value[3],k);
			}
		
			if(match(bitpattern_of_search,bitpattern_of_group,one->value[4])==1)
			{
				if(one->value[4]>search_linklist[4])
			    {
                    for(i=0;i<5;i++)
					{
						search_linklist[i]=two->value[i];
					}
						
					flag2++;
					
				}

			}

			one=one->next;
		}

		if (flag2 != 0) 
		{
			fprintf(resultk,"%d.%d.%d.%d/%d\n",search_linklist[0], search_linklist[1], search_linklist[2], search_linklist[3], search_linklist[4]);
		}		
		flag2 = 0;


//if (one->next==NULL && two->next==NULL && three->next==NULL && flag2 == 0&& flag == 0 && flag1 == 0) fprintf(resultk, "0.0.0.0/0\n");
	}					

	}	
	end1=rdtsc();
	result1=end1-begin1;
	fprintf(print_search,"%d\n",result1);
}


	int insert[5];
	insertk=fopen("IPv4_insert.txt","r");
	if(check_open_file(insertk)==0)
		return 0;
	
	FILE *print_insert;
	print_insert=fopen("Insert.txt","w");
	if(check_open_file(print_insert)==0)
	{
		return 0;
	}
unsigned long long int begin2,end2,result2=0;

	while(!feof(insertk))
	{
		begin2=rdtsc();
		fscanf(insertk,"%d%*[.]%d%*[.]%d%*[.]%d%*[/]%d%*[^\n]",&insert[0],&insert[1],&insert[2],&insert[3],&insert[4]);			
		node *fix=newNode();
		for(i=0;i<5;i++)
		{
			fix->value[i]=insert[i];	
		}
		
		if(insert[4]>=8&&insert[4]<=15)
		{
			fix->next=group1[insert[0]];
			group1[insert[0]]=fix;
		}
		
		if(insert[4]>=16&&insert[4]<=24)
		{
			fix->next=group2[insert[0]];
			group2[insert[0]]=fix; 
		}
		
		if(insert[4]>=25&&insert[4]<=32)
		{
			for(i=0;i<5;i++)
			{
				fix->next=group3[insert[0]]->next;
				group3[insert[0]]=fix;
			}
		}
	end2=rdtsc();
	result2=end2-begin2;
		fprintf(print_insert,"%d\n",result2);
	
	}

		int kill[5];
		node *pre;
		node *target;
		int rich;
		node *pointer1; 
		node *pointer2; 
		node *pointer3;
		int bitpattern_of_delete[32];
	deletek=fopen("IPv4_delete.txt","r");
	if(check_open_file(deletek)==0)
		return 0;
		FILE *print_delete;
	print_delete=fopen("Delete.txt","w");
	if(check_open_file(print_delete)==0)
	{
		return 0;
	}
	unsigned long long int begin3,end3,result3=0;
	while(!feof(deletek))
	{
		begin3=rdtsc();
		fscanf(deletek,"%d%*[.]%d%*[.]%d%*[.]%d%*[/]%d%*[^\n]",&kill[0],&kill[1],&kill[2],&kill[3],&kill[4]);	
		{
			node *fine=newNode();	
			int S = 0, S2 = 0;
			for(i=0;i<5;i++)
			{
				fine->value[i]=kill[i];	
			}
			for(k=0;k<8;k++)
			{
				bitpattern_of_delete[7-k]=changetobit(fine->value[0],k);
				bitpattern_of_delete[15-k]=changetobit(fine->value[1],k);
				bitpattern_of_delete[23-k]=changetobit(fine->value[2],k);
				bitpattern_of_delete[31-k]=changetobit(fine->value[3],k);
			}	
				int opopmi3=changetoint(bitpattern_of_delete,12);
				int opopmi2=changetoint(bitpattern_of_delete,12);
				int opopmi1=changetoint(bitpattern_of_delete,8);
		
			if(kill[4]>=8&&kill[4]<=15)
			{
				node *LOL = group1[opopmi1];
				node *LOL2;
				for ( i = 0; i < 5; i++){
					if (LOL->value[i] != fine->value[i]) S = 1;
				}
				if (S != 1){
						LOL2 = LOL;
						LOL = LOL->next;
						free(LOL2);
				}
				else {
					while(LOL->next != NULL){
						for (int i = 0; i < 5; i++){
							if (LOL->value[i] != fine->value[i]) S2 = 1;
						}
						if (S2 != 1){
							LOL2 = LOL->next;
							LOL->next = LOL->next->next;
							free(LOL2);
						}
						else LOL = LOL->next;
					}
				}
				S = 0;
				S2 = 0;
				
			}
		
		if(kill[4]>=16&&kill[4]<=24)
		{
			node *LOL = group2[opopmi2];
				node *LOL2;
				for (i = 0; i < 5; i++){
					if (LOL->value[i] != fine->value[i]) S = 1;
				}
				if (S != 1){
						LOL2 = LOL;
						LOL = LOL->next;
						free(LOL2);
				}
				else {
					while(LOL->next != NULL){
						for (int i = 0; i < 5; i++){
							if (LOL->value[i] != fine->value[i]) S2 = 1;
						}
						if (S2 != 1){
							LOL2 = LOL->next;
							LOL->next = LOL->next->next;
							free(LOL2);
						}
						else LOL = LOL->next;
					}
				}
				S = 0;
				S2 = 0;
		}
		
		if(kill[4]>=25&&kill[4]<=32)
		{
			node *LOL = group3[opopmi3];
				node *LOL2;
				for (int i = 0; i < 5; i++){
					if (LOL->value[i] != fine->value[i]) S = 1;
				}
				if (S != 1){
						LOL2 = LOL;
						LOL = LOL->next;
						free(LOL2);
				}
				else {
					while(LOL->next != NULL){
						for (int i = 0; i < 5; i++){
							if (LOL->value[i] != fine->value[i]) S2 = 1;
						}
						if (S2 != 1){
							LOL2 = LOL->next;
							LOL->next = LOL->next->next;
							free(LOL2);
						}
						else LOL = LOL->next;
					}
				}
				S = 0;
				S2 = 0;
		}

		}
	end3=rdtsc();
	result3=end3-begin3;
	fprintf(print_delete,"%d\n",result3);
		
	}
	return 0;
}















