#include <iostream>
#include <ctime>
#include <chrono>
#include <iomanip>


#include "obj.h"
#include "config.h"
#include "clickhouse/client.h"

using namespace clickhouse;


int main(int argc, char *argv[])
{
    const std::string version = "v1.1";




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


    

    std::string cm = "";
    std::string kc = "Add";

    while(true){
        std::cout << "Adapter:-> ";
        std::cin >> cm;
        // std::getline(std::cin, cm);
        try {
            if (cm == "exit"){
                break;
            } else if (cm == "xcolumns"){
                std::cout << adapter.GetColumnCount() << " columns.\r\n";
            } else if (cm == "xrows"){
                std::cout << adapter.GetRowCount() << " rows.\n";
            }else if (cm == "rtime"){
                adapter.resetTime(kc);
            } else if (cm == "atime"){
                adapter.addElapsedTime(kc);
            } else if (cm == "gtime"){
                double absres = adapter.getAbsoluteTime(kc);
                std::cout << "Absolute time (" << kc << "): " << absres << std::endl;
            } else if (cm == "dbcreate"){
                adapter.createDatabase();
            } else if (cm == "dbdrop"){
                adapter.dropDatabase();
            } else if (cm == "table"){
                std::string cm2;
                std::cin >> cm2;
                if (cm2 == "create"){
                    adapter.createTable();
                } else if (cm2 == "drop"){
                    adapter.dropTable();
                }
            } else if (cm == "column"){
                std::string cm2;
                std::cin >> cm2;
                if (cm2 == "delete"){
                    std::string col_name;
                    std::cin >> col_name;
                    std::cout << "delete column: " << col_name << std::endl;
                    adapter.deleteColumn(col_name);
                } else if (cm2 == "add"){
                    std::string col_name, col_type;
                    std::cin >> col_name >> col_type;
                    std::cout << "add column: " << col_name << std::endl;
                    adapter.addColumn(col_name, col_type);
                }
            } else if (cm == "execute"){
                std::string cmd = "";
                std::getline(std::cin, cmd);
                std::cout << "cmd: " << cmd << std::endl;
                if (cmd.size() > 0){
                    adapter.Execute(cmd);
                }
            } else if (cm == "help"){
                std::string help = "- exit\n";
                help += "- xcolumns, get count columns\n";
                help += "- xrows, get count rows\n";
                help += "- rtime, reset time\n";
                help += "- atime, add time to sum\n";
                help += "- gtime, show sum time\n";
                help += "- dbcreate\n";
                help += "- dbdrop\n";
                help += "- table\n";
                help += "   - create\n";
                help += "   - drop\n";
                help += "- column\n";
                help += "   - add\n";
                help += "   - delete\n";
                help += " - execute\n";
                help += "- help\n";
                help += "\n Version " + version;
                std::cout << help << std::endl;
            }
        } catch(const std::exception& ex){
            std::cout << ex.what() << std::endl;
        }
    }

    // adapter.dropTable();

    return 0;
}

