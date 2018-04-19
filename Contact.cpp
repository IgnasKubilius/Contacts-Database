#include "Contact.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#define NOTSET "notSet"
using namespace std;
//**********************************CONSTRUCTOR**********************************
Contact::Contact()
{
    nameInput = NOTSET;
    surnameInput = NOTSET;
    phoneNumberInput = NOTSET;
    emailInput = NOTSET;
};
//**********************************CONSTRUCTOR**********************************
Contact::Contact(const std::string& setConstructName=NOTSET, const std::string& setConstructSurname=NOTSET, const std::string& setConstructPhoneNumber=NOTSET, const std::string& setConstructEmail=NOTSET)
{
    nameInput = setConstructName;
    surnameInput = setConstructSurname;
    phoneNumberInput = setConstructPhoneNumber;
    emailInput = setConstructEmail;
}
//***********************************DESTRUCTOR**********************************
Contact::~Contact()
{

};
//************************************SET_NAME***********************************
void Contact::setName()
{
    string input;
    cout << "Enter your name: ";
    cin >> input;
    if (input != NOTSET)
        nameInput = input;
    else cerr << "Invalid data." << endl;
}
//**********************************SET_SURNAME***********************************
void Contact::setSurname()
{
    string input;
    cout << "Enter your surname: ";
    cin >> input;
    if (input != NOTSET)
        surnameInput = input;
    else cerr << "Invalid data." << endl;
}
//********************************SET_PHONENUMBER*********************************
void Contact::setPhoneNumber()
{
    string input;
    cout << "Enter your phone number: ";
    cin >> input;
    if (input != NOTSET)
        phoneNumberInput = input;
    else cerr << "Invalid data." << endl;
}
//************************************SET_EMAIL***********************************
void Contact::setEmail()
{
    string input;
    cout << "Enter your email: ";
    cin >> input;
    if (input != NOTSET)
        emailInput = input;
    else cerr << "Invalid data." << endl;
}
//************************************GET_NAME************************************
string Contact::getName() const
{
    return nameInput;
}
//**********************************GET_SURNAME***********************************
string Contact::getSurname() const
{
    return surnameInput;
}
//********************************GET_PHONENUMBER*********************************
string Contact::getPhoneNumber() const
{
    return phoneNumberInput;
}
//************************************GET_EMAIL***********************************
string Contact::getEmail() const
{
    return emailInput;
}
////*********************************CHANGE_NAME**********************************
void Contact::changeName(string name)
{
    nameInput = name;
}
//*********************************CHANGE_SURNAME*********************************
void Contact::changeSurname(string surname)
{
    surnameInput = surname;
}
//*******************************CHANGE_PHONENUMBER*******************************
void Contact::changePhoneNumber(string phoneNumber)
{
    phoneNumberInput = phoneNumber;
}
//************************************GET_EMAIL***********************************
void Contact::changeEmail(string email)
{
    emailInput = email;
}
//************************************SET_DATA************************************
void Contact::setData()
{
    cout << endl;
    cout << ("--------------------------------------------------------")<<endl;
    setName();
    setSurname();
    setPhoneNumber();
    setEmail();
    cout << ("--------------------------------------------------------")<<endl;
}
//***********************************EDIT_DATA************************************
void Contact::editData()
{
    cout << ("--------------------------------------------------------")<<endl;
    setName();
    setSurname();
    setPhoneNumber();
    setEmail();
}
//**********************************DELETE_DATA***********************************
void Contact::deleteData(vector<Contact*>&Vector)
{
    //----------VARIABLES---------
    int option = 0;
    bool quit = false;
    //----------------------------
    while(quit == false)
    {
        cout << endl;
        cout << ("--------------------------------------------------------") << endl;
        cout << ("Choose DATA which you want to delete. Type the number you have chosen.") << endl;
        cout << ("-----------------------MENIU----------------------------") << endl;
        cout << (" 1 - Delete the contact.") << endl;
        cout << (" 2 - Delete all contacts.") << endl;
        cout << (" 3 - Delete certain contact.") << endl;
        cout << (" 0 - Quit.") << endl;
        cout << ("--------------------------------------------------------") << endl;
        cout << ("Enter your number: ");
        cin >> option;
        switch (option)
        {
        case 1 :
        {
            Vector.pop_back();
            cout << "Data succesfully deleted." << endl;
            break;
        }
        case 2 :
        {
            ofstream dataFile("ContactsDataBase.txt", ofstream::trunc);
            if(dataFile.is_open())
            {
                cerr << "Data was succesfully deleted." << endl;
                dataFile.close();
            }
            else cerr << "Unable to open file.";
            cout << Vector.size() << endl;
            Vector.erase(Vector.begin(),Vector.end());
            for(size_t i = Vector.size(); i>0; i--)
                delete Vector[i];
            changeName(NOTSET);
            changeSurname(NOTSET);
            changePhoneNumber(NOTSET);
            changeEmail(NOTSET);
            break;
        }
        case 3 :
        {
            int number;
            cout << "Enter number's data you want to delete: ";
            cin >> number;
            Vector.erase (Vector.begin()+(number-1));
        }
        case 0 :
        {
            quit = true;
            printf("Exiting... \n");
            break;
        }
        default :
        {
            cout <<"There is no action like this."<<endl;
            break;
        }
        }
    }
    setIntroduction();
}
//**********************************SORT_DATA************************************
void Contact::sortData(vector<Contact*>&Vector)
{
    //----------VARIABLES---------
    int option = 0;
    bool quit = false;
    //----------------------------
    cout << ("--------------------------------------------------------\n") << endl;
    cout << ("Choose DATA which you want to sort by. Type the number you have chosen.\n") << endl;
    cout << ("-----------------------MENIU----------------------------\n") << endl;
    cout << (" 1 - Name") << endl;
    cout << (" 2 - Surname") << endl;
    cout << (" 3 - Phone number") << endl;
    cout << (" 4 - Email") << endl;
    cout << (" 0 - Quit") << endl;
    cout << ("--------------------------------------------------------\n") << endl;
    while(quit == false)
    {
        cout << ("Enter your number: ");
        cin >> option;
        switch (option)
        {
        case 1 :
        {
            sort(Vector.begin(), Vector.end(), sortByName);
            cout << "Data was sorted succesfully." << endl;
            break;
        }
        case 2 :
        {
            sort(Vector.begin(), Vector.end(), sortBySurname);
            cout << "Data was sorted succesfully." << endl;
            break;
        }
        case 3 :
        {

            sort(Vector.begin(), Vector.end(), sortByPhoneNumber);
            cout << "Data was sorted succesfully." << endl;
            break;
        }
        case 4 :
        {

            sort(Vector.begin(), Vector.end(), sortByEmail);
            cout << "Data was sorted succesfully." << endl;
            break;
        }
        case 0 :
        {
            quit = true;
            printf("Exiting... \n");
            break;
        }
        default :
        {
            cout <<"There is no action like this."<<endl;
            break;
        }
        }
    }
}
//********************************FILTER_DATA************************************
void Contact::filterData(vector<Contact*>&Vector)
{
    //----------VARIABLES---------
    int option = 0;
    string customData;
    bool quit = false;
    //----------------------------
    cout << ("--------------------------------------------------------\n") << endl;
    cout << ("Choose DATA which you want to filter by. Type the number you have chosen.\n") << endl;
    cout << ("-----------------------MENIU----------------------------\n") << endl;
    cout << (" 1 - Name") << endl;
    cout << (" 2 - Surname") << endl;
    cout << (" 3 - Phone number") << endl;
    cout << (" 4 - Email") << endl;
    cout << (" 0 - Quit") << endl;
    cout << ("--------------------------------------------------------\n") << endl;
    while(quit == false)
    {
        cout << ("Enter your number: ");
        cin >> option;
        switch (option)
        {
        case 1 :
        {
            cout << "Enter your data to filter by: ";
            cin >> customData;
            for (int i = 0; i < Vector.size(); i++)
                if (customData == Vector[i]->getName())
                {
                    cout << "Name: " << Vector[i]->getName() << endl;
                    cout << "Surname: " << Vector[i]->getSurname() << endl;
                    cout << "Phone number: " << Vector[i]->getPhoneNumber() << endl;
                    cout << "Email: " << Vector[i]->getEmail() << endl;
                }
            break;
        }
        case 2 :
        {
            cout << "Enter your data to filter by: ";
            cin >> customData;
            for (int i = 0; i < Vector.size(); i++)
                if (customData == Vector[i]->getSurname())
                {
                    cout << "Name: " << Vector[i]->getName() << endl;
                    cout << "Surname: " << Vector[i]->getSurname() << endl;
                    cout << "Phone number: " << Vector[i]->getPhoneNumber() << endl;
                    cout << "Email: " << Vector[i]->getEmail() << endl;
                }
            break;
        }
        case 3 :
        {
            cout << "Enter your data to filter by: ";
            cin >> customData;
            for (int i = 0; i < Vector.size(); i++)
                if (customData == Vector[i]->getPhoneNumber())
                {
                    cout << "Name: " << Vector[i]->getName() << endl;
                    cout << "Surname: " << Vector[i]->getSurname() << endl;
                    cout << "Phone number: " << Vector[i]->getPhoneNumber() << endl;
                    cout << "Email: " << Vector[i]->getEmail() << endl;
                }
            break;
        }
        case 4 :
        {
            cout << "Enter your data to filter by: ";
            cin >> customData;
            for (int i = 0; i < Vector.size(); i++)
                if (customData == Vector[i]->getEmail())
                {
                    cout << "Name: " << Vector[i]->getName() << endl;
                    cout << "Surname: " << Vector[i]->getSurname() << endl;
                    cout << "Phone number: " << Vector[i]->getPhoneNumber() << endl;
                    cout << "Email: " << Vector[i]->getEmail() << endl;
                }
            break;
        }
        case 0 :
        {
            quit = true;
            printf("Exiting... \n");
            break;
        }
        default :
        {
            cout <<"There is no action like this."<<endl;
            break;
        }
        }
    }
}
//**********************************PRINT_DATA***********************************
void Contact::printData()
{
    cout << "Name: " << getName() << endl;
    cout << "Surname: " << getSurname() << endl;
    cout << "Phone number: " << getPhoneNumber() << endl;
    cout << "Email: " << getEmail() << endl;
    cout << ("--------------------------------------------------------") << endl;
}
void Contact::printData(Contact data)
{
    cout << "Name: " << data.getName() << endl;
    cout << "Surname: " << data.getSurname() << endl;
    cout << "Phone number: " << data.getPhoneNumber() << endl;
    cout << "Email: " << data.getEmail() << endl;
    cout << ("--------------------------------------------------------") << endl;
}
void Contact::printData(vector<Contact*>&Vector)
{
    for (int i = 0; i < Vector.size(); i++)
    {
        cout << "Name: " << Vector[i]->getName() << endl;
        cout << "Surname: " << Vector[i]->getSurname() << endl;
        cout << "Phone number: " << Vector[i]->getPhoneNumber() << endl;
        cout << "Email: " << Vector[i]->getEmail() << endl;
    }
}
void printPresentClassData(Contact dataInfo)
{
    cout << dataInfo.nameInput << endl;
    cout << dataInfo.surnameInput << endl;
    cout << dataInfo.phoneNumberInput << endl;
    cout << dataInfo.emailInput << endl;
}
//**************************************JURIDICAL**********************************
void Juridical::printData()
{
    cout << "Name: " << getName() << endl;
    cout << "Surname: " << getSurname() << endl;
    cout << "Phone number: " << getPhoneNumber() << endl;
    cout << "Email: " << getEmail() << endl;
    cout << "Type: " << getJuridical() << endl;
};
void printJuridicalOnlyClassData(Contact contactData)
{
    cout << "Name: " << contactData.getName() << endl;
    cout << "Surname: " << contactData.getSurname() << endl;
    cout << "Phone number: " << contactData.getPhoneNumber() << endl;
    cout << "Email: " << contactData.getEmail() << endl;
};
//************************************************
string Juridical::getJuridical() const
{
    return juridicalInput;
}
//************************************************
void Juridical::setType()
{
    juridicalInput = "Juridical";
}
//***************************************INDIVIDUAL*********************************
void Individual::printData()
{
    cout << "Name: " << getName() << endl;
    cout << "Surname: " << getSurname() << endl;
    cout << "Phone number: " << getPhoneNumber() << endl;
    cout << "Email: " << getEmail() << endl;
    cout << "Type: " << getIndividual() << endl;
};
void printIndividualOnlyClassData(Contact contactData)
{
    cout << "Name: " << contactData.getName() << endl;
    cout << "Surname: " << contactData.getSurname() << endl;
    cout << "Phone number: " << contactData.getPhoneNumber() << endl;
    cout << "Email: " << contactData.getEmail() << endl;
};
//************************************************
string Individual::getIndividual() const
{
    return individualInput;
};
//************************************************
void Individual::setType()
{
    individualInput = "Individual";
};
