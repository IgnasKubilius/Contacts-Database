#include "Contact.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <cstring>
#include <sstream>
#include <algorithm>
#define NOTSET "notSet"
using namespace std;
//********************************INTRODUCTION**********************************
void setIntroduction()
{
    cout << ("--------------------------------------------------------") << endl;
    cout << ("Hello. You have uploaded database application for managing data.\n") << endl;
    cout << ("--------------------------------------------------------") << endl;
    cout << ("Choose DATA which you want to fill up. Type the number you have chosen.") << endl;
    cout << ("-----------------------MENIU----------------------------") << endl;
    cout << (" 1 - Enter data.") << endl;
    cout << (" 2 - Edit last data.") << endl;
    cout << (" 3 - View all the data.") << endl;
    cout << (" 4 - Delete data.") << endl;
    cout << (" 5 - Sort") << endl;
    cout << (" 6 - Filter data.") << endl;
    cout << (" 0 - Quit") << endl;
    cout << ("--------------------------------------------------------") << endl;
}
//********************************DO_OPTION*************************************
void doOption ()
{
    //----------VARIABLES---------
    int option = 0;
    bool quit = false;
    vector<Contact*>ContactVectorDataBase;
    ofstream dataFileOf;
    ifstream dataFileIf;
    Contact* data = new Contact;
    char type;
    //----------------------------
    loadFromTextFile(ContactVectorDataBase);
    while(quit == false)
    {
        cout << ("Enter your number: ");
        cin >> option;
        switch (option)
        {
        case 1 :
        {
            data->setData();
            cout << "You can choose your type: J - Juridical, I - Individual"<< endl;
            cout << "Set your type: ";
            cin >> type;
            validateName(data->getName(), data);
            validateSurname(data->getSurname(), data);
            validatePhoneNumber(data->getPhoneNumber(), data);
            validateEmail(data->getEmail(),data);
            if(type == 'J')
                ContactVectorDataBase.push_back(new Juridical(data->getName(),data->getSurname(),data->getPhoneNumber(),data->getEmail()));
            else if (type == 'I')
                ContactVectorDataBase.push_back(new Individual(data->getName(),data->getSurname(),data->getPhoneNumber(),data->getEmail()));
            else cout << "No type. Try again." << endl;
            break;
        }
        case 2 :
        {
            data -> editData();
            ContactVectorDataBase.pop_back();
            ContactVectorDataBase.push_back(new Contact(data->getName(),data->getSurname(),data->getPhoneNumber(),data->getEmail()));
            break;
        }
        case 3 :
        {
            for(size_t i = 0; i<ContactVectorDataBase.size(); i++)
                ContactVectorDataBase[i]->printData();
            break;
        }
        case 4 :
        {
            data->deleteData(ContactVectorDataBase);
            break;
        }
        case 5 :
        {
            data -> sortData(ContactVectorDataBase);
            break;
        }
        case 6 :
        {
            data -> filterData(ContactVectorDataBase);
            break;
        }
        case 0 :
        {
            quit = true;
            printf("Exiting... ");
            printToTextFile(ContactVectorDataBase);
            //----------------------------------DEALLOCATING MEMORY--------------------------------
            ContactVectorDataBase.erase(ContactVectorDataBase.begin(),ContactVectorDataBase.end());
            for(size_t i = ContactVectorDataBase.size(); i>0; i--)
                delete ContactVectorDataBase[i];
            delete data;
            //-------------------------------------------------------------------------------------
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
//*****************************NAME_VALIDATION***********************************
void validateName(string Input, Contact* dataX)
{
    //--------------------VARIABLES--------------------
    int nameCounter = 0;
    int spaceCounter = 0;
    size_t stringSize = Input.size();
    //-------------------------------------------------
    if (stringSize <= 20)
    {
        for (int i = 0; i < stringSize; ++i)
        {
            if (isalpha(Input[i]) != 0)
                nameCounter++;
            if (Input[i] == ' ')
                spaceCounter++;
        }
        if (nameCounter ==  stringSize - spaceCounter)
        {
            if (firstLetterIsDigit(Input) != 1)
            {
                cout << "Your name's first letter must be digital." << endl;
                dataX->setName();
            }
            else  cout << "Your name was set succesfully." << endl;
        }
        else
        {
            cout << "Your name can not contain numbers." << endl;
            dataX->setName();
        }
    }
    else
    {
        cout << "Your name can not be longer than 20 letters" << endl;
        dataX->setName();
    }

}
//**************************SURNAME_VALIDATION***********************************
void validateSurname(string Input, Contact* dataX)
{
    //--------------------VARIABLES--------------------
    int surnameCounter = 0;
    int spaceCounter = 0;
    size_t stringSize = Input.size();
    //-------------------------------------------------
    if (stringSize <= 25)
    {
        for (int i = 0; i < stringSize; ++i)
        {
            if (isalpha(Input[i]) != 0)
                surnameCounter++;
            if (Input[i] == ' ')
                spaceCounter++;
        }
        if (surnameCounter ==  stringSize - spaceCounter)
        {
            if (firstLetterIsDigit(Input) != 1)
            {
                cout << "Your surname's first letter must be digital." << endl;
                dataX->setSurname();
            }
            else cout << "Your surname was set succesfully." << endl;
        }
        else
        {
            cout << "Your surname can not contain numbers." << endl;
            dataX->setSurname();
        }
    }
    else
    {
        cout << "Your surname can not be longer than 25 letters." << endl;
        dataX->setSurname();
    }
}
//*****************************PHONENUMBER_VALIDATION*********************************
void validatePhoneNumber(string Input, Contact* dataX)
{
    //--------------------VARIABLES--------------------
    int digitsCounter = 0;
    size_t stringSize = Input.size();
    //-------------------------------------------------
    if (stringSize == 12)
    {
        if (Input[0] == '+' && Input[1] == '3' && Input[2] == '7' && Input[3] == '0' && Input[4] == '6')
        {
            for (int i = 0; i < stringSize; ++i)
                if (isdigit(Input[i]) != 0)
                    ++digitsCounter;
            if (digitsCounter == 11)
                cout << "Your number was set succesfully." << endl;
            else
            {
                cout << "Your number must contain only digits. " << endl;
                dataX->setPhoneNumber();
            }
        }
        else
        {
            cout << "The number must be +3706xxxxxxx format." << endl;
            dataX->setPhoneNumber();
        }
    }
    else
    {
        cout << "The number must be 12 digits long." << endl;
        dataX->setPhoneNumber();
    }
}
//*******************************EMAIL_VALIDATION*************************************
void validateEmail(string Input, Contact* dataX)
{
    //--------------------VARIABLES--------------------
    int etFounder = 0;
    int dotFounder = 0;
    int numberWhereEtWasFound = 0;
    int numberWhereDotWasFound = 0;
    size_t stringSize = Input.size();
    //-------------------------------------------------
    for (int i = 0; i < stringSize; i++)
        if (Input[i] == '@')
        {
            etFounder++;
            numberWhereEtWasFound = i;
        }
    if (etFounder == 1)
    {
        for (int i = numberWhereEtWasFound; i<stringSize; i++)
            if (Input[i] == '.')
            {
                dotFounder ++;
                numberWhereDotWasFound = i;
            }
        if (dotFounder == 1 && etFounder == 1 && numberWhereDotWasFound != stringSize-1)
            printf("Your email was set succesfully.");
        else
        {
            cout << "Email format must be soemthing@something.something" << endl;
            dataX->setEmail();
        }
    }
    else
    {
        cout << "Email  must be something@something.something format." << endl;
        dataX->setEmail();
    }
}
//*********************************FIRST_LETTER_IS_DIGIT***********************************
int firstLetterIsDigit(string nameString)
{
    //--------------------VARIABLES--------------------
    int spaceCounter = 0;
    int digitalLettersCounter = 0;
    int firstLetterIsDigitalAfterSpace = 0;
    size_t stringSize = nameString.size();
    //-------------------------------------------------
    if(isupper(nameString[0]))
    {
        for(int i=0; i < stringSize; i++)
        {
            if (nameString[i] == ' ')
            {
                spaceCounter++;
                if(isupper(nameString[i+1]))
                    firstLetterIsDigitalAfterSpace++;
                else return 0;
            }
        }
        for(int i=0; i < stringSize; i++)
        {
            if(isupper(nameString[i]))
                digitalLettersCounter++;
        }
        if((digitalLettersCounter == spaceCounter+1)&&(firstLetterIsDigitalAfterSpace == spaceCounter))
        {
            return 1;
        }
        else return 0;
    }
    else return 0;
}
//********************************PRINT_TO_TEXT_FILE*****************************
void printToTextFile(vector<Contact*>&Vector)
{
    ofstream out("ContactsDataBase.txt", ifstream::out);
    if(!out)
        cerr << "Unable to open file" << endl;
    else
    {
        for(size_t i = 0; i<Vector.size(); i++)
        {
            Juridical* juridicalVector = dynamic_cast<Juridical*>(Vector[i]);
            if(juridicalVector != nullptr)
                out <<Vector[i]->getName()<<";"<<Vector[i]->getSurname()<<";"<<Vector[i]->getPhoneNumber()<<";"<<Vector[i]->getEmail()<<";" <<juridicalVector->getJuridical()<<endl;
        }
        for(size_t i = 0; i<Vector.size(); i++)
        {
            Individual* individualVector = dynamic_cast<Individual*>(Vector[i]);
            if(individualVector != nullptr)
                out <<Vector[i]->getName()<<";"<<Vector[i]->getSurname()<<";"<<Vector[i]->getPhoneNumber()<<";"<<Vector[i]->getEmail()<<";" <<individualVector->getIndividual()<<endl;
        }
    }
    out.close();
}
//*******************************READ_FROM_TEXT_FILE*****************************
void loadFromTextFile(vector<Contact*>&Vector)
{
    ifstream in("ContactsDataBase.txt", ifstream::in);
    if(!in)
        cerr << "Unable to open file" << endl;
    else
    {
        string line;
        while(getline(in, line))
        {
            istringstream lineStream(line);
            string nameInputString;
            getline(lineStream, nameInputString, ';' );
            string surnameInputString;
            getline(lineStream, surnameInputString, ';' );
            string phoneNumberInputString;
            getline(lineStream, phoneNumberInputString, ';' );
            string emailInputString;
            getline(lineStream, emailInputString, ';' );
            string typeInputString;
            getline(lineStream, typeInputString, ';');
            if(typeInputString == "Juridical")
                Vector.push_back(new Juridical(nameInputString,surnameInputString,phoneNumberInputString,emailInputString,typeInputString));
            if(typeInputString == "Individual")
                Vector.push_back(new Individual(nameInputString,surnameInputString,phoneNumberInputString,emailInputString,typeInputString));
        }
    }
    in.close();
}
//**********************************SORT_FUNCTIONS*******************************
bool sortByName(const Contact *lhs, const Contact *rhs)
{
    const string lhs_nameInput = lhs->getName();
    const string rhs_nameInput = rhs->getName();
    return lhs_nameInput < rhs_nameInput;
}
bool sortBySurname(const Contact *lhs, const Contact *rhs)
{
    const string lhs_surnameInput = lhs->getSurname();
    const string rhs_surnameInput = rhs->getSurname();
    return lhs_surnameInput < rhs_surnameInput;
}
bool sortByPhoneNumber(const Contact *lhs, const Contact *rhs)
{
    const string lhs_PhoneNumberInput = lhs->getPhoneNumber();
    const string rhs_PhoneNumberInput = rhs->getPhoneNumber();
    return lhs_PhoneNumberInput < rhs_PhoneNumberInput;
}
bool sortByEmail(const Contact *lhs, const Contact *rhs)
{
    const string lhs_EmailInput = lhs->getEmail();
    const string rhs_EmailInput = rhs->getEmail();
    return lhs_EmailInput < rhs_EmailInput;
}
