#include <iostream>
#include <ctime>
#include <chrono>
#include <string>
#include <fstream>
#include <iomanip>


#include "obj.h"
#include "clickhouse/client.h"

using namespace clickhouse;


int main(int argc, char *argv[])
{
    init_reader ir;
    ir.read_file("db.config");

    std::string host = ir.get("host");
    std::string user = ir.get("username");
    std::string pass = ir.get("pass");
    std::string output_file = ir.get("output_file");
    std::string db_nm = ir.get("database");
    std::string tb_nm = ir.get("table");

    if (host == "") host = "localhost";
    if (user == "") user = "default";
    if (pass == ""){
        std::cout << "Password for " << user << "('-' for skip): ";
        std::cin >> pass;
        if (pass == "-") pass = "";
    }
    if (output_file == "") output_file = "output.txt";
    if (db_nm == "") db_nm = "test";
    if (tb_nm == "") tb_nm = "uso";

    const std::string ft_nm = db_nm + "." + tb_nm;


    Adapter adapter(host, user, pass);


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

