// Including Header Files!
#include <iostream>
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
            break;
        }
        if (i == d.GetArray().Size() - 1)
        {
            cout << "Invalid Credentials!" << endl;
            break;
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
    const char *userAttributes[12] = {"fname", "lname", "username", "phoneNumber", "gender", "email", "city", "state", "country", "joinDate", "password"};
    const char *SellerAccountAttribute[7] = {"type", "subscriptopn", "TotalAds", "AllowedAd", "ActiveAd", "SoldGood", "Revenue"};
    const char *sellerAttributes[9] = {"productId", "productTitle", "productDescription", "productCategory", "adDate", "adLocation", "adAdress", "productPrice", "adFeature"};
    string Personal[12][2] = {{"Id ", ""}, {"First Name", ""}, {"Last Name", ""}, {"Username ", ""}, {"Phone Number", ""}, {"Gender", ""}, {"Email", ""}, {"City", ""}, {"State", ""}, {"Country", ""}, {"Joining Date", ""}, {"Password", ""}};
    string Account[7][2] = {{"Type ", ""}, {"Subscription ", ""}, {"TotalAds", ""}, {"Allowed Ads", ""}, {"Active Ads ", ""}, {"Good Solded", ""}, {"Revenue", ""}};
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
    ~Registration()
    {
        cout << "Registered!";
    }
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
        Account.AddMember("subscriptopn", StringRef(Seller::GetSubscription().c_str()), d.GetAllocator());
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
    int x;
    cout << "Enter Your First Name Here : ";
    cin >> fname;
    cout << "Enter Your Last Name Here : ";
    cin >> lname;
    cout << "Enter Your Username Here : ";
    cin >> username;
    cout << "Enter Your Email Here : ";
    cin >> email;
    cout << "Enter Your Password Here : ";
    cin >> pass;
    cout << "Enter Your Phone Number Here : ";
    cin >> phone;
    cout << "Enter Your Gender Here : ";
    cin >> gender;
    cout << "Enter Your City Here : ";
    cin.ignore();
    getline(cin, city);
    cout << "Enter Your State Here : ";
    cin >> state;
    cout << "Enter Your Country Here : ";
    cin >> country;
    cout << "Select Your Account Type " << endl;
    for (int i = 0; i < 3; i++)
    {
        cout << "-> " << i + 1 << " For " << acc[i] << endl;
    }
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
    Seller::SetJoinDate(joindate);
    Seller::SetAccountType(acc[0]);
    int y;
    cout << "Select Your Subscription Plan " << endl;
    for (int i = 0; i < 3; i++)
    {
        cout << "-> " << i + 1 << " For " << sub[i] << endl;
    }
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
    int y;
    cout << "Select Your Subscription Plan " << endl;
    for (int i = 0; i < 3; i++)
    {
        cout << "-> " << i + 1 << " For " << sub[i] << endl;
    }
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
protected:
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
//Filter Class Start Here
class Filter
{
private:
public:
    void Search(string);
    void Price(int, int);
    void Date();
    void byCategory(string);
};
//Filter Class Start Here
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
class Dashboard
{
private:
    bool auth;

public:
    Dashboard()
    {
        auth = false;
    }
    //Protype Of Dashboard Methods
    void LogOut();
    void Information();
    void PersonalInformation();
    void EditInformation();
};
//Dashboard Class End Here

class SellerDashboard : public Dashboard, public Seller, public Ads
{
private:
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
    void selectCategory(int);
};
//Scope Resoluted Class Method Defination
void SellerDashboard::selectCategory(int x)
{
    ProductCategorySetter(Category[x - 1]);
}
void SellerDashboard::createAd()
{
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
    }
    else
    {
        cout << "Your Ad Posting Limit Exceeds!" << endl;
    }
};
//BuyerDashboard Class Start Here
class BuyerDashboard : public Dashboard, public Buyer
{
private:
    // vector<vector<string>> mycart;
    // vector<vector<string>> favourite;

protected:
    string Arr[11] = {"AdId", "AdTitle", "AdDescription", "Category", "UploadDate", "AdLocation", "AdAdress", "AdPrice", "ForAuction", "UploadBy", "PhoneNumber"};

public:
    void explorerAds();
    // void adToFavourite(string, vector<vector<string>> &data);
    // void addToCart(string, vector<vector<string>> &obj);
    void myCart(string);
    void myFavourite(string);
    void delCart(string);
    void checkOut(string);
    void favouriteToCart(string);
    void delFavourite(string);
    void clearCart(string);
    void clearFavourite(string);
    void clearAds(int);
};
int main()
{
    string email, pass;
    int temp;
Main:
    Registration Reg;
    Authentications Log;
    system("clear");
    cout << "Press 1 For Login " << endl;
    cout << "Press 2 For SignUp " << endl;
    int x;
    cout << "Enter Here : ";
    cin >> x;
    switch (x)
    {
    case 1:
        cout << "Enter Your Email Here : ";
        cin >> email;
        cout << "Enter Your Password Here : ";
        cin >> pass;
        Log.Login(email, pass);
        cout << Log.Index() << endl;
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
}