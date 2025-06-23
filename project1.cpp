#include <iostream>
#include <bits/stdc++.h>
using namespace std;
bool changesMade = false; // ideas-
class Student
{                // 1-make a function to create new file(also renameing like english_marks)                                                     //2-make lowercase function(check if needed - donot think needed now)
    string Name; // 3-data transfer between files possible(ex-newfile=maths_marks just update marks)
    int RollNo;
    double Marks;

public:
    Student(string name1, int rollNo1, double marks1)
    {
        Name = name1;
        RollNo = rollNo1;
        Marks = marks1;
    }
    void setName(string name)
    {
        Name = name;
    }
    void setRollNo(int rollno)
    {
        RollNo = rollno;
    }
    void setMarks(double marks)
    {
        Marks = marks;
    }
    string getName(void) const
    {
        return Name;
    }
    double getMarks(void) const
    {
        return Marks;
    }
    int getRollNo(void) const
    {
        return RollNo;
    }
};
void handleInputError()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    throw string("Not a Valid input");
}

int getValidatedInput()
{
    int input;
    cin >> input;
    if (cin.fail())
        handleInputError();
    return input;
}
double getValidatedDoubleInput()
{
    double input;
    cin >> input;
    if (cin.fail())
        handleInputError();
    return input;
}

void toLower(string &str)
{
    transform(str.begin(), str.end(), str.begin(), ::tolower);
}

bool studentAlreadyExists(vector<Student> &students, int rollno)
{
    for (int i = 0; i < students.size(); i++)
    { // checks if rollno already exists
        if (students[i].getRollNo() == rollno)
        {
            return true;
        }
    }
    return false;
}

string getValidatedName() {
    string name;
    while (true) {
        getline(cin, name);
        name.erase(0, name.find_first_not_of(" \t\n\r\f\v")); // Left trim by giving index of first not space,\t,\n.... then erase
        name.erase(name.find_last_not_of(" \t\n\r\f\v") + 1); // Right trim last index of first not space,\t,\n.... then erase
        if (name.empty()) {
            cout << "Name cannot be empty or just spaces" << endl;
            cout << "Try name again" << endl;
        } else {
            break;
        }
    }

    toLower(name); 
    return name;
}

void loadDataToRam(vector<Student> &students)
{                                                                               // vector acts as RAM
    ifstream in;
    in.open("student_record.txt");
    string line;
    while (getline(in, line))
    {
        if (line.empty() || line.length() < 20)
            continue;                                                           // prevents crashing if someone left blank space
        size_t namepos = line.find("name: ");                                   // at starting of document when it was empty
        size_t rollpos = line.find(" rollNo: ");
        size_t markspos = line.find(" marks: ");                                // guarented to find these unless empty as are inserted by code not user input
        string name = line.substr(namepos + 6, rollpos - namepos - 6);
        int roll_no = stoi(line.substr(rollpos + 9, markspos - rollpos - 9));
        double marks = stod((line.substr(markspos + 8)));
        students.push_back(Student(name, roll_no, marks));
    }
    in.close();
}

void clearFile(void)
{
    ofstream out;
    out.open("student_record.txt", ios::trunc);
    out.close();
}

void addStudent(vector<Student> &students)
{                                                                                   // if 1 pressed
    bool flag = false;
    string name;
    int roll_no;
    double marks;
    while (flag == false)
    {
        cout << "Enter student_name, roll_no , marks repectively" << endl; // ingnores all spaces till /n before getline
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        name = getValidatedName();
        cout << "Enter rollNo" << endl;
        while (true)
        {
            try
            {
                roll_no = getValidatedInput();
                bool alreadyExist = studentAlreadyExists(students, roll_no);
                if (alreadyExist)
                {
                    cout << "A student with this rollno already exist" << endl;
                    cout << "try rollno again" << endl;
                }
                if (!alreadyExist)
                    break;
            }
            catch (string err)
            {
                cout << "Error: " << err << endl;
                cout << "try roll_No again" << endl;
                cout << endl;
            }
        }
        cout << "Enter Marks" << endl;
        while (true)
        {
            try
            {
                marks = getValidatedDoubleInput();
                if(marks>100) throw string("Marks cannot be greater than 100");
                else break;
            }
            catch (string err)
            {
                cout << "Error: " << err << endl;
                cout << "try marks again" << endl;
                cout << endl;
            }
        }
        while (true)
        {
            try
            {
                cout << "please press 0 to confirm and 1 to cancel" << endl;
                int confirm = getValidatedInput();
                if (confirm == 0)
                {
                    flag = true;
                    changesMade = true;
                    students.push_back(Student(name, roll_no, marks));
                    break;
                }
                else if (confirm == 1)
                {
                    cout << "cancelled" << endl;
                    cout << endl;
                    flag = true;
                    break;
                }
                else
                {
                    throw string("value outside menu range");
                }
            }
            catch (string err)
            {
                cout << "Error: " << err << endl;
                cout << endl;
            }
        }
    }
    cout << endl;
}

