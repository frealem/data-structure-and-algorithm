#include <iostream>
#include<fstream>

using namespace std;
//=================Structures for student and course
//structure to register courses to student
struct course{
    string stuID;
    string courseNo;
    string courseTitle;
    int crh;
    string grade;
    course*next;
}*courseHead=NULL;
//structure to manage courses separately
struct courseMan{
    string courseNo;
    string courseTitle;
    int crh;
    courseMan*next;
}*courseManHead=NULL;
//structure to manage students
struct student{

    string  id;
    string fname;
    string lname;
    int age;
    char sex;
    student*next;

}*stuHead=NULL;
//=====================================================================


student* getStudentInfo(string id,string fname,string lname,int age,char sex){

    student* temp=new student;
    temp->id=id;
    temp->fname=fname;
    temp->lname=lname;
    temp->age=age;
    temp->sex=sex;
    temp->next=NULL;
    return temp;
}
course* getCourseInfo(string stuID,string courseNo,string courseTitle, int crh,string grade){
    course *temp = new course;
    temp->stuID=stuID;
    temp->courseNo=courseNo;
    temp->courseTitle=courseTitle;
    temp->crh=crh;
    temp->grade=grade;
    temp->next=NULL;
    return temp;
}
courseMan* getCourseManInfo(string courseNo,string courseTitle, int crh){
    courseMan *temp = new courseMan;
    temp->courseNo=courseNo;
    temp->courseTitle=courseTitle;
    temp->crh=crh;
    temp->next=NULL;
    return temp;
}
//=====================global variable=======================
bool sorted;
//=====================Function Declaration====================
void menu();
void loadStudent();
void loadCourses();
void loadStudentRecord();
student* searchStudent(string);
courseMan* searchCourse(string);
course* searchRecored(string,string);
void studentRegister();
void addCourses();
void courseRegister();
void manageGrade();
void insertStudent(student*);
void insertCourse(courseMan*);
void insertIntoStudentRecored(course*);
void displayStudent();
void displayCourse();
void displayStudentRecord();
void searchdisplayStudent();
void sortStudent();
void deleteStudent();
void deleteCourse();
void deleteStudentRecord(string);
void writeStudentToFile();
void writeCourseToFile();
void writeStudentRecordToFile();
bool getSorted();
//=============================================================
//====================Main function ===========================
int main()
{
    loadCourses();
    loadStudent();
    loadStudentRecord();
    sorted=false;
    menu();

    return 0;
}
//==============================================================
//=======================Menu======================================
void menu(){
    char ch;
    cout<<"================Welcome to student management system===============\n";
    do{
        int option,id;
        cout<<"===============The following are the available options===========\n";
        cout<<"Enter 1 to register students info.\n";
        cout<<"Enter 2 to register students course.\n";
        cout<<"Enter 3 to add courses.\n";
        cout<<"Enter 4 to search student.\n";
        cout<<"Enter 5 to display students.\n";
        cout<<"Enter 6 to display courses.\n";
        cout<<"Enter 7 to display registered courses by a student.\n";
        cout<<"Enter 8 to manage grade.\n";
        cout<<"Enter 9 to delete student.\n";
        cout<<"Enter 10 to delete courses.\n";
        cout<<"Enter 11 to sort students.\n";
        cout<<"Your choice: ";
        cin>>option;
        switch(option){
        case 1:
            studentRegister();
            sorted=false;
            break;
        case 2:
            courseRegister();
            break;
        case 3:
            addCourses();
            break;
        case 4:
            searchdisplayStudent();
            break;
        case 5:
            displayStudent();
            break;
        case 6:
            displayCourse();
            break;
        case 7:
            displayStudentRecord();
            break;
        case 8:
            manageGrade();
            break;
        case 9:
            deleteStudent();
            break;
        case 10:
            deleteCourse();
            break;
        case 11:
            sortStudent();
            sorted=true;
            break;
        default:
            cout<<"There is no option for this value.\n";
            break;
        }
        writeStudentToFile();
        writeCourseToFile();
        writeStudentRecordToFile();
        cout<<"\nwould you like to go to menu.(Y or N): ";
        cin>>ch;
    }while (ch=='y'||ch=='Y');
}
//====================================================================
//============================Function definition======================
void studentRegister(){
    char ch,sex;
    string fname,lname,id;
    int age;
    do{
    cout<<"==============student registration============\n";
    cout<<"Enter student first name: ";
    cin>>fname;
    cout<<"Enter student last name: ";
    cin>>lname;
    cout<<"Enter student ID: ";
    cin>>id;
    cout<<"Enter student age: ";
    cin>>age;
    cout<<"Enter student sex (f or m): ";
    cin>>sex;
    student * node=getStudentInfo(id,fname,lname,age,sex);
    insertStudent(node);
    cout<<"would you like to continue student registeration?(Y or N): ";
    cin>>ch;
    }while(ch=='y'||ch=='Y');
}
//=====================================================
//========loads student info from file==================

