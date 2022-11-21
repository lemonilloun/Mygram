#include <iostream>
#include <fstream>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
using namespace std;
int doin;
bool run = true, aut, act = true;
string delim = ":";
string d = ".txt";

struct sockaddr_in local;
int s;
int sl;
char rc;
bool isExit = false;
int bufsize = 1024;



void send_com(char* bufer){
        
}


class Users {
private:
    string id;
    string paswwd;
    char buf[1024];
public:


    string GetId(){
        return id;
    }

    void SetId(string ValueId){
        id = ValueId;
    }

    void SetPas(string ValuePas){
        paswwd = ValuePas;
    }

    string GetPas(){
        return paswwd;
    }

    bool check_uzers(string id){
        string path = "user_list.txt";
        string str;
        size_t pos = 0;
        string us_n, token;
        ifstream cu;
        cu.open(path);
        if(cu.is_open()){
            while (!cu.eof())
            {
            getline(cu, str);
            pos = str.find(delim);
            us_n = str.substr(0, pos);
            if(us_n == id){
                return 1;
                }
            }
    }else{
        cout << "smthng wrong" << endl;
    }
    cu.close();
    return 0;
    }

    bool log_in(string user_id, string user_pas, string des){
        string path = user_id + d;
        size_t pos = 0;
        string us_n, us_pas, token;
        ifstream uzeri;
        uzeri.open("users/"+path);
        cout << "\n";
        if(uzeri.is_open()){
            string str;
            while(!uzeri.eof()){
                getline(uzeri, str);
                pos = str.find(delim);
                us_n = str.substr(0, str.find(pos));
                if(us_n == id){
                    pos = pos + delim.length();
                    us_pas = str.substr(pos,-1);
                    if(us_pas == user_pas){
                        cout << "Вход в аккаунт успешно выполнен" << endl;
                        cout << "\n";
                        break;
                                    }   
                                }
                            }
        uzeri.close();
        }
        else if (des == "0")
        {
            return false;
        }
        
        else{
            uzeri.close();
            ofstream fr;
            fr.open("user_list.txt", ofstream::app);
            fr << id + delim + paswwd << "\n";
            fr.close();
            for(int i=0; i < 1024; i++){
                buf[i] = ' ';
            }
            string mes = "1 " +  user_id + " " + user_pas + " *";
            for(int i=0; i < mes.length(); i++){
                buf[i] = mes[i];
            }

            send(sl, buf, bufsize, 0);
            }
    return true;
    }

    ~Users(){}
};

class RegedUsers: public Users { 
private:
    string user1;
    string pas;
    string access;
public:

    RegedUsers(string aded_id, string aded_ps){
        user1 = aded_id;
        pas = aded_ps;

    }

    int do_panel(){
        int a;
        cout << "Выберете действие:" << endl;
        cout << "1. - Друзья\n2. - Профиль\n3. - Просмотр сообщений\n4. - Написать сообщение\n5. - Выйти" << endl; cin >> a;
        return a;
    }

    void add_friend(){
    // выбор пользователя
    cout << "-------------------------------------------------------" << endl;
    ifstream list;
    string str;
    string user2;
    list.open("user_list.txt");
    cout << "\nСписок пользователей" << endl;
    while(!list.eof())
    {
        getline(list, str);
        cout << str << endl;
    }
    list.close();
    bool ret = true;
    while(ret){
        cout << "Добавить в друзья - "; cin >> user2; 
        if(user1 != user2 and check_uzers(user2)){
        // добавление пользователя в *user_friends.txt
        string path = user1 + "_fr_list.txt";
        ofstream us2;
        us2.open("users/friends/" + path, ofstream::app);
        us2 << user2 << endl;
        us2.close();
        ret = false;
        }else{
        cout << "Подумай" << endl;
        }
    }

    }

    void view_friend_list(){
    string path = "users/friends/" + user1 + "_fr_list.txt";
    string str;
    ifstream fls;
    cout << "\n";
    fls.open(path);
    if(fls.is_open()){
        while (!fls.eof())
    {
        getline(fls, str);
        cout << str << endl;
    }
    }
    else{
        cout << "У вас нет друзей :(" << endl;
    }
    cout << "\n";
    
    fls.close();
    cout << "\n";
}

