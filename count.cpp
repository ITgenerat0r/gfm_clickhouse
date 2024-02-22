#include <iostream>
#include <ctime>
#include <chrono>
#include <string>
#include <fstream>
#include <iomanip>


#include "obj.h"
#include "config.h"
#include "clickhouse/client.h"

using namespace clickhouse;


int main(int argc, char *argv[])
{
    const std::string output_file = "output.txt";
    const std::string db_nm = "test";
    const std::string tb_nm = "uso";
    const std::string ft_nm = db_nm + "." + tb_nm;


    Adapter adapter(HOST, USER, PASS);


    adapter.setTableName(ft_nm);

    


    std::string arg = "rc";
    if (argc > 1){
        std::stringstream ss;
        ss << argv[1];
        ss >> arg;
    }

    if (arg == "rows"){
        std::cout << adapter.GetRowCount() << " rows." << std::endl;
    } else if (arg == "columns" || arg == "cols"){
        std::cout << adapter.GetColumnCount() << " columns." << std::endl;
    } else if (arg == "rc"){
        std::cout << adapter.GetRowCount() << " rows." << std::endl;
        std::cout << adapter.GetColumnCount() << " columns." << std::endl;
    }
    

    return 0;
}

