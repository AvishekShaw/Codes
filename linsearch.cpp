#include <iostream>
#include <vector>

bool linearSearchUnsorted(std::vector<int> &data,int value)
{
int size=data.size();
for(int i=0;i<size;i++)
{
 if (value==data[i])
 {
   return true;
 }
}
return false;
}


int main ()
{
bool istrue;
std::vector<int> a;
for(int i=0;i<10;i++)
a.push_back(i*i);
istrue=linearSearchUnsorted(a,0);
std::cout<<istrue<<std::endl;

return 0;

}
