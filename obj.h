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
	}

	void setTableName(const std::string &full_table_name);

	void createTable();

	void insert(const int rows, int cols);

	void select();

	void dropTable();

	void resetTime(const std::string& desc);

	double getElapsedTime(const std::string& desc);

private:
	std::string table_;
	const std::string host_;
	const std::string user_;
	const std::string pass_;
	struct ClientOptions options_;
	// options.SetHost(host_);
    // options.SetUser(user_);
    // options.SetPassword(pass_);
	Client* client;
	// time_type start;
	// time_type end;
	std::map<std::string, time_type> time_storage;

};