void loadStudent(){
    fstream myfile;
    myfile.open("Student.txt",ios::in);
    if(myfile.is_open()){
       string id,fname,lname;
       int age;
       char sex;
          while(myfile>>id>>fname>>lname>>age>>sex){
                student* temp= getStudentInfo(id,fname,lname,age,sex);
                insertStudent(temp);
          }

        myfile.close();
    }
}
//===========loads course management info from file=======
void loadCourses(){
    fstream myfile("Course.txt");
    if(myfile.is_open()){
       string courseNo,courseTitle;
       int crh;
          while(myfile>>courseNo>>courseTitle>>crh){
                courseMan* temp= getCourseManInfo(courseNo,courseTitle,crh);
                insertCourse(temp);
          }
    }
}
//=========================================================
//==============loads student registered courses from file=====
void loadStudentRecord(){
    fstream myfile("StudentRecord.txt");
    if(myfile.is_open()){
       string stuID,courseTitle,courseNo;
       string grade;int crh;
          while(myfile>>stuID>>courseNo>>courseTitle>>crh>>grade){
                 course* temp= getCourseInfo(stuID,courseNo,courseTitle,crh,grade);
                 insertIntoStudentRecored(temp);
                cout<<stuID<<endl;
          }
    }
}
//============================================================
//============insert functions================================
//============adds student info to the linked list ===============
void insertStudent(student* node){

    if(stuHead==NULL){
        stuHead=node;
        stuHead->next=NULL;
    }
    else{
        student*temp = searchStudent(node->id);
        if(temp!=NULL){
            cout<<"This id already exists!\n";
            return;
        }
        node->next=stuHead;
        stuHead=node;
    }
}
//====================================================================
//===========insert courses to the linked list============
void insertCourse(courseMan* node){

    if(courseManHead==NULL){
        courseManHead=node;
        courseManHead->next=NULL;
    }
    else{
        courseMan*temp=searchCourse(node->courseNo);
        if(temp!=NULL){
            cout<<"This id already exists!\n";
            return;
        }
        node->next=courseManHead;
        courseManHead=node;
    }
}
//==============================================================
//=============insert student record to linked list=============
void insertIntoStudentRecored(course*node){
    if(courseHead==NULL){
        courseHead=node;
        courseHead->next=NULL;
    }
    else{
        course*temp=searchRecored(node->stuID,node->courseNo);
        if(temp==NULL){
            node->next=courseHead;
            courseHead=node;
        }
        else{
            cout<<"Student is already registered to course!\n";
        }
    }
}
//=====================================================================

//==============register students to courses===========================
void courseRegister(){
    int courseHr;
    string courseName,id,courseNo;
    char ch;
    do{
    cout<<"Enter id of the student: ";
    cin>>id;
    student *temp=searchStudent(id);
    if(temp==NULL)
        cout<<"Student doesn't exist!\n";
    else{
    cout<<"Enter course number: ";
    cin>>courseNo;
    cout<<"Enter course name: ";
    cin>>courseName;
    cout<<"Enter course hour: ";
    cin>>courseHr;
    course* temp1 = getCourseInfo(temp->id,courseNo,courseName,courseHr,"0");
    insertIntoStudentRecored(temp1);
    }
    cout<<"would you like to continue registering course?(Y or N): ";
    cin >>ch;
    }while(ch=='y'|| ch=='Y');
}
//=====================================================================
//====================adds courses to the list=========================
void addCourses(){
    int courseHr;
    string courseNo,courseName;
    char ch;
    do{
    cout<<"Enter course number: ";
    cin>>courseNo;
    cout<<"Enter course name: ";
    cin>>courseName;
    cout<<"Enter course hour: ";
    cin>>courseHr;
    courseMan* temp = getCourseManInfo(courseNo,courseName,courseHr);
    insertCourse(temp);
    cout<<"would you like to continue adding course?(Y or N): ";
    cin>> ch;
    }while(ch=='y'|| ch=='Y');
}
//======================================================================
//================manages grade of a student============================
void manageGrade(){
    string id,courseNo;
    string grade;
    cout<<"Enter student's id: ";
    cin>>id;
    cout<<"Enter registered course number: ";
    cin>>courseNo;
    course*temp = searchRecored(id,courseNo);
    if(temp==NULL){
        cout<<"The student record doesn't exist!\n";}
    else{
            cout<<"Enter grade here: ";
            cin>>grade;
            temp->grade=grade;
            cout<<"student id "<<temp->stuID<<endl;
            cout<<"course number "<<temp->courseNo<<endl;
            cout<<"course title "<<temp->courseTitle<<endl;
            cout<<"course hour "<<temp->crh<<endl;
            cout<<"grade "<<temp->grade<<endl;
    }
}


