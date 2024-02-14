#pragma once

#include <iostream>
#include <ctime>
#include <chrono>
#include <string>

#include "clickhouse/client.h"
using namespace clickhouse;





class Adapter : Client {
public:
	Adapter(const string &host, const string &user, const string &pass): host_(host), user_(user), pass_(pass){};

	void setTableName(const string &full_table_name);

	void createTable();

	void insert();

	void select();

	void dropTable();

	void resetTime();

	void getElapsedTime();

private:
	string table_;
	const string host_;
	const string user_;
	const string pass_;
	struct ClientOptions options;
	options.SetHost(host_);
    options.SetUser(user_);
    options.SetPassword(pass_);
	Client client(options);
	auto start;
	auto end;

}