bool getStudentInfo(const vector<Student> &students, string name)
{                                                                                        // if 2 pressed
    bool found = false;
    for (int i = 0; i < students.size(); i++)
    {
        if (students[i].getName() == name)
        {
            found = true;
            cout << "Name: " << students[i].getName() << " "
                 << "Roll No: " << students[i].getRollNo() << " "
                 << "marks: " << students[i].getMarks() << endl;
        }
    }
    if (found == false)
    {
        cout << "Student not found" << endl;
        cout << "press 1 to try again" << endl;
        cout << "anything else to return to main menu" << endl;
        try
        {
            int inp = getValidatedInput();
            if (inp != 1)
            {
                found = true;
            }
        }
        catch (string err)
        {
            found = true;
        }
    }
    cout << endl;
    return found;
}

int getStudentInfoRollno(const vector<Student> &students)
{
    int rollno;
    bool found = false;
    while (!found)
    {
        cout << "Enter the roll No of student" << endl;
        while (true)
        {
            try
            {
                rollno = getValidatedInput();
                break;
            }
            catch (string err)
            {
                cout << "Error: " << err << endl;
                cout << "try roll_No again" << endl;
                cout << endl;
            }
        }
        for (int i = 0; i < students.size(); i++)
        {
            if (students[i].getRollNo() == rollno)
            {
                found = true;
                cout << "Name: " << students[i].getName() << " "
                     << "Roll No: " << students[i].getRollNo() << " "
                     << "marks: " << students[i].getMarks() << endl;
                cout << endl;
                return i;
            }
        }
        cout << "this rollno donot exist" << endl;
        cout << "press 1 to try again" << endl;
        cout << "anything else to return to main menu" << endl;
        try
        {
            int inp = getValidatedInput();
            if (inp != 1)
            {
                found = true;
            }
        }
        catch (string err)
        {
            found = true;
        }
    }
    cout << endl;
    return -1;
}

void clearStudentRecord(vector<Student> &students)
{                                                                                   // if 3 pressed
    int found = getStudentInfoRollno(students);
    if (found != -1)
    {
        while (true)
        {
            try
            {
                cout << "do u want to remove this student" << endl;
                cout << "press 0 to confirm and 1 to cancel" << endl;
                int inp = getValidatedInput();
                if (inp == 0)
                {
                    students.erase(students.begin() + found);
                    changesMade = true;
                    cout << "student data erased" << endl;
                    cout << endl;
                    return;
                }
                else if (inp == 1)
                {
                    cout << "cancelled" << endl;
                    cout << endl;
                    return;
                }
                else
                {
                    throw string("value outside menu range");
                }
            }
            catch (string err)
            {
                cout << "Error: " << err << endl;
                cout << endl;
            }
        }
    }
    cout << endl;
}

void seeWholeRecord( const vector<Student> &students)
{                                                                           // if 4 pressed
    if (students.empty())
        cout << "Nothing to show" << endl;
    else
    {
        for (int i = 0; i < students.size(); i++)
        {
            cout << "Name: " << students[i].getName() << " "
                 << "Roll No: " << students[i].getRollNo() << " "
                 << "marks: " << students[i].getMarks() << endl;
        }
    }
    cout << endl;
}

