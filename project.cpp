// Including Header Files!
#include <iostream>
#include <unistd.h>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>
#include <array>
#include <stdlib.h>
//Including External Library!
#include "xlsxwriter.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/ostreamwrapper.h"
using namespace rapidjson;
using namespace std;
void ClearAd(int id, vector<vector<string> > &obj, vector<string> &ref);
void escape(int);
//Excel Data Handle Class Start Here
class Excel
{
private:
    int index;

public:
    //Class Constructor
    Excel()
    {
        index = -1;
    }
    //Class Method Prototype
    void SetIndex(int);
    int GetIndex();
    int ForBuyerReport();
    int ForSellerReport();
};
void Excel::SetIndex(int i)
{
    index = i;
}
int Excel::GetIndex()
{
    return index;
}
int Excel::ForBuyerReport()
{
    int row = 1;
    int col = 0;
    int id = index;
    ifstream ifs("Userdetail.json");
    IStreamWrapper isw(ifs);
    Document d;
    d.ParseStream(isw);
    string filename = d.GetArray()[id].GetObject()["Personal"].GetObject()["username"].GetString();
    filename = filename + ".xlsx";
    lxw_workbook *workbook = workbook_new(filename.c_str());
    lxw_worksheet *worksheet = workbook_add_worksheet(workbook, NULL);
    lxw_format *format = workbook_add_format(workbook);
    format_set_bold(format);
    worksheet_write_string(worksheet, 0, 0, "Ad Title", format);
    worksheet_write_string(worksheet, 0, 1, "Category", format);
    worksheet_write_string(worksheet, 0, 2, "Date", format);
    worksheet_write_string(worksheet, 0, 3, "Location", format);
    worksheet_write_string(worksheet, 0, 4, "Name", format);
    worksheet_write_string(worksheet, 0, 5, "Price", format);
    int x = d.GetArray()[id].GetObject()["Account"].GetObject()["Purchase"].GetArray().Size();
    for (int i = 0; i < x; i++)
    {
        string title = d.GetArray()[id].GetObject()["Account"].GetObject()["Purchase"].GetArray()[i].GetObject()["Adtitle"].GetString();
        string category = d.GetArray()[id].GetObject()["Account"].GetObject()["Purchase"].GetArray()[i].GetObject()["Category"].GetString();
        string date = d.GetArray()[id].GetObject()["Account"].GetObject()["Purchase"].GetArray()[i].GetObject()["Date"].GetString();
        string Loc = d.GetArray()[id].GetObject()["Account"].GetObject()["Purchase"].GetArray()[i].GetObject()["Location"].GetString();
        string name = d.GetArray()[id].GetObject()["Account"].GetObject()["Purchase"].GetArray()[i].GetObject()["Name"].GetString();
        int price = d.GetArray()[id].GetObject()["Account"].GetObject()["Purchase"].GetArray()[i].GetObject()["Price"].GetInt();
        worksheet_write_string(worksheet, row, 0, title.c_str(), NULL);
        worksheet_write_string(worksheet, row, 1, category.c_str(), NULL);
        worksheet_write_string(worksheet, row, 2, date.c_str(), NULL);
        worksheet_write_string(worksheet, row, 3, Loc.c_str(), NULL);
        worksheet_write_string(worksheet, row, 4, name.c_str(), NULL);
        worksheet_write_number(worksheet, row, 5, price, NULL);
        row++;
    }
    string sum = "=SUM(F2:F" + to_string(row) + ")";
    worksheet_write_string(worksheet, row, 4, "Total", format);
    worksheet_write_formula(worksheet, row, 5, sum.c_str(), format);
    cout << "Report Has Been Generated!" << endl;
    return workbook_close(workbook);
}
int Excel::ForSellerReport()
{
    int row = 1;
    int col = 0;
    int id = index;
    ifstream ifs("Userdetail.json");
    IStreamWrapper isw(ifs);
    Document d;
    d.ParseStream(isw);
    string filename = d.GetArray()[id].GetObject()["Personal"].GetObject()["username"].GetString();
    filename = filename + ".xlsx";
    lxw_workbook *workbook = workbook_new(filename.c_str());
    lxw_worksheet *worksheet = workbook_add_worksheet(workbook, NULL);
    lxw_format *format = workbook_add_format(workbook);
    format_set_bold(format);
    worksheet_write_string(worksheet, 0, 0, "Ad Title", format);
    worksheet_write_string(worksheet, 0, 1, "Date", format);
    worksheet_write_string(worksheet, 0, 2, "Price", format);
    int x = d.GetArray()[id].GetObject()["Account"].GetObject()["History"].GetArray().Size();
    for (int i = 0; i < x; i++)
    {
        string title = d.GetArray()[id].GetObject()["Account"].GetObject()["History"].GetArray()[i].GetObject()["Adtitle"].GetString();
        string date = d.GetArray()[id].GetObject()["Account"].GetObject()["History"].GetArray()[i].GetObject()["Date"].GetString();
        int price = d.GetArray()[id].GetObject()["Account"].GetObject()["History"].GetArray()[i].GetObject()["Price"].GetInt();
        worksheet_write_string(worksheet, row, 0, title.c_str(), NULL);
        worksheet_write_string(worksheet, row, 1, date.c_str(), NULL);
        worksheet_write_number(worksheet, row, 2, price, NULL);
        row++;
    }
    string sum = "=SUM(C2:C" + to_string(row) + ")";
    worksheet_write_string(worksheet, row, 1, "Total", format);
    worksheet_write_formula(worksheet, row, 2, sum.c_str(), format);
    cout << "Report Has Been Generated!" << endl;
    return workbook_close(workbook);
}
//Excel Data Handle Class End Here
//Class Credentials Start Here
class Credentials
{
private:
    string userId;
    int ind;
    bool auth;

public:
    Credentials()
    {
        userId = "";
        ind = -1;
        auth = false;
    }
    //Protype Of Setter Methods
    void SetUserId(string);
    void SetIndex(int);
    void SetAuth(bool);
    //Protype Of Getter Method
    string GetUserId();
    int GetIndex();
    bool GetAuth();
};
//Scope Resoluted Setter Methods
void Credentials::SetUserId(string id)
{
    userId = id;
}
void Credentials::SetIndex(int index)
{
    ind = index;
}
void Credentials::SetAuth(bool val)
{
    auth = val;
}
//Scope Resoluted Getter Methods
string Credentials::GetUserId()
{
    return userId;
}
int Credentials::GetIndex()
{
    return ind;
}
bool Credentials::GetAuth()
{
    return auth;
}
//Class Credentials End Here
class Authentications : public Credentials
{
private:
    int indexes;

protected:
    const char *userAttributes[12] = {"fname", "lname", "username", "phoneNumber", "gender", "email", "city", "state", "country", "joinDate", "password"};
    const char *SellerAccountAttribute[7] = {"type", "Subscription", "TotalAds", "AllowedAd", "ActiveAd", "SoldGood", "Revenue"};
    const char *sellerAttributes[9] = {"productId", "productTitle", "productDescription", "productCategory", "adDate", "adLocation", "adAdress", "productPrice", "adFeature"};
    string Personal[13][2] = {{"Index Is", ""}, {"Id", ""}, {"First Name", ""}, {"Last Name", ""}, {"Username ", ""}, {"Phone Number", ""}, {"Gender", ""}, {"Email", ""}, {"City", ""}, {"State", ""}, {"Country", ""}, {"Joining Date", ""}, {"Password", ""}};
    string Account[7][2] = {{"Type ", ""}, {"Subscription ", ""}, {"TotalAds", ""}, {"Allowed Ads", ""}, {"Active Ads ", ""}, {"Good Solded", ""}, {"Revenue", ""}};
    string AccountBuyer[6][2] = {{"Type", ""}, {"Subscription", ""}, {"Total Bids", ""}, {"Bidded", ""}, {"Won Bids", ""}, {"Loss Bids", ""}};
    string DisplayAd[11] = {"Ad Unique ID : ",
                            "Ad Title : ",
                            "Ad Description : ",
                            "Category : ",
                            "Upload Date : ",
                            "Ad Loction : ",
                            "Ad Address : ",
                            "Ad Price : Rs",
                            "For Auction : ",
                            "Uploaded By : ",
                            "Phone Number : "};

public:
    void Login(string, string);
    int Index();
};
//Scope Resoluted Class Method Defination
void Authentications::Login(string email, string pass)
{
    ifstream ifs("Userdetail.json");
    IStreamWrapper isw(ifs);
    Document d;
    d.ParseStream(isw);
    for (SizeType i = 0; i < d.GetArray().Size(); i++)
    {
        string mail = d.GetArray()[i].GetObject()["Personal"].GetObject()["email"].GetString();
        string password = d.GetArray()[i].GetObject()["Personal"].GetObject()["password"].GetString();
        if (mail == email && password == pass)
        {
            cout << "Login Successfully!" << endl;
            indexes = i;
            SetAuth(true);
            break;
        }
        if (i == d.GetArray().Size() - 1)
        {
            cout << "Invalid Credentials!" << endl;
            break;
            Login(email,pass);
        }
    }
}
int Authentications::Index()
{
    return indexes;
}
class Global
{
private:
    string Serials;
    int index;

protected:
    int Date[3];
    int Time[3];

public:
    Global()
    {
        Serials = "";
        index = -1;
    };
    string SerialGenerator(int);
    void GenrateDate();
    void GenerateTime();
    void FindIndex(string);
    //Class Getter Functions
    string GetDate();
    string GetTime();
    int GetIndex();
};
//Scoper Resolution Classes Setter Functions
string Global::SerialGenerator(int len)
{
    srand(time(0));
    string str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    string newstr;
    int pos;
    while (newstr.size() != len)
    {
        pos = ((rand() % (str.size() - 1)));
        newstr += str.substr(pos, 1);
    }
    Serials = newstr;
    return Serials;
};
void Global::GenrateDate()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    Date[0] = 1 + ltm->tm_mon;
    Date[1] = ltm->tm_mday;
    Date[2] = 1900 + ltm->tm_year;
};
void Global::GenerateTime()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    Time[0] = ltm->tm_hour;
    Time[1] = ltm->tm_min;
    Time[2] = ltm->tm_sec;
};
void Global::FindIndex(string id)
{
    ifstream ifs("Userdetail.json");
    IStreamWrapper isw(ifs);
    Document d;
    d.ParseStream(isw);
    for (int i = 0; i < d.GetArray().Size(); i++)
    {
        string ids = d.GetArray()[i].GetObject()["userId"].GetString();
        if (ids == id)
        {
            index = i;
        }
    }
}
int Global::GetIndex()
{
    return index;
}
string Global::GetDate()
{
    GenrateDate();
    string date;
    for (int i = 0; i < 3; i++)
    {
        if (i < 2)
        {
            if (i == 0)
            {
                if (Date[i] < 10)
                {
                    date += "0" + to_string(Date[i]) + "-";
                }
                else
                {
                    date += to_string(Date[i]) + "-";
                }
            }
            else
            {
                date += to_string(Date[i]) + "-";
            }
        }
        else
        {
            date += to_string(Date[i]);
        }
    }
    return date;
}
string Global::GetTime()
{
    GenerateTime();
    string time;
    for (int i = 0; i < 3; i++)
    {
        if (i != 3)
        {
            time += to_string(Time[i]) + " : ";
        }
        else
        {
            time += to_string(Time[i]);
        }
    }
    return time;
}
//For User Working Classes Are Starting Here
//User Class Starting
class User
{
private:
    string firstName, lastName, userName, passWord, eMail, gender, city, state, country, phoneNumber, joinDate;
    string id;

public:
    User()
    {
        firstName = "";
        lastName = "";
        phoneNumber = "";
        gender = "";
        passWord = "";
        userName = "";
        city = "";
        state = "";
        eMail = "";
        country = "";
        id = "";
        joinDate = "";
    }
    //Encapsulation!
    //Setter Of Class
    void SetFirstName(string);
    void SetLastName(string);
    void SetUserName(string);
    void SetPhoneNumber(string);
    void SetGender(string);
    void SetPassword(string);
    void SetCity(string);
    void SetState(string);
    void SetEmail(string);
    void SetCountry(string);
    void SetId(string);
    void SetJoinDate(string);
    virtual void SetSubscription(string) = 0;
    virtual void SetAccountType(string) = 0;
    //Getter Of Class
    string GetFirstName();
    string GetLastName();
    string GetUserName();
    string GetPhoneNumber();
    string GetGender();
    string GetPassword();
    string GetState();
    string GetCity();
    string GetEmail();
    string GetCountry();
    string GetId();
    string GetJoinDate();
    virtual string GetAccountType() = 0;
    virtual string GetSubscription() = 0;
};

