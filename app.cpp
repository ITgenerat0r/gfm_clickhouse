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

    adapter.resetTime("Main");

    adapter.setTableName(ft_nm);

    adapter.createTable();







    adapter.dropTable();

    adapter.getElapsedTime("Main");
    return 0;
}