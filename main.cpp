#include<iostream>
#include<bits/stdc++.h>
using namespace std;

// This is Global variables
const int MAX_SPECIALIZATION=20;
const int MAX_QUEUE=5;
string names [MAX_SPECIALIZATION+1][MAX_QUEUE+1];
int status [MAX_SPECIALIZATION+1][MAX_QUEUE+1]; // 0 regular , 1 urgent
int queue_length[MAX_SPECIALIZATION+1];		// for each specialization: how many patients so far

int menu()
{
    int  choice =-1;
    while(choice==-1)
    {
        cout << "Enter your choice:"<<endl;
        cout << "1) Add new patient"<<endl;
        cout << "2) Print all patients"<<endl;
        cout << "3) Get next patient"<<endl;
        cout << "4) Exit"<<endl;
        cin >> choice;
    }
    if(!(choice>=1 && choice<=4))
    {
        cout<<"invalid choice. Plz, tray again"<<endl;
        choice =-1;
    }
    return choice;
}
// Move each patient to the left. E.g if patient in position 5, it will be in 4
// Help in removing patient
void shift_left(int spec, string names_sp[], int status_sp[])
{
    int len=queue_length[spec];
    for (int i = 1; i < len; ++i)
    {
        names_sp[i-1] = names_sp[i]; // shift left
        status_sp[i-1] = status_sp[i];
    }
    queue_length[spec]--;

}
// If the patient's condition is urgent, he will be in the first place (position 0).
// Move each patient to the right. E.g if patient in position 5, it will be in 6
// Help in adding patient
void shift_right(int spc, string names_sp[], int status_sp[])
{
    int len = queue_length[spc];
    for (int i  =len-1;  i <0 ; i++)
    {
        names_sp[i+1] = names_sp[i];
        status_sp[i+1] = status_sp[i];
    }
    queue_length[spc]++;
}


bool add_new_patient()
{
    int spc, stat ;
    string name;
    cout<< "Enter your Specialization , Name and Status";
    cin >> spc >> name >> stat;
    int pos=queue_length[spc];
    if (pos>MAX_QUEUE)
    {
        cout << "Sorry we can't add more patients for this specialization"<<endl;
        return false;
    }
    if (stat==0) // regular, add to end
    {
        names[spc][pos]=name;
        status[spc][pos]=stat;
        queue_length[spc]++;
    }
    else // urgent, add to begin. Shift, then add

        // urgent, add to begin. Shift, then add
    {
        shift_right(spc, names[spc], status[spc]);
        names[spc][0]=name;
        status[spc][0]=stat;
    }
    return true;
}
void print_patient(int spc, string names_sp[], int status_sp[])
{
    int len = queue_length[spc];
    if (len == 0)
    {
        return;
    }
    cout << "There are " << len << " patients in specialization " << spc  << endl;

    for(int i =0; i<len;  i++)
    {
        cout << names_sp[i]<<" ";
        if (status_sp[i])
            cout << "urgent"<<endl;
        else
            cout << "regular"<<endl;
    }
    cout <<endl;
}


void print_patients()
{
    cout << "****************************\n";
    for(int spc =0; spc<MAX_SPECIALIZATION; spc++)
    {
        print_patient(spc,names[spc],status[spc]);
    }
}
void get_next_patients()
{
    int spc;
    cout << "Enter specialization: ";
    cin>>spc;
    int len = queue_length[spc];
    if (len ==0)
    {
        cout<<"No patients at the moment. Have rest, Dr"<<endl;
        return;
    }
    cout << names[spc][0]<< "Go with the Dr"<<endl;
    shift_left(spc, names[spc],status[spc]); 	// delete the patient in position 0

}


void hospital_system()
{
    while(true)
    {
        int choice = menu();

        if (choice==1)
            add_new_patient();
        else if (choice == 2)
            print_patients();
        else if (choice == 3)
            get_next_patients();
        else
            break;
    }
}
int main()
{
    hospital_system();
    return 0;
}