//03205946869
//Scoper Resolution Classes Setter Functions
void User::SetFirstName(string name)
{
    firstName = name;
};
void User::SetLastName(string name)
{
    lastName = name;
};
void User::SetUserName(string name)
{
    userName = name;
};
void User::SetGender(string gen)
{
    gender = gen;
};
void User::SetPassword(string pass)
{
    passWord = pass;
};
void User::SetPhoneNumber(string phone)
{
    phoneNumber = phone;
};
void User::SetCity(string val)
{
    city = val;
};
void User::SetState(string val)
{
    state = val;
};
void User::SetEmail(string mail)
{
    eMail = mail;
};
void User::SetCountry(string val)
{
    country = val;
};
void User::SetId(string val)
{
    id = val;
}
void User::SetJoinDate(string val)
{
    joinDate = val;
};
//Scoper Resolution Classes Getter Functions
string User::GetFirstName()
{
    return firstName;
};
string User::GetLastName()
{
    return lastName;
};
string User::GetUserName()
{
    return userName;
};
string User::GetPassword()
{
    return passWord;
};
string User::GetPhoneNumber()
{
    return phoneNumber;
};
string User::GetGender()
{
    return gender;
};
string User::GetCity()
{
    return city;
};
string User::GetState()
{
    return state;
};
string User::GetEmail()
{
    return eMail;
};
string User::GetCountry()
{
    return country;
};
string User::GetId()
{
    return id;
};
string User::GetJoinDate()
{
    return joinDate;
};
//User Class Ends

//Seller Class Start
class Seller : public User
{
private:
    int totalAds, allowedAds, activeAds, soldGoods;
    float revenue;
    string subScription, accountType;

public:
    Seller()
    {
        totalAds = 0;
        allowedAds = 0;
        activeAds = 0;
        soldGoods = 0;
        revenue = 0.0;
        subScription = "";
        accountType = "";
    }
    //Class Setter Function
    void SetTotalAds(int);
    void SetAllowedAds(int);
    void SetActiveAd(int);
    void SetSoldGood(int);
    void SetRevenue(float);
    void SetSubscription(string);
    void SetAccountType(string);
    //class Getter Functions
    int GetTotalAds();
    int GetAllowedAds();
    int GetActiveAd();
    int GetSoldGood();
    float GetRevenue();
    string GetAccountType();
    string GetSubscription();
};

//Scope Revolution Setter Function
void Seller::SetTotalAds(int val)
{
    totalAds = val;
};
void Seller::SetAllowedAds(int val)
{
    allowedAds = val;
};
void Seller::SetActiveAd(int val)
{
    activeAds = val;
};
void Seller::SetSoldGood(int val)
{
    soldGoods = val;
};
void Seller::SetRevenue(float val)
{
    revenue = val;
};
void Seller::SetSubscription(string val)
{
    subScription = val;
};
void Seller::SetAccountType(string type)
{
    accountType = type;
}
//Scope Resolution Getter Function
string Seller::GetAccountType()
{
    return accountType;
}
int Seller::GetTotalAds()
{
    return totalAds;
};
int Seller::GetAllowedAds()
{
    return allowedAds;
};
int Seller::GetActiveAd()
{
    return activeAds;
};
int Seller::GetSoldGood()
{
    return soldGoods;
};
float Seller::GetRevenue()
{
    return revenue;
};
string Seller::GetSubscription()
{
    return subScription;
};
//Seller Class End's

//Buyer Class Start's
class Buyer : public User
{
private:
    int toltalBid, Bidding, Won, Loss;
    string subScription, accountType;

public:
    //Buyer Class Setter
    void SetTotalBid(int);
    void SetBidding(int);
    void SetWonBid(int);
    void SetLossBid(int);
    void SetSubscription(string);
    void SetAccountType(string);
    //Buyer Class Getter
    int GetTotalBid();
    int GetBidding();
    int GetSetWon();
    int GetLoss();
    string GetSubscription();
    string GetAccountType();
};
//Scope Resoluted Class Methods Getter
void Buyer::SetTotalBid(int value)
{
    toltalBid = value;
}
void Buyer::SetBidding(int value)
{
    Bidding = value;
}
void Buyer::SetWonBid(int value)
{
    Won = value;
}
void Buyer::SetLossBid(int value)
{
    Loss = value;
}
void Buyer::SetAccountType(string value)
{
    accountType = value;
}
void Buyer::SetSubscription(string value)
{
    subScription = value;
}
//Scope Resoluted Class Methods Setter
int Buyer::GetTotalBid()
{
    return toltalBid;
}
int Buyer::GetBidding()
{
    return Bidding;
}
int Buyer::GetSetWon()
{
    return Won;
}
int Buyer::GetLoss()
{
    return Loss;
}
string Buyer::GetSubscription()
{
    return subScription;
}
string Buyer::GetAccountType()
{
    return accountType;
}
class Registration : public Seller, public Buyer
{
private:
    Global Obj;
    string acc[3] = {"Seller", "Buyer", "Both"};
    string sub[3] = {"Free", "Standard", "VVIP"};
    string fname, lname, pass, email, city, state, gender, country, joindate, username, phone;

public:
    Registration()
    {
        fname = "";
        lname = "";
        pass = "";
        email = "";
        city = "";
        state = "";
        gender = "";
        country = "";
        joindate = "";
        username = "";
        phone = "";
    };
    //Protype Class Methods
    int GenericSignUp();
    void SellerSignUp();
    void BuyerSignUp();
    void SavingData(int);
    //Class Destructor
};
//Scope Resoluted Defination Of Protype
void Registration::SavingData(int val)
{
    val -= 1;
    //Opening Json File
    ifstream file("Userdetail.json");
    IStreamWrapper json(file);
    Document d;
    //Deserialize Json
    d.ParseStream(json);
    // Creating New Object
    Value MainObj(kObjectType);
    Value Account(kObjectType);
    cout << acc[val] << endl;
    if (acc[val] == "Seller")
    {
        MainObj.AddMember("userId", StringRef(Seller::GetId().c_str()), d.GetAllocator());
        Value Personal(kObjectType);
        Personal.AddMember("fname", StringRef(Seller::GetFirstName().c_str()), d.GetAllocator());
        Personal.AddMember("lname", StringRef(Seller::GetLastName().c_str()), d.GetAllocator());
        Personal.AddMember("username", StringRef(Seller::GetUserName().c_str()), d.GetAllocator());
        Personal.AddMember("phoneNumber", StringRef(Seller::GetPhoneNumber().c_str()), d.GetAllocator());
        Personal.AddMember("gender", StringRef(Seller::GetGender().c_str()), d.GetAllocator());
        Personal.AddMember("password", StringRef(Seller::GetPassword().c_str()), d.GetAllocator());
        Personal.AddMember("email", StringRef(Seller::GetEmail().c_str()), d.GetAllocator());
        Personal.AddMember("city", StringRef(Seller::GetCity().c_str()), d.GetAllocator());
        Personal.AddMember("state", StringRef(Seller::GetState().c_str()), d.GetAllocator());
        Personal.AddMember("country", StringRef(Seller::GetCountry().c_str()), d.GetAllocator());
        Personal.AddMember("joinDate", StringRef(Seller::GetJoinDate().c_str()), d.GetAllocator());
        MainObj.AddMember("Personal", Personal, d.GetAllocator());
        Account.AddMember("type", StringRef(Seller::GetAccountType().c_str()), d.GetAllocator());
        Value ads(kArrayType);
        Account.AddMember("Ads", ads, d.GetAllocator());
        Account.AddMember("Subscription", StringRef(Seller::GetSubscription().c_str()), d.GetAllocator());
        Value Purchase(kArrayType);
        Account.AddMember("History", Purchase, d.GetAllocator());
        Account.AddMember("TotalAds", GetTotalAds(), d.GetAllocator());
        Account.AddMember("AllowedAd", GetAllowedAds(), d.GetAllocator());
        Account.AddMember("ActiveAd", GetActiveAd(), d.GetAllocator());
        Account.AddMember("SoldGood", GetSoldGood(), d.GetAllocator());
        Account.AddMember("Revenue", GetRevenue(), d.GetAllocator());
    }
    else if (acc[val] == "Buyer")
    {
        MainObj.AddMember("userId", StringRef(Buyer::GetId().c_str()), d.GetAllocator());
        Value Personal(kObjectType);
        Personal.AddMember("fname", StringRef(Buyer::GetFirstName().c_str()), d.GetAllocator());
        Personal.AddMember("lname", StringRef(Buyer::GetLastName().c_str()), d.GetAllocator());
        Personal.AddMember("username", StringRef(Buyer::GetUserName().c_str()), d.GetAllocator());
        Personal.AddMember("phoneNumber", StringRef(Buyer::GetPhoneNumber().c_str()), d.GetAllocator());
        Personal.AddMember("gender", StringRef(Buyer::GetGender().c_str()), d.GetAllocator());
        Personal.AddMember("password", StringRef(Buyer::GetPassword().c_str()), d.GetAllocator());
        Personal.AddMember("email", StringRef(Buyer::GetEmail().c_str()), d.GetAllocator());
        Personal.AddMember("city", StringRef(Buyer::GetCity().c_str()), d.GetAllocator());
        Personal.AddMember("state", StringRef(Buyer::GetState().c_str()), d.GetAllocator());
        Personal.AddMember("country", StringRef(Buyer::GetCountry().c_str()), d.GetAllocator());
        Personal.AddMember("joinDate", StringRef(Buyer::GetJoinDate().c_str()), d.GetAllocator());
        MainObj.AddMember("Personal", Personal, d.GetAllocator());
        Account.AddMember("type", StringRef(Buyer::GetAccountType().c_str()), d.GetAllocator());
        Account.AddMember("Subscription", StringRef(Buyer::GetSubscription().c_str()), d.GetAllocator());
        Account.AddMember("totalBid", GetTotalBid(), d.GetAllocator());
        Account.AddMember("Bidded", GetBidding(), d.GetAllocator());
        Account.AddMember("WonBids", GetSetWon(), d.GetAllocator());
        Account.AddMember("LossBids", GetLoss(), d.GetAllocator());
        Value Carts(kArrayType);
        Account.AddMember("Cart", Carts, d.GetAllocator());
        Value Favourite(kArrayType);
        Account.AddMember("Favourite", Favourite, d.GetAllocator());
        Value Purchase(kArrayType);
        Account.AddMember("Purchase", Purchase, d.GetAllocator());
    }
    MainObj.AddMember("Account", Account, d.GetAllocator());
    d.PushBack(MainObj, d.GetAllocator());
    // 3. Stringify the DOM
    ofstream ofs("Userdetail.json");
    OStreamWrapper osw(ofs);
    Writer<OStreamWrapper> writers(osw);
    d.Accept(writers);
}
int Registration::GenericSignUp()
{
    system("clear");
    int x;
    cout<<"\n\n";
    cout<<setw(50)<<"SIGN UP"<<"\n\n";
    cout<<setw(45);
    cout << "Enter Your First Name Here : "<<setw(45);
    cin >> fname;
    cout <<endl<< "Enter Your Last Name Here : "<<setw(45);
    cin >> lname;
    cout <<endl<< "Enter Your Username Here : "<<setw(45);
    cin >> username;
    cout <<endl<< "Enter Your Email Here : "<<setw(45);
    cin >> email;
    cout <<endl<< "Enter Your Password Here : "<<setw(45);
    cin >> pass;
    cout <<endl<< "Enter Your Phone Number Here : "<<setw(45);
    cin >> phone;
    cout <<endl<< "Enter Your Gender Here : "<<setw(45);
    cin >> gender;
    cout <<endl<< "Enter Your City Here : "<<setw(45);
    cin.ignore();
    getline(cin, city);
    cout<<endl << "Enter Your State Here : "<<setw(45);
    cin >> state;
    cout<<endl << "Enter Your Country Here : "<<setw(45);
    cin >> country;
    cout<<endl << "Select Your Account Type " << endl<<setw(23);
    for (int i = 0; i < 3; i++)
    {
        cout << "-> " << i + 1 << " For " << acc[i] << endl<<setw(23);
    }
    cout<<setw(33)<<"Enter Here : ";
    cin >> x;
    return x;
};
void Registration::SellerSignUp()
{
    Seller::SetId(Obj.SerialGenerator(12));
    Seller::SetFirstName(fname);
    Seller::SetLastName(lname);
    Seller::SetUserName(username);
    Seller::SetEmail(email);
    Seller::SetPassword(pass);
    Seller::SetGender(gender);
    Seller::SetCity(city);
    Seller::SetState(state);
    Seller::SetCountry(country);
    Seller::SetPhoneNumber(phone);
    Seller::SetJoinDate(Obj.GetDate());
    Seller::SetAccountType(acc[0]);
    int y;
    cout<<setw(50) << "Select Your Subscription Plan " <<setw(23);
    for (int i = 0; i < 3; i++)
    {
        if(i<2){
        cout<<endl << "-> " << i + 1 << " For " << sub[i] <<setw(23);
        }
        else{
        cout<<endl << "-> " << i + 1 << " For " << sub[i];
        }
    }
    cout<<endl<<setw(33)<<"Enter Here : ";
    cin >> y;
    switch (y)
    {
    case 1:
        Seller::SetSubscription("Free");
        Seller::SetTotalAds(10);
        Seller::SetAllowedAds(10);
        Seller::SetActiveAd(0);
        Seller::SetSoldGood(0);
        Seller::SetRevenue(0);
        break;
    case 2:
        Seller::SetSubscription("Standard");
        Seller::SetTotalAds(20);
        Seller::SetAllowedAds(20);
        Seller::SetActiveAd(0);
        Seller::SetSoldGood(0);
        Seller::SetRevenue(0);
        break;
    case 3:
        Seller::SetSubscription("VVIP");
        Seller::SetTotalAds(50);
        Seller::SetAllowedAds(50);
        Seller::SetActiveAd(0);
        Seller::SetSoldGood(0);
        Seller::SetRevenue(0);
        break;
    }
}
void Registration::BuyerSignUp()
{
    Buyer::SetId(Obj.SerialGenerator(12));
    Buyer::SetFirstName(fname);
    Buyer::SetLastName(lname);
    Buyer::SetUserName(username);
    Buyer::SetEmail(email);
    Buyer::SetPassword(pass);
    Buyer::SetGender(gender);
    Buyer::SetCity(city);
    Buyer::SetState(state);
    Buyer::SetCountry(country);
    Buyer::SetPhoneNumber(phone);
    Buyer::SetJoinDate(joindate);
    Buyer::SetAccountType(acc[1]);
    Buyer::SetJoinDate(Obj.GetDate());
    int y;
    cout<<setw(50) << "Select Your Subscription Plan " <<endl;
    for (int i = 0; i < 3; i++)
    {
        cout<<setw(23) << "-> " << i + 1 << " For " << sub[i] << endl;
    }
    cout<<setw(33)<<"Enter Here : ";
    cin >> y;
    switch (y)
    {
    case 1:
        Buyer::SetSubscription("Free");
        Buyer::SetTotalBid(10);
        Buyer::SetBidding(0);
        Buyer::SetWonBid(0);
        Buyer::SetLossBid(0);
        break;
    case 2:
        Buyer::SetSubscription("Standard");
        Buyer::SetTotalBid(20);
        Buyer::SetBidding(0);
        Buyer::SetWonBid(0);
        Buyer::SetLossBid(0);
        break;
    case 3:
        Buyer::SetSubscription("VVIP");
        Buyer::SetTotalBid(30);
        Buyer::SetBidding(0);
        Buyer::SetWonBid(0);
        Buyer::SetLossBid(0);
        break;
    }
};
//Categories Class Start Here
class Categories
{
public:
    string Category[11] = {"Mobile", "Vehicles", "Land", "Electronics", "Computer", "Fashion", "Cosmetics", "Books", "Funiture", "Gaming Console", "Hobbies"};

public:
    void DisplayCategory();
};
//Scope Resoluted Methods
void Categories::DisplayCategory()
{
    for (int i = 0; i < 11; i++)
    {
        cout << "-> " << i + 1 << " For " << Category[i] << endl;
    }
};
//Categories Class End Here
//Produc Class Start's
class Product : public Categories
{
private:
    //Composition
    Global obj;
    string ProductID, ProductDesc, ProductCategories, ProductTitle;
    bool ForAuction;
    int ProductPrice;

public:
    Product()
    {
        ProductID = "";
        ProductDesc = "";
        ProductCategories = "";
        ProductTitle = "";
        ForAuction = false;
        ProductPrice = 0;
    }
    //Class Setter Function
    void ProductIDGenerator();
    void ProdutDescSetter(string);
    void ProductCategorySetter(string);
    void ProductTitleSetter(string);
    void ForAuctionSetter(bool);
    void ProductPriceSetter(int);
    //Class Getter Function
    string GetProductID();
    string GetProducDesc();
    string GetProductCategory();
    string GetProductTitle();
    bool GetForAuction();
    int GetProudctPrice();
};
//Scoper Resolution Classes Setter Functions
void Product::ProductIDGenerator()
{
    ProductID = obj.SerialGenerator(10);
};
void Product::ProdutDescSetter(string desc)
{
    ProductDesc = desc;
};
void Product::ProductCategorySetter(string category)
{
    ProductCategories = category;
};
void Product::ProductTitleSetter(string Title)
{
    ProductTitle = Title;
};
void Product::ProductPriceSetter(int price)
{
    ProductPrice = price;
};
void Product::ForAuctionSetter(bool val)
{
    ForAuction = val;
};
//Scoper Resolution Classes Getter Functions
string Product::GetProductID()
{
    return ProductID;
};
string Product::GetProducDesc()
{
    return ProductDesc;
};
string Product::GetProductCategory()
{
    return ProductCategories;
};
string Product::GetProductTitle()
{
    return ProductTitle;
};
bool Product::GetForAuction()
{
    return ForAuction;
};
int Product::GetProudctPrice()
{
    return ProductPrice;
};
//Crete Ad Class

