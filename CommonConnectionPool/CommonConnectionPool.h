#pragma once
#include <string>
#include <queue>
#include <mutex>
#include <atomic>
#include <thread>
#include <memory>
#include <functional>
#include "Connection.h"

using namespace std;

class ConnectionPool {
public:
	//线程安全的单例函数接口
	static ConnectionPool* getConnectionPool();
	shared_ptr<Connection> getConnection();
private:
	//构造函数私有化
	ConnectionPool();
	//从配置文件中加载配置项
	bool loadConfigFile();
	//运行在独立的线程中,专门负责生产新连接
	void produceConnectionTask();
	//运行在独立的线程中,扫描超过maxIdleTime时间的空闲连接,进行对于的连接回收
	void scannerConnectionTask();
	
private:
	string _ip; //Mysql的ip地址
	unsigned short _port; //Mysql的端口号
	string _username; //Mysql登录用户名
	string _password; //Mysql登录密码
	string _dbname; //连接而数据库名称
	int _initSize; //连接池的初始连接量
	int _maxSize; //连接池的最大连接量
	int _maxIdleTime; //连接池的最大空闲时间
	int _connectionTimeout; //连接池获取连接的超时时间

	queue<Connection*> _connectionQue; //存储Mysql连接的队列
	atomic_int _connectionCnt; //记录连接所创建的connection连接的总数量
	mutex _queueMutex; //维护连接队列的线程安全互斥锁
	condition_variable cv; //设置条件变量,用于连接生产线程和连接消费线程的通信
};