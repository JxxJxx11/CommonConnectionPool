#pragma once
#include <string>
#include <ctime>
#include "mysql.h"

using namespace std;

class Connection
{
public:
	//��ʼ�����ݿ�����
	Connection();
	//�ͷ����ݿ�������Դ
	~Connection();
	//�������ݿ�
	bool connect(string ip, unsigned short port,string user, string password, string daname);
	//���²��� insert  delete  upgrate
	bool update(string sql);
	//��ѯ���� select
	MYSQL_RES* query(string sql);
	//ˢ��һ�����ӵ���ʼ����ʱ���
	void refreshAliveTime() { _alivetime = clock(); }
	//���ش��ʱ��
	clock_t getAliveTime() const{ return clock() - _alivetime; }

private:
	MYSQL* _conn;
	clock_t _alivetime;
};

