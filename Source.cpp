#include<iostream>
#include<vector>
#include<string>
#include<iomanip>
#include<fstream>
#include<algorithm>
#include<limits>
#include<conio.h>
using namespace std;

//item structure
struct item{string name;int quantity;double price;};

//inventory system
class inventorysystem{
    vector<item> inventory;

    void clearinput(){cin.clear(); cin.ignore(numeric_limits<streamsize>::max(),'\n');}
    string tolowercase(string str){transform(str.begin(),str.end(),str.begin(),[](unsigned char c){return tolower(c);}); return str;}
    
    void loadfromfile(){
        ifstream file("inventory.txt"); if(!file) return;
        item i; while(getline(file,i.name) && file>>i.quantity>>i.price){ file.ignore(numeric_limits<streamsize>::max(),'\n'); inventory.push_back(i);}
        file.close();
    }

    void savetofile(){ofstream file("inventory.txt"); for(const auto &i:inventory){file<<i.name<<endl<<i.quantity<<endl<<i.price<<endl;} file.close();}
    
    bool itemexists(string name){string search=tolowercase(name); for(const auto &i:inventory) if(tolowercase(i.name)==search) return true; return false;}

public:
    inventorysystem(){loadfromfile();} ~inventorysystem(){savetofile();}

    bool adminlogin(){
        string u,p=""; cout<<"===== admin login =====\nusername: "; cin>>u; cout<<"password: ";
        char ch; while((ch=_getch())!=13) if(ch==8){if(!p.empty()){p.pop_back(); cout<<"\b \b";}} else {p+=ch; cout<<"*";} 
        cout<<endl; if(u=="admin"&&p=="12345"){cout<<"login successful!\n"; return true;} cout<<"galat username ya password\n"; return false;
    }

    void additem(){
        item newitem; clearinput(); cout<<"\nitem ka naam enter karein: "; getline(cin,newitem.name);
        if(itemexists(newitem.name)){cout<<"item already exist karta hai!\n"; return;}
        cout<<"quantity enter karein: "; while(!(cin>>newitem.quantity)||newitem.quantity<0) {cout<<"galat input,dobara enter karein: "; clearinput();}
        cout<<"price enter karein: "; while(!(cin>>newitem.price)||newitem.price<0) {cout<<"galat input,dobara enter karein: "; clearinput();}
        inventory.push_back(newitem); savetofile(); cout<<"item successfully add ho gaya!\n";
    }

    void displayinventory(){
        if(inventory.empty()){cout<<"\ninventory khali hai.\n"; return;}
        cout<<"\n========= inventory list =========\n"<<left<<setw(20)<<"name"<<setw(10)<<"qty"<<setw(10)<<"price\n-------------------------------------\n";
        for(const auto &i:inventory) cout<<left<<setw(20)<<i.name<<setw(10)<<i.quantity<<fixed<<setprecision(2)<<"$"<<i.price<<endl;
    }

    void sortinventory(){
        if(inventory.empty()){cout<<"\ninventory khali hai.\n"; return;}
        int opt; cout<<"\nsort by:\n1.name\n2.price\n3.quantity\nchoice: "; cin>>opt;
        if(opt==1) {sort(inventory.begin(),inventory.end(),[&](const item &a,const item &b){return tolowercase(a.name)<tolowercase(b.name);}); cout<<"name ke hisaab se sort ho gaya.\n";}
        else if(opt==2){sort(inventory.begin(),inventory.end(),[](const item &a,const item &b){return a.price<b.price;}); cout<<"price ke hisaab se sort ho gaya.\n";}
        else if(opt==3){sort(inventory.begin(),inventory.end(),[](const item &a,const item &b){return a.quantity<b.quantity;}); cout<<"quantity ke hisaab se sort ho gaya.\n";}
        else cout<<"invalid choice\n";
    }

    void searchitem(){
        string name; clearinput(); cout<<"\nsearch ke liye item ka naam enter karein: "; getline(cin,name);
        string search=tolowercase(name); for(const auto &i:inventory) if(tolowercase(i.name)==search){cout<<"\nitem mil gaya!\nname: "<<i.name<<"\nquantity: "<<i.quantity<<"\nprice: $"<<fixed<<setprecision(2)<<i.price<<endl; return;}
        cout<<"item nahi mila\n";
    }

    void updatequantity(){
        string name; clearinput(); cout<<"\nupdate ke liye item ka naam enter karein: "; getline(cin,name);
        string search=tolowercase(name); for(auto &i:inventory) if(tolowercase(i.name)==search){cout<<"nayi quantity enter karein: "; while(!(cin>>i.quantity)||i.quantity<0){cout<<"galat input,dobara enter karein: "; clearinput();} savetofile(); cout<<"quantity update ho gayi!\n"; return;}
        cout<<"item nahi mila\n";
    }

    void deleteitem(){
        string name; clearinput(); cout<<"\ndelete ke liye item ka naam enter karein: "; getline(cin,name);
        string search=tolowercase(name); for(auto it=inventory.begin(); it!=inventory.end(); ++it) if(tolowercase(it->name)==search){inventory.erase(it); savetofile(); cout<<"item delete ho gaya!\n"; return;}
        cout<<"item nahi mila\n";
    }
};

int main(){
    inventorysystem s; if(!s.adminlogin()) return 0;
    int choice; do{
        cout<<"\n====== inventory management system ======\n1.add item\n2.display inventory\n3.search item\n4.update quantity\n5.delete item\n6.sort inventory\n7.exit\nchoice enter karein: ";
        while(!(cin>>choice)){cout<<"galat input,dobara number enter karein: "; cin.clear(); cin.ignore(numeric_limits<streamsize>::max(),'\n');}
        switch(choice){case 1: s.additem(); break; case 2: s.displayinventory(); break; case 3: s.searchitem(); break; case 4: s.updatequantity(); break; case 5: s.deleteitem(); break; case 6: s.sortinventory(); break; case 7: cout<<"program band ho raha hai...\n"; break; default: cout<<"invalid choice\n";}
    }while(choice!=7); return 0;
}
