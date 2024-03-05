
#include "obj.h"



void init_reader::read_file(std::string filename){
  data.clear();

  std::ifstream initf(filename);
  while (initf.is_open())
  {
      std::string key, value;
      initf >> key;
      initf >> value;
      std::cout << key << ":" << value << std::endl;
      if (value == "") break;
      data[key] = value;
  }
}


std::string init_reader::get(std::string key){
  if (data.count(key) == 1){
    return data[key];
  }
  return "";
}



int init_reader::size(){
  return data.size();
}













// Adapter::Adapter(const std::string &host, const std::string &user, const std::string &pass): host_(host), user_(user), pass_(pass){
//   options_.SetHost(host_);
//   options_.SetUser(user_);
//   options_.SetPassword(pass_);
//   client = new Client(options_);
// }


void Adapter::resetTime(const std::string& desc){
	// start = std::chrono::system_clock::now();
  time_storage[desc] = std::chrono::system_clock::now();

	std::time_t t = std::time(0);   // get time now
    std::tm* now = std::localtime(&t);
    std::cout << desc << " started at " << (now->tm_year + 1900) << '-' 
         << (now->tm_mon + 1) << '-'
         <<  now->tm_mday << " "
         << now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec << std::endl;
}

double Adapter::getElapsedTime(const std::string& desc){
	time_type end = std::chrono::system_clock::now();

  if (time_storage.count(desc) != 1) return 0;
  std::chrono::duration<double> elapsed_seconds = end-time_storage.at(desc);
  std::time_t end_time = std::chrono::system_clock::to_time_t(end);

  std::cout << desc << " finished computation at " << std::ctime(&end_time) << desc << " elapsed time: " << elapsed_seconds.count() << "s" << std::endl;
  return elapsed_seconds.count();

}



void Adapter::addElapsedTime(const std::string& desc){
  double res = getElapsedTime(desc);
  if(time_inside.count(desc) == 1){
    time_inside[desc] += res;
  } else {
    time_inside[desc] = res;
  }
}


double Adapter::getAbsoluteTime(const std::string& desc){
  if (time_inside.count(desc) == 1){
    return time_inside[desc];
  }
  return 0;
}


void Adapter::setTableName(const std::string &full_table_name){
  table_ = full_table_name;
  std::stringstream ss(full_table_name);
  std::getline(ss, current_database, '.');
  ss >> current_table;
  std::cout << "USE " << current_database << '.' << current_table << std::endl; 
}

void Adapter::createDatabase(){
  client->Execute("CREATE DATABASE IF NOT EXISTS test ENGINE = Atomic;");
}

void Adapter::dropDatabase(){
  client->Execute("DROP DATABASE test;");
}

void Adapter::createTable(){
  client->Execute("CREATE TABLE IF NOT EXISTS "+table_+" (dt DateTime, f1 Float64, f2 Float64, f3 Float64, f4 Float64, f5 Float64, f6 Float64, f7 Float64, f8 Float64, f9 Float64, f10 Float64, f11 Float64, f12 Float64, f13 Float64, f14 Float64, f15 Float64, f16 Float64, f17 Float64, f18 Float64, f19 Float64, f20 Float64, f21 Float64, f22 Float64, f23 Float64, f24 Float64, f25 Float64, f26 Float64, f27 Float64, f28 Float64, f29 Float64, f30 Float64, f31 Float64, f32 Float64, f33 Float64, f34 Float64, f35 Float64, f36 Float64, f37 Float64, f38 Float64, f39 Float64, f40 Float64, f41 Float64, f42 Float64, f43 Float64, f44 Float64, f45 Float64, f46 Float64, f47 Float64, f48 Float64, f49 Float64, f50 Float64) ENGINE = MergeTree() ORDER BY (dt);");
}



void Adapter::Execute(const std::string& command){
  client->Execute(command);
}


void Adapter::addColumn(std::string column_name, std::string column_type){
  std::string query = "ALTER TABLE "+table_+" ADD COLUMN "+column_name+" "+column_type+";";
  std::cout << "addColumn = " << query << std::endl;
  client->Execute(query);
}

void Adapter::deleteColumn(std::string column_name){
  std::string query = "ALTER TABLE " + table_;
  query +=  " DROP COLUMN " + column_name + ";";
  std::cout << "query: " << query << std::endl;
  client->Execute(query);
}