    void write(){
    // выбор пользователя
    ifstream list;
    string str;
    string user2;
    size_t pos = 0;
    list.open("user_list.txt");
    cout << "\nСписок пользователей" << endl;
    while(!list.eof())
    {
        getline(list, str);
        pos = str.find(delim);
        cout << str.substr(0,pos) << endl;
        pos = 0;
    }
    list.close();
    
    bool sev = true;
    while(sev){
    cout << "Написать: "; cin >> user2; cin.ignore();
    if(user1 != user2 and check_uzers(user2)){
        string line;
        cout << user1+":"; getline(cin, line);

    // запись в свой файл
        string path = "users/messages/" + user1 + "To" + user2 + ".txt";
        ifstream wrmt;
        wrmt.open(path);
        if(wrmt.is_open()){
            wrmt.close();
            ofstream wrmf;
            wrmf.open(path, ofstream::app);
            wrmf << user1+": " + line << "\n";
            wrmf.close();
        }else{
            wrmt.close();
            path = "users/messages/" + user2 + "To" + user1 + ".txt";
            ofstream wrmf;
            wrmf.open(path, ofstream::app);
            wrmf << user1+": " + line << "\n";
            wrmf.close();
        }
        sev = false;
    }
    else{
        cout << "Подумай" << endl;

    }
    }
    cout << "-------------------------------------------------------" << endl;
}

    void read(){
    cout << "-------------------------------------------------------" << endl;
    ifstream list;
    string str;
    string user2;
    size_t pos = 0;
    list.open("user_list.txt");
    cout << "\nСписок пользователей" << endl;
    while(!list.eof())
    {
        getline(list, str);
        pos = str.find(delim);
        cout << str.substr(0,pos) << endl;
        pos = 0;
    }
    list.close();
    str = "";
    cout << "Открыть переписку с "; cin >> user2; cin.ignore();
    cout << "\n";
    ifstream mesg;
    string path = "users/messages/" + user1 + "To" + user2 + ".txt";
    mesg.open(path);
    if(mesg.is_open()){
        while (!mesg.eof())
        {
            getline(mesg, str);
            cout << str << endl;
        }
        mesg.close();
    }
    else{
        mesg.close();
        path = "users/messages/" + user2 + "To" + user1 + ".txt";
        ifstream messg;
        messg.open(path);
        if(messg.is_open()){
            while(!messg.eof()){
                getline(messg,str);
                cout << str << endl;
            }
            messg.close();
        }else{
            cout << "Вы не общаетесь(" << endl;
        }
        
    }
   
    cout << "\n";
cout << "-------------------------------------------------------" << endl;
}

