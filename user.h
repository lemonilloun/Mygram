
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
string delim = ":";
string d = ".txt";

class Users {
private:
    string id;
    string paswwd;
public:

    Users(){
        id = "user";
        paswwd = "user";
    }
    
    string GetId(){
        return id;
    }

    void SetId(string ValueId){
        cin >> ValueId;
        id = ValueId;
    }

    void SetPas(string ValuePas){
        cin >> ValuePas;
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

    bool log_in(){
        string path = id + d;
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
                    if(us_pas == paswwd){
                        cout << "Вход в аккаунт успешно выполнен" << endl;
                        cout << "\n";
                        break;
                                    }   
                                }
                            }
        uzeri.close();
        }
        else{
            uzeri.close();
            ofstream uzero;
            uzero.open("users/"+path);
            //uzer.open("users/"+path, ofstream::app);
            if(!uzero.is_open()){
                cout << "Ошибка создания файла";
                return false;
            }else{
                uzero << paswwd << endl;
                //uzer << "\n"+pas;
                }
            uzero.close();
             // добавление пользователя в лист
         ofstream fr;
        fr.open("user_list.txt", ofstream::app);
        fr << id << "\n";
        fr.close();
        //
            }
    return true;
    }


};


class RegedUsers : public Users { 
private:
    string user1;
    string pas;
    string access;
public:

    RegedUsers(){
        user1 = GetId();
        pas = GetPas();

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