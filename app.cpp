#include <iostream>
#include <ctime>
#include <chrono>
#include <string>


#include "obj.h"
#include "config.h"
#include "clickhouse/client.h"

using namespace clickhouse;

int main()
{
    const std::string db_nm = "test";
    const std::string tb_nm = "uso";
    const std::string ft_nm = db_nm + "." + tb_nm;


    /// Initialize client connection.
    // struct ClientOptions options;
    // options.SetHost(HOST);
    // options.SetUser(USER);
    // options.SetPassword(PASS);

    // Adapter adapter(options);
    Adapter adapter(HOST, USER, PASS);

    adapter.resetTime("Main");

    adapter.setTableName(ft_nm);

    adapter.createTable();


    adapter.insert(10, 20);
    adapter.insert(10, 20);
    adapter.insert(10, 20);
    adapter.insert(10, 20);
    adapter.insert(10, 20);

    adapter.select();




    adapter.dropTable();

    adapter.getElapsedTime("Main");
    return 0;
}