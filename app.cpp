#include <iostream>
#include <ctime>
#include <chrono>
#include <string>


#include "obj.h"
#include "clickhouse/client.h"

using namespace clickhouse;

int main()
{
    init_reader ir;
    ir.read_file("db.config");

    std::string host = ir.get("host");
    std::string user = ir.get("username");
    std::string pass = "";
    std::string output_file = ir.get("output_file");
    std::string db_nm = ir.get("database");
    std::string tb_nm = ir.get("table");

    
    std::cout << "Password for " << user << "('-' for skip): ";
    std::cin >> pass;
    if (pass == "-") pass = "";
    const std::string ft_nm = db_nm + "." + tb_nm;


    /// Initialize client connection.
    // struct ClientOptions options;
    // options.SetHost(HOST);
    // options.SetUser(USER);
    // options.SetPassword(PASS);

    // Adapter adapter(options);
    Adapter adapter(host, user, pass);

    adapter.resetTime("Main");

    adapter.setTableName(ft_nm);

    adapter.createTable();


    adapter.insert(10, 20, "select");
    adapter.insert(10, 20, "select");
    adapter.insert(10, 20, "select");
    adapter.insert(10, 20, "select");
    adapter.insert(10, 20, "select");

    adapter.select();




    adapter.dropTable();

    adapter.getElapsedTime("Main");
    return 0;
}