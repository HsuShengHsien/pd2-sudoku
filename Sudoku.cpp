#include "Sudoku.h"

int arr[81];
int index_arr=0;

Sudoku::Sudoku()
{
	for(int i=0; i<sudokuSize; i++)
	{	
		map[i]=0;
	}
}

bool Sudoku::checkUnity(int arr[])
{
	int arr_unity[9];

	for(int i=0; i<9; i++)
		arr_unity[i]=0;
	for(int i=0; i<9; i++)
	    if(arr[i]!=0)
		    ++arr_unity[arr[i]-1];
	for(int i=0; i<9; i++)
		if(arr_unity[i]>1)
			return false;
	return true;
}
 
bool Sudoku::isCorrect()
{
    bool check_result;
	int check_arr[9];
	int location;
	for(int i=0; i<sudokuSize; i+=9) //check rows
	{
		for(int j=0; j<9; j++)
			check_arr[j]=map[i+j];
		check_result = checkUnity(check_arr);
		if(check_result==false)
			return false;
	}
	for(int i=0; i<9; i++) //check collumns
	{
		for(int j =0; j<9; j++)
			check_arr[j]=map[i+j*9];
		check_result = checkUnity(check_arr);
		if(check_result==false)
			return false;
	}
    for(int i=0; i<9; i++) //check cells
	{
		for(int j=0; j<9; j++)
		{
			location = 27*(i/3)+3*(i%3)+9*(j/3)+(j%3);
			check_arr[j] = map[location];
		}
	    check_result=checkUnity(check_arr);
		if(check_result==false)
			return false;
	}
	return true;
}

int Sudoku::getNextZeroIndex(int index)
{
	do{
		index++;

	}while(index<sudokuSize && map[index]>0 );
	return(index);
} 

void Sudoku::printOut()
{
	for(int i=0; i<sudokuSize; i++)
		cout<<map[i]<<((i+1)%9==0?'\n':' ');
}

void Sudoku::giveQuestion()
{
	int const question[sudokuSize]={1,0,0,2,0,0,3,0,0,0,5,0,0,7,0,0,2,0,0,0,0,0,0,4,0,0,8,3,0,0,0,0,0,6,0,0,0,8,0,0,0,0,0,1,0,0,0,4,0,0,0,0,0,9,8,0,0,1,0,0,0,0,0,0,2,0,0,5,0,0,7,0,0,0,9,0,0,3,0,0,4};
	for(int i=0; i<sudokuSize; i++)
		cout<<question[i]<<((i+1)%9==0?'\n':' ');
}
void Sudoku::readInstr()
{
	string str;
	cin>>str;
	for(int i=0; i<sudokuSize; i++)
		map[i]=str[i]-'0';

}
void Sudoku::readIn()
{
	for(int i=0; i<sudokuSize; i++)
		cin>>map[i];
}

void Sudoku::solve()
{   
    if(isCorrect()==false)
	{
		cout<<"0"<<endl;
		return;
	}
   	int zero=0;
    
	for(int i=0; i<sudokuSize; i++)
	{
		if(map[i]==0)
			++zero;
	}
	//cout<<zero<<endl;
	
	if(zero==81||zero>64) 
	{
		cout<<"2"<<endl;
        return;
	}
    if(zero==0)
	{
		cout<<"1"<<endl;
		printOut();
	}

	else{
        			
       int num=backtrace(); 
       //cout<<num<<endl;
       if(num==0) cout<<"0"<<endl;
	   if(num==1)
	   {
		   cout<<"1"<<endl;
		   for(int i=0; i<sudokuSize; i++)
			   cout<<ans[i]<<((i+1)%9==0?'\n':' ');
	   }
       if(num==2) cout<<"2"<<endl;	   
	    
	}    
}

int Sudoku::backtrace()
{
	int sum=0;
	int index=getNextZeroIndex(-1);
	do{
		map[index]++;
		if(map[index]> 9)
		{
			map[index]=0;
			index= pop();
		}
		else{
			if(isCorrect()== true )
			{ 
				push(index);
				index = getNextZeroIndex(index);
				if(index==sudokuSize)
				{
					for(int i=0; i<sudokuSize;i++)
						ans[i]=map[i];
				    sum++;
					index=pop();
				}
			}
		}
	}while(index>=0 && (index< sudokuSize) && sum<2);
	return sum;
}
	
int Sudoku::push(int index)
{
	arr[index_arr++]=index;

}

int Sudoku::pop()
{
	if(index_arr<=0)
		return -1;
	else return(arr[--index_arr]);
}

void Sudoku::changeNum(int a, int b)
{
	if(a==b) return;
    for(int i=0; i<sudokuSize; i++)
	{   
		if(map[i]==a) {
			map[i]=b;
			continue;
		}
		if(map[i]==b) map[i]=a;
	    
	}
}

void Sudoku::changeRow(int a, int b)
{
    if(a==b) return;
	int temp;

    for(int i=0;i<27; i++)	
	{
		temp=map[i+a*27];
		map[i+a*27]=map[i+b*27];
		map[i+b*27]=temp;
	}
}	

void Sudoku::changeCol(int a, int b)
{   
	if(a==b) return;
	int temp;

    for(int i=0; i<=2; i++)
	{
		for(int j=0; j<9; j++)
		{    
			temp=map[i+a*3+j*9];
		    map[i+a*3+j*9]=map[i+b*3+j*9];
			map[i+b*3+j*9]=temp;
		}
	}
}

void Sudoku::rotate(int n)
{   
    int k=n%4;
	if(n==0||k==0) return; 
    
    int temp[sudokuSize];

	int times=1;
	while(times<=k)
	{
		for(int i=0; i<sudokuSize; i++) temp[i]=map[i];
	
	    for(int i=0; i<9; i++)
	        for(int j=8; j>=0; j--)
			    map[j+i*9]=temp[72-9*j+i];
		times++;
	}
}

void Sudoku::flip(int n)
{
	int temp[sudokuSize];
    for(int i=0; i<sudokuSize; i++)
	    temp[i]=map[i];
	
	if(n==0)
	{
		for(int i=0; i<9; i++)
		{
		    map[i]=map[i+72];
		    map[i+9]=map[i+63];
		    map[i+18]=map[i+54];
			map[i+27]=map[i+45];
		}
		for(int i=0; i<9; i++)
		{
			map[i+72]=temp[i];
			map[i+63]=temp[i+9];
		    map[i+54]=temp[i+18];
			map[i+45]=temp[i+27];	
	    } 
	}
    if(n==1)
	{
	    for(int i=0; i<9; i++)
		{
			map[i*9+8]=map[i*9];
			map[i*9+7]=map[i*9+1];
			map[i*9+6]=map[i*9+2];
			map[i*9+5]=map[i*9+3];
		}
		for(int i=0; i<9; i++)
		{
		    map[i*9]=temp[i*9+8];
			map[i*9+1]=temp[i*9+7];
		    map[i*9+2]=temp[i*9+6];
			map[i*9+3]=temp[i*9+5];
	   	}

	}
}

void Sudoku::change()
{
	srand(time(NULL));
	changeNum(rand()%9+1, rand()%9+1);
	changeRow(rand()%3, rand()%3);
	changeCol(rand()%3, rand()%3);
	rotate(rand()%101);
	flip(rand()%2);
		
}

void Sudoku::transform()
{
	change();
	printOut();
}
