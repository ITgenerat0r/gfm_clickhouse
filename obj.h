#pragma once

#include <iostream>
#include <ctime>
#include <chrono>
#include <string>
#include <sstream>

#include "clickhouse/client.h"
using namespace clickhouse;


using time_type = std::chrono::time_point<std::chrono::system_clock>;





class Adapter {
public:
	// explicit Adapter(const std::string &host, const std::string &user, const std::string &pass): host_(host), user_(user), pass_(pass);

	Adapter(const std::string &host, const std::string &user, const std::string &pass): host_(host), user_(user), pass_(pass){
		options_.SetHost(host_);
		options_.SetUser(user_);
		options_.SetPassword(pass_);
		client = new Client(options_);
		last_time = std::time(0);
	}

	void setTableName(const std::string &full_table_name);

	void createTable();

	void addColumn(std::string column_name, std::string column_type);

	void deleteColumn(std::string column_name);

	void insert(const int rows, int cols, const std::string& desc, int offset_c);

	void select(const int tab_count, const int limit, const int offset_r, const std::string& desc, int offset_c);

	void dropTable();

	uint64_t GetColumnCount();

	uint64_t GetRowCount();

	void resetTime(const std::string& desc);

	double getElapsedTime(const std::string& desc);

	void addElapsedTime(const std::string& desc);

	double getAbsoluteTime(const std::string& desc);

private:
	std::string table_;
	std::string current_database;
	std::string current_table;
	const std::string host_;
	const std::string user_;
	const std::string pass_;
	struct ClientOptions options_;
	time_t last_time;
	// options.SetHost(host_);
    // options.SetUser(user_);
    // options.SetPassword(pass_);
	Client* client;
	// time_type start;
	// time_type end;
	std::map<std::string, time_type> time_storage;
	std::map<std::string, double> time_inside;

};