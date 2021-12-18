# include <iostream>
using namespace std;

int main()
{
	int guess=0;
	int counter=1;
	while(counter<2)
	{
		cout<<"Please enter any no. other than 5:";
		cin>>guess;
		if(guess==5)
		{
			cout<<"hey i asked you not to enter 5";
			exit(EXIT_FAILURE);
		}
		counter++;
	}
	cout<<"wow you have a lot of patience";
return 0;
}