    void view_profile(){
    cout << "Посмотреть своий пофиль - me\nПосмотреть профиль друзей - friends" << endl; string d; cin >> d; 
    cout << "\n";
    if (d == "me"){
        ifstream profile1;
        string path = "users/" + user1 + ".txt";
        string str;
        profile1.open(path);
        cout << "-------------------------------------------------------" << endl;
        while(!profile1.eof()){
                getline(profile1, str);
                if(str != pas){
                    cout << str << endl;
                }       
        }
        cout << "-------------------------------------------------------" << endl;
        profile1.close();
        cout << "\n";

        int r;
        cout << "Редактировать информацию о себе?\n1. - Да\n2. - Назад" << endl; cin >> r; cin.ignore();
        cout << "\n";
        if(r == 1){
            string run = "1";
            ofstream pr;
            pr.open(path);
            while (run == "1")
            {
                string tt; cout << "Введите текст: "; getline(cin, tt); pr << "status: " + tt << endl;
                cout <<"Ввести что-то еще?\nда- 1\nнет - 0" << endl; cin >> run; 
                if(run != "0" or run != "0"){
                    cout <<"Ошибка ввода: " << endl;
                    run = "0";
                }
            }
            pr.close();
            
        }

    }
    else if(d == "friends"){
        string user2;
        string path = "users/friends/" + user1 + "_fr_list.txt";
        string str, us_n;
        size_t pos = 0;
        ifstream fls;
        cout << "\n";
        fls.open(path);
        if(fls.is_open()){
            while (!fls.eof())
            {
            getline(fls, str);
            pos = str.find(delim);
            us_n = str.substr(0, pos);
            cout << us_n << endl;
            pos = 0;
            }
        }
        else{
            cout <<"У вас нет друзей :(" << endl;
            }
        cout << "\n";
    
        fls.close();
        cout << "\n";
        str = "";

        bool ag = true;
        while (ag)
        {
        cout << "Чей профиль посмотреть? :"; cin >> user2; cin.ignore();
        if(check_uzers(user2)){
            cout << "\n";
            string pathf = "users/" + user2 + ".txt";
            ifstream pf;
            pf.open(pathf);
            cout << "-------------------------------------------------------" << endl;
            int k = 0;
            while(!pf.eof()){
                getline(pf, str);
                cout << str << endl;
            }
                pf.close();
                cout << "-------------------------------------------------------" << endl;
                cout << "\n";
                string dr;
                cout << "Посмотреть другой профиль?\n1. - да\n2. - нет" << endl; cin >> dr; cin.ignore();
                if(dr == "1"){
                    ag = true;
                }else{
                    ag = 0;
                }
            
        }else{
            cout << "новокек не найден" << endl;}
    }
    }else{
        cout << "Неправильно выбрано действие(" << endl;
    }
}    

};

int main(){

    // запуск сервера

    local.sin_family = AF_INET;
    local.sin_port = htons(10050);
    local.sin_addr.s_addr = htonl(INADDR_ANY);
    s = socket(AF_INET, SOCK_STREAM, 0);

    if(s<0){
        perror("ошибка вызова socket");
        exit(1);
    }

    cout << "Creating server" << endl;

    rc = ::bind(s, (struct sockaddr *)&local, sizeof(local));
    if(rc<0){
        perror("ошибка вызова bind");
        exit(1);
    }

    rc = listen(s, 5);
    if(rc){
        perror("ошибка вызова listen");
        exit(1);
    }

    sl = accept(s, NULL, NULL);
    if(sl<0){
        perror("ошибка вызова accept");
        exit(1);
    }

    cout << "Hi server" << endl;
    
    //

    Users user;
    string ad_id;
    string ad_pas;
    setlocale(LC_ALL, "rus");
    bool log = true;
    while(log)
    {
    cout << "Login: "; cin >> ad_id; user.SetId(ad_id);
    cout << "Password: "; cin >> ad_pas; user.SetPas(ad_pas);
    aut = user.log_in(ad_id, ad_pas, "0");
    string sogl;
    while(run){
    if(!aut){
        cout << "Вы хотите повторно авторизоваться или создать нового пользователя\n1. - да; 2. - нет" << endl; cin >> sogl;
        if(sogl == "1"){
            cout << "Login: "; cin >> ad_id; 
            cout << "Password: "; cin >> ad_pas;
            aut = user.log_in(ad_id, ad_pas, "1");
        }
        else{
            log = 0;
            run = 0;
            break;}
    }
    else{
        RegedUsers r_user(ad_id, ad_pas);
        // основной функционал соц-сети
        while(act){
            doin = r_user.do_panel();
            bool wht;
            switch (doin)
            {
            case 1: // Друзья
                cout << "1. - Посмотреть список друзей\n2. - Добавить в друзя\n"; int t; cin >> t; cin.ignore();
                switch (t)
                {
                case 1:
                    r_user.view_friend_list();
                    break;
                case 2:
                    r_user.add_friend();
                        break;
                default:
                    break;
                }
                break;

            case 2:
                r_user.view_profile();
                break;
            case 3: // просмотр сообщений
                r_user.read();
                break;
            
            case 4: // написать сообщение
                r_user.write();
                break;

            case 5:
                act = 0;
                break;

            default:
                act = 0;
                log = 0;
                break;
        }
        }
        run = 0;
        }
    
    }
    }
    
    return 0;
}