//=============search Functions=======================================
//=============searches for student record=============================
course* searchRecored(string id,string courseNo){
    course*temp=courseHead;
        while(temp!=NULL){
            if(temp->stuID==id&&temp->courseNo==courseNo)
                 return temp;
            temp=temp->next;
        }
        return NULL;
}
//====================================================================
//==============searches for student=================================
student* searchStudent(string id){
    student* temp = stuHead;
    while(temp!=NULL&&temp->id!=id){
        temp=temp->next;
    }
    return temp;
}
//=====================================================================
//===============searches for courses==================================
courseMan* searchCourse(string courseNo){
    courseMan*temp = courseManHead;
    while(temp!=NULL&&temp->courseNo!=courseNo){
        temp=temp->next;
    }
    return temp;
}
//========================================================================
//========================================================================
//======================Delete functions==================================
//===================deletes a student from the list======================
void deleteStudent(){
    string id;
    cout<<"Enter student id to delete student: ";
    cin>>id;
    student*curr=stuHead;
    if(stuHead==NULL){
        cout<<"The list is empty!\n";
    }
    else if(stuHead->id==id){
        stuHead=stuHead->next;
        delete curr;
        cout<<"Student deleted successfully!\n";
    }
    else{
    student*prev = new student;
      while(curr!=NULL&&curr->id!=id){
        prev=curr;
        curr=curr->next;
      }
      if(curr==NULL){
        cout<<"id doesn't exist!\n";
      }
      else{
      prev->next=curr->next;
      delete curr;
      cout<<"Student deleted successfully!\n";
      deleteStudentRecord(id);
      }
    }
}
//==================================================================
//============ automatically cascades student record after deletion of a student=============
void deleteStudentRecord(string id){
    student*temp=stuHead;
    if(courseHead==NULL)
        return;
    else{
    while(temp!=NULL){
        course*prev =courseHead;
        course*curr=prev->next;
    if(courseHead->stuID==id){
        courseHead=courseHead->next;
        delete prev;
        prev=courseHead;
        curr=curr->next;
          }
    else{
      while(curr!=NULL&&curr->stuID!=id){
        prev=curr;
        curr=curr->next;
      }
      prev->next=curr->next;
      delete curr;
     }
     temp=temp->next;
   }
  }
}
//=======================================================================
//===================Deletes courses=====================================
void deleteCourse(){
    string courseNo;
    cout<<"Enter course number to delete: ";
    cin>>courseNo;
    courseMan*curr=courseManHead;
    if(courseManHead==NULL){
        cout<<"The list is empty!\n";
    }
    else if(courseManHead->courseNo==courseNo){
        courseManHead=courseManHead->next;
        delete curr;
        cout<<"Course deleted successfully!\n";
    }
    else{
    courseMan*prev = new courseMan;
      while(curr!=NULL&&curr->courseNo!=courseNo){
        prev=curr;
        curr=curr->next;
      }
      if(curr==NULL){
        cout<<"course doesn't exist!\n";
        return;
      }
      prev->next=curr->next;
      delete curr;
      cout<<"Course deleted successfully!\n";
    }
}
//=======================================================================
//======================display functions=================================
//===================display's search results for a student===============
void searchdisplayStudent(){
    string id;
    cout<<"Enter id to search: ";
    cin>>id;
    student *temp = searchStudent(id);
    if(temp==NULL){
        cout<<"Student doesn't exist!\n";
        return;
    }
    cout<<"student with id "<<id<<endl;
    cout<<"student name "<<temp->fname<<" "<<temp->lname;
    cout<<"\nstudent age "<<temp->age;
    cout<<"\nstudent sex "<<temp->sex;
}
//=======================================================================
//====================display a student's record======================
void displayStudentRecord(){
    string id,courseNo;
    cout<<"Enter student's id: ";
    cin>>id;
    student*temp3=searchStudent(id);
    if(temp3==NULL){
        cout<<"Student desn't exist!\n";
        return;
    }
      cout<<"Registered course: \n";
      courseMan* temp2=new courseMan;
      for(temp2=courseManHead;temp2!=NULL;temp2=temp2->next){
            string n=temp2->courseNo;
            course*temp = searchRecored(id,n);
            if(temp==NULL)
                continue;
            else{

            cout<<"course number "<<temp->courseNo<<"    ";
            cout<<"course title "<<temp->courseTitle<<"    ";
            cout<<"course hour "<<temp->crh<<"    ";
            cout<<"grade "<<temp->grade<<endl;

        }

    }
}
//======================================================================
//================display students from list============================
void displayStudent(){
    if(stuHead==NULL)
        cout<<"The file is Empty!\n";
    else{
        cout<<"id========First name======Last name===== age=======sex\n";
        student *temp=stuHead;
        while(temp!=NULL){
            cout<<temp->id<<"     ";
            cout<<temp->fname<<"     ";
            cout<<temp->lname<<"     ";
            cout<<temp->age<<"     ";
            cout<<temp->sex<<"     "<<endl;
            temp=temp->next;
        }
    }
}
//=====================================================================
//==============display all courses====================================
void displayCourse(){
    if(courseManHead==NULL)
        cout<<"The file is Empty!\n";
    else{
        cout<<"course number====course name====course hour\n";
        courseMan *temp=courseManHead;
        while(temp!=NULL){
            cout<<temp->courseNo<<"          ";
            cout<<temp->courseTitle<<"       ";
            cout<<temp->crh<<"       "<<endl;
            temp=temp->next;
        }
    }
}
//======================================================================
//======================================================================
void writeStudentToFile(){
    fstream myfile;
    myfile.open("Student.txt",ios::out);
    student* temp=stuHead;
    while(temp!=NULL){
        myfile<<temp->id<<" ";
        myfile<<temp->fname<<" ";
        myfile<<temp->lname<<" ";
        myfile<<temp->age<<" ";
        myfile<<temp->sex<<" "<<endl;
        temp=temp->next;
    }
    myfile.close();
}
void writeCourseToFile(){
    fstream myfile;
    myfile.open("Course.txt",ios::out);
    courseMan* temp=courseManHead;
    while(temp!=NULL){
        myfile<<temp->courseNo<<" ";
        myfile<<temp->courseTitle<<" ";
        myfile<<temp->crh<<" "<<endl;
        temp=temp->next;
    }
    myfile.close();
}
void writeStudentRecordToFile(){
    fstream myfile;
    myfile.open("StudentRecord.txt",ios::out);
    course* temp=courseHead;
    while(temp!=NULL){
        myfile<<temp->stuID<<" ";
        myfile<<temp->courseNo<<" ";
        myfile<<temp->courseTitle<<" ";
        myfile<<temp->crh<<" ";
        myfile<<temp->grade<<" "<<endl;
        temp=temp->next;
    }
    myfile.close();
}
//==========sorts students alphabetically=============
void sortStudent(){
    student*p=new student;

    if(stuHead==NULL)
        cout<<"The list is empty!\n";
    else if(sorted)
        cout<<"The list is already sorted!\n";
    else{
    for(p=stuHead;p!=NULL;p=p->next){
    student*temp=new student;
    student *curr=stuHead->next;
    student *prev=stuHead;
        while(curr!=NULL){
            if(prev->fname>curr->fname){
                temp->id=prev->id;
                temp->fname=prev->fname;
                temp->lname=prev->lname;
                temp->age=prev->age;
                temp->sex=prev->sex;

                prev->id=curr->id;
                prev->fname=curr->fname;
                prev->lname=curr->lname;
                prev->age=curr->age;
                prev->sex=curr->sex;

                curr->id=temp->id;
                curr->fname=temp->fname;
                curr->lname=temp->lname;
                curr->age=temp->age;
                curr->sex=temp->sex;

            }
            curr=curr->next;
            prev=prev->next;
        }
     }
     displayStudent();
   }
}