class Ads : public Product
{
private:
    //Composition
    Global Obj;
    string AdDate, AdPostedBy, AdLocation, AdAddress;
    bool AdFeatured;

public:
    Ads()
    {
        AdDate = "";
        AdPostedBy = "";
        AdLocation = "";
        AdAddress = "";
        AdFeatured = false;
    }
    //Class Setter Functions;
    void SetAdDate();
    void SetAdPostedBy(string);
    void SetAdLocation(string);
    void SetAdAdress(string);
    void SetAddFeature(bool);
    //Class Getter Functions;
    string GetAdDate();
    string GetAdPostedBy();
    string GetAdLocation();
    string GetAdAdress();
    bool GetIsAuction();
    //Class Functionality
};
//Scoper Resolution Classes Setter Functions
void Ads::SetAdDate()
{
    AdDate = Obj.GetDate();
};
void Ads::SetAdPostedBy(string val)
{
    AdPostedBy = val;
};
void Ads::SetAdAdress(string val)
{
    AdAddress = val;
};
void Ads::SetAdLocation(string val)
{
    AdLocation = val;
};
void Ads::SetAddFeature(bool val)
{
    AdFeatured = val;
};

//Scoper Resolution Classes Getter Functions

string Ads::GetAdDate()
{
    return AdDate;
};
string Ads::GetAdPostedBy()
{
    return AdPostedBy;
};
string Ads::GetAdLocation()
{
    return AdLocation;
};
string Ads::GetAdAdress()
{
    return AdAddress;
};
bool Ads::GetIsAuction()
{
    return AdFeatured;
}
//Ads Class End

