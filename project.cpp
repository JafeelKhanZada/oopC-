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
//Produc Class Start's

class Product
{
private:
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

int main()
{
    Seller obj;
    obj.SetSubscription("Seller");
    cout << obj.GetSubscription() << endl;
    Buyer obj1;
    obj1.SetAccountType("Buyer");
    cout << obj1.GetAccountType() << endl;
    Product obj2;
    obj2.ProductIDGenerator();
    cout<<obj2.GetProductID()<<endl;
}