#include <iostream>
#include <fstream>
using namespace std;

class Student
{
    public:
    char Name[20];
    int Roll;
    float Percentage;
};

class MyFiles
{
private:
    Student studInfo;
public:
    void createFile();
    void addRecords();
    void displayRecords();
    void searchRecord();
    void deleteRecord();
    void modifyRecord();
};

//Function to Create a file if it does not exist already
void MyFiles :: createFile()
{
    ifstream fin;
    fin.open("StudData.dat");
    if(fin)
    {
        cout<<"File already Created!\n";
    }
    else
    {
        ofstream fout;
        fout.open("StudData.dat", ios::app);
        cout<<"StudData.dat File Created Successfully!\n";
    }
    fin.close();
}

//Function to add Data into file
void MyFiles :: addRecords()
{
    ofstream fout;
    fout.open("StudData.dat", ios::app);

    //Taking input from user
    cout<<"Enter Name: ";
    cin>>studInfo.Name;
    cout<<"Enter RollNo: ";
    cin>>studInfo.Roll;
    cout<<"Enter Percentage: ";
    cin>>studInfo.Percentage;

    fout.write((char*)&studInfo, sizeof(studInfo));
    fout.close();
}

//Function to display records from file to console
void MyFiles :: displayRecords()
{
    ifstream fin;
    fin.open("StudData.dat");

    fin.read((char*)&studInfo, sizeof(studInfo));
    cout<<"Name\t\tRoll\t\tPercentage\n";
    while(!fin.eof())
    {
        cout<<studInfo.Name<<"\t\t"<<studInfo.Roll<<"\t\t"<<studInfo.Percentage<<"\n";
        fin.read((char*)&studInfo, sizeof(studInfo));
    }

    fin.close();
}

//Function to Search for a record in file
void MyFiles :: searchRecord()
{
    int searchRoll;

    ifstream fin;
    fin.open("StudData.dat");

    fin.read((char*)&studInfo, sizeof(studInfo));

    cout<<"Enter Roll Number you want to search: ";
    cin>>searchRoll;

    int flag = 0;

    while(!fin.eof())
    {
        if(studInfo.Roll == searchRoll)
        {
            cout<<"\nData found!!\n";
            cout<<"Name\t\tRollNo\t\tPercentage\n";
            cout<<studInfo.Name<<"\t\t"<<studInfo.Roll<<"\t\t"<<studInfo.Percentage<<"\n\n";
            flag = 1;
            break;
        }
        else
        {
            fin.read((char*)&studInfo, sizeof(studInfo));
        }
    }

    if(flag != 1)
    {
        cout<<"Data is NOT PRESENT in the file!\n";
    }

    fin.close();
}

//Funtion to delete a record from the records already exist in original file
void MyFiles :: deleteRecord()
{
    int delRoll;
    ofstream fout;
    fout.open("Copy.dat", ios::app);

    ifstream fin;
    fin.open("StudData.dat");

    fin.read((char*)&studInfo, sizeof(studInfo));

    cout<<"Enter Roll Number to be Deleted: ";
    cin>>delRoll;

    while(!fin.eof())
    {
        if(delRoll != studInfo.Roll)
        {
            fout.write((char*)&studInfo, sizeof(studInfo));
            fin.read((char*)&studInfo, sizeof(studInfo));
        }
        else
        {
            cout<<"\nFollowing Record Deleted Successfully!\n";
            cout<<"Name\t\tRoll\t\tPercentage\n";
            cout<<studInfo.Name<<"\t\t"<<studInfo.Roll<<"\t\t"<<studInfo.Percentage<<"\n";
            fin.read((char*)&studInfo, sizeof(studInfo));
        }
    }

    fin.close();
    fout.close();

    remove("StudData.dat");
    rename("Copy.dat", "StudData.dat");

    cout<<"\nDataBase after Deleting Record is as Follows.\n";
    displayRecords();
}

//Function to Modify an Existing Record
void MyFiles :: modifyRecord()
{
    int modifyRoll;
    ifstream fin;
    fin.open("StudData.dat");

    ofstream fout;
    fout.open("ModiFile.dat");

    fin.read((char*)&studInfo, sizeof(studInfo));

    cout<<"Enter Roll Number of Student whose Data is to be Modified: ";
    cin>>modifyRoll;

    while(!fin.eof())
    {
        if(studInfo.Roll != modifyRoll)
        {
            fout.write((char*)&studInfo, sizeof(studInfo));
            fin.read((char*)&studInfo, sizeof(studInfo));
        }
        else
        {
            int modifyMore;
            do
            {
                int choice;
                cout<<"Record to modify Found!\n";
                cout<<"Which field to modify?\n1)Name\n2)RollNumber\n3)Percentage\n";
                cin>>choice;

                if(choice == 1)
                {
                    cout<<"Enter Modified Name: ";
                    cin>>studInfo.Name;
                }
                else if(choice == 2)
                {
                    cout<<"Enter Modified Roll Number: ";
                    cin>>studInfo.Roll;
                }
                else if(choice == 3)
                {
                    cout<<"Enter Modified Percentage: ";
                    cin>>studInfo.Percentage;
                }

                cout<<"\nDo you want to Modify More Fields? 1)Yes 2)No: ";
                cin>>modifyMore;
            } while (modifyMore == 1);
            fout.write((char*)&studInfo, sizeof(studInfo));
            cout<<"\nRecord Modified Successfully!\n";
            fin.read((char*)&studInfo, sizeof(studInfo));
        }
    }

    fin.close();
    fout.close();

    remove("StudData.dat");
    rename("ModiFile.dat", "StudData.dat");

    cout<<"\nDataBase after Modifying Record is as Follows.\n";
    displayRecords();
}

int main()
{
    MyFiles obj;
    cout<<"----------------------FILE HANDLING----------------------\n";
    while(true)
    {
        int choice;
        cout<<"\nWhich operation to perform?\n1)Add Records\n2)Display Records\n3)Search Record\n4)Delete Record\n5)Modify Record\n6)Exit\n ";
        cin>>choice;

        if(choice == 1)
        {
            cout<<"\n";
            obj.addRecords();
            cout<<"\n";
        }
        else if(choice == 2)
        {
            cout<<"\n";
            obj.displayRecords();
            cout<<"\n";
        }
        else if(choice == 3)
        {
            cout<<"\n";
            obj.searchRecord();
            cout<<"\n";
        }
        else if(choice == 4)
        {
            cout<<"\n";
            obj.deleteRecord();
            cout<<"\n";
        }
        else if(choice == 5)
        {
            cout<<"\n";
            obj.modifyRecord();
            cout<<"\n";
        }
        else if(choice == 6)
        {
            break;
        }
        else
        {
            cout<<"Please Enter A valid Choice!\n";
        }
    }
    
    cout<<"Thank You!\n";

    return 0;
}