//Dashboard Class Start's Here:
class Dashboard : public Authentications
{
private:
    bool auth;

protected:
    vector<vector<string> > SumAdd;

public:
    Dashboard()
    {
        auth = false;
    }
    //Protype Of Dashboard Methods
    void LogOut();
    virtual void Information(int);
    virtual void AccountInformation();
    virtual void History();
    void PersonalInformation();
    void Listing();
    void EditInformation();
    string AccountType();
    void Search(string);
    void Price(int);
    void byCategory(string);
};
void Dashboard::byCategory(string cat)
{
    system("clear");
    fstream ifs("Userdetail.json");
    IStreamWrapper efs(ifs);
    Document d;
    d.ParseStream(efs);
    const Value &Array = d.GetArray();
    const int index = Array.Size();
    int x = 0;
    SumAdd.clear();
    for (int i = 0; i < index; i++)
    {
        const Value &Account = Array[i].GetObject()["Account"];
        string type = Account.GetObject()["type"].GetString();
        if (type == "Seller" || type == "Both")
        {
            const Value &Ads = Account.GetObject()["Ads"];
            int ads = Ads.GetArray().Size();
            if (ads > 0)
            {

                for (int j = 0; j < ads; j++)
                {
                    if (Ads.GetArray()[j].GetObject()["productCategory"].GetString() == cat)
                    {
                        x++;
                        vector<string> tempdata;
                        for (int k = 0; k < 12; k++)
                        {
                            if (k < 7)
                            {
                                tempdata.push_back(Ads.GetArray()[j].GetObject()[sellerAttributes[k]].GetString());
                            }
                            else if (k == 7)
                            {
                                tempdata.push_back(to_string(Ads.GetArray()[j].GetObject()[sellerAttributes[k]].GetInt()));
                                // cout<<DisplayAd[k] <<UserAds[i][j]<<endl;
                            }
                            else if (k == 8)
                            {
                                string y;
                                bool x = Ads.GetArray()[j].GetObject()[sellerAttributes[k]].GetBool();
                                if (x == true)
                                {
                                    y = "True";
                                }
                                else
                                {
                                    y = "False";
                                }
                                tempdata.push_back(y);
                            }
                            else if (k == 9)
                            {
                                tempdata.push_back(Array[i].GetObject()["Personal"].GetObject()["username"].GetString());
                            }
                            else if (k == 10)
                            {
                                tempdata.push_back(Array[i].GetObject()["Personal"].GetObject()["phoneNumber"].GetString());
                            }
                            else
                            {
                                tempdata.push_back(Array[i].GetObject()["userId"].GetString());
                            }
                        }
                        SumAdd.push_back(tempdata);
                    }
                }
            }
            else
            {
                break;
            }
        }
    }
     if(SumAdd.size() >0){
    for (int i = 0; i < SumAdd.size(); i++)
    {
        if (i == 0)
        {
            cout << "*************************************************************************************************" << endl;
        }
        cout << "Ad No# Is " << i + 1 << endl;
        for (int j = 0; j < SumAdd[i].size(); j++)
        {
            cout << DisplayAd[j] << SumAdd[i][j] << endl;
        }
        cout << "*************************************************************************************************" << endl;
    }
    }
    else{
        cout<<"\n\n\n\n\n\n\n\n\n"<<setw(60);
        cout<<"No Ads Available Now!"<<endl;
    }
}
void Dashboard::Search(string cat)
{
    system("clear");
    fstream ifs("Userdetail.json");
    IStreamWrapper efs(ifs);
    Document d;
    d.ParseStream(efs);
    const Value &Array = d.GetArray();
    const int index = Array.Size();
    int x = 0;
    SumAdd.clear();
    for (int i = 0; i < index; i++)
    {
        const Value &Account = Array[i].GetObject()["Account"];
        string type = Account.GetObject()["type"].GetString();
        if (type == "Seller" || type == "Both")
        {
            const Value &Ads = Account.GetObject()["Ads"];
            int ads = Ads.GetArray().Size();
            if (ads > 0)
            {

                for (int j = 0; j < ads; j++)
                {
                    if (Ads.GetArray()[j].GetObject()["productCategory"].GetString() == cat || Ads.GetArray()[j].GetObject()["productDescription"].GetString() == cat || Ads.GetArray()[j].GetObject()["productTitle"].GetString() == cat)
                    {
                        x++;
                        vector<string> tempdata;
                        for (int k = 0; k < 12; k++)
                        {
                            if (k < 7)
                            {
                                tempdata.push_back(Ads.GetArray()[j].GetObject()[sellerAttributes[k]].GetString());
                            }
                            else if (k == 7)
                            {
                                tempdata.push_back(to_string(Ads.GetArray()[j].GetObject()[sellerAttributes[k]].GetInt()));
                                // cout<<DisplayAd[k] <<UserAds[i][j]<<endl;
                            }
                            else if (k == 8)
                            {
                                string y;
                                bool x = Ads.GetArray()[j].GetObject()[sellerAttributes[k]].GetBool();
                                if (x == true)
                                {
                                    y = "True";
                                }
                                else
                                {
                                    y = "False";
                                }
                                tempdata.push_back(y);
                            }
                            else if (k == 9)
                            {
                                tempdata.push_back(Array[i].GetObject()["Personal"].GetObject()["username"].GetString());
                            }
                            else if (k == 10)
                            {
                                tempdata.push_back(Array[i].GetObject()["Personal"].GetObject()["phoneNumber"].GetString());
                            }
                            else
                            {
                                tempdata.push_back(Array[i].GetObject()["userId"].GetString());
                            }
                        }
                        SumAdd.push_back(tempdata);
                    }
                }
            }
            else
            {
                break;
            }
        }
    }
    if(SumAdd.size() >0){
    for (int i = 0; i < SumAdd.size(); i++)
    {
        if (i == 0)
        {
            cout << "*************************************************************************************************" << endl;
        }
        cout << "Ad No# Is " << i + 1 << endl;
        for (int j = 0; j < SumAdd[i].size(); j++)
        {
            cout << DisplayAd[j] << SumAdd[i][j] << endl;
        }
        cout << "*************************************************************************************************" << endl;
    }
    }
    else{
        cout<<"\n\n\n\n\n\n\n\n\n"<<setw(60);
        cout<<"No Ads Available Now!"<<endl;
    }

}
void Dashboard::Price(int cat)
{
    system("clear");
    fstream ifs("Userdetail.json");
    IStreamWrapper efs(ifs);
    Document d;
    d.ParseStream(efs);
    const Value &Array = d.GetArray();
    const int index = Array.Size();
    int x = 0;
    SumAdd.clear();
    for (int i = 0; i < index; i++)
    {
        const Value &Account = Array[i].GetObject()["Account"];
        string type = Account.GetObject()["type"].GetString();
        if (type == "Seller" || type == "Both")
        {
            const Value &Ads = Account.GetObject()["Ads"];
            int ads = Ads.GetArray().Size();
            if (ads > 0)
            {

                for (int j = 0; j < ads; j++)
                {
                    if (Ads.GetArray()[j].GetObject()["productPrice"].GetInt() <= cat)
                    {
                        x++;
                        vector<string> tempdata;
                        for (int k = 0; k < 12; k++)
                        {
                            if (k < 7)
                            {
                                tempdata.push_back(Ads.GetArray()[j].GetObject()[sellerAttributes[k]].GetString());
                            }
                            else if (k == 7)
                            {
                                tempdata.push_back(to_string(Ads.GetArray()[j].GetObject()[sellerAttributes[k]].GetInt()));
                                // cout<<DisplayAd[k] <<UserAds[i][j]<<endl;
                            }
                            else if (k == 8)
                            {
                                string y;
                                bool x = Ads.GetArray()[j].GetObject()[sellerAttributes[k]].GetBool();
                                if (x == true)
                                {
                                    y = "True";
                                }
                                else
                                {
                                    y = "False";
                                }
                                tempdata.push_back(y);
                            }
                            else if (k == 9)
                            {
                                tempdata.push_back(Array[i].GetObject()["Personal"].GetObject()["username"].GetString());
                            }
                            else if (k == 10)
                            {
                                tempdata.push_back(Array[i].GetObject()["Personal"].GetObject()["phoneNumber"].GetString());
                            }
                            else
                            {
                                tempdata.push_back(Array[i].GetObject()["userId"].GetString());
                            }
                        }
                        SumAdd.push_back(tempdata);
                    }
                }
            }
            else
            {
                break;
            }
        }
    }
    if(SumAdd.size() >0){
    for (int i = 0; i < SumAdd.size(); i++)
    {
        if (i == 0)
        {
            cout << "*************************************************************************************************" << endl;
        }
        cout << "Ad No# Is " << i + 1 << endl;
        for (int j = 0; j < SumAdd[i].size(); j++)
        {
            cout << DisplayAd[j] << SumAdd[i][j] << endl;
        }
        cout << "*************************************************************************************************" << endl;
    }
    }
    else{
        cout<<"\n\n\n\n\n\n\n\n\n"<<setw(60);
        cout<<"No Ads Available Now!"<<endl;
    }
}
void Dashboard::History()
{
    cout << "User Detail!" << endl;
}
void Dashboard::Listing()
{
    ifstream ifs("Userdetail.json");
    IStreamWrapper efs(ifs);
    Document d;
    SumAdd.clear();
    d.ParseStream(efs);
    const int index = d.GetArray().Size();
    int x = 0;
    for (SizeType i = 0; i < index; i++)
    {
        string type = d.GetArray()[i].GetObject()["Account"].GetObject()["type"].GetString();
        if (type == "Seller")
        {
            int ads = d.GetArray()[i].GetObject()["Account"].GetObject()["Ads"].Size();
            if (ads > 0)
            {
                for (int j = 0; j < ads; j++)
                {
                    x++;
                    vector<string> tempdata;
                    for (int k = 0; k < 12; k++)
                    {
                        if (k < 7)
                        {
                            tempdata.push_back(d.GetArray()[i].GetObject()["Account"].GetObject()["Ads"].GetArray()[j].GetObject()[sellerAttributes[k]].GetString());
                        }
                        else if (k == 7)
                        {
                            tempdata.push_back(to_string(d.GetArray()[i].GetObject()["Account"].GetObject()["Ads"].GetArray()[j].GetObject()[sellerAttributes[k]].GetInt()));
                            // cout<<DisplayAd[k] <<Userd.GetArray()[i].GetObject()["Account"].GetObject()["Ads"][i][j]<<endl;
                        }
                        else if (k == 8)
                        {
                            string y;
                            bool x = d.GetArray()[i].GetObject()["Account"].GetObject()["Ads"].GetArray()[j].GetObject()[sellerAttributes[k]].GetBool();
                            if (x == true)
                            {
                                y = "True";
                            }
                            else
                            {
                                y = "False";
                            }
                            tempdata.push_back(y);
                        }
                        else if (k == 9)
                        {
                            tempdata.push_back(d.GetArray()[i].GetObject()["Personal"].GetObject()["username"].GetString());
                        }
                        else if (k == 10)
                        {
                            tempdata.push_back(d.GetArray()[i].GetObject()["Personal"].GetObject()["phoneNumber"].GetString());
                        }
                        else
                        {
                            tempdata.push_back(d.GetArray()[i].GetObject()["userId"].GetString());
                        }
                    }
                    SumAdd.push_back(tempdata);
                }
            }
        }
    }
     if(SumAdd.size() >0){
    for (int i = 0; i < SumAdd.size(); i++)
    {
        if (i == 0)
        {
            cout << "*************************************************************************************************" << endl;
        }
        cout << "Ad No# Is " << i + 1 << endl;
        for (int j = 0; j < SumAdd[i].size(); j++)
        {
            cout << DisplayAd[j] << SumAdd[i][j] << endl;
        }
        cout << "*************************************************************************************************" << endl;
    }
    }
    else{
        cout<<"\n\n\n\n\n\n\n\n\n"<<setw(60);
        cout<<"No Ads Available Now!"<<endl;
    }
}
void Dashboard::Information(int id)
{
    int temp = 1;
    ifstream ifs("Userdetail.json");
    IStreamWrapper isw(ifs);
    Document d;
    d.ParseStream(isw);
    Personal[0][1] = to_string(id);
    Personal[1][1] = d.GetArray()[id].GetObject()["userId"].GetString();
    for (int i = 0; i < 11; i++)
    {
        Personal[temp + 1][1] = d.GetArray()[id].GetObject()["Personal"].GetObject()[userAttributes[i]].GetString();
        temp++;
    }
    if (d.GetArray()[id].GetObject()["Account"].GetObject()["type"] == "Seller")
    {
        for (int i = 0; i < 7; i++)
        {
            if (i < 2)
            {
                Account[i][1] = d.GetArray()[id].GetObject()["Account"].GetObject()[SellerAccountAttribute[i]].GetString();
            }
            else if (i < 6)
            {
                int x = d.GetArray()[id].GetObject()["Account"].GetObject()[SellerAccountAttribute[i]].GetInt();
                Account[i][1] = to_string(x);
            }
            else
            {
                float x = d.GetArray()[id].GetObject()["Account"].GetObject()[SellerAccountAttribute[i]].GetFloat();
                Account[i][1] = to_string(x);
            }
        }
    }
    else if (d.GetArray()[id].GetObject()["Account"].GetObject()["type"] == "Buyer")
    {
        Account[0][1] = "Buyer";
    }
}
void Dashboard::PersonalInformation()
{
    cout<<"\n\n\n\n\n\n\n"<<setw(60)<<"Personal Information"<<endl<<endl;
    for (int i = 2; i < 12; i++)
    {
        cout <<setw(40)<< Personal[i][0] << " Is :"<<setw(20) << Personal[i][1] << endl<<endl;
    }
}
string Dashboard::AccountType()
{
    return Account[0][1];
}
void Dashboard::AccountInformation()
{
    cout<<"\n\n\n\n\n\n\n\n\n"<<setw(56)<<"Account Information"<<endl<<endl;
    for (int i = 0; i < 7; i++)
    {
        cout<<setw(41) << Account[i][0] << " Is : \t" << Account[i][1] << endl<<endl;
    }
}
//Dashboard Class End Here

