#include "socket.hh"
#include "util.hh"

#include <cstdlib>
#include <iostream>

using namespace std;

void get_URL(const string &host, const string &path) {
    // Your code here.
    //创建TCP套接字
    TCPSocket sock1;
    //通过解析主机名和服务名来构造web页面地址
    const Address adr(host,"http");
    //连接web页面地址
    sock1.connect(adr);
    //写这三个命令,这里特别注意第四命令就是一个换行符
    sock1.write("GET "+path+" HTTP/1.1\r\nHost: "+host+"\r\nConnection: close\r\n\r\n");
    //提示说了套接字到达“EOF”（文件结尾）仅调用一次读取是不够的，所以采用while循环
    do
    {
        auto recvd=sock1.read();
        cout<<recvd;
    } while (!sock1.eof());
    sock1.close();
    
    // You will need to connect to the "http" service on
    // the computer whose name is in the "host" string,
    // then request the URL path given in the "path" string.

    // Then you'll need to print out everything the server sends back,
    // (not just one call to read() -- everything) until you reach
    // the "eof" (end of file).

    cerr << "Function called: get_URL(" << host << ", " << path << ").\n";
    cerr << "Warning: get_URL() has not been implemented yet.\n";
}

int main(int argc, char *argv[]) {
    try {
        if (argc <= 0) {
            abort();  // For sticklers: don't try to access argv[0] if argc <= 0.
        }

        // The program takes two command-line arguments: the hostname and "path" part of the URL.
        // Print the usage message unless there are these two arguments (plus the program name
        // itself, so arg count = 3 in total).
        if (argc != 3) {
            cerr << "Usage: " << argv[0] << " HOST PATH\n";
            cerr << "\tExample: " << argv[0] << " stanford.edu /class/cs144\n";
            return EXIT_FAILURE;
        }

        // Get the command-line arguments.
        const string host = argv[1];
        const string path = argv[2];

        // Call the student-written function.
        get_URL(host, path);
    } catch (const exception &e) {
        cerr << e.what() << "\n";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
