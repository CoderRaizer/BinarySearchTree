#include <iostream>


using namespace std;

bool KiemTraSoNguyenTo(int x)
{
	if(x < 2)
	{
		return false;
	}
	
	if(x == 2)
	{
		return true;
	}
	
	else
	{
		if(x%2 == 0)
		{
			return false;
		}
		
		else
		{
			for(int i = 2; i < x; i++)
			{
				if(x%i == 0)
				return false;
			}
		}
	}
	
	return true;
}