class SellerDashboard : public Dashboard, public Seller, public Ads
{
private:
    vector<vector<string> > UserAds;
    string pname, pdesc, pcategory, add;
    int pprice;
    string date;
    int swi;

public:
    SellerDashboard()
    {
        pname = "";
        pdesc = "";
        pcategory = "";
        add = "";
        pprice = 0;
        date = "";
        swi = 0;
    }
    //Prototype Of Class Methods
    void createAd();
    void myAd();
    void editAd();
    void delAd();
    void SetSeller();
    void selectCategory(int);
    void PostAd();
    void History();
};
//Scope Resoluted Class Method Defination
void SellerDashboard::selectCategory(int x)
{
    ProductCategorySetter(Category[x - 1]);
}
void SellerDashboard::SetSeller()
{
    SetId(Personal[1][1]);
    SetFirstName(Personal[2][1]);
    SetLastName(Personal[3][1]);
    SetUserName(Personal[4][1]);
    SetPhoneNumber(Personal[5][1]);
    SetGender(Personal[6][1]);
    SetEmail(Personal[7][1]);
    SetCity(Personal[8][1]);
    SetState(Personal[9][1]);
    SetCountry(Personal[10][1]);
    SetJoinDate(Personal[11][1]);
    SetPassword(Personal[12][1]);
    SetAccountType(Account[0][1]);
    SetSubscription(Account[1][1]);
    SetTotalAds(stoi(Account[2][1]));
    SetAllowedAds(stoi(Account[3][1]));
    SetActiveAd(stoi(Account[4][1]));
    SetSoldGood(stoi(Account[5][1]));
    SetRevenue(stoi(Account[6][1]));
}
// g++ project.cpp -o myexcel -I/usr/local/include -L/usr/local/lib -lxlsxwriter
void SellerDashboard::PostAd()
{
    ifstream file("Userdetail.json");
    IStreamWrapper Json(file);
    Document d;
    d.ParseStream(Json);
    for (int i = 0; i < d.GetArray().Size(); i++)
    {
        if (d.GetArray()[i].GetObject()["userId"].GetString() == Personal[1][1])
        {
            int x = d.GetArray()[i].GetObject()["Account"].GetObject()["Ads"].GetArray().Size();
            int y = GetTotalAds() - x;
            Value ad(kObjectType);
            ad.AddMember("productId", StringRef(GetProductID().c_str()), d.GetAllocator());
            ad.AddMember("productDescription", StringRef(GetProducDesc().c_str()), d.GetAllocator());
            ad.AddMember("productCategory", StringRef(GetProductCategory().c_str()), d.GetAllocator());
            ad.AddMember("productTitle", StringRef(GetProductTitle().c_str()), d.GetAllocator());
            ad.AddMember("adDate", StringRef(GetAdDate().c_str()), d.GetAllocator());
            ad.AddMember("adLocation", StringRef(GetAdLocation().c_str()), d.GetAllocator());
            ad.AddMember("adAdress", StringRef(GetAdAdress().c_str()), d.GetAllocator());
            ad.AddMember("productPrice", GetProudctPrice(), d.GetAllocator());
            ad.AddMember("adFeature", GetIsAuction(), d.GetAllocator());
            d.GetArray()[i].GetObject()["Account"].GetObject()["Ads"].PushBack(ad, d.GetAllocator());
            d.GetArray()[i].GetObject()["Account"].GetObject()["AllowedAd"].SetInt(y);
            d.GetArray()[i].GetObject()["Account"].GetObject()["ActiveAd"].SetInt(x);
            ofstream ofs("Userdetail.json");
            OStreamWrapper osw(ofs);
            Writer<OStreamWrapper> writers(osw);
            d.Accept(writers);
            ofs.close();
        }
    }
}
void SellerDashboard::createAd()
{
    SetSeller();
    if (GetAllowedAds() > 0)
    {
        cout << "Enter Product Title Here : ";
        cin.ignore();
        getline(cin, pname);
        cout << "Enter Product Description Here : ";
        getline(cin, pdesc);
        DisplayCategory();
        cout << "Select Product Category Here : ";
        cin >> swi;
        selectCategory(swi);
        getline(cin, pcategory);
        cout << "Enter Product Price Here : ";
        cin >> pprice;
        ProductIDGenerator();
        ProdutDescSetter(pdesc);
        ProductTitleSetter(pname);
        ProductPriceSetter(pprice);
        SetAdDate();
        SetAdPostedBy(GetUserName());
        SetAdLocation(GetCity());
        add = GetCity() + " " + GetState() + "," + GetCountry();
        SetAdAdress(add);
        SetAddFeature(false);
        PostAd();
    }
    else
    {
        cout << "Your Ad Posting Limit Exceeds!" << endl;
    }
};
void SellerDashboard::myAd()
{
    ifstream ifs("Userdetail.json");
    IStreamWrapper efs(ifs);
    Document d;
    d.ParseStream(efs);
    UserAds.clear();
    int index = stoi(Personal[0][1]);
    int looping = d.GetArray()[index].GetObject()["Account"].GetObject()["Ads"].GetArray().Size();
    if(looping > 0){

    
    for (int i = 0; i < looping; i++)
    {
        if (i == 0)
        {
            cout << "*************************************************************************************************" << endl;
        }
        cout << "No# Of Ads : " << i + 1 << endl;
        UserAds.push_back(vector<string>());
        for (int j = 0; j < 9; j++)
        {
            if (j < 7)
            {
                string x = d.GetArray()[index].GetObject()["Account"].GetObject()["Ads"].GetArray()[i].GetObject()[sellerAttributes[j]].GetString();
                UserAds[i].push_back(x);
            }
            else if (j == 7)
            {
                int x = d.GetArray()[index].GetObject()["Account"].GetObject()["Ads"].GetArray()[i].GetObject()[sellerAttributes[j]].GetInt();
                UserAds[i].push_back(to_string(x));
            }
            else
            {
                bool x = d.GetArray()[index].GetObject()["Account"].GetObject()["Ads"].GetArray()[i].GetObject()[sellerAttributes[j]].GetBool();
                string y = x == true ? "Yes" : "No";
                UserAds[i].push_back(y);
            }
            cout << DisplayAd[j] << UserAds[i][j] << endl;
        }
        cout << "*************************************************************************************************" << endl;
    }
    }
    else{
        cout<<"\n\n\n\n\n\n\n\n\n"<<setw(60);
        cout<<"No Ads Available Now!"<<endl;
    }
}
void SellerDashboard::editAd()
{
    char *updates[4] = {"productTitle", "productDescription", "productCategory", "productPrice"};
    ifstream ifs("Userdetail.json");
    IStreamWrapper efs(ifs);
    Document d;
    d.ParseStream(efs);
    int index = stoi(Personal[0][1]);
    if(d.GetArray()[index].GetObject()["Account"].GetObject()["Ads"].GetArray().Size()>0){
    myAd();
    int x;
    cout << endl
         << "Enter Ad Number Here To Edit : ";
    cin >> x;
    cout << "-> Press 1 For Ad Title : " << endl;
    cout << "-> Press 2 For Ad Description : " << endl;
    cout << "-> Press 3 For Ad Category :" << endl;
    cout << "-> Press 4 For Ad Price : " << endl;
    cout << "-> Enter Here : ";
    int y;
    cin >> y;
    if (x - 1 < d.GetArray()[index].GetObject()["Account"].GetObject()["Ads"].GetArray().Size())
    {
        int updatep;
        string update;
        switch (y)
        {
        case 1:
            cin.ignore();
            cout << "Enter New Title Here : ";
            getline(cin, update);
            d.GetArray()[index].GetObject()["Account"].GetObject()["Ads"].GetArray()[x - 1].GetObject()[updates[y - 1]].SetString(StringRef(update.c_str()));
            break;
        case 2:
            cin.ignore();
            cout << "Enter New Description Here : ";
            getline(cin, update);
            d.GetArray()[index].GetObject()["Account"].GetObject()["Ads"].GetArray()[x - 1].GetObject()[updates[y - 1]].SetString(StringRef(update.c_str()));
            break;
        case 3:
            cin.ignore();
            cout << "Enter New Category Here : ";
            getline(cin, update);
            d.GetArray()[index].GetObject()["Account"].GetObject()["Ads"].GetArray()[x - 1].GetObject()[updates[y - 1]].SetString(StringRef(update.c_str()));
            break;
        case 4:
            cout << "Enter New Price Here : ";
            cin >> updatep;
            d.GetArray()[index].GetObject()["Account"].GetObject()["Ads"].GetArray()[x - 1].GetObject()[updates[y - 1]].SetInt(updatep);
            break;
        default:
            cout << "Enter Valid Option!" << endl;
            break;
        }
        ofstream is("Userdetail.json");
        OStreamWrapper osw(is);
        Writer<OStreamWrapper> writes(osw);
        d.Accept(writes);
        cout << "Ad Has Been Edited!" << endl;
    }
    }
    else{
        cout<<"\n\n\n\n\n\n\n\n\n"<<setw(60);
        cout<<"No Ads Available Now!"<<endl;
    }

}
void SellerDashboard::History()
{
    Excel obj;
    int id = stoi(Personal[0][1]);
    ifstream ifs("Userdetail.json");
    IStreamWrapper isw(ifs);
    Document d;
    d.ParseStream(isw);
    int x = d.GetArray()[id].GetObject()["Account"].GetObject()["History"].GetArray().Size();
    cout << "Ad Title " << setw(30) << "Sell Date " << setw(31) << "Price " << endl;
    for (int i = 0; i < x; i++)
    {
        int x = d.GetArray()[id].GetObject()["Account"].GetObject()["History"].GetArray()[i].GetObject()["Adtitle"].GetStringLength();
        cout << d.GetArray()[id].GetObject()["Account"].GetObject()["History"].GetArray()[i].GetObject()["Adtitle"].GetString()<<setw(30-x+9);
        cout << d.GetArray()[id].GetObject()["Account"].GetObject()["History"].GetArray()[i].GetObject()["Date"].GetString()<<setw(30);
        cout <<setw(30)<< d.GetArray()[id].GetObject()["Account"].GetObject()["History"].GetArray()[i].GetObject()["Price"].GetInt() << endl;
    }
    cout << endl;
    cout << "--> 1 For Generate Excel File!" << endl;
    cout << "--> 2 For Skip It" << endl;
    int mn;
    cin >> mn;
    switch (mn)
    {
    case 1:
        obj.SetIndex(id);
        obj.ForSellerReport();
        break;
    default:
        break;
    }
}
//BuyerDashboard Class Start Here
class BuyerDashboard : public Dashboard, public Buyer, public Categories
{
private:
    vector<vector<string> > mycart;
    vector<vector<string> > favourite;

protected:
    string Arr[12] = {"AdId", "AdTitle", "AdDescription", "Category", "UploadDate", "AdLocation", "AdAdress", "AdPrice", "ForAuction", "UploadBy", "PhoneNumber", "userId"};
    const char *buyerAttributes[6] = {"type", "Subscription", "totalBid", "Bidded", "WonBids", "LossBids"};

public:
    // void adToFavourite(string, vector<vector<string>> &data);
    void Information(int);
    void addToCart();
    void myCart();
    void delCart();
    void clearCart();
    void adToFavourite();
    void myFavourite();
    void delFavourite();
    void clearFavourite();
    void checkOut();
    void clearAds(int);
    void favouriteToCart();
    void AccountInformation();
    friend void ClearAd(int, vector<vector<string> > &obj, vector<string> &ref);
    void Purchase(vector<string> &obj);
    void History();
};
void BuyerDashboard::Information(int id)
{
    int temp = 1;
    ifstream ifs("Userdetail.json");
    IStreamWrapper isw(ifs);
    Document d;
    d.ParseStream(isw);
    Personal[0][1] = to_string(id);
    Personal[1][1] = d.GetArray()[id].GetObject()["userId"].GetString();
    for (int i = 0; i < 11; i++)
    {
        Personal[temp + 1][1] = d.GetArray()[id].GetObject()["Personal"].GetObject()[userAttributes[i]].GetString();
        temp++;
    }
    for (int i = 0; i < 6; i++)
    {
        if (i < 2)
        {
            AccountBuyer[i][1] = d.GetArray()[id].GetObject()["Account"].GetObject()[buyerAttributes[i]].GetString();
        }
        else
        {
            int x = d.GetArray()[id].GetObject()["Account"].GetObject()[buyerAttributes[i]].GetInt();
            AccountBuyer[i][1] = to_string(x);
        }
    }
}
void BuyerDashboard::addToCart()
{
    int x;
    cout << "Enter Ad Number To Add It Cart : " << endl;
    cin >> x;
    int y = stoi(Personal[0][1]);
    ifstream ifs("Userdetail.json");
    IStreamWrapper efs(ifs);
    Document d;
    bool ad = true;
    d.ParseStream(efs);
    int cartSize = d.GetArray()[y].GetObject()["Account"].GetObject()["Cart"].GetArray().Size();
    for (int i = 0; i < cartSize; i++)
    {
        const Value &Cart = d.GetArray()[y].GetObject()["Account"].GetObject()["Cart"].GetArray()[i].GetObject();
        vector<string> cart;
        for (int j = 0; j < 12; j++)
        {
            cart.push_back(Cart[Arr[j].c_str()].GetString());
            // cout<<DisplayAd[j]<<Cart[Arr[j].c_str()].GetString()<<endl;
        }
        mycart.push_back(cart);
    }
    for (int i = 0; i < mycart.size(); i++)
    {
        if (mycart[i][0] == SumAdd[x - 1][0])
        {
            ad = false;
        }
    }
    if (ad == true)
    {

        Value cart(kObjectType);
        for (int i = 0; i < 12; i++)
        {
            cart.AddMember(StringRef(Arr[i].c_str()), StringRef(SumAdd[x - 1][i].c_str()), d.GetAllocator());
        }
        d.GetArray()[y].GetObject()["Account"].GetObject()["Cart"].PushBack(cart, d.GetAllocator());
        ifs.close();
        ofstream isw("Userdetail.json");
        OStreamWrapper nfw(isw);
        Writer<OStreamWrapper> writes(nfw);
        d.Accept(writes);
        isw.close();
        cout << "Added To Cart Successfully!" << endl;
    }
    else
    {
        cout << "Already In Cart!" << endl;
    }
}
void BuyerDashboard::myCart()
{
    int y = stoi(Personal[0][1]);
    ifstream ifs("Userdetail.json");
    IStreamWrapper efs(ifs);
    Document d;
    d.ParseStream(efs);
    mycart.clear();
    int cartSize = d.GetArray()[y].GetObject()["Account"].GetObject()["Cart"].GetArray().Size();
    if(cartSize > 0){
    for (int i = 0; i < cartSize; i++)
    {
        const Value &Cart = d.GetArray()[y].GetObject()["Account"].GetObject()["Cart"].GetArray()[i].GetObject();
        vector<string> cart;
        for (int j = 0; j < 12; j++)
        {
            cart.push_back(Cart[Arr[j].c_str()].GetString());
            // cout<<DisplayAd[j]<<Cart[Arr[j].c_str()].GetString()<<endl;
        }
        mycart.push_back(cart);
    }
     }
     else{
        //  cout<<"\n\n\n\n\n\n\n\n\n"<<setw(60);
        // cout<<"Cart Is Empty Now!"<<endl;
     }
    ifs.close();
if(mycart.size() >0){
    for (int i = 0; i < mycart.size(); i++)
    {
        if (i == 0)
        {
            cout << "*************************************************************************************************" << endl;
        }
        cout << "Cart No# " << i + 1 << endl;
        for (int j = 0; j < 11; j++)
        {
            cout << DisplayAd[j] << mycart[i][j] << endl;
        }
        cout << "*************************************************************************************************" << endl;
    }
}
else{
    cout<<"\n\n\n\n\n\n\n\n\n"<<setw(60);
        cout<<"Cart Is Empty Now!"<<endl;
}
}
void BuyerDashboard::delCart()
{
    int cartNo;
    cout << "Enter Cart No Here ";
    cin >> cartNo;
    cartNo = cartNo - 1;
    mycart.erase(mycart.begin() - cartNo);
    int y = stoi(Personal[0][1]);
    ifstream ifs("Userdetail.json");
    IStreamWrapper efs(ifs);
    Document d;
    d.ParseStream(efs);
    Value carts(kObjectType);
    if (mycart.size() > 1)
    {
        d.GetArray()[y].GetObject()["Account"].GetObject()["Cart"].Clear();
        for (int i = 0; i < mycart.size(); i++)
        {
            for (int j = 0; j < mycart[i].size(); j++)
            {
                carts.AddMember(StringRef(Arr[j].c_str()), StringRef(mycart[i][j].c_str()), d.GetAllocator());
            }
        }
        d.GetArray()[y].GetObject()["Account"].GetObject()["Cart"].PushBack(carts, d.GetAllocator());
    }
    else
    {
        d.GetArray()[y].GetObject()["Account"].GetObject()["Cart"].Clear();
    }
    ifs.close();
    ofstream isw("Userdetail.json");
    OStreamWrapper nfw(isw);
    Writer<OStreamWrapper> writes(nfw);
    d.Accept(writes);
    isw.close();
    cout << "Ad Deleted From Cart Successfully!" << endl;
}
void BuyerDashboard::clearCart()
{
    ifstream is("Userdetail.json");
    IStreamWrapper nf(is);
    Document d;
    d.ParseStream(nf);
    int ind = stoi(Personal[0][1]);
    d.GetArray()[ind].GetObject()["Account"].GetObject()["Cart"].Clear();
    is.close();
    ofstream of("Userdetail.json");
    OStreamWrapper nof(of);
    Writer<OStreamWrapper> output(nof);
    d.Accept(output);
    of.close();
    cout << "Cart Will Be Clear Successfully!" << endl;
}
void BuyerDashboard::adToFavourite()
{
    int x;
    cout << "Enter Ad Number To Add It Favourite : " << endl;
    cin >> x;
    int y = stoi(Personal[0][1]);
    ifstream ifs("Userdetail.json");
    IStreamWrapper efs(ifs);
    Document d;
    d.ParseStream(efs);
    const Value &Fav = d.GetArray()[y].GetObject()["Account"].GetObject()["Favourite"];
    if (Fav.Size() > 0)
    {
        for (int j = 0; j < Fav.Size(); j++)
        {
            if (Fav.GetArray()[j].GetObject()["AdId"].GetString() != SumAdd[x - 1][0])
            {
                Value cart(kObjectType);
                for (int i = 0; i < SumAdd[x - 1].size(); i++)
                {
                    cart.AddMember(StringRef(Arr[i].c_str()), StringRef(SumAdd[x - 1][i].c_str()), d.GetAllocator());
                }
                d.GetArray()[y].GetObject()["Account"].GetObject()["Favourite"].PushBack(cart, d.GetAllocator());
                ofstream isw("Userdetail.json");
                OStreamWrapper nfw(isw);
                Writer<OStreamWrapper> writes(nfw);
                d.Accept(writes);
                break;
            }
            else
            {
                cout << false;
                break;
            }
        }
    }
    else
    {
        Value cart(kObjectType);
        for (int i = 0; i < SumAdd[x - 1].size(); i++)
        {
            cart.AddMember(StringRef(Arr[i].c_str()), StringRef(SumAdd[x - 1][i].c_str()), d.GetAllocator());
        }
        d.GetArray()[y].GetObject()["Account"].GetObject()["Favourite"].PushBack(cart, d.GetAllocator());
        ofstream isw("Userdetail.json");
        OStreamWrapper nfw(isw);
        Writer<OStreamWrapper> writes(nfw);
        d.Accept(writes);
        isw.close();
    }
    ifs.close();
    cout << "Ad Will Be Added In Favourite Successfully!" << endl;
}
void BuyerDashboard::myFavourite()
{
    int y = stoi(Personal[0][1]);
    ifstream ifs("Userdetail.json");
    IStreamWrapper efs(ifs);
    Document d;
    d.ParseStream(efs);
    int FavouriteSize = d.GetArray()[y].GetObject()["Account"].GetObject()["Favourite"].GetArray().Size();
    for (int i = 0; i < FavouriteSize; i++)
    {
        const Value &Favourites = d.GetArray()[y].GetObject()["Account"].GetObject()["Favourite"].GetArray()[i].GetObject();
        vector<string> Fav;
        for (int j = 0; j < 12; j++)
        {
            Fav.push_back(Favourites[Arr[j].c_str()].GetString());
        }
        favourite.push_back(Fav);
    }
    if(favourite.size()>0){
    for (int i = 0; i < favourite.size(); i++)
    {
        if (i == 0)
        {
            cout << "*************************************************************************************************" << endl;
        }
        cout << "Item No# " << i + 1 << endl;
        for (int j = 0; j < 11; j++)
        {
            cout << DisplayAd[j] << favourite[i][j] << endl;
        }
        cout << "*************************************************************************************************" << endl;
    }        
    }
    else{
        cout<<"\n\n\n\n\n\n\n\n\n"<<setw(60);
        cout<<"No Ads Available Now!"<<endl;
    }
    ifs.close();
}
void BuyerDashboard::delFavourite()
{
    int ItemNo;
    cout << "Enter Cart No Here ";
    cin >> ItemNo;
    ItemNo = ItemNo - 1;
    favourite.erase(favourite.begin() - ItemNo);
    int y = stoi(Personal[0][1]);
    ifstream ifs("Userdetail.json");
    IStreamWrapper efs(ifs);
    Document d;
    d.ParseStream(efs);
    if (favourite.size() > 1)
    {
        d.GetArray()[y].GetObject()["Account"].GetObject()["Favourite"].Clear();
        for (int i = 0; i < favourite.size(); i++)
        {
            Value fav(kObjectType);
            for (int j = 0; j < 11; j++)
            {
                fav.AddMember(StringRef(Arr[j].c_str()), StringRef(favourite[i][j].c_str()), d.GetAllocator());
            }
            d.GetArray()[y].GetObject()["Account"].GetObject()["Favourite"].PushBack(fav, d.GetAllocator());
        }
    }
    else
    {
        d.GetArray()[y].GetObject()["Account"].GetObject()["Favourite"].Clear();
    }
    ifs.close();
    ofstream isw("Userdetail.json");
    OStreamWrapper nfw(isw);
    Writer<OStreamWrapper> writes(nfw);
    d.Accept(writes);
    isw.close();
    cout << "Ad Is Deleted From Favourite Successfully!" << endl;
}
void BuyerDashboard::clearFavourite()
{
    ifstream is("Userdetail.json");
    IStreamWrapper nf(is);
    Document d;
    d.ParseStream(nf);
    int ind = stoi(Personal[0][1]);
    d.GetArray()[ind].GetObject()["Account"].GetObject()["Favourite"].Clear();
    is.close();
    ofstream of("Userdetail.json");
    OStreamWrapper nof(of);
    Writer<OStreamWrapper> output(nof);
    d.Accept(output);
    of.close();
    cout << "Favourite Will Be Clear Succesfully!" << endl;
}
void BuyerDashboard::checkOut()
{
    int a;
    vector<vector<string> > tempads;
    int ads;
    int index = stoi(Personal[0][1]);
    ifstream file("Userdetail.json");
    IStreamWrapper json(file);
    Document Oper;
    Oper.ParseStream(json);
    const Value &User = Oper.GetArray()[index];
    cout << "Enter Ad No Here : ";
    cin >> ads;
    ads -= 1;
    cout << "Sellect Payment Methods!" << endl;
    cout << "-> 1 For Cash On Delivery!" << endl;
    cout << "-> 2 For Online Payment!" << endl;
    cin >> a;
    string adid = mycart[ads][0];
    string userID = mycart[ads][11];
    for (SizeType i = 0; i < Oper.GetArray().Size(); i++)
    {
        string id = Oper.GetArray()[i].GetObject()["userId"].GetString();
        const Value &Account = Oper.GetArray()[i].GetObject()["Account"].GetObject();
        if (id == userID)
        {
            const Value &Ads = Account.GetObject()["Ads"];
            for (SizeType j = 0; j < Account["Ads"].Size(); j++)
            {
                vector<string> tempdata;
                for (int k = 0; k < 9; k++)
                {
                    if (k < 7)
                    {
                        tempdata.push_back(Ads.GetArray()[j].GetObject()[sellerAttributes[k]].GetString());
                    }
                    else if (k == 7)
                    {
                        tempdata.push_back(to_string(Ads.GetArray()[j].GetObject()[sellerAttributes[k]].GetInt()));
                    }
                    else if (k == 8)
                    {
                        string y;
                        bool x = Ads.GetArray()[j].GetObject()[sellerAttributes[k]].GetBool();
                        if (x == true)
                        {
                            y = "True";
                        }
                        else
                        {
                            y = "False";
                        }
                        tempdata.push_back(y);
                    }
                }
                tempads.push_back(tempdata);
            }
        }
    }
    for (int i = 0; i < tempads.size(); i++)
    {
        if (tempads[i][0] == mycart[ads][0])
        {
            tempads.erase(tempads.begin() + i);
        }
    }
    for (int i = 0; i < Oper.GetArray().Size(); i++)
    {
        string id = Oper.GetArray()[i].GetObject()["userId"].GetString();
        if (id == userID)
        {
            ClearAd(i, tempads, mycart[ads]);
            Purchase(mycart[ads]);
        }
    }
    mycart.erase(mycart.begin() - ads);
    int y = stoi(Personal[0][1]);
    ifstream ifs("Userdetail.json");
    IStreamWrapper efs(ifs);
    Document d;
    d.ParseStream(efs);
    Value carts(kObjectType);
    if (mycart.size() > 1)
    {
        d.GetArray()[y].GetObject()["Account"].GetObject()["Cart"].Clear();
        for (int i = 0; i < mycart.size(); i++)
        {
            for (int j = 0; j < mycart[i].size(); j++)
            {
                carts.AddMember(StringRef(Arr[j].c_str()), StringRef(mycart[i][j].c_str()), d.GetAllocator());
            }
        }
        d.GetArray()[y].GetObject()["Account"].GetObject()["Cart"].PushBack(carts, d.GetAllocator());
    }
    else
    {
        d.GetArray()[y].GetObject()["Account"].GetObject()["Cart"].Clear();
    }
    ifs.close();
    ofstream isw("Userdetail.json");
    OStreamWrapper nfw(isw);
    Writer<OStreamWrapper> writes(nfw);
    d.Accept(writes);
    isw.close();
    cout<<"Product Succssfuly Purchased!"<<endl;
}
void BuyerDashboard::favouriteToCart()
{
    int ind;
    cout << "Enter Item Number Here : ";
    cin >> ind;
    ind -= 1;
    int index = stoi(Personal[0][1]);
    ifstream file("Userdetail.json");
    IStreamWrapper json(file);
    Document doc;
    doc.ParseStream(json);
    if (doc.GetArray()[index].GetObject()["Account"].GetObject()["Cart"].Size() > 0)
    {
        for (int m = 0; m < doc.GetArray()[index].GetObject()["Account"].GetObject()["Cart"].Size(); m++)
        {
            if (doc.GetArray()[index].GetObject()["Account"].GetObject()["Cart"].GetArray()[m].GetObject()["AdId"].GetString() != favourite[ind][0])
            {
                Value cart(kObjectType);
                for (int i = 0; i < 12; i++)
                {
                    cart.AddMember(StringRef(Arr[i].c_str()), StringRef(favourite[ind][i].c_str()), doc.GetAllocator());
                }
                doc.GetArray()[index].GetObject()["Account"].GetObject()["Cart"].PushBack(cart, doc.GetAllocator());
                file.close();
                ofstream newFile("Userdetail.json");
                OStreamWrapper ofs(newFile);
                Writer<OStreamWrapper> writes(ofs);
                doc.Accept(writes);
                cout << "Added To Cart Successfully!" << endl;
                break;
            }
            else
            {
                cout << "Already In Cart!" << endl;
            }
        }
    }
    else
    {
        Value cart(kObjectType);
        for (int i = 0; i < 12; i++)
        {
            cart.AddMember(StringRef(Arr[i].c_str()), StringRef(favourite[ind][i].c_str()), doc.GetAllocator());
        }
        doc.GetArray()[index].GetObject()["Account"].GetObject()["Cart"].PushBack(cart, doc.GetAllocator());
        file.close();
        ofstream newFile("Userdetail.json");
        OStreamWrapper ofs(newFile);
        Writer<OStreamWrapper> writes(ofs);
        doc.Accept(writes);
        cout << "Added To Cart Successfully!" << endl;
    }
}
void BuyerDashboard::AccountInformation()
{
    cout<<"\n\n\n\n\n\n\n\n\n"<<setw(56)<<"Account Information"<<endl<<endl;
    for (int i = 0; i < 6; i++)
    {
        cout<<setw(41) << AccountBuyer[i][0] << " Is : \t" << AccountBuyer[i][1] << endl<<endl;
    }
}
void BuyerDashboard::Purchase(vector<string> &obj)
{
    int id = stoi(Personal[0][1]);
    ifstream file("Userdetail.json");
    IStreamWrapper json(file);
    Document d;
    d.ParseStream(json);
    Value Purchase(kObjectType);
    Purchase.AddMember("Adtitle", StringRef(obj[1].c_str()), d.GetAllocator());
    Purchase.AddMember("Category", StringRef(obj[3].c_str()), d.GetAllocator());
    Purchase.AddMember("Date", StringRef(obj[4].c_str()), d.GetAllocator());
    Purchase.AddMember("Location", StringRef(obj[5].c_str()), d.GetAllocator());
    Purchase.AddMember("Price", stoi(obj[7]), d.GetAllocator());
    Purchase.AddMember("Name", StringRef(obj[9].c_str()), d.GetAllocator());
    d.GetArray()[id].GetObject()["Account"].GetObject()["Purchase"].GetArray().PushBack(Purchase, d.GetAllocator());
    ofstream of("Userdetail.json");
    OStreamWrapper nof(of);
    Writer<OStreamWrapper> output(nof);
    d.Accept(output);
    of.close();
}
void ClearAd(int id, vector<vector<string> > &obj, vector<string> &ref)
{
    ifstream file("Userdetail.json");
    IStreamWrapper json(file);
    Document d;
    d.ParseStream(json);
    d.GetArray()[id].GetObject()["Account"].GetObject()["Ads"].Clear();
    for (int k = 0; k < obj.size(); k++)
    {
        Value ad(kObjectType);
        ad.AddMember("productId", StringRef(obj[k][0].c_str()), d.GetAllocator());
        ad.AddMember("productDescription", StringRef(obj[k][2].c_str()), d.GetAllocator());
        ad.AddMember("productCategory", StringRef(obj[k][3].c_str()), d.GetAllocator());
        ad.AddMember("productTitle", StringRef(obj[k][1].c_str()), d.GetAllocator());
        ad.AddMember("adDate", StringRef(obj[k][4].c_str()), d.GetAllocator());
        ad.AddMember("adLocation", StringRef(obj[k][5].c_str()), d.GetAllocator());
        ad.AddMember("adAdress", StringRef(obj[k][6].c_str()), d.GetAllocator());
        ad.AddMember("productPrice", stoi(obj[k][7]), d.GetAllocator());
        ad.AddMember("adFeature", true, d.GetAllocator());
        d.GetArray()[id].GetObject()["Account"].GetObject()["Ads"].PushBack(ad, d.GetAllocator());
    }
    Value History(kObjectType);
    History.AddMember("Adtitle", StringRef(ref[1].c_str()), d.GetAllocator());
    History.AddMember("Date", StringRef(ref[4].c_str()), d.GetAllocator());
    History.AddMember("Price", stoi(ref[7]), d.GetAllocator());
    d.GetArray()[id].GetObject()["Account"].GetObject()["History"].GetArray().PushBack(History, d.GetAllocator());
    int tempactive = d.GetArray()[id].GetObject()["Account"].GetObject()["ActiveAd"].GetInt();
    --tempactive;
    d.GetArray()[id].GetObject()["Account"].GetObject()["ActiveAd"].SetInt(tempactive);
    int tempsold = d.GetArray()[id].GetObject()["Account"].GetObject()["SoldGood"].GetInt();
    tempsold++;
    d.GetArray()[id].GetObject()["Account"].GetObject()["SoldGood"].SetInt(tempsold);
    float temprevenue = d.GetArray()[id].GetObject()["Account"].GetObject()["Revenue"].GetFloat();
    temprevenue += stoi(ref[7]);
    d.GetArray()[id].GetObject()["Account"].GetObject()["Revenue"].SetFloat(temprevenue);
    ofstream of("Userdetail.json");
    OStreamWrapper nof(of);
    Writer<OStreamWrapper> output(nof);
    d.Accept(output);
    of.close();
}
void BuyerDashboard::History()
{
    Excel obj;
    int id = stoi(Personal[0][1]);
    ifstream ifs("Userdetail.json");
    IStreamWrapper isw(ifs);
    Document d;
    d.ParseStream(isw);
    system("clear");
    int x = d.GetArray()[id].GetObject()["Account"].GetObject()["Purchase"].GetArray().Size();
    cout << "Ad Title " << setw(20) << "Category" << setw(20) << "Sell Date " << setw(20) << "Name" << setw(20) << "Price" << endl;
    for (int i = 0; i < x; i++)
    {
        int y = d.GetArray()[id].GetObject()["Account"].GetObject()["Purchase"].GetArray()[i].GetObject()["Adtitle"].GetStringLength();
        int z = d.GetArray()[id].GetObject()["Account"].GetObject()["Purchase"].GetArray()[i].GetObject()["Category"].GetStringLength();
        int w =d.GetArray()[id].GetObject()["Account"].GetObject()["Purchase"].GetArray()[i].GetObject()["Name"].GetStringLength();
        int t = d.GetArray()[id].GetObject()["Account"].GetObject()["Purchase"].GetArray()[i].GetObject()["Price"].GetInt();
        string temp = to_string(t);
        t = temp.length();
        cout << d.GetArray()[id].GetObject()["Account"].GetObject()["Purchase"].GetArray()[i].GetObject()["Adtitle"].GetString();
        cout.width(21-y + z);
        cout << d.GetArray()[id].GetObject()["Account"].GetObject()["Purchase"].GetArray()[i].GetObject()["Category"].GetString();
        cout.width(20-z+8);
        cout << d.GetArray()[id].GetObject()["Account"].GetObject()["Purchase"].GetArray()[i].GetObject()["Date"].GetString();
        cout.width(19-9+11);
        cout << d.GetArray()[id].GetObject()["Account"].GetObject()["Purchase"].GetArray()[i].GetObject()["Name"].GetString();
        cout.width(21 - w + t);
        cout << d.GetArray()[id].GetObject()["Account"].GetObject()["Purchase"].GetArray()[i].GetObject()["Price"].GetInt() << endl;
    }
    cout << endl;
    cout << "--> 1 For Generate Excel File!" << endl;
    cout << "--> 2 For Skip It" << endl;
    int mn;
    cin >> mn;
    switch (mn)
    {
    case 1:
        obj.SetIndex(id);
        obj.ForBuyerReport();
        break;
    default:
        break;
    }
}
int main()
{
    string email, pass;
    int temp;
    bool auth;
    string type;
    string query;

Main:
    Registration Reg;
    Authentications Log;
    Dashboard Obj;
    SellerDashboard Sellers;
    BuyerDashboard Buyer;
    system("clear");
    cout<<"\n\n\n\n\n\n\n\n\n\n\n"<<setw(53);
    cout<<"WELCOME USER"<<endl<<endl<<setw(53);
    cout << "-> Press 1 For Login " << endl<<endl<<setw(54);
    cout << "-> Press 2 For SignUp " << endl<<endl<<setw(48);
    int x;
    cout << "-> Enter Here : ";
    cin >> x;
    switch (x)
    {
    case 1:
        system("clear");
        cout<<"\n\n\n\n\n\n\n\n\n\n\n"<<setw(44);
        cout << "Enter Your Email Here : ";
        cin >> email;
        cout<<endl<<setw(44);
        cout << "Enter Your Password Here : ";
        cin >> pass;
        Log.Login(email, pass);
        system("clear");
        cout<<"\n\n\n\n\n\n\n\n\n\n\n"<<setw(44);
        if(Log.GetAuth() == true){
        system("clear");
        Obj.Information(Log.Index());
        type = Obj.AccountType();
        int swi;
        if (type == "Seller")
        {
            swi = 1;
        }
        else if (type == "Buyer")
        {
            cout << type << endl;
            swi = 2;
        }
        switch (swi)
        {
        case 1:
            Sellers.Information(Log.Index());
        SellerMenu:
            system("clear");
            cout<<"\n\n\n\n\n\n\n\n"<<setw(58);
            cout << "-> Press 1 For Create New Ad!" << endl<<endl<<setw(51);
            cout << "-> Press 2 For My Ads!" << endl<<endl<<setw(48);
            cout << "-> Press 3 Edit Ad!" << endl<<endl<<setw(57);
            cout << "-> Press 4 For Explorer Ads!" << endl<<endl<<setw(73);
            cout << "-> Press 5 For Display Personal Information!" << endl<<endl<<setw(64);
            cout << "-> Press 6 For Account Information!" << endl<<endl<<setw(58);
            cout << "-> Press 7 For Sale's Record!" << endl<<endl<<setw(51);
            cout << "-> Press 8 For Logout!" << endl<<endl<<setw(45);
            cout << "-> Enter Here : ";
            int seller;
            cin >> seller;
            switch (seller)
            {
            case 1:
                system("clear");
            cout<<"\n\n\n\n\n\n\n\n";
                Sellers.createAd();
                cout << "Press 1 To Go Main Menu And 0 For Logout!" << endl;
                int go;
                cin >> go;
                switch (go)
                {
                case 1:
                    goto SellerMenu;
                    break;
                case 0:
                    goto Main;
                    break;
                default:
                    break;
                }
                break;
            case 2:
                system("clear");
                Sellers.myAd();
                cout << "Press 1 To Go Main Menu And 0 For Logout!" << endl;
                cin >> go;
                switch (go)
                {
                case 1:
                    goto SellerMenu;
                    break;
                case 0:
                    goto Main;
                    break;
                default:
                    break;
                }
                break;
            case 3:
                system("clear");
                Sellers.editAd();
                cout << "Press 1 To Go Main Menu And 0 For Logout!" << endl;
                cin >> go;
                switch (go)
                {
                case 1:
                    goto SellerMenu;
                    break;
                case 0:
                    goto Main;
                    break;
                default:
                    break;
                }
                break;
            case 4:
                system("clear");
                Sellers.Listing();
                cout << "--> 1 For By Category!" << endl;
                cout << "--> 2 For Seaching!" << endl;
                cout << "--> 3 For Price Range!" << endl;
                cout << "--> 4 For Main Menu!"<<endl;
                    cout << "Enter Here : ";
                    int fil;
                    cin >> fil;
                    switch (fil)
                    {
                    case 1:
                        Sellers.DisplayCategory();
                        cout << "Enter Here : ";
                        int cat;
                        cin >> cat;
                        Sellers.byCategory(Sellers.Category[cat - 1]);
                        break;
                    case 2:
                        cout << "Enter Your Query Here : ";
                        cin.ignore();
                        getline(cin,query);
                        Sellers.Search(query);
                        break;
                    case 3:
                        cout << "Enter Your Range Here : ";
                        int range;
                        cin >> range;
                        Sellers.Price(range);
                        break;
                    case 4:
                        goto SellerMenu;
                        break;
                    default:
                        break;
                    }
                    cout<<setw(70) << "Press 1 To Go Main Menu And 0 For Logout : " ;
                cin >> go;
                switch (go)
                {
                case 1:
                    goto SellerMenu;
                    break;
                case 0:
                    goto Main;
                    break;
                default:
                    break;
                }
                break;
            case 5:
                system("clear");
                Sellers.PersonalInformation();
                cout<<setw(70) << "Press 1 To Go Main Menu And 0 For Logout : " ;
                cin >> go;
                switch (go)
                {
                case 1:
                    goto SellerMenu;
                    break;
                case 0:
                    goto Main;
                    break;
                default:
                    break;
                }
                break;
            case 6:
                system("clear");
                Sellers.AccountInformation();
                cout <<setw(67)<< "Press 1 To Go Main Menu And 0 For Logout : ";
                cin >> go;
                switch (go)
                {
                case 1:
                    goto SellerMenu;
                    break;
                case 0:
                    goto Main;
                    break;
                default:
                    break;
                }
                break;
            case 7:
                system("clear");
                Sellers.History();
                cout << "Press 1 To Go Main Menu And 0 For Logout!" << endl;
                cin >> go;
                switch (go)
                {
                case 1:
                    goto SellerMenu;
                    break;
                case 0:
                    goto Main;
                    break;
                default:
                    break;
                }
                break;
            case 8:
                goto Main;
                break;
            default:
                break;
            }
            break;
        case 2:
            Buyer.Information(Log.Index());
        BuyerMenu:
            system("clear");
            cout<<"\n\n\n\n\n\n\n\n\n\n\n"<<setw(55);
            cout<<"Buyer Dashboard"<<endl<<endl<<setw(55);
            cout << "--> Press 1 For Explorer Ads!" << "\n\n"<<setw(55);
            cout << "--> Press 2 For My Favourite!" <<  "\n\n"<<setw(50);
            cout << "--> Press 3 For My Cart!" <<  "\n\n"<<setw(71);
            cout << "--> Press 4 For Display Personal Information!" <<  "\n\n"<<setw(62);
            cout << "--> Press 5 For Account Information!" <<  "\n\n"<<setw(50);
            cout << "--> Press 6 For History!" <<  "\n\n"<<setw(49);
            cout << "--> Press 7 For Logout!" <<  "\n\n"<<setw(43);
            cout << "--> Enter Here : ";
            int buyer;
            cin >> buyer;
            switch (buyer)
            {
            case 1:
                system("clear");
                Buyer.Listing();
            Cart:
                int ads;
                cout << "--> Press 1 For Add To Cart!" << endl;
                cout << "--> Press 2 For Add To Favourite!" << endl;
                cout << "--> Press 3 For Apply Filters!" << endl;
                cout << "--> Press 4 For GoTo Main Menu! "<<endl;
                cout << "Enter Here : ";
                cin >> ads;
                switch (ads)
                {
                case 1:
                    Buyer.addToCart();
                    break;
                case 2:
                    Buyer.adToFavourite();
                    break;
                case 3:
                    cout << "--> 1 For By Category!" << endl;
                    cout << "--> 2 For Seaching!" << endl;
                    cout << "--> 3 For Price Range!" << endl;
                    cout << "Enter Here : ";
                    int fil;
                    cin >> fil;
                    switch (fil)
                    {
                    case 1:
                        Buyer.DisplayCategory();
                        cout << "Enter Here : ";
                        int cat;
                        cin >> cat;
                        Buyer.byCategory(Buyer.Category[cat - 1]);
                        goto Cart;
                        break;
                    case 2:
                        cout << "Enter Your Query Here : ";
                        cin >> query;
                        Buyer.Search(query);
                        goto Cart;
                        break;
                    case 3:
                        cout << "Enter Your Range Here : ";
                        int range;
                        cin >> range;
                        Buyer.Price(range);
                        goto Cart;
                    default:
                        break;
                    }
                    break;
                case 4:
                    goto BuyerMenu;
                    break;
                default:
                    break;
                }
                int go;
                cout << "Press 1 To Go Main Menu And 0 For Logout!" << endl;
                cin >> go;
                switch (go)
                {
                case 1:
                    goto BuyerMenu;
                    break;
                case 0:
                    goto Main;
                    break;
                default:
                    break;
                }
                break;
            case 2:
                system("clear");
                Buyer.myFavourite();
                int fav;
                cout << "--> Press 1 For Favourite Item To Cart!" << endl;
                cout << "--> Press 2 For Delete Item From Favourite!" << endl;
                cout << "--> Press 3 For Clear Favourite!" << endl;
                cout << "--> Press 4 For Goto Main Menu!"<<endl;
                cout << "Enter Here : ";
                cin >> fav;
                switch (fav)
                {
                case 1:
                    Buyer.favouriteToCart();
                    break;
                case 2:
                    Buyer.delFavourite();
                    break;
                case 3:
                    Buyer.clearFavourite();
                    break;
                case 4:
                    goto BuyerMenu;
                    break;
                default:
                    break;
                }
                cout << "Press 1 To Go Main Menu And 0 For Logout!" << endl;
                cin >> go;
                switch (go)
                {
                case 1:
                    goto BuyerMenu;
                    break;
                case 0:
                    goto Main;
                    break;
                default:
                    break;
                }
                break;
            case 3:
                system("clear");
                Buyer.myCart();
                int cart;
                cout << "--> Press 1 For Delete Item From Cart!" << endl;
                cout << "--> Press 2 For Clear Cart!" << endl;
                cout << "--> Press 3 For CheckOut!" << endl;
                cout << "--> Press 4 For Go To Main Menu!"<<endl;
                cout << "Enter Here : ";
                cin >> cart;
                switch (cart)
                {
                case 1:
                    Buyer.delCart();
                    break;
                case 2:
                    Buyer.clearCart();
                    break;
                case 3:
                    Buyer.checkOut();
                    break;
                case 4:
                    goto BuyerMenu;
                    break;
                default:
                    break;
                }
                cout << "Press 1 To Go Main Menu And 0 For Logout!" << endl;
                cin >> go;
                switch (go)
                {
                case 1:
                    goto BuyerMenu;
                    break;
                case 0:
                    goto Main;
                    break;
                default:
                    break;
                }
                break;
            case 4:
                system("clear");
                Buyer.PersonalInformation();
                cout <<setw(68) <<"Press 1 To Go Main Menu And 0 For Logout : ";
                cin >> go;
                switch (go)
                {
                case 1:
                    goto BuyerMenu;
                    break;
                case 0:
                    goto Main;
                    break;
                default:
                    break;
                }
                break;
            case 5:
                system("clear");
                Buyer.AccountInformation();
                cout <<setw(68) <<"Press 1 To Go Main Menu And 0 For Logout : ";
                cin >> go;
                switch (go)
                {
                case 1:
                    goto BuyerMenu;
                    break;
                case 0:
                    goto Main;
                    break;
                default:
                    break;
                }
                break;
            case 6:
                Buyer.History();
                break;
            case 7:
                goto Main;
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
        break;
    case 2:
        temp = Reg.GenericSignUp();
        switch (temp)
        {
        case 1:
            Reg.SellerSignUp();
            Reg.SavingData(temp);
            break;
        case 2:
            Reg.BuyerSignUp();
            Reg.SavingData(temp);
        default:
            break;
        }
        goto Main;
        break;
    default:
        break;
    }
    else{
        int go;
        cout<<"\n\n\n\n\n\n\n\n\n\n\n\n"<<setw(60);
        cout<<"Invalid Credentials!"<<"\n\n"<<setw(65);
        cout << "-> Press 1 To Try Again 0 For Exit!" << endl<<endl<<setw(55);
        cout<<"Enter Here : ";
                cin >> go;
                switch (go)
                {
                case 0:
                    break;
                case 1:
                    goto Main;
                    break;
                default:
                    break;
                }
            }
        }
}