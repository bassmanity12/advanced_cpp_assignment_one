#include "Date.h"
#include<time.h>
#include<random>
#include<iostream>
#include<map>
#include<vector>
#include<fstream>
#include<string>
#include<list>
#include<iterator>
#include<algorithm>
using namespace std;

Date::Date()
{
	char MonthNames[12][4] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
	pText = nullptr;
	//time(&Now);
	struct tm Tm;
	//localtime_s(&Tm, &Now);
	//Day = Tm.tm_mday; // 1...31
	//strcpy_s(Month, MonthNames[Tm.tm_mon]); // 0...11
	//iMonth = Tm.tm_mon + 1;
	//Year = Tm.tm_year + 1900; // current year - 1900
}
Date::Date(int d, int m, int y)
{
	SetYear(y);
	SetMonth(m);
	SetDay(d);
}
Date::Date(const Date &Original)
{ // copy constructor
	Day = Original.Day; 
	Year = Original.Year;
	iMonth = Original.iMonth;
	//strcpy_s(Month, Original.Month);
}
Date::~Date()
{
	//destructor
}

bool Date::IsLeap(int y)
{ 
	if (y % 4 == 0)
	{
		if (y % 100 == 0)
		{	// year is divisible by 400, hence the year is a leap year
			if (y % 400 == 0)
				return true;
			else
				return false;
		}
		else
			return true;
	}
	else
		return false;
}
char *Date::ToString() const
{
	(const_cast<Date *>(this))->pText = new char[12];
	sprintf_s(pText, 12, "%02d %s %d", Day, Month, Year);
	return pText;
}
void Date::SetMonth(int m)
{
	if (m < 1 || m > 12)
		 throw "Wrong month";
	//strcpy_s(Month, MonthNames[m - 1]);
	iMonth = m;
}
int Date::GetMonth(char *pBuf, int nBuf) const 
{
	if (!pBuf || nBuf < 4)
		return iMonth;
	//strcpy_s(pBuf, nBuf, Month); 
	return iMonth;
}
void Date::SetYear(int y)  
{
	if (y < 0)
		throw "Wrong year";
	Year = y;
}
void Date::SetDay(int d) 
{
	if (d < 1 || d > 31)
		throw "Wrong day";
	if ((iMonth == 4 || iMonth == 6 || iMonth == 9 || iMonth == 11) && d == 31)
		throw "Wrong day";
	if (iMonth == 2)
	{
		if (IsLeap(Year))
		{
			if (d > 29)
				throw "Wrong day";
		}
		else
		{
			if (d > 28)
				throw "Wrong day";
		}
	}
	Day = d;
}
void Date::SetDate(int d, int m, int y)
{
	SetYear(y);
	SetMonth(m);
	SetDay(d);
}
bool Date::operator==(const Date &other) const
{
	if (Day == other.Day && iMonth == other.iMonth && Year == other.Year)
		return true;
	else
		return false;
}
bool Date::operator<(const Date &other) const
{
	if (Year != other.Year)
		return Year < other.Year;
	if (iMonth != other.iMonth)
		return iMonth < other.iMonth;
	return Day < other.Day;
}
Date &Date::operator=(const Date &Right)
{
	//cout << "operator= called\n";
	if (this == &Right) // & - address operator
		return *this; // necessary for expressions like d1 = *pd where pd points to d1
	Day = Right.Day; 
	Year = Right.Year;
	iMonth = Right.iMonth;
	//strcpy_s(Month, Right.Month);
	return *this;
}
Date Date::CreateRandomDate(Date begin, Date end)
{   // returns a date between begin and end

	tm tm_begin, tm_end;
	memset(&tm_begin, 0, sizeof tm_begin);
	memset(&tm_end, 0, sizeof tm_end);
	tm_begin.tm_mday = begin.GetDay();
	tm_end.tm_mday = end.GetDay();
	tm_begin.tm_mon = begin.GetMonth() - 1;
	tm_end.tm_mon = end.GetMonth() - 1;
	tm_begin.tm_year = begin.GetYear() - 1900;
	tm_end.tm_year = end.GetYear() - 1900;
	time_t lower = mktime(&tm_begin);
	time_t upper = mktime(&tm_end);
	random_device rd; // obtain a random number from hardware
	mt19937 eng(rd()); // seed the generator
	uniform_int_distribution<> distr((unsigned int)lower, (unsigned int)upper);
	time_t time_t_rand = distr(eng);
	tm tm_rand;
	localtime_s(&tm_rand, &time_t_rand);
	return Date(tm_rand.tm_mday, tm_rand.tm_mon + 1, tm_rand.tm_year + 1900);
}
//implementation.
Date d1(1,1,2000);
Date d2(1,1,2010);
Date d3;
class Item:public Date{
public:
char Group; // Any from range 'A'...'Z'
int Subgroup; // Any from range 0...99
string Name; // Any, but not empty
Date Timestamp; // Any
public:
vector<string> str;
	Item(){// Fills the four fields above with preudo-random values
		srand(time(NULL));
		Group=rand()%26+65;
		d3 = CreateRandomDate(d1,d2);
		Timestamp=d3;
		srand(time(NULL));
		Subgroup=rand()%100;
		ifstream read;
		read.open("Birds.txt");
		int i =0;string a;
		while(!read.eof()){ //reading from birds.txt and storing in vector named str.
			getline(read,a);
			auto in= str.insert(str.begin()+i,a);
			i++;
		}
		read.close();
		int j=rand()%(i-1);
		Name=str.at(j);  //assigning random name from the loaded names in memory.
	} 
};
class data:public Item{
public:
	 map<char, map<int, string > > DataStructure;
	data(int n)
	         { // constructor to fill the container with n random items.
				 list<Item>itm(n); //list of objects of item class
		list<Item>::iterator it=itm.begin();
		for(int i=0;i<n;i++)
		{
			DataStructure[it->Group][it->Subgroup]=it->Name;  // filling the container with groups and subgroups pointing to the list having name
			it++;
		}
	  }
    data(){
		data obj; //container will be empty here
	}
	void PrintAll(){
		map<char, map<int, string > >::iterator itr;
		map<int,string>::iterator ptr;
		for (itr = DataStructure.begin(); itr != DataStructure.end(); itr++) { 
  
        for (ptr = itr->second.begin(); ptr != itr->second.end(); ptr++) { 
            cout << "First key is " << itr->first 
                 << " And second key is " << ptr->first 
				 << " And value is " << ptr->second <<endl; 
        } 
	   }
	}
	int CountItems(){
	map<char, map<int, string > >::iterator itr;
		map<int,string>::iterator ptr;
		int a=0;
		for (itr = DataStructure.begin(); itr != DataStructure.end(); itr++) { 
        for (ptr = itr->second.begin(); ptr != itr->second.end(); ptr++) { 
            a++;
        } 
	   }
		return a;
	}
	map<int,string> GetGroup(char c){
	 map<char, map<int, string > >::iterator itr;
	 map<int,string>hello;
	 bool hal=true;
		map<int,string>::iterator ptr;
		for (itr = DataStructure.begin(); itr != DataStructure.end(); itr++) { 
        for (ptr = itr->second.begin(); ptr != itr->second.end(); ptr++) { 
			if(c==itr->first){ 
			cout<<"group found";
			hal=false;
			return hello;
			}
        }
	   }
		if(hal==true)
			cout<<"group not found";
		return hello;
	}
	void PrintGroup(char c){
		bool a=true;
	map<char, map<int, string > >::iterator itr;
		map<int,string>::iterator ptr;
		for (itr = DataStructure.begin(); itr != DataStructure.end(); itr++) { 
        for (ptr = itr->second.begin(); ptr != itr->second.end(); ptr++) { 
			if(c==itr->first){
            cout << "First key is " << itr->first 
                 << " And second key is " << ptr->first 
				 << " And value is " << ptr->second <<endl; 
			a=false;
			}
        } 
	   }
		if(a==true)
			cout<<"group to be printed is not present in the container";
	}
	int CountGroupItems(char c){
		bool hal=true;int a=0;
	map<char, map<int, string > >::iterator itr;
		map<int,string>::iterator ptr;
		for (itr = DataStructure.begin(); itr != DataStructure.end(); itr++) { 
        for (ptr = itr->second.begin(); ptr != itr->second.end(); ptr++) { 
			if(c==itr->first){
            a++;
			hal=false;
        } 
		}
	   }
		if(hal==true){
			return 0;
		}
		if(hal==false)
			return a;
	}
	string GetSubgroup(char c, int i){
	 map<char, map<int, string > >::iterator itr;
		map<int,string>::iterator ptr;
		for (itr = DataStructure.begin(); itr != DataStructure.end(); itr++) { 
        for (ptr = itr->second.begin(); ptr != itr->second.end(); ptr++) { 
			if(c==itr->first&&i==ptr->first){
            return ptr->second; 
			}
        } 
	   }
		return "0";
	}
	void PrintSubgroupByNames(char c, int i){
	map<char, map<int, string > >::iterator itr;
		map<int,string>::iterator ptr;
		for (itr = DataStructure.begin(); itr != DataStructure.end(); itr++) { 
        for (ptr = itr->second.begin(); ptr != itr->second.end(); ptr++) { 
			if(c==itr->first&&i==ptr->first){
				cout<<ptr->second<<endl;
			}
        } 
	   }
	}
	void PrintSubgroupByDates(char c, int i){
	map<char, map<int, string > >::iterator itr;
		map<int,string>::iterator ptr;
		for (itr = DataStructure.begin(); itr != DataStructure.end(); itr++) { 
        for (ptr = itr->second.begin(); ptr != itr->second.end(); ptr++) { 
			if(c==itr->first&&i==ptr->first){
				cout<<ptr->first<<endl;
			}
        } 
	   }
	}
	int CountSubgroupItems(char c, int i){
		int a=0;
	map<char, map<int, string > >::iterator itr;
		map<int,string>::iterator ptr;
		for (itr = DataStructure.begin(); itr != DataStructure.end(); itr++) { 
        for (ptr = itr->second.begin(); ptr != itr->second.end(); ptr++) { 
			if(c==itr->first&&i==ptr->first){
				a++;
			}
        } 
	   }
		return a;
	}
	string GetItem(char c, int i, string s){
	map<char, map<int, string > >::iterator itr;
		map<int,string>::iterator ptr;
		for (itr = DataStructure.begin(); itr != DataStructure.end(); itr++) { 
        for (ptr = itr->second.begin(); ptr != itr->second.end(); ptr++) { 
			if(c==itr->first&&i==ptr->first&&ptr->second==s){
				return ptr->second;
			}
        } 
	   }
		return"not found";
	}
	void PrintItem(char c, int i, string s){
	map<char, map<int, string > >::iterator itr;
		map<int,string>::iterator ptr;
		for (itr = DataStructure.begin(); itr != DataStructure.end(); itr++) { 
        for (ptr = itr->second.begin(); ptr != itr->second.end(); ptr++) { 
			if(c==itr->first&&i==ptr->first&&ptr->second==s){
				cout<< ptr->second;
			}
        } 
	   }
	}
	string InsertItem(char c, int i, string s){
		DataStructure[c][i]=s;
	}
	string InsertSubgroup(char s, int i,string items){
		map<char, map<int, string > >::iterator itr;
		map<int,string>::iterator ptr;
		for (itr = DataStructure.begin(); itr != DataStructure.end(); itr++) { 
        for (ptr = itr->second.begin(); ptr != itr->second.end(); ptr++) { 
			if(i==ptr->first){
				return"already exists";
			}
        } 
	   }
	    DataStructure[s][i]=items;
		return"added subgroup successfully";
	}
	map<int,string> InsertGroup(char c,int subgroups,string items){
		map<int,string> newgroup;
		DataStructure[c][subgroups]=items;
		return newgroup;
	}
	bool RemoveItem(char c, int i, string s){
	map<char, map<int, string > >::iterator itr;
		map<int,string>::iterator ptr;
		for (itr = DataStructure.begin(); itr != DataStructure.end(); itr++) { 
        for (ptr = itr->second.begin(); ptr != itr->second.end(); ptr++) { 
			if(c==itr->first&&i==ptr->first&&ptr->second==s){
				DataStructure.erase(itr->first);
			}
        } 
	   }
	}
	bool RemoveSubgroup(char c, int i){
	map<char, map<int, string > >::iterator itr;
		map<int,string>::iterator ptr;
		for (itr = DataStructure.begin(); itr != DataStructure.end(); itr++) { 
        for (ptr = itr->second.begin(); ptr != itr->second.end(); ptr++) { 
			if(c==itr->first&&i==ptr->first){
				DataStructure.erase(ptr->first);
			}
        } 
	   }
	}
	bool RemoveGroup(char c){
	map<char, map<int, string > >::iterator itr;
		map<int,string>::iterator ptr;
		for (itr = DataStructure.begin(); itr != DataStructure.end(); itr++) { 
        for (ptr = itr->second.begin(); ptr != itr->second.end(); ptr++) { 
			if(c==itr->first){
				DataStructure.erase(itr->first);
			}
        } 
	   }
	}
};
int main()
{
	
	Item obj;
	cout<<"random generated group is: "<<obj.Group;
	cout<<"\nrandom generated subgroup is: "<<obj.Subgroup;
	cout<<"\nrandom generated name is: "<<obj.Name;
	cout<<"\nrandom generated date is: "<<obj.Timestamp.GetDay()<<"-"<<obj.Timestamp.GetMonth()<<"-"<<obj.Timestamp.GetYear();
	cout<<"\n\ndata read from birds.txt and stored in memory is as below:\n\n";
	for(int i=0;i<300;i++)
	cout<<obj.str.at(i)<<endl;
    cout<<"\n\nimplementing container functions:\n";
	data obj1(10);
	obj1.PrintAll();
	int a=obj1.CountItems();
	cout<<endl<<"total items present are: "<<a<<endl;
	cout<<endl;
	obj1.GetGroup('C');
	cout<<endl<<obj1.CountGroupItems('C')<<endl;
	obj1.PrintGroup('C');
	cout<<"\ntotal number of items in group c are: "<<obj1.CountGroupItems('C')<<endl;
	system("pause>0");
return 0;
}

