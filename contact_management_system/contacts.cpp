// Evan Adams
// 4/10/25
// A contact management system that allows you to enter contacts and either remove, search, or display them

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

void add_contact (ofstream &myfile);
void display_contacts (ifstream &myfile);
void find_contact (ifstream &myfile);
void remove_contact (ifstream &myfile);
vector<string> create_vector (ifstream &myfile);

struct info
{
    string name;
    string email;
    string phone;
};

int main()
{
    vector<string> vec = {};

    cout << "What would you like to do? (Enter 1, 2, 3, or 4)" << endl
         << "1) Add new contact" << endl
         << "2) Display all contacts" << endl
         << "3) Find a contact" << endl
         << "4) Remove a contact" << endl;

    int answer;
    cin >> answer;

    if (answer == 1)
    {
        ofstream myfile;

        myfile.open("contacts.txt", ios::app);

        if (myfile.is_open())
        {
            add_contact(myfile);
        }

        myfile.close();
    }

    else if (answer == 2)
    {
        ifstream myfile;

        myfile.open("contacts.txt", ios::in);

        if (myfile.is_open())
        {
            display_contacts(myfile);
        }

        myfile.close();
    }

    else if (answer == 3)
    {
        ifstream myfile;

        myfile.open("contacts.txt", ios::in);

        if (myfile.is_open())
        {
            find_contact(myfile);
        }

        myfile.close(); 
    }

    else if (answer == 4)
    {
        ifstream myfile;

        myfile.open("contacts.txt", ios::in);

        if (myfile.is_open())
        {
            remove_contact(myfile);
        }

        myfile.close(); 
    }

    return 0;
}

void add_contact (ofstream &file)
{
    string line;
    info contact;
    vector<string> file_lines = {};

    cout << "How many contacts do you wish to add?" << endl;

    int cons_to_add;
    cin >> cons_to_add;

    int count;

    while (count < cons_to_add)
    {
        cout << "Contact name: ";
        
        getline(cin >> ws, contact.name);
        file_lines.push_back(contact.name);

        cout << "Email: ";
        
        getline(cin >> ws, contact.email);
        file_lines.push_back(contact.email);

        cout << "Phone: ";
        
        getline(cin >> ws, contact.phone);
        file_lines.push_back(contact.phone);

        count += 1;
    }

    for (string line : file_lines)
    {
        file << line << endl;
    }
}

void display_contacts (ifstream &file)
{
    string line;
    int num = 0;

    while(getline(file, line))
    {
        cout << line << endl;

        num++;

        if (num % 3 == 0)
        {
            cout << "" << endl;
        }
    }
}

void find_contact (ifstream &file)
{
    info contact;
    int index = 0;
    bool in_vector = false;
    vector<string> vec = create_vector(file);

    cout << "Enter name of contact you wish to find: ";
    getline(cin >> ws, contact.name);

    cout << endl;

    for (string info : vec)
    {
        if (info == contact.name)
        {
            cout << "Name: " << contact.name << endl
                 << "Email: " << vec.at(index + 1) << endl
                 << "Phone: " << vec.at(index + 2) << endl;

            in_vector = true;

            break;
        }

        index += 1;
    } 

    if (in_vector == false)
    {
        cout << "Contact not found" << endl;
    }
}

void remove_contact (ifstream &file)
{
    info contact;
    int index = 0;
    vector<string> vec = create_vector(file);

    cout << "Enter name of contact you wish to remove: ";
    getline(cin >> ws, contact.name);

    file.close();

    for (string info : vec)
    {
        if (info == contact.name) 
        {
            vec.erase(vec.begin() + index, vec.begin() + (index + 3));
        }  

        index += 1;
    }

    ofstream outfile("contacts.txt");

    for (const string &line : vec)
    {
        outfile << line << endl;
    }

    outfile.close();

    cout << "Removed " << contact.name << " and updated file." << endl;
}

vector<string> create_vector (ifstream &file)
{
    string line;
    vector<string> file_lines = {};

    while (getline(file, line))
    {
        file_lines.push_back(line);
    }

    return file_lines;
}
