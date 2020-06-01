#include "Header.h"


void registration()
{

    User user;
    cout << "Create your login" << endl;
    cin >> user.login;
    cout << "Create your password" << endl;
    cin >> user.password;
    cout << "Select your status:\n1.Admin\n2.User" << endl;
    int select; //selection
    cin >> select;
    User r;



    FILE* f = fopen("basa.bin", "rb");
    if (f == NULL)
    {
        user.id = 1;
        if (select == 1) user.status = Status::ADMIN;
        else user.status = Status::USER;
        f = fopen("basa.bin", "wb");
        fwrite(&user, sizeof(User), 1, f);

    }
    else
    {
        f = fopen("basa.bin", "rb");
        bool newlogin = true;
        while (!feof(f))
        {
            fread(&r, sizeof(User), 1, f);
            if (feof(f)) break;
            if (!strcmp(r.login, user.login))
            {
                cout << "This login is already used" << endl;
                newlogin = false;
            }
        }
        if (newlogin == true)
        {
            fseek(f, (-1) * (long)sizeof(int), SEEK_END);
            fread(&r.id, sizeof(int), 1, f);
            user.id=r.id+1;
            if (select == 1) user.status = Status::ADMIN;
            else user.status = Status::USER;
            f = fopen("basa.bin", "ab");
            fwrite(&user, sizeof(User), 1, f);
        }
    }
    fclose(f);

}

void admintransport()
{
    Transport b;
    cout << "Add the transport code" << endl;
    cin >> b.code;
    cout << "Add the transport type" << endl;
    cin >> b.type;
    FILE* t = fopen("transport.bin", "rb");
    if (t == NULL)
    {
        t = fopen("transport.bin", "wb");
        fwrite(&b, sizeof(Transport), 1, t);
    }
    else
    {
        t = fopen("transport.bin", "ab");
        fwrite(&b, sizeof(Transport), 1, t);
    }
    fclose(t);
}

void adminstation()
{
    Station s;
    cout << "Add the station code" << endl;
    cin >> s.code;
    cout << "Add the station name" << endl;
    cin >> s.name;
    FILE* c = fopen("station.bin", "rb");
    if (c == NULL)
    {
        c = fopen("station.bin", "wb");
        fwrite(&s, sizeof(Station), 1, c);
    }
    else
    {
        c = fopen("station.bin", "ab");
        fwrite(&s, sizeof(Station), 1, c);
    }
    fclose(c);
}

void adminactions()
{

    cout << "What would you like to do?" << endl;
    cout << "1.Add transport" << endl;
    cout << "2.Add station " << endl;
    int choose;
    cin >> choose;
    if (choose == 1)
    {
        admintransport();
    }
    if (choose == 2)
    {
        adminstation();
    }
}

void useractions()
{
    char trans[15] = {};
    cout << "Enter the transport: <type>_<number>" << endl;
    cin >> trans;
    Transport b;
    Station s;
    bool isTransportFind = false;
    FILE* t = fopen("transport.bin", "rb");
    while (!feof(t))
    {
        fread(&b, sizeof(Transport), 1, t);
        if (feof(t)) break;
        if (!strcmp(b.type, trans))
        {
            isTransportFind = true;
            FILE* c = fopen("station.bin", "rb");
            while (!feof(c))
            {
                fread(&s, sizeof(Station), 1, c);
                if (feof(c)) break;
                if (b.code == s.code)
                {
                    cout << b.type << " is on the station " << s.name << endl;
                    break;
                }
            }
            break;
            fclose(c);
        }
    }
    if (isTransportFind == false)
        cout << "Transport wasn't found" << endl;
    fclose(t);
}

void enter()
{
    User r;
    cout << "Press 1 to sign in\nPress 2 to sign up" << endl;
    int a;
    cin >> a;
    if (a == 1)
    {
        cout << "Enter your login" << endl;
        char log[20] = {};
        cin >> log;
        cout << "Enter your password" << endl;
        char pin[12] = {};
        cin >> pin;



        FILE* f = fopen("basa.bin", "rb");
        if (f == NULL)
        {
            cout << "This login is absent" << endl;
        }
        else
        {
            f = fopen("basa.bin", "rb");
            //int k = 0, l = 0, m = 0;
            bool IsLoginFind = false, IsPasswordCorrect = false;
            while (!feof(f))
            {
                fread(&r, sizeof(User), 1, f);
                if (feof(f)) break;
                if (!strcmp(r.login, log))
                {
                    //k++;
                    IsLoginFind = true;
                    if (!strcmp(r.password, pin))
                    {
                        IsPasswordCorrect = true;
                        //l++;
                        switch (r.status)
                        {
                        case Status::ADMIN:
                        {
                            cout << "Welcome, admin" << endl;
                            adminactions();
                        }
                        break;
                        case Status::USER:
                        {
                            cout << "Welcome,user" << endl;
                            useractions();
                        }
                        break;

                        }
                    }
                }
            }
            fclose(f);
            if (!IsLoginFind)
            {
                cout << "This login is absent" << endl;
            }
            else if (!IsPasswordCorrect)
            {
                cout << "The password is wrong" << endl;
            }
        }
    }
    else registration();
}
