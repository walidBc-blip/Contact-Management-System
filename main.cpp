
//=================================================================================
// Name         : DS Assignment#3
// Author       :
// Version      : 1.0
// Date Created : 03-20-2022
// Date Modified:
// Description  : Starter Code for Contact Management System using BST Tree in C++
// Copyright © 2022 Khalid Mengal and Mai Oudah. All rights reserved.
//=================================================================================
#include<iostream>
#include<cstdlib>
#include<sstream>
#include<fstream>

using namespace std;
//==========================================================
class Contact
{
    private:
        string fname;
        string lname;
        string email;
        string primaryPhone;
        string city;
        string country;
        bool isFav;

    public:
        Contact(string fname, string lname, string email, string primaryPhone, string city, string country, bool isFav)
        {
            this->fname = fname;
            this->lname=lname;
            this->email=email;
            this->primaryPhone=primaryPhone;
            this->city=city;
            this->country=country;
            this->isFav=isFav;
        }
    
        void display()
        {
            cout<<"\n Firstname :"<<fname<<"\n Lastname :"<<lname<<"\n Email :"<<email<<"\n Phone :"<<primaryPhone<<"\n City :"<<city<<"\n Country :"<<country<<"\n Favorite :"<<isFav<<endl;
            
        }
    
        void displayData()
        {
            cout<<fname<<","<<lname<<","<<email<<","<<primaryPhone<<","<<city<<","<<country<<","<<isFav<<endl;
        }
    
        void updateFname(string x)
        {
            fname = x;
        }
        void updateLname(string x)
        {
            lname = x;
        }
        void updateEmail(string x)
        {
            email = x;
        }
        void updatePhone(string x)
        {
            primaryPhone = x;
        }
        void updateCity(string x)
        {
            city = x;
        }
        void updateCountry(string x)
        {
            country = x;
        }
       
        void markFav()
        {
            isFav = true;
        }
    
        void unmarkFav()
        {
            isFav = false;
        }
    
        bool checkFav()
        {
            return (isFav == true);
        }
    
        string getFname()
        {
            return fname;
        }
        string getLname()
        {
            return lname;
        }
        string getEmail()
        {
            return email;
        }
        string getCity()
        {
            return city;
        }
        string getPhone()
        {
            return primaryPhone;
        }
        string getCountry()
        {
            return country;
        }
        bool getFav()
        {
            return isFav;
        }
    
        //added this later
        Contact()
        {
            
        }
        
};

//==========================================================
typedef Contact elem;

template<typename T>
class MyVector
{
public:
    MyVector()
    {
        a = new T[0];
        capacity = 0;
        n = 0;
    }
    int size() const {  return n; }
    
    bool empty() const { return n == 0 ; }
    
    //exceptions
    elem& operator[] (int i) { return a[i]; };
    
    elem& at(int i) { return a[i]; };
    
    //exceptions
    void erase(int i)
    {
        for (int j = i; j < n; j++)
        {
            a[j] = a[j+1];
        }
         n--;
    }
    //exceptions
    void insert(int i , const elem& e )
    {
        if (n == capacity)
            reserve( max(1, 2 * capacity) );
        
        if (!empty())
        for ( int j = n - 1 ; j >= i ; j--)
        {
            a[j+1] = a[j];
            
        }
        
        a[i] = e;
        n++;
          
        
    }
    void reserve(int size)
    {
       if (capacity >= size)
           return;
        
        elem* b = new elem [size];
        
        for (int i = 0; i < n; i++)
            b[i] = a[i];
        
        if (a!= NULL) delete [ ] a;
        a = b;
        capacity = size;
    }
    
    void display()
    {
        cout<<"\n "<<n<<" Records found :";
        for (int i = 0; i < n ; i ++)
        {
            cout<<endl<<endl<<" "<<i+1<<".";
            at(i).display();
        }
        
    }
    
private:
    int capacity;
    int n;
    elem* a;
    
};

//==========================================================
class Node
{
    private:
        string key;
        MyVector<Contact>* contactVector;
        Node* left;
        Node* right;
    public:
        Node(string key, MyVector<Contact>* contactVector)
        {
            this->key = key;
            this->contactVector = contactVector;
            this->left = nullptr;
            this->right = nullptr;
            
        }
        ~Node();
        string getKey() { return this->key;}
        MyVector<Contact>* getData() { return this->contactVector;}
        friend class ContactBST;
};

