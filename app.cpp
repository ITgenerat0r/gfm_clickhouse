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
    auto start = std::chrono::system_clock::now();



    Adapter adapter(HOST, USER, PASS);
    

    // std::cout << "Started at " << start << std::endl;
    std::time_t t = std::time(0);   // get time now
    std::tm* now = std::localtime(&t);
    std::cout << "Started at " << (now->tm_year + 1900) << '-' 
         << (now->tm_mon + 1) << '-'
         <<  now->tm_mday << " "
         << now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec << std::endl;


    /// Initialize client connection.
    struct ClientOptions options;
    options.SetHost(HOST);
    options.SetUser(USER);
    options.SetPassword(PASS);

    Client client(options);
    // client = client(options);
    // Client client(options);

    /// Create a table.
    std::cout << "Create table if exists " << ft_nm << std::endl;
    client.Execute("CREATE TABLE IF NOT EXISTS "+ft_nm+" (dt DateTime, f1 Float64, f2 Float64, f3 Float64, f4 Float64, f5 Float64, f6 Float64, f7 Float64, f8 Float64, f9 Float64, f10 Float64, f11 Float64, f12 Float64, f13 Float64, f14 Float64, f15 Float64, f16 Float64, f17 Float64, f18 Float64, f19 Float64, f20 Float64, f21 Float64, f22 Float64, f23 Float64, f24 Float64, f25 Float64, f26 Float64, f27 Float64, f28 Float64, f29 Float64, f30 Float64, f31 Float64, f32 Float64, f33 Float64, f34 Float64, f35 Float64, f36 Float64, f37 Float64, f38 Float64, f39 Float64, f40 Float64, f41 Float64, f42 Float64, f43 Float64, f44 Float64, f45 Float64, f46 Float64, f47 Float64, f48 Float64, f49 Float64, f50 Float64) ENGINE = Memory");

    /// Insert some values.
    {
        std::cout << "Insert..." << std::endl;

        Block block;

        auto fl = std::make_shared<ColumnFloat64>();
        for (int i = 0; i<10; ++i){
            fl->Append(i);
        }

        // fl->Append(7);

        auto date = std::make_shared<ColumnDateTime>();
        const int64_t c = 123456;
        for (int i = 0; i<10; ++i){
            time_t now = std::time(0);
            date->Append(now);
        }
        // try {
        //     // time_t time(time_t *time);
        //     date->Append(now);
        // } catch (const Exception& e){
        //     std::cout << "Err 1" << std::endl;
        // }
        // try {
        //     date->Append(now);
        // } catch (const Exception& e){
        //     std::cout << "Err 2" << std::endl;
        // }
        // date->Append("2023-01-01 23:24:11");
        // date->Append("2023-07-07 19:16:00");


        block.AppendColumn("dt", date);
        block.AppendColumn("f1"  , fl);
        block.AppendColumn("f2"  , fl);

        client.Insert(ft_nm, block);
    }

    /// Select values inserted in the previous step.
    // std::cout << "Select..." << std::endl;
    // client.Select("SELECT * FROM " + ft_nm, [] (const Block& block)
    //     {
    //         for (size_t i = 0; i < block.GetRowCount(); ++i) {
    //             std::cout << block[0]->As<ColumnDateTime>()->At(i) << " ";
    //             for(int i = 0; i < 2; ++i){
    //                 std::cout << block[i]->As<ColumnFloat64>()->At(i) << " ";
    //             }
    //             std::cout << std::endl;
    //         }
    //     }
    // );

    /// Delete table.
    // client.Execute("DROP TABLE " + ft_nm);




    auto end = std::chrono::system_clock::now();
 
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
 
    std::cout << "finished computation at " << std::ctime(&end_time)
              << "elapsed time: " << elapsed_seconds.count() << "s"
              << std::endl;

    return 0;
}