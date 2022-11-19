#include <iostream>
#include <fstream>
#include <string>
using namespace std;
const int buf_size = 7;
char buf[buf_size];

void do_buffer() {
    string temp = "howera";
    char buf[buf_size];
    strcpy(buf, temp.c_str());
}

int main() {
    setlocale(LC_ALL, "rus");
    do_buffer();
    for(int i = 0; i <= buf_size; i++){
        cout << buf[i] << endl;
    }
    return 0;
}