void clearRecord(vector<Student> &students)
{                                                                               // if 5 presses
    string password;
    cout << "authorized users only" << endl;
    cout << "type the password to access" << endl;
    cin >> password;
    if (password == "pass123")
    {
        while (true)
        {
            try
            {
                cout << "are u sure u want to erase whole data" << endl;
                cout << "press 0 to confirm and 1 to cancel" << endl;
                int confirm = getValidatedInput();
                if (confirm == 0)
                {
                    students.clear();
                    clearFile();
                    cout << "cleared whole record" << endl;
                    cout << endl;
                    break;
                }
                else if (confirm == 1)
                {
                    cout << "cancelled" << endl;
                    cout << endl;
                    return;
                }
                else
                {
                    throw string("value outside menu range");
                }
            }
            catch (string err)
            {
                cout << "Error: " << err << endl;
                cout << endl;
            }
        }
    }
    else
    {
        cout << "access denied" << endl;
        cout << endl;
    }
}
void updateStudentDetails(vector<Student> &students)
{                                                                                     // if 6 pressed
    int rollno;
    while (true)
    {
        cout << "Enter the RollNo of student" << endl;
        try
        {
            rollno = getValidatedInput();
            if (!studentAlreadyExists(students, rollno))
            {
                cout << "No student with this rollno exists" << endl;
                cout << "try rollno again" << endl;
            }
            else
            {
                break;
            }
        }
        catch (string err)
        {
            cout << "Error: " << err << endl;
            cout << endl;
        }
    }
    double marks;
    int choice;
    string name;
    while (true)
    {
        try
        {
            cout << "press 1 to update name" << endl;
            cout << "press 2 to update marks" << endl;
            cout << "press 0 to exit" << endl;
            choice = getValidatedInput();
            if (choice > 2 || choice < 0)
            {
                throw string("value outside menu range");
            }
        }
        catch (string err)
        {
            cout << "Error: " << err << endl;
            cout << endl;
            continue;
        }
        if (choice == 0)
            break;
        if (choice == 1)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter new Name" << endl;
            name = getValidatedName();
        }
        else
        {
            while (true)
            {
                try
                {
                    cout << "enter new Marks" << endl;
                    marks = getValidatedDoubleInput();
                    if(marks>100) throw string("Marks cannot be greater than 100");
                    else break;
                }
                catch (string err)
                {
                    cout << "Error: " << err << endl;
                    cout << endl;
                }
            }
        }
        for (int i = 0; i < students.size(); i++)
        {
            if (students[i].getRollNo() == rollno)
            {
                if (choice == 1)
                {
                    students[i].setName(name);
                    cout << "Name updated successfully for Roll No: " << rollno << endl;
                }
                else
                {
                    students[i].setMarks(marks);
                    cout << "Marks updated successfully for Roll No: " << rollno << endl;
                }
                cout << endl;
                changesMade = true;
                break;
            }
        }
    }
}

void sortAccToMarks(vector<Student> &students){                                          //if 7 pressed
    sort(students.begin(),students.end(),[](const Student &a,const Student &b){         //lamda function one liner
        return a.getMarks()==b.getMarks() ? a.getName()<b.getName() : a.getMarks()>b.getMarks();
    });
    cout<<"Sorted Successfully"<<endl;
    cout<<endl;
    changesMade=true;
}

double calAverageScore(const vector<Student> &students){                                   //if 8 pressed
    double averageMarks=0;
    long double total=0;
    for(int i=0; i<students.size();i++){
        total+=(long double)students[i].getMarks();
    }
    if(students.size()>0){
        averageMarks=(double)(total/(double)students.size());
    }
    return averageMarks;
}

string giveAbsoluteGrade(double marks){
    vector<pair<double, string>> absoluteGrades={{90,"A"},{80,"A-"},{70,"B"},{60,"B-"},{50,"C"},{40,"D"}, {30,"E"},{0,"F"}};
    if(marks>100 || marks<0) return "Invalid";
    for(auto it:absoluteGrades){
        if(marks>=it.first && marks<=100){
            return it.second;
        }
    }
    return "Invalid";
}

void assignAbsoluteGrades(vector<Student> &students,map<int,string> &grades){           // if 9 pressed
    for(int i=0;i<students.size();i++){
        grades[students[i].getRollNo()]=giveAbsoluteGrade(students[i].getMarks());
    }
}

