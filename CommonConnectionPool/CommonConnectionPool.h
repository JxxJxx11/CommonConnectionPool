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
	//�̰߳�ȫ�ĵ��������ӿ�
	static ConnectionPool* getConnectionPool();
	shared_ptr<Connection> getConnection();
private:
	//���캯��˽�л�
	ConnectionPool();
	//�������ļ��м���������
	bool loadConfigFile();
	//�����ڶ������߳���,ר�Ÿ�������������
	void produceConnectionTask();
	//�����ڶ������߳���,ɨ�賬��maxIdleTimeʱ��Ŀ�������,���ж��ڵ����ӻ���
	void scannerConnectionTask();
	
private:
	string _ip; //Mysql��ip��ַ
	unsigned short _port; //Mysql�Ķ˿ں�
	string _username; //Mysql��¼�û���
	string _password; //Mysql��¼����
	string _dbname; //���Ӷ����ݿ�����
	int _initSize; //���ӳصĳ�ʼ������
	int _maxSize; //���ӳص����������
	int _maxIdleTime; //���ӳص�������ʱ��
	int _connectionTimeout; //���ӳػ�ȡ���ӵĳ�ʱʱ��

	queue<Connection*> _connectionQue; //�洢Mysql���ӵĶ���
	atomic_int _connectionCnt; //��¼������������connection���ӵ�������
	mutex _queueMutex; //ά�����Ӷ��е��̰߳�ȫ������
	condition_variable cv; //������������,�������������̺߳����������̵߳�ͨ��
};