void Adapter::insert(const int rows, int cols, const std::string& desc, int offset_c){
  // std::cout << "Insert..." << std::endl;

  Block block;

  // auto fid = std::make_shared<ColumnFloat64>();
  auto fl = std::make_shared<ColumnFloat64>();
  auto date = std::make_shared<ColumnDateTime>();
  const int64_t c = 4'987'654'321'987'654'321;
  
  int id = 0;
  for (int i = 0; i<rows; ++i){
      date->Append(last_time++);
      std::tm* now = std::localtime(&last_time-1);
      // std::cout << "added  " << (now->tm_year + 1900) << '-' 
      //    << (now->tm_mon + 1) << '-'
      //    <<  now->tm_mday << " "
      //    << now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec << std::endl;
      // time_t now = std::time(0);
      // date->Append(now);
      // if(now == last_time){
      //   id++;
      // } else {
      //   id = 0;
      // }
      // fid->Append(id);
      fl->Append(c);
  }

  block.AppendColumn("dt", date);
  // block.AppendColumn("f1"  , fid);
  if (cols > 50) cols = 50;
  for (int i = 1; i <= cols; i++){
    std::stringstream ss;
    ss << i + offset_c;
    std::string field = "f"+ss.str();
    block.AppendColumn(field, fl);
  }
  // block.AppendColumn("f2"  , fl);
  resetTime(desc);
  client->Insert(table_, block);
  double res = getElapsedTime(desc);
  if(time_inside.count(desc) == 1){
    time_inside[desc] += res;
  } else {
    time_inside[desc] = res;
  }
}

void Adapter::select(const int tab_count, const int limit, const int offset_r, const std::string& desc, int offset_c){
  // std::cout << "Select..." << std::endl;
    std::string tabs = "*";
    if(tab_count > 1) tabs = "dt";
    for(int it = 1; it <= tab_count; it++){
      tabs += ", f" + std::to_string(it + offset_c);
    }

    std::string querys = "SELECT " + tabs + " FROM " + table_ + " LIMIT " + std::to_string(limit) + " OFFSET " + std::to_string(offset_r * limit);
    resetTime(desc);
    // std::cout << "Query: " << querys << std::endl;
    client->Select(querys, [&] (const Block& block)
        {
          double res = getElapsedTime(desc);
          if(block.GetRowCount()==0 && block.GetColumnCount()==0){
            if(time_inside.count(desc) == 1){
              time_inside[desc] += res;
            } else {
              time_inside[desc] = res;
            }
          }
          // std::cout << "block(" << block.GetRowCount() << ", " << block.GetColumnCount() << ")" << std::endl;
          // std::cout << res << "s" << std::endl; 
          // for (size_t i = 0; i < block.GetRowCount(); ++i) {
          //     std::cout << block[0]->As<ColumnDateTime>()->At(i) << " ";
          //     for(size_t j = 1; j < block.GetColumnCount(); ++j){
          //         std::cout << block[j]->As<ColumnFloat64>()->At(i) << " ";
          //     }
          //     std::cout << std::endl;
          // }
        }
    );
    
}


uint64_t Adapter::GetColumnCount(){
  std::string querys = "SELECT COUNT(*) FROM INFORMATION_SCHEMA.COLUMNS WHERE table_catalog = '"+current_database+"' AND table_name = '"+current_table+"'";

  uint64_t res = 0;
  client->Select(querys, [&](const Block& block)
   {
    // std::cout << std::endl << "GetColumnCount" << std::endl;
    // std::cout << "block(" << block.GetRowCount() << ", " << block.GetColumnCount() << ")" << std::endl;
    try {
      if(block.GetRowCount() > 0 && block.GetColumnCount() > 0){
        for (size_t i = 0; i < block.GetRowCount(); ++i) {
            // std::cout << block[0]->As<ColumnDateTime>()->At(i) << " ";
            for(size_t j = 0; j < block.GetColumnCount(); ++j){
                // std::cout << block[j]->GetType().GetName() << " ";
              // std::cout << block[j]->As<ColumnUInt64>()->At(i) << " ";
              res = block[j]->As<ColumnUInt64>()->At(i);
            }
            // std::cout << std::endl;
        }
      }
    } catch (const std::exception& ex){
      std::cout << "Exception: " << ex.what() << std::endl;
    }
   }
   );
  return res;
}


uint64_t Adapter::GetRowCount(){
  std::string querys = "SELECT COUNT(*) FROM " + table_;

  uint64_t res = 0;
  client->Select(querys, [&](const Block& block)
   {
    // std::cout << std::endl << "GetColumnCount" << std::endl;
    // std::cout << "block(" << block.GetRowCount() << ", " << block.GetColumnCount() << ")" << std::endl;
    try {
      if(block.GetRowCount() > 0 && block.GetColumnCount() > 0){
        for (size_t i = 0; i < block.GetRowCount(); ++i) {
            // std::cout << block[0]->As<ColumnDateTime>()->At(i) << " ";
            for(size_t j = 0; j < block.GetColumnCount(); ++j){
                // std::cout << block[j]->GetType().GetName() << " ";
              // std::cout << block[j]->As<ColumnUInt64>()->At(i) << " ";
              res = block[j]->As<ColumnUInt64>()->At(i);
            }
            // std::cout << std::endl;
        }
      }
    } catch (const std::exception& ex){
      std::cout << "Exception: " << ex.what() << std::endl;
    }
   }
   );
  return res;
}

void Adapter::dropTable(){
  client->Execute("DROP TABLE " + table_);
}
