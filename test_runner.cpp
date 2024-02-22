
// #include <stdio.h>
#include <stdlib.h>


int main(){
	std::system("./insert 5 1 1");

	std::system("./insert 50 1000 10");
	std::system("./insert 5 10000 10");
	std::system("./insert 50 100 100");
	std::system("./insert 5 1000 100");


	std::system("./select 50 1000 10");
	std::system("./select 5 10000 10");
	std::system("./select 50 100 100");
	std::system("./select 5 1000 100");

	std::system("./addcolumn 50");

	std::system("./insert 50 1000 10 50");
	std::system("./insert 5 10000 10 50");
	std::system("./insert 50 100 100 50");
	std::system("./insert 5 1000 100 50");


	std::system("./select 50 1000 10 50");
	std::system("./select 5 10000 10 50");
	std::system("./select 50 100 100 50");
	std::system("./select 5 1000 100 50");

}