/**********
Student Number: F74045018
Name: Cayon Liow Keei Yann
Way of Compiling: gcc -o hw6_2 hw6_2.c
Way of Executing: ./hw6_2
Function of the Program:A program designed to convert between float or double and bit pattern by applying the method of union.
Updated Date: 2015.12.20
**********/
#include <stdio.h>
#include<limits.h>
typedef union Float_to_Bits	//the application of bit pattern and union
{
    struct {         
        unsigned int  mantissa  : 23;
        unsigned int  exponment : 8;
        unsigned int  sign : 1;
    };
    float s;
  
}FtB;
 
 void Double_display_Bits(unsigned long long value)	//the function of changing DOUBLE to 64-BITS PATTERN
{
	int c;
	unsigned long long displaymask = 0x8000000000000000;
	int C_B= CHAR_BIT*sizeof(unsigned long long);
	printf("The bit pattern of Double=\n");
	 
	for(c=0;c<C_B;c++)
	{
		putchar(value&displaymask?'1':'0');	//AND case
		value<<=1;	//shifting
	}

	putchar('\n');
} 

void Bits_display_Float(int b[])	//the function of changing 32-BITS PATTERN to FLOAT 
	{
		int i,e;
		int t=0;
		float two=1;			
		int Exponent=0;
		float Value;
		float Mantissa=0.0;
		int power1=1;
		float power2=0.5;
			
		for(i=8;i>=1;i--)
		{
			Exponent=Exponent+(b[i])*power1;
			power1=power1*2;	
		}
		e=Exponent-127;
			
		while(e>=0)
		{
			two=two*2;
			t++;
			if(t==e)break;
		}
		while(e<0)
		{
			two=two*0.5;
			t--;
			if(t==e)break;
		}	
		
		for(i=9;i<=31;i++)
		{
			Mantissa=Mantissa+(b[i])*power2;
			power2=power2*(0.5);
			
		}
			
		Value=(1+Mantissa)*two;
	
		if(b[0]==0)
			Value=Value*1;
		if(b[0]==1)
			Value=Value*-1;
	
		printf("The Standard form of the 32-bits pattern:\n");
		printf("%e\n",Value);
			
	}
		
void Bits_display_Double(int b[])	//the function of changing 64-BITS PATTERN to DOUBLE
		{
			int i;
			int Exponent,e;
			double Value;
			Exponent=0;
			double Mantissa=0.0;
			int power1=1;
			float power2=0.5;
			
			for(i=11;i>=1;i--)
			{
				Exponent=Exponent+(b[i])*power1;
				power1=power1*2;	
			}
			e=Exponent-1023;
			int t=0;
			float two=1.0;
			while(e>=0)
			{
				two=two*2;
				t++;
				if(t==e)break;
			}
			
			while(e<0)
			{
				two=two*0.5;
				t--;
				if(t==e)break;
			}	
		
			for(i=12;i<=63;i++)
			{
				Mantissa=Mantissa+(b[i])*power2;
				power2=power2*(0.5);
			}
			
			Value=(1+Mantissa)*two;
	
			if(b[0]==0)
				Value=Value*1;
			if(b[0]==1)
				Value=Value*-1;
			
			printf("The Standard form of the 64-bits pattern:\n");
			printf("%e\n",Value);
			
		}
 
int main()
{
    int i;
	int y=1;
	int t=0;
	float v;
	int b[23];
	FtB s;
	
    printf("Please input a floating number:\n");
    scanf("%f", &s);
     	
 	printf("The bit pattern of the floating number:\n");
    printf("%d", s.sign);
	
	unsigned ddisplaymask = 1<<7;
	for(i=0;i<8;i++)
	{
		putchar(s.exponment&ddisplaymask?'1':'0');	//AND case
		ddisplaymask>>=1;
	}
	
	unsigned displaymask = 1<<22;
	for(i=0;i<23;i++)
	{
		b[i]=(s.mantissa&displaymask?'1':'0')-48;	//AND case
		displaymask>>=1;	//shifting
		printf("%d",b[i]);
	}
	printf("\n");
	
	
		
		double d;
		char bb[32];
		int BB[32];
		printf("Please input a bit pattern in 32 bits:\n");
		scanf("%s",&bb);	//input with the type of string into the charater array
		
		for(i=31;i>=0;i--)
			BB[i]=(int)bb[i]-48;	//casting
		Bits_display_Float(BB);
			;

		printf("Enter the Double number=\n");
		scanf("%lf",&d);
		unsigned long long h = *(unsigned long long*)&d;	//not casting, the way of putting the contents of the memory of h into d
		Double_display_Bits(h);
	
		char cc[64];
		int CC[64];
		printf("Please input a bit pattern in 64 bits:\n");
		scanf("%s",&cc);	//input with the type of string into the charater array
		
		for(i=63;i>=0;i--)
			CC[i]=(int)cc[i]-48;	//casting
		Bits_display_Double(CC);
	
    return 0;
}