//=============================================================================
class ContactBST
{
    private:
        Node* root;
    public:
        ContactBST()
        {
            this->root=nullptr;
        }
        ~ContactBST()
        {
            //Keep removing the root of the tree untill it becomes empty
            while(root)
                root=del(root,root->key);
        }
        Node* getRoot() { return root; }                    //returns the root of the Tree
        Node* add(Node* ptr,string key, Contact* data) ;    //add key into tree/subtree with root ptr
        Node* update(Node* ptr, string key);                //Edit the node with key
        Node* del(Node* ptr,string key);                    //Delete a node with key from the tree/subtree with root
        Node* search(Node* ptr,string key);                 //Find and returns the node with key
    
        bool markFav(Node* ptr, string key);  //Mark a contact as favorite
        bool unmarkFav(Node* ptr, string key);  //Unmark a contact as favorite
        void printASC(Node* ptr);            //Print the data at nodes in an ascending order
        void printDES(Node* ptr);            //Print the data at nodes in a descending order
        void printFav(Node* ptr);           //Print the favorite data at nodes in an ascending order
        int importCSV(Node* ptr, string path); //Load all the contacts from the CSV file to the BST
        int exportCSV(Node* ptr, string path); //Export all the contacts from the BST to a CSV file in an ascending order

    public:    //helper methods
        void insert_helper(string key, Contact* data);  //Helper method for insert method
        void remove_helper(string key);  //Helper method for remove method
    
        // added later
        Node* findMin(Node*ptr);
    
    private:
        void printTreeHelper(string* A, bool* B, Node* ptr, int n); //Helper method for PrintTree()
};


//==========================================================
void listCommands()
{
    cout<<endl<<"----------------------------------"<<endl;
    cout<<"import <path>      :Import contacts from a CSV file"<<endl
        <<"export <path>      :Export contacts to a CSV file"<<endl
        <<"add                :Add a new contact"<<endl
        <<"edit <key>         :Update a contact's details"<<endl
        <<"del <key>          :Delete a contact"<<endl
        <<"searchFor <key>    :Search for a contact"<<endl
        <<"markfv <key>       :Mark as favourite"<<endl
        <<"umarkfv <key>      :Unmark as favourite"<<endl
        <<"printASC           :Print contacts in ascending order"<<endl
        <<"printDES           :Print contacts in descending order"<<endl
        <<"printfv            :Print all favourite contacts"<<endl
        <<"help               :Display the available commands"<<endl
        <<"exit               :Exit the program"<<endl;
}
//==========================================================

void ContactBST::insert_helper(string key, Contact* data)  //Helper method for insert method
{
    Node* ptr = getRoot();
    root = add( ptr , key, data);
}

void ContactBST::remove_helper(string key)
{
    Node* ptr = getRoot();
    root = del (ptr, key);
    
    //cout<<"\n Contact deleted successfully!";
}

Node* ContactBST::add(Node* ptr,string key, Contact* data)
{
    
    if (ptr == nullptr)
    {
        MyVector<Contact>* myVector  = new MyVector<Contact>;
        myVector->insert(0, *data);
        ptr = new Node (key, myVector);
        
        return ptr;
    }
    
    else if (ptr->key == key)
    {
        
        MyVector<Contact>* temp = ptr->getData();
        int i = temp->size();
        temp->insert(i, *data);
        
        return ptr;
        
    }

    // if the key is smaller then the new node is added to ptr->left and the edge is refreshed
    else if (key < ptr->key)
    {
        ptr -> left = add(ptr->left, key , data);
    }

    else if (key > ptr->key)
    {
        ptr -> right = add(ptr->right, key, data);
    }
    
    
    return ptr;
    
}

Node* ContactBST::findMin(Node*ptr)
{
    if ( ptr -> left == nullptr )
        return ptr;
    
    else
        return findMin(ptr->left);
    
}

