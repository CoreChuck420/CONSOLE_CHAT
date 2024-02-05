// Chat.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "Chat.h"
#include <iostream>

void Chat::Start()
{
    _isOnline = true;
}
shared_ptr<User>Chat::getUserLOgin(const string& userLogin)const
{
    for (auto& user : _userList)
    {
        if (userLogin == user.getUserLogin())
            return make_shared<User>(user);
    }
    return nullptr;
}
shared_ptr<User>Chat::getUserName(const string& userName)const
{
    for (auto& user : _userList)
    {
        if (userName == user.getUserName())
            return make_shared<User>(user);
    }
}
void Chat::logIn()
{
    string login, password;
    char chatItem;

    //do  while
    do
    {
        
        cout << "ЛОГИН: ";
        cin >> login;
        cout << "ПАРОЛЬ: ";
        cin >> password;
        _currentUser = getUserLOgin(login);

        if (_currentUser == nullptr || (password != _currentUser->getUserPassword()))
        {
            _currentUser = nullptr;
            cout << "ОШИБКА! ВВеден неверный логин, повторите попытку." << endl;
            cout << "Выход [0], повторить [любая клавиша]";
            cin >> chatItem;
            if (chatItem == '0')
                break;
        }
    } while (!_currentUser);

}
void Chat::signUp()
{
    
    string name, login, password;
    cout << "ИМЯ: ";
    cin >> name;
    cout << "ЛОГИН: ";
    cin >> login;
    cout << "ПАРОЛЬ: ";
    cin >> password;

    if (login == "all")
    {
        throw UserLoginIsExist();
    }
    if (name == "all")
    {
        throw UserNameIsExist();
    }
    User user = User(login, password, name);
    _userList.push_back(user);
    _currentUser = make_shared<User>(user);

}
void Chat::showLoginMenu()
{
    _currentUser = nullptr;
    char chatItem;
    do
    {
        cout << "ДОБРО ПОЖАЛОВАТЬ! ВЫБЕРИТЕ ОДИН ИЗ ПЕРЕЧИСЛЕННЫХ ПУНКТОВ МЕНЮ" << endl;
        cout << "[1] ВХОД ПО ЛОГИНУ И ПАРОЛЮ" << endl;
        cout << "[2] РЕГИСТРАЦИЯ" << endl;
        cout << "[0] ВЫХОД" << endl;
        cin >> chatItem;
        switch (chatItem)
        {
        case '1':
            logIn();
            break;
        case '2':
            try
            {
                signUp();
            }
            catch (const exception& e)
            {
                cout << e.what() << endl;
            }
            break;
        case '0':
            _isOnline = false;
            break;
        default:
            cout << "1 или 2..." << endl;
            break;
        }
    } while (!_currentUser && _isOnline);
}
void  Chat::showAllUsers() const
{
    for (auto& user : _userList)
    {
        cout << " " << user.getUserLogin() << endl;;

    }

}
void Chat::showUserMenu()
{
    char item;
    cout << "Здравствуйте, " << _currentUser->getUserName()<<"!" << endl;
    while (_currentUser)
    {
        cout << "МЕНЮ ЧАТА: [1] СМОТРЕТЬ ЧАТ  | [2] ОТПРАВИТЬ СООБЩЕНИЕ  | [3] СПИСОК ПОЛЬЗОВАТЕЛЕЙ  | [0] ВЫХОД ";
        cout << endl;
        cout << "---------->";
        cin >> item;
        switch (item)
        {
        case '1':
            viewChat();
            break;
        case '2':
            addMessage();
            break;
        case '3':
            showAllUsers();
            break;
        case '0':
            _currentUser = nullptr;
            break;
        default:
            cout << " Введите один из перечисленных пунктов меню..." << endl;
            break;
        }
    }
}



void Chat::addMessage()
{
    string to, text;
    cout << "КОМУ: (введите имя пользователя или 'all' для отправки ВСЕМ пользователям чата): ";
    cin >> to;
    cout << "ТЕКСТ:  ";
    cin.ignore();
    getline(cin >> to, text);
    if (!(to == "all" || getUserName(to)))
    {
        cout << "ОШИБКА ОТПРАВКИ СООБЩЕНИЯ! ПОЛЬЗОВАТЕЛЬ НЕ НАЙДЕН" << to << endl;
        return;
    }
    if (to == "all")
    {
        _messageList.push_back(Message(_currentUser->getUserLogin(), "all", text));
    }
    else
    {
        _messageList.push_back(Message(_currentUser->getUserLogin(), getUserName(to)->getUserLogin(), text));
    }
}

void Chat::viewChat() const
{
    string from, to;
    cout << "*************ЧАТ*************" << endl;
    for (auto& mess : _messageList)
    {
        if (_currentUser->getUserLogin() == mess.getFromUser() || _currentUser->getUserLogin() == mess.getToUser() || mess.getToUser() == "all")
        {
            from = (_currentUser->getUserLogin() == mess.getFromUser()) ? "me" : getUserLOgin(mess.getFromUser())->getUserName();
        }
        if (mess.getToUser() == "all")
        {
            to = "(all)";
        }
        else
        {
            to = (_currentUser->getUserLogin() == mess.getToUser()) ? "me" : getUserLOgin(mess.getToUser())->getUserName();
        }
        cout << "Сообщение от: " << from << "Кому: " << to << endl;
        cout << "Текст сообщения:       " << mess.getMessageText() << endl;
    }
    cout << "" << endl;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
