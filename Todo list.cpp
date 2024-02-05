#include<iostream>
#include<string.h>
using namespace std;

struct Todo
{
	string data;
	Todo *next;
	int priority;
};

Todo *head = nullptr;
Todo *tail = nullptr;

void set_priority(Todo *node, int p)
{
    Todo *temp = head;
    while (temp != nullptr)
    {
        if (p == temp->priority)
        {
            cout << "A task already exists at this priority. Please enter another priority: ";
            cin>>p;
            temp = head;
        }
        else
        {
            temp = temp->next;
        }
    }
    node->priority = p;//set the priority that user enter.
}

void Add(string s, int p)
{
    Todo *element = new Todo;
    element->data = s;
    set_priority(element, p);

    if (head == nullptr || p < head->priority) {     //insertion sort
        element->next = head;
        head = element;
    } else {
        Todo *current = head;
        Todo *prev = nullptr;

        while (current != nullptr && p >= current->priority) {
            prev = current;
            current = current->next;
        }

        prev->next = element;
        element->next = current;
    }

    if (element->next == nullptr) {
        tail = element;
    }
}

void display()
{
	Todo *temp = head;
	if(temp == nullptr)
	{
		cout<<"Woohoo you've got nothing to do!"<<endl;
		cout<<endl;
	}
	else
	{
	cout<<"Your To-do List:"<<endl;
	while(temp!= nullptr)
	{
		cout<<temp->data<<"( "<<temp->priority<<" )"<<endl;
		temp = temp->next;
	}
   }
}

void MarkasDone(int p)
{
    char checkMark = 251; // ASCII code for check mark
    Todo *temp = head;
     while(temp != nullptr)
     {
        if(p == temp->priority)
        {
            temp->data = checkMark +string(" ")+ temp->data;
        }
        temp = temp->next;
     }
}

void update(int k, string s)
{
	char r;
	Todo *temp = head;
	while(temp!=nullptr)
	{
	   if(k == temp->priority)
	   {
	   	  cout<<"Do you want to append to the existing data (y/n): ";
	   	  cin>>r;
	   	  if(r=='y')
	   	  {
	   	  	temp->data.append(s);
		  }
		  else if(r=='n')
		  {
		  	 cout<<"Do you want to add data at the beginning of the existing data (y/n): ";
	   	     cin>>r;
	   	     if(r=='y')
	   	     {
	   	     	temp->data = s + " " + temp->data;
			 }
		  }
		  else
		  {
	   	    temp->data = s;
	      }
	   	  break;
	   }
	   temp = temp->next;
    }
}

void del(int k)
{
    if (head == nullptr)
    {
        cout << "List is empty. Cannot delete." << endl;
        return;
    }

    Todo *temp = head;
    Todo *prev = nullptr;

    
    while (temp != nullptr && temp->priority != k)
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp == nullptr)
    {
        cout << "Node with priority " << k << " not found. Cannot delete." << endl;
        return;
    }

    if (prev == nullptr)
    {
        head = head->next;
        if (head != nullptr) {
            set_priority(head, temp->priority);
        }
        delete temp;

        Todo *current = head;
        while (current != nullptr)
        {
            set_priority(current, current->priority - 1);
            current = current->next;
        }
    }
    else
    {
        
        prev->next = temp->next;
        delete temp;

        Todo *current = prev->next;
        while (current != nullptr)
        {
            set_priority(current, current->priority - 1);
            current = current->next;
        }
    }
}

void search(int p)
{
	Todo *temp = head;
	int found = 0;
	while(temp!=nullptr)
	{
		if(p==temp->priority)
		{
			cout<<"Task found: "<<endl;
			cout<<temp->data<<endl;
			cout<<endl;
			found = 1;
		}
		temp = temp->next;
	}
	if(found==0)
	{
		cout<<"Priority with task "<<p<<" not found"<<endl;
	}
}

int main()
{
	int choice,p;
	string data;
	do
	{
	  cout<<"1: Display"<<endl<<"2: Add"<<endl<<"3: update to-do list"<<endl<<"4: To mark as done "<<endl<<"5: To search "<<endl<<"6: To delete "<<endl<<"0: Exit"<<endl<<"Enter your choice:"<<endl;
	  cin>>choice;
	  cout<<endl;
	  if(choice == 1)
	  {
	    cout<<endl;
	    cout<<endl;
	    display();
	    cout<<endl;
	    cout<<endl;
	  }
	  else if(choice == 2)
	  {
	  	 cout<<"Enter the data:";
	  	 cin.ignore();
	  	 getline(cin,data);
	  	 cout<<"Enter the priority of your task:";
	  	 cin>>p;
	  	 Add(data,p);
	  }
	  else if(choice == 3)
	  {
	  	if(head==nullptr)
        {
    	cout<<"No tasks exist yet!"<<endl;
	    }
	    else
	    {
	  	 cout<<"Enter the priority of the task you want to update:"<<endl;
	  	 cin>>p;
	  	 cin.ignore();
	  	 cout<<"Enter your updated data:";
		 getline(cin,data);
		 update(p,data); 
	    }
	  }
	  else if(choice == 4)
	  {
	  	if(head==nullptr)
        {
    	cout<<"No tasks exist yet!"<<endl;
	    }
	    else
	    {
	  	  cout<<"Enter the priority of the task you want to mark as done:"<<endl;
	  	  cin>>p;
	  	  MarkasDone(p);
	    }
	  }
	  else if(choice == 5)
	  {
	  	if(head==nullptr)
	  	{
	  	   	cout<<"No tasks exist yet!"<<endl;
		}
		else
		{
	  	cout<<"Enter the priority of the task you want to search:"<<endl;
	  	cin>>p;
	  	search(p);
	  }
	  }
	  else if(choice == 6)
	  {
	  	cout<<"Enter the priority of the task you want to delete:"<<endl;
	  	cin>>p;
	  	del(p);
	  }
	  cout<<endl;
    }while(choice != 0);
    cout<<"You have exited the option menu, Goodbye!";
    return 0;
}
