#include<stdio.h>
#include<stdlib.h>

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

void build_table(FILE *file)
{
	int i,j;
	while(!feof(file))
	{
		fscanf(file,"%d%*[.]%d%*[.]%d%*[.]%d%*[/]%d%*[^\n]",&prefix[0],&prefix[1],&prefix[2],&prefix[3],&prefix[4]);
/*		for(i=0;i<5;i++)
		{
		printf("%d.",prefix[i]);
		}
		printf("\n");
*/
		if(prefix[4]>=8&&prefix[4]<=15)
		{
			for(i=0;i<5;i++)
			{
				tail1[prefix[0]]->value[i]=prefix[i];
			//	printf("%d.",tail1[prefix[0]]->value[i]);
			}
		//printf("\n");	
			
			tail1[prefix[0]]->next=newNode(); 
			tail1[prefix[0]]=tail1[prefix[0]]->next;
			
		}
	
		if(prefix[4]>=16&&prefix[4]<=24)
		{
			for(i=0;i<5;i++)
			{
				tail2[prefix[0]]->value[i]=prefix[i];
			//printf("%d.ll",tail2[prefix[0]]->value[i]);
			}
			//printf("\n");
			tail2[prefix[0]]->next=newNode(); 
			tail2[prefix[0]]=tail2[prefix[0]]->next;
				
		}
	
		if(prefix[4]>=25&&prefix[4]<=32)
		{
			for(i=0;i<5;i++)
			{
				tail3[prefix[0]]->value[i]=prefix[i];
			}
			
			tail3[prefix[0]]->next=newNode(); 
			tail3[prefix[0]]=tail3[prefix[0]]->next;
			//count3[prefix[0]]++;
		}
	
	}
//printf("%d.ll",tail2[204]->value[0]);	
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
	
int match(int bit1[],int bit2[],int length)
{
	int i;
	int match=0;
	int matchnumber=0;
	for(i=0;i<length;i++)
		{
			if(bit1[i]==bit2[i])
			{
				match++;
			}
	
		}
	/*			
	for(i=0;i<length;i++)
	{
		matchnumber=matchnumber+match[i];
	}*/
				
	if(match==length)
		return 1;
				
	else
		return 0;		
}

node* Search_match(node *search[],FILE *searchk,node *group1[])
{
	int i,j,k;
	node *search_pt;
	node *search_linklist;
	node *search_linklist_head;
	int bitpattern_of_search[32];
	int bitpattern_of_group[32];
	search_linklist_head=newNode();		
	search_linklist=search_linklist_head;
	for(i=0;i<8;i++)
		{
			bitpattern_of_search[7-i]=changetobit(search[0],i);
			bitpattern_of_search[15-i]=changetobit(search[1],i);
			bitpattern_of_search[23-i]=changetobit(search[2],i);
			bitpattern_of_search[31-i]=changetobit(search[3],i);
		}
			
		for(j=0;j<256;j++)
		{	search_pt=group1[j];
		
			while(search_pt->next!=NULL)
			{
				for(k=0;k<8;k++)
				{
					bitpattern_of_group[7-k]=changetobit(search_pt->value[0],k);
					bitpattern_of_group[15-k]=changetobit(search_pt->value[1],k);
					bitpattern_of_group[23-k]=changetobit(search_pt->value[2],k);
					bitpattern_of_group[31-k]=changetobit(search_pt->value[3],k);
				}
				
				if(match(bitpattern_of_search,bitpattern_of_group,search_pt->value[4])==1)
				{
					for(i=0;i<5;i++)
					{
						search_linklist->value[i]=search_pt->value[i];
					}	
				
					search_linklist->next=newNode();
					search_linklist=search_linklist->next;
					search_pt=search_pt->next;
					
				} 
					
				else
					{
						search_linklist->next=newNode();
						search_linklist=search_linklist->next;
						search_pt=search_pt->next;
					}
		
			}	
		return 	search_linklist_head;
				
		}

	}	







int main()
{
	int i,j,k,h;
	node *ppp;
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

	/*searchk=fopen("IPv4_search.txt","r");
	if(check_open_file(searchk)==0)
	{	
		return 0;
	}*/

	int insert[5];
	insertk=fopen("IPv4_insert.txt","r");
		if(check_open_file(insertk)==0)
			return 0;
	while(!feof(insertk))
	{
		fscanf(insertk,"%d%*[.]%d%*[.]%d%*[.]%d%*[/]%d%*[^\n]",&insert[0],&insert[1],&insert[2],&insert[3],&insert[4]);			
		node *fix=newNode();
		for(i=0;i<5;i++)
		{
		fix->value[i]=insert[i];	
		//printf("%d",fix->value[i]);
		}
		//break;	
			
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
		//printf("\n");
			}
	
	
	}
	
	/*node *print;
print=group2[203];
while(print->next!=NULL)
{
	if(print->value[1]==163)
	{
		for(i=0;i<5;i++)
	{
	printf("%d.",print->value[i]);
	}
	printf("\n");
	}

	print=print->next;	
}
*/
	
	deletek=fopen("IPv4_delete.txt","r");
	if(check_open_file(deletek)==0)
		return 0;
	
	

return 0;
} 
