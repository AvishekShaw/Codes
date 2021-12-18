# include <iostream>
using namespace std

void main()
{
	int guess=0;
	cout<<"Please enter any no. other than 5:";
	cin>>guess;
	if(guess==5)
	{
		cout<<"hey i asked you not to enter 5";
		exit()
	}
}

