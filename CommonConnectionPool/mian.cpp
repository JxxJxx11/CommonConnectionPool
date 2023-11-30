#include <iostream>
#include "Connection.h"
#include "CommonConnectionPool.h"

using namespace std;


int main()
{
    //Connection conn;
    //char sql[1024] = { 0 };
    //sprintf(sql, "insert into user(name, age, sex) values('%s', %d, '%s')", "zhangsan", 20, "male");
    //conn.connect("127.0.0.1", 3306, "root", "H9MvYSqY3JmAC4aj", "chat");
    //conn.update(sql);
    
    clock_t begin = clock();
    ConnectionPool* cp = ConnectionPool::getConnectionPool();
    for (int i = 0; i < 10; ++i) {
        shared_ptr<Connection> sp = cp->getConnection();
        char sql[1024] = { 0 };
        sprintf(sql, "insert into user(name, age, sex) values('%s', %d, '%s')", "zhangsan", 20, "male");
        sp->update(sql);
    }
    clock_t end = clock();
    cout << (end - begin) << "ms" << endl;

    return 0;
}
