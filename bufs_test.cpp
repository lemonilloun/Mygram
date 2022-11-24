#include <iostream>
#include <string>
using namespace std;

const int bufsize = 1024;
char buf[bufsize];
string delim = " ";

int main (){
    setlocale(LC_ALL, "rus");
    string mes = "2 hello you fuck your dog";
    int size = 4;
    string recvd;
    string comm;
    string inform[size];
    
    // обновление буффера
    for(int i=0; i < 1022; i++){
        buf[i] = '*';
    }
     // запись строки в буффер
    for(int i=0; i < mes.length(); i++){
            buf[i] = mes[i];
    }

    int run = int(buf[0]);
    cout << run << endl;

    // запись из буффера в строку и разбиение строки на команду и информацию
    for(int i=0; i<bufsize; i++){
        if(buf[i] != '*'){
            recvd += buf[i];
        }else{
            break;
        }
    }

    size_t pos = 0; //текущая позиция делиметра в строке
    for(int i = 0; i < size; i++){
        if(i == (size - 1)){
            inform[i] = recvd;
            cout << inform[i] << endl;
        }else{
        pos = recvd.find(delim);
        inform[i] = recvd.substr(0, pos);
        cout << inform[i] << endl;
        pos += delim.length();
        recvd = recvd.substr(pos, -1);

        }
        
    }

    cout << "вроде все выполнилось нормально" << endl;
    return 0;
}
