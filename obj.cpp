
#include "obj.h"


void Adapter::resetTime(){
	start = std::chrono::system_clock::now();

	std::time_t t = std::time(0);   // get time now
    std::tm* now = std::localtime(&t);
    std::cout << "Started at " << (now->tm_year + 1900) << '-' 
         << (now->tm_mon + 1) << '-'
         <<  now->tm_mday << " "
         << now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec << std::endl;
}

void Adapter::getElapsedTime(){
	end = std::chrono::system_clock::now();
 
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
 
    std::cout << "finished computation at " << std::ctime(&end_time)
              << "elapsed time: " << elapsed_seconds.count() << "s"
              << std::endl;
}