Node* ContactBST::del(Node* ptr,string key)
{
    if (ptr != nullptr)
    {
        if(ptr->key == key && ptr->getData()->size() != 1)
        {
            ptr->getData()->display();
            string i;
            cout<<"\n Please select the record you want to delete :";
            getline(cin,i);
            ptr->getData()->erase(stoi(i)-1);
            
        }
        
        
        // if the node has no children
        else if (ptr->key == key && ptr-> left == nullptr && ptr->right == nullptr )
            return nullptr;
        
        //if only one left child
        else if ( ptr->key == key && ptr->right == nullptr )
            return ptr->left;
        
        //if only one right child
        else if ( ptr->key == key && ptr->left == nullptr )
            return ptr->right;
        
        // if two children then we swap with the right min and then remove that node
        else if ( ptr->key == key )
        {
            string temp = findMin(ptr->right)->getKey();
            MyVector<Contact>* tempVector = findMin(ptr->right)->getData();
            
            del( ptr ,temp);
            
            ptr->key = temp;
            ptr->contactVector = tempVector;
            
            return ptr;
        }
        
        // does not remove anything if the left end of the tree has been reached and the key has not been found
        else if ( key < ptr->key && ptr->left != nullptr)
            ptr -> left = del( ptr->left , key);
        
        else if (key > ptr->key && ptr->right!= nullptr)
            ptr -> right = del( ptr->right, key);
    }
    
    //cout<<"\n Contact not found!";
    return ptr;
    
}

Node* ContactBST::search(Node* ptr,string key)
{
    if( ptr!= nullptr )
    {
        if (ptr->key == key)
        {
            MyVector<Contact>* temp = ptr->getData();
            temp->display();
            
            return ptr;
        }
        // if the key to be searched is smaller we search the left side
        else if(ptr->key > key && ptr->left != nullptr)
            return search(ptr->left, key);
        
        // if the key is bigher search the right side
        else if (ptr->key < key && ptr->right != nullptr)
            return search(ptr->right, key);
        
    }
   
        return nullptr;
    
}

Node* ContactBST::update(Node* ptr, string key)
{
    if( ptr!= nullptr)
    {
        if (ptr->key == key)
        {
            MyVector<Contact>* temp = ptr->getData();
            temp->display();
            
            string i;
            cout<<"\n Please select the record you want to edit :";
            getline(cin,i);
            
            string choice;
            string x;
            string ch;
            
            while(true)
            {
                cout<<"\n Which field do you want to edit 1) first name, 2) last name, 3) email, 4) primaryPhone, 5) city, or 6) country :";
                getline(cin,choice);
                
                cout<<"Enter value to be updated :";
                getline(cin,x);
                
                if(choice == "1")
                    ptr->getData()->at(stoi(i) - 1).updateFname(x);
                else if (choice == "2")
                    ptr->getData()->at(stoi(i) - 1).updateLname(x);
                else if (choice == "3")
                    ptr->getData()->at(stoi(i) - 1).updateEmail(x);
                else if (choice == "4")
                    ptr->getData()->at(stoi(i) - 1).updatePhone(x);
                else if (choice == "5")
                    ptr->getData()->at(stoi(i) - 1).updateCity(x);
                else if (choice == "6")
                    ptr->getData()->at(stoi(i) - 1).updateCountry(x);
                
                cout<<"\n Do you want to edit another field (y/n)?";
                getline(cin,ch);
                
                if(ch == "n")
                    break;
                
            }
            
            string newKey = ptr->getData()->at(stoi(i) - 1).getFname() + " " + ptr->getData()->at(stoi(i) - 1).getLname() ;
            
            if ( (ptr->getData()->size() == 1) && (newKey != ptr->key) )
            {
                Contact * data  =  new Contact();
                *data = ptr->getData()->at(stoi(i)-1);
                
                insert_helper(newKey, data );
                remove_helper(key);
  
            }
            
            else
            {
                Contact * data  =  new Contact();
                *data = ptr->getData()->at(stoi(i)-1);
                
                insert_helper(newKey, data );
                ptr->getData()->erase(stoi(i)-1);
            }
                
            
            return ptr;
        }
        // if the key to be searched is smaller we search the left side
        else if(ptr->key > key && ptr->left != nullptr)
            return update(ptr->left, key);
        
        // if the key is bigher search the right side
        else if (ptr->key < key && ptr->right != nullptr)
            return update(ptr->right, key);
        
    }
   
        return nullptr;
    
}


