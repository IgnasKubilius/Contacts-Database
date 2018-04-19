#ifndef CONTACT_H
#define CONTACT_H
#include <iostream>
#include <vector>
#define NOTSET "notSet"
//*******************************************CONTACT_CLASS*****************************************************
class Contact
{
public:
    Contact();
    Contact(const std::string& setConstructName, const std::string& setConstructSurname, const std::string& setConstructPhoneNumber, const std::string& setConstructEmail);
    virtual ~Contact();
    void setName();
    void setSurname();
    void setPhoneNumber();
    void setEmail();
    std::string getName() const;
    std::string getSurname() const;
    std::string getPhoneNumber() const;
    std::string getEmail() const;
    void changeName(std::string name);
    void changeSurname(std::string surname);
    void changePhoneNumber(std::string phoneNumber);
    void changeEmail(std::string email);
    void setData();
    void editData();
    virtual void printData();
    void printData(Contact data);
    void printData(std::vector<Contact*>&Vector);
    void deleteData(std::vector<Contact*>&Vector);
    void sortData(std::vector<Contact*>&Vector);
    void filterData(std::vector<Contact*>&Vector);
    friend void printPresentClassData(Contact dataInfo);
private:
    std::string nameInput;
    std::string surnameInput;
    std::string phoneNumberInput;
    std::string emailInput;
};
//*******************************************JURIDICAL_CLASS*****************************************************
class Juridical : public Contact
{
public:
    Juridical (const std::string& setConstructName, const std::string& setConstructSurname, const std::string& setConstructPhoneNumber,
               const std::string& setConstructEmail, const std::string& setConstructType="Juridical") : Contact(setConstructName, setConstructSurname
        ,setConstructPhoneNumber,setConstructEmail), juridicalInput(setConstructType) { };
    void printData() override;
     friend void printJuridicalOnlyClassData(Contact contactData);
    std::string getJuridical() const;
    void setType();
private:
    Contact contactData;
    std::string juridicalInput;

};
//*******************************************INDIVIDUAL_CLASS*****************************************************
class Individual : public Contact
{
public:
    Individual (const std::string& setConstructName, const std::string& setConstructSurname, const std::string& setConstructPhoneNumber,
                const std::string& setConstructEmail, const std::string& setConstructType="Individual") : Contact(setConstructName, setConstructSurname
        ,setConstructPhoneNumber,setConstructEmail), individualInput(setConstructType) { };
    void printData() override;
    friend void printIndividualOnlyClassData(Contact contactData);
    std::string getIndividual() const;
    void setType();
private:
    Contact contactData;
    std::string individualInput;
};
//***************************FUNCTIONS_OUT_OF_CLASS******************************
void setIntroduction();
void doOption ();
void validateName(std::string Input, Contact* dataX);
void validateSurname(std::string Input, Contact* dataX);
void validatePhoneNumber(std::string Input, Contact* dataX);
void validateEmail(std::string Input, Contact* dataX);
int firstLetterIsDigit(std::string nameString);
void printToTextFile(std::vector<Contact*>&Vector);
void loadFromTextFile(std::vector<Contact*>&Vector);
bool sortByName(const Contact *lhs, const Contact *rhs);
bool sortBySurname(const Contact *lhs, const Contact *rhs);
bool sortByPhoneNumber(const Contact *lhs, const Contact *rhs);
bool sortByEmail(const Contact *lhs, const Contact *rhs);
#endif // CONTACT_H
