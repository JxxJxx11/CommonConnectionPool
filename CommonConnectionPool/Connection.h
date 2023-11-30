#pragma once
#include <string>
#include <ctime>
#include "mysql.h"

using namespace std;

class Connection
{
public:
	//初始化数据库连接
	Connection();
	//释放数据库连接资源
	~Connection();
	//链接数据库
	bool connect(string ip, unsigned short port,string user, string password, string daname);
	//更新操作 insert  delete  upgrate
	bool update(string sql);
	//查询操作 select
	MYSQL_RES* query(string sql);
	//刷新一下连接的起始空闲时间点
	void refreshAliveTime() { _alivetime = clock(); }
	//返回存活时间
	clock_t getAliveTime() const{ return clock() - _alivetime; }

private:
	MYSQL* _conn;
	clock_t _alivetime;
};