bool ContactBST::markFav(Node* ptr, string key)
{
    string i;
    ptr = search(ptr, key);
    
    if (ptr == nullptr)
        return 0;
    else
    {
        MyVector<Contact>* temp = ptr->getData();
        
        if( temp->size() != 1 )
        {
            cout<<"\n Please select the record you want to mark as favorite :";
            getline(cin,i);
            temp->at(stoi(i)-1).markFav();
        }
        
        else
            temp->at(0).markFav();
        
        return 1;
    }
}

bool ContactBST::unmarkFav(Node* ptr, string key)
{
    string i;
    ptr = search(ptr, key);
    
    if (ptr == nullptr)
        return 0;
    else
    {
        MyVector<Contact>* temp = ptr->getData();
        
        if( temp->size()!=1 )
        {
        cout<<"\n Please select the record you want to unmark as favorite :";
        getline(cin,i);
        temp->at(stoi(i)-1).unmarkFav();
        }
        
        else
            temp->at(0).unmarkFav();
        
        return 1;
    }
}

void ContactBST::printASC(Node* ptr)
{
    // if pointer reaches nullpthr then return
    if (ptr == nullptr)
        return;
    
    else
    {
        //goes to left end first
        printASC(ptr->left);
        
        //prints and then goes to the right and then moves back towards the top
        MyVector<Contact> * temp = ptr->getData();
        for (int i = 0; i < temp->size() ; i++ )
            temp->at(i).displayData();
        
        printASC(ptr->right);
        
    }

}

void ContactBST::printDES(Node* ptr)
{
    // if pointer reaches nullpthr then return
    if (ptr == nullptr)
        return;
    
    else
    {
        printDES(ptr->right);
        
        MyVector<Contact> * temp = ptr->getData();
        for (int i = 0; i < temp->size() ; i++ )
            temp->at(i).displayData();
        
        printDES(ptr->left);
        
    }
    
    
}

void ContactBST:: printFav(Node* ptr)
{
    if (ptr == nullptr)
        return;
    
    else
    {
        //goes to left end first
        printFav(ptr->left);
        
        //prints and then goes to the right and then moves back towards the top
        MyVector<Contact> * temp = ptr->getData();
        for (int i = 0 ; i < temp->size() ; i++ )
        {
            if ( temp->at(i).checkFav() )
                temp->at(i).displayData();
        }
        
        printFav(ptr->right);
        
    }
}


int ContactBST::importCSV(Node* ptr, string path)
{
    ifstream f1;
    string x;
    int count = 0;
    
    f1.open(path, ios::in);

    while( getline(f1,x) )
    {
        
        string fname= "",  lname="",  email="", primaryPhone="",  city="",  country="";
        bool isFav;
        
        int check = 0;
        
        for ( int i = 0 ; i< x.length() ; i++)
            
        {
            if ( check == 0 && x[i] != ',' )
            {
                fname += x[i];
            }
            
            else if ( check == 1 && x[i] != ',' )
            {
                lname += x[i];
            }
            
            else if ( check == 2 && x[i] != ',' )
            {
                email += x[i];
            }
            
            else if ( check == 3 && x[i] != ',' )
            {
                primaryPhone += x[i];
            }
            
            else if ( check == 4 && x[i] != ',' )
            {
                city += x[i];
            }
            
            else if ( check == 5 && x[i] != ',' )
            {
                country += x[i];
            }
            
            else if ( check == 6 && x[i] != ',')
            {
                if( x[i] == '1')
                    isFav = true;
                else
                    isFav = false;
          
                Contact* data = new Contact(fname,  lname,  email, primaryPhone,  city,  country, isFav);
                string key = fname + " " + lname;
                insert_helper( key , data);
                check = 0;
                count++;
                
            }
            
            if (x[i] == ',')
                check++;
                
        }
        
    }
    
    if (count == 0)
        return -1;
    
    else
        return count;
}


