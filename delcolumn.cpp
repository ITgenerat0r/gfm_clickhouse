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



    /// Initialize client connection.
    // struct ClientOptions options;
    // options.SetHost(HOST);
    // options.SetUser(USER);
    // options.SetPassword(PASS);

    // Adapter adapter(options);
    Adapter adapter(host, user, pass);


    adapter.setTableName(ft_nm);

    adapter.createTable();

    int b, c, r;
    if (argc > 1){
        std::stringstream ss;
        ss << argv[1];
        ss >> c;
    } else {
        std::cout << "How many columns? ";
        std::cin >> c;
    }
    // if (argc > 2){
    //     std::stringstream ss;
    //     ss << argv[2];
    //     ss >> r;
    // } else {
    //     std::cout << "How many rows? ";
    //     std::cin >> r;
    // }
    // if (argc > 3){
    //     std::stringstream ss;
    //     ss << argv[3];
    //     ss >> b;
    // } else {
    //     std::cout << "How many blocks? ";
    //     std::cin >> b;
    // }
    // std::cout << "Columns: " << c << std::endl;
    // std::cout << "Rows: " << r << std::endl;
    // std::cout << "Blocks: " << b << std::endl;

    std::string kc = "Delete";
    int x = adapter.GetColumnCount();

    for(int ic=0; ic<c; ic++){
        adapter.resetTime(kc);
        adapter.deleteColumn("f"+std::to_string(x-ic-1));
        adapter.addElapsedTime(kc);
    }

    std::cout << "RESULT: " << adapter.GetColumnCount();
    // adapter.GetColumnCount();


    // double res = adapter.getElapsedTime(kc);
    double absres = adapter.getAbsoluteTime(kc);
    
    std::ofstream of(output_file, std::ios_base::app);
    of << "delete" << std::setw(8) << c << "c|" << std::setw(8) << "-|" << std::setw(8) << "-|" << std::setw(15) << absres << "s|" << std::endl;
    of.close();




    // adapter.dropTable();

    return 0;
}

