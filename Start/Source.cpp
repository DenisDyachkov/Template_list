#include <iostream>
#include "../Template_list/List.h"

using namespace miit::list;

int main() 
{
	List<int> list{ 1,2,3,4 };
	std::cout << list;
	return 0;
}