int ContactBST::exportCSV(Node* ptr, string path)
{
  
    int count = 0;
    ofstream f1;
  
    f1.open(path, ios::app);
    
    if (ptr == nullptr)
        return 0;

    else
    {
        count += exportCSV( ptr->left, path);
  
        MyVector<Contact> * temp = ptr->getData();
        
        for (int i = 0; i < temp->size() ; i++ )
        { f1<<temp->at(i).getFname()<<","<<temp->at(i).getLname()<<","<<temp->at(i).getEmail()<<","<<temp->at(i).getPhone()<<","<<temp->at(i).getCity()<<","<<temp->at(i).getCountry()<<","<<temp->at(i).getFav()<<endl;
        
            count++;
        }
        count += exportCSV(ptr->right, path);
        
    }
    
    f1.close();
    
    return count;
}
// to be completed with all the necessary method definitions

//==========================================================
int main(void)
{
    ContactBST myContactBST;
    MyVector<Contact> myVector;

    listCommands();
    
    string user_input;
    string command;
    string key;
    //string choice;
    
    while(true)
    {
        cout<<endl<<">";
        getline(cin,user_input);

        // parse userinput into command and parameter(s)
        stringstream sstr(user_input);
        getline(sstr,command,' ');
        getline(sstr,key);
        
        
        if( command == "import" )
        {
            Node* ptr = myContactBST.getRoot();
            cout<<myContactBST.importCSV( ptr, key );
        }
        
        else if (command == "export")
        {
            ofstream f1;
            f1.open(key, ios::out);
            
            Node* ptr = myContactBST.getRoot();
            cout<<myContactBST.exportCSV( ptr, key );
        }
        
        else if(command == "add")
        {
            string fname,  lname,  email, primaryPhone,  city,  country;
            string fav;
            bool isFav;
            
            cout<<"Enter Details: ";
            getline(cin,fname);
            getline(cin,lname);
            getline(cin,email);
            getline(cin,primaryPhone);
            getline(cin,city);
            getline(cin,country);
            getline(cin,fav);
            
            if(fav == "y")
                isFav = true;
            else
                isFav = false;
            
            
            Contact* data = new Contact(fname,  lname,  email, primaryPhone,  city,  country, isFav);
            
            string key = fname + " " + lname;
            
            myContactBST.insert_helper( key , data);
            
            cout<<"\n Contact has been successfully added!";
        }
        
        
        else if (command == "del")
        {
            myContactBST.remove_helper(key);
        }

        // fix key format later
        else if (command == "search")
        {

            Node* ptr = myContactBST.getRoot();
            ptr = myContactBST.search(ptr, key);
            
            if (ptr == nullptr)
                {
                    cout<<"\n Contact not found!";
                }
            
        }
        
        else if (command == "edit")
        {
            
            Node* ptr = myContactBST.getRoot();
            
            ptr = myContactBST.update(ptr, key);
    
            if (ptr == nullptr)
                {
                    cout<<"\n Contact not found!";
                }
            
        }
        
        else if (command == "markfv")
        {
            Node* ptr = myContactBST.getRoot();
            
            if ( myContactBST.markFav( ptr, key) )
                cout<<endl<<key<<" has successfuly been marked as favorite.";
            
            else
                cout<<"\n Contact not found!";
        }
        
        else if (command == "umarkfv")
        {
            Node* ptr = myContactBST.getRoot();
            
            if ( myContactBST.unmarkFav( ptr, key) )
                cout<<endl<<key<<" has successfuly been unmarked as favorite.";
            
            else
                cout<<"\n Contact not found!";
        }
       
        else if (command == "printASC")
        {
            Node *ptr = myContactBST.getRoot();
            myContactBST.printASC(ptr);
            
        }
        
        else if (command == "printDES")
        {
            Node *ptr = myContactBST.getRoot();
            myContactBST.printDES(ptr);
            
        }
        
        else if (command == "printfv")
        {
            Node *ptr = myContactBST.getRoot();
            myContactBST.printFav(ptr);
        }
        
        else if (command == "help")
            listCommands();
        
        else if(command == "exit")
            break;
        
        else
            cout<<"\n Invalid Command";
        
    }

    return 0;
}