void showFailingStudents(const vector<Student> &students){                              // if 10 pressed
    bool failFound=false;
    if (students.empty())
        cout << "Nothing to show" << endl;
    else
    {
        for (int i = 0; i < students.size(); i++)
        {   
            if(students[i].getMarks()<30){
                failFound=true;
                cout << "Name: " << students[i].getName() << " "
                    << "Roll No: " << students[i].getRollNo() << " "
                    << "marks: " << students[i].getMarks() << endl;
            }
        }
        if(!failFound) cout<<"Everyone Passed"<<endl;
    }
    cout << endl;
}
void exportToCSV(const vector<Student> students){                                      // if 11 pressed
    ofstream file;
    file.open("student_data.csv");
    file<<"Name,Roll No,Marks,Grades\n";
    
    for(int i=0;i<students.size();i++){
        string grade=giveAbsoluteGrade(students[i].getMarks());
        file<<students[i].getName()<<","
            <<students[i].getRollNo()<<","
            <<students[i].getMarks()<<","
            <<grade<<"\n";
    }
    file.close();
    cout<<"exported data to student_data.csv file"<<endl;
    cout<<endl;
}
void whatToDo(vector<Student> &students)
{
    while (true)
    {
        cout << "what do u want to do" << endl;
        cout << "press 1 to add a student" << endl;
        cout << "press 2 to get student info" << endl;
        cout << "press 3 to clear a student record" << endl;
        cout << "press 4 to see whole student record" << endl;
        cout << "press 5 to clear whole student record" << endl;
        cout << "press 6 to update student details" << endl;
        cout << "press 7 to sort according to marks"<<endl;
        cout << "press 8 to get Average class marks" << endl;
        cout << "press 9 to assign Grades" << endl;
        cout << "press 10 to show failing students" << endl;
        cout << "press 11 to export data to CSV file" << endl;
        cout << "press 0 to exit" << endl
             << endl;

        try
        {
            int input = getValidatedInput();
            if (input == 0)
            {
                break;
            }
            else if (input == 1)
            {
                addStudent(students);
            }
            else if (input == 2)
            {
                cout << "press 0 to search by name" << endl;
                cout << "press 1 to search by roll no" << endl;
                int inp = getValidatedInput();
                if (inp == 0)
                {
                    bool found = false;
                    while (!found)
                    {
                        string name;
                        cout << "enter the student name" << endl;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        name = getValidatedName();
                        found = getStudentInfo(students, name);
                    }
                }
                else if (inp == 1)
                {
                    getStudentInfoRollno(students);
                }
                else
                    throw string("value outside menu range");
            }
            else if (input == 3)
            {
                clearStudentRecord(students);
            }
            else if (input == 4)
            {
                seeWholeRecord(students);
            }
            else if (input == 5)
            {
                clearRecord(students);
            }
            else if (input == 6)
            {
                updateStudentDetails(students);        
            }
            else if(input == 7){
                sortAccToMarks(students);
            }
            else if(input == 8){
                cout<<calAverageScore(students)<<endl;
                cout<<endl;
            }
            else if(input == 9){
                map<int,string> grades;
                assignAbsoluteGrades(students,grades);
                for(auto it:grades){
                    cout<<"Roll No: "<<it.first<<" Grade: "<<it.second<<endl;
                }
                cout<<endl;
            }
            else if(input == 10){
                showFailingStudents(students);
            }
            else if(input == 11){
                exportToCSV(students);
            }
            else
                throw string("value outside menu range");
        }
        catch (string err)
        {
            cout << "Error: " << err << endl;
            cout << endl;
        }
    }
}

void wantToSave(vector<Student> &students)
{
    while (true)
    {
        cout << "U have unsaved data" << endl;
        cout << "Do U want to save it" << endl;
        cout << "press 0 to save or 1 to cancel" << endl;
        try
        {
            int save = getValidatedInput();
            if (save == 0)
            {
                ofstream data;
                data.open("student_record.txt");

                for (int i = 0; i < students.size(); i++)
                {
                    data << "name: " << students[i].getName() << " rollNo: " << students[i].getRollNo() << " marks: " << students[i].getMarks() << endl;
                }
                changesMade = false;
                data.close();
                break;
            }
            else if (save == 1)
            {
                cout << "cancelled" << endl;
                break;
            }
            else
                throw string("value outside menu range");
        }
        catch (string err)
        {
            cout << "Error: " << err << endl;
            cout << endl;
        }
    }
}

int main(int argc, char const *argv[])
{
    vector<Student> students;
    loadDataToRam(students);
    whatToDo(students);
    if (changesMade)
    {
        wantToSave(students);
    }
    return 0;
}

