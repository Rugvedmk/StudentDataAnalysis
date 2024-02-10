#include<iostream>
#include<string.h>
#include<graphics.h>
#include<fstream>
using namespace std;

class Student{
    public:
        string  first_name,last_name,full_name, ch, cls,div;
        int roll_no;
};

class Div_A:public Student
{
    protected:
    public:
    int fds,cg,deld,dm,oop;
    static int count_a_m,count_avg,count_poor,count_good;
    static int count_a,count_temp,count_a_s;
    static int count_a_fds,count_a_cg,count_a_oop,count_a_deld,count_a_dm;
    int percentage;
    
    
    Div_A()
    {
        //This is the default constructor setting division and class of the student and assigning marks to zero or null.
        count_a++;
        cls = "SE";
        div = "A";
        roll_no = count_a;
        fds = cg = oop = dm = deld = percentage = 0;
    }
    
        //This function gives the basic data of the student.
    void get_data()
    {
        cout<<full_name<<endl;
        cout<<cls<<endl;
        cout<<div<<endl;
        cout<<roll_no<<endl;
    }
    
        //In this function the basic data of the function is set.
    void set_data()
    {
        cout<<"Enter first name : ";
        cin>>first_name;
        cout<<"Enter last name : ";
        cin>>last_name;
        full_name = last_name + " " + first_name;
    }
    void set_marks(Div_A* , int choice_update);
}*A[100],*A_aggre[100],*A_fds[100],*A_cg[100],*A_deld[100],*A_dm[100],*A_oop[100],*A_temp[100]; 

    //This function sorts the student according to their names in assending order.
    //We have used insertion sort algorithm in it.
void setdata()
{
    for(int i = 1;i<=Div_A::count_a;i++)
    {
            Div_A *temp1,*temp2;
            if((A[Div_A::count_a]->full_name)<(A[i]->full_name)){
                //temp = A[i];
                temp1 = A[i];
                A[i] = A[Div_A::count_a];
                A[i]->roll_no = i;
                for(int j=i+1;j<Div_A::count_a;j++){
                    temp2 = A[j];
                    A[j] = temp1;
                    A[j]->roll_no = j;
                    temp1 = temp2;
                }
                A[Div_A::count_a] = temp1;
                A[Div_A::count_a]->roll_no = Div_A::count_a;
                
                break;    
            }
                    
        }
}

    //Writes the data into raw text file in order to save it
void write()
{
    ofstream file("raw.txt", ios::out);
    file << Div_A ::count_a << endl;   // keeps the count of new objects
    for (int i = 1; i <= Div_A ::count_a; i++)
    {
        file << A[i]->first_name << endl;
        file << A[i]->last_name << endl;
        file << A[i]->fds << endl;
        file << A[i]->cg << endl;
        file << A[i]->oop << endl;
        file << A[i]->deld << endl;
        file << A[i]->dm << endl;
        file << A[i]->percentage << endl;
    }
}

    //Reads the raw data from the file and restores with when the programme is run
void read()
{
    string a;
    int num;

    ifstream myfile;
    myfile.open("raw.txt");

    getline(myfile,a);
    num = stoi(a);
    string first_name, last_name, full_name;
    string marks;
    for (int i = 1; i <= num; i++)
    {
        getline(myfile,first_name);
        getline(myfile,last_name);
        A[i] = new Div_A();
        A[i]->first_name = first_name;
        A[i]->last_name = last_name;
        A[i]->full_name = last_name + " " + first_name;
        getline(myfile,marks);
        A[i]->fds = stoi(marks);
        getline(myfile,marks);
        A[i]->cg = stoi(marks);
        getline(myfile,marks);
        A[i]->oop = stoi(marks);
        getline(myfile,marks);
        A[i]->deld = stoi(marks);
        getline(myfile,marks);
        A[i]->dm = stoi(marks);
        getline(myfile,marks);
        A[i]->percentage = stoi(marks);
        A_temp[i-1] = A[i];
        Div_A::count_temp++;   
    }
}

    //In this function we create 2 text files  from which one takes the entry of the new students then it copies into the main
void student_data()
{   
    ofstream f3;
    f3.open("Student_data.txt", ios::out);
    for(int i=1; i <= Div_A ::count_a; i++)
    {
        f3 << i <<"."<<A[i]->full_name<<endl;
        f3 << "Class: " << A[i]->cls << " Divsion: " << A[i]->div << " Roll No. : " << A[i]->roll_no<<endl; 
        f3 << "FDS: " << A[i]->fds << " "<< "CG: " << A[i]->cg << " "<< "OOP: " << A[i]->oop  << " "<< "DELD: " <<A[i]->deld << " "<<"DM: " << A[i]->dm  << " "<<"Percentage: " << A[i]->percentage <<endl;
        f3 << endl;
        f3 << "\n";
    }
}  

    //Checks wether the input is valid or not
int er_handler(int* marks)
{
    try{
        if(*marks<0 || *marks>100){
            throw *marks;
        }
    }
    catch(int temp){
        cout<<"Invalid input the marks should be greater than or equal to 0 and less than or equal to 100";
        cout<<"\nPlease enter valid marks :";
        cin>>*marks;
        er_handler(marks);
    }
    return *marks;
}

void Div_A :: set_marks(Div_A* temp1, int choice_update)// 0 means the marks are entered for the 1st time
{
    cout<<"Enter marks of "<<full_name<<" roll number "<<roll_no<<endl;
    cout<<"Enter marks out of 100 "<<endl;
    cout<<"FDS :";
    cin>>fds;
    er_handler(&fds);
    cout<<"CG :";
    cin>>cg;
    er_handler(&cg);
    cout<<"DELD :";
    cin>>deld;
    er_handler(&deld);
    cout<<"OOP :";
    cin>>oop;
    er_handler(&oop);
    cout<<"DM :";
    cin>>dm;
    
    if(choice_update == 0){

        percentage = float((fds+cg+deld+oop+dm)*0.2);

        if (percentage >= 80){
            count_good++;
        }
        else if (percentage <= 40){
            count_poor++;
        }
        else{
            count_avg++;
        }

        A_temp[count_temp] = temp1;
        count_temp++;
    }
    else
    {   
        if (percentage >= 80){
            count_good--;
        }
        else if (percentage <= 40){
            count_poor--;
        }
        else{
            count_avg--;
        }

        percentage = float((fds+cg+deld+oop+dm)*0.2);

        if (percentage >= 80){
            count_good++;
        }
        else if (percentage <= 40){
            count_poor++;
        }
        else{
            count_avg++;
        }
    }
}

//This function takes the file name and array pointers declared for class Div_A (eg *A_fds[100]) and 
//subject (fds,deld, etc) ,it is a variable name for class Div_A
void w_marks_template(string fileName, Div_A *typeArray[],int Div_A :: *subject){
        
        ofstream file(fileName, ios::out);
        for(int i = 0;i<Div_A::count_a_m;i++)
        {
        file << typeArray[i]->full_name<<" : ";
        file << typeArray[i]->*subject<<endl;
        }
        
}

    //In this function we create data files for storing the marks of all the subjects
void w_marks()
{   

    w_marks_template("FDS.txt",A_fds,&Div_A:: fds);
    w_marks_template("CG.txt",A_cg,&Div_A:: cg);
    w_marks_template("DELD.txt",A_deld,&Div_A:: deld);
    w_marks_template("OOP.txt",A_oop,&Div_A:: oop);
    w_marks_template("DM.txt",A_dm,&Div_A:: dm);
    w_marks_template("Overall_Percentage.txt",A_aggre,&Div_A:: percentage);

}

int Div_A :: count_a;//keeps the count of new objects
int Div_A :: count_a_m;//keeps the count of aggregate percentage
int Div_A :: count_poor;//keeps the count of students below 40%
int Div_A :: count_avg;//keeps the count of students between 40% and 80%
int Div_A :: count_good;//keeps the count of students above 80%
int Div_A :: count_temp;//keeps the count of students who are not yet included in the sorted marks list
int Div_A :: count_a_s;//keeps the count of marks set of the student
int Div_A :: count_a_fds;//keeps the count of students in the sorted marks list of FDS
int Div_A :: count_a_cg;//keeps the count of students in the sorted marks list of CG
int Div_A :: count_a_deld;//keeps the count of students in the sorted marks list of DELD
int Div_A :: count_a_oop;//keeps the count of students in the sorted marks list of OOP
int Div_A :: count_a_dm;//keeps the count of students in the sorted marks list of DM

    //This function sorts Subject marks
void sortTemplate(Div_A *typeArray[],int &count,int Div_A:: *subject ){
    Div_A *temp1,*temp2;
    
    for (int i = 0; i <Div_A::count_temp; i++){
        typeArray[count] = A_temp[i];
        count++;
        temp1 = A_temp[i];
        for (int j = 0; j <count; j++){
            if (temp1->*subject > typeArray[j]->*subject){
                for (int k = j; k < count; k++){
                    temp2 = typeArray[k];
                    typeArray[k] = temp1;
                    temp1 = temp2;
                }
                break;
            }            
        }
        
    }
}

    //Sorts the student percent in descending order
void A_sortpercent(){
    Div_A *temp1,*temp2;
    
    sortTemplate(A_aggre,Div_A::count_a_m,&Div_A:: percentage);
    sortTemplate(A_fds,Div_A::count_a_fds, &Div_A:: fds);
    sortTemplate(A_cg,Div_A::count_a_cg,&Div_A:: cg);
    sortTemplate(A_oop,Div_A::count_a_oop,&Div_A:: oop);
    sortTemplate(A_dm,Div_A::count_a_dm,&Div_A:: dm);
    sortTemplate(A_deld,Div_A::count_a_deld,&Div_A:: deld);
    Div_A::count_temp = 0;
}

    //Function to draw solid rectangular graph
void solid_rect(int arg1,int arg2){
    int num1 = arg1,num2 = arg2;
    for (int i = 0; i < 11; i++)
    {
        rectangle(arg1,arg2,num1+1,num2+1);
        num1++;
        num2++;
    }
}

    //Function to draw graph
void draw(int count_g,int count_av,int count_p)
{       
    int total = count_g + count_p + count_av;
    count_g = count_g*3.9*100/total;
    count_p = count_p*3.9*100/total;
    count_av = count_av*3.9*100/total;
    int gd = DETECT,gm;
    initgraph(&gd,&gm,NULL);
    int c = 0;
    while(c<2){
    cleardevice();
    setbkcolor(WHITE);
    c++;
    }

    setcolor(BLACK);
    line(50,0,50,480);
    line(0,440,640,440);


    setcolor(BLACK);
    int y = 440;
    char arr[20];
    for (int i = 0; i < 110; i = i + 10)
    {   
        sprintf(arr,"%d",i);
        outtextxy(20,y-7,arr);
        delay(100);
        line(47,y,52,y);
        delay(50);
        y = y - 39;
    }
    setcolor(GREEN);
    solid_rect(450,55);
    delay(100);
    outtextxy(470,55,"ABOVE 80 percentage");
    delay(100);

    setcolor(YELLOW);
    solid_rect(450,105);
    delay(100);
    outtextxy(470,105,"Between 40 and 80 ");
    outtextxy(470,130,"percentage");
    delay(100);

    setcolor(RED);
    solid_rect(450,175);
    delay(100);
    outtextxy(470,175," BELOW 40 Percentage ");
    delay(100);

    setcolor(RED);
         y = 440;
    for (int i = 0; i < count_p; i++)
    {
        line(125,y,165,y);
        delay(1);
        y--;
    }
    setcolor(YELLOW);
        y = 440;
    for (int i = 0; i < count_av; i++)
    {
        line(240,y,280,y);
        delay(1);
        y--;
    }
    setcolor(GREEN);
        y = 440;
    for (int i = 0; i < count_g; i++)
    {
        line(355,y,395,y);
        delay(1);
        y--;
    }

    //delay(1000);
    cout<<"Please Enter C to close the graph ";
    string closeGraph;
    cin>>closeGraph;
    // getch();
    closegraph();
}

void argumentsForGraph(int &count_g, int &count_av, int &count_p,int Div_A:: *subject){
    for(int i = 1;i<=Div_A::count_a;i++)
    {
        if (A[i]->*subject > 80)
        {
            count_g++;
        }
        else if (A[i]->*subject <= 40)
        {
            count_p++;
        }
        else
        {
            count_av++;
        }
    }
}

    //Function to give choice and set proper arguments for draw() function
void graph()
{   
    cout<<"Do you want graphical analysis for aggreate marks or specific subject :"<<endl;
    cout<<"Please enter 1 for aggregate and 2 for specific subject : ";
    int ch;
    cin>>ch;

    int count_g = 0,count_av = 0,count_p = 0;
    if (ch == 1)
    {
        argumentsForGraph(count_g, count_av, count_p,&Div_A:: percentage);
        draw( count_g, count_av, count_p);
        count_g = 0;
        count_av = 0;
        count_p = 0;
    }
    if (ch == 2)
    {
        int choice;
        cout<<"Please Enter :\n1 for FDS\n2 for OOP\n3 for CG\n4 for DELD\n5 for DM \n";
        cout<<"Enter choice :";
        cin>>choice;
        if (choice == 1)
        {
            argumentsForGraph(count_g, count_av, count_p,&Div_A:: fds);
            draw( count_g, count_av, count_p);
            count_g = 0;
            count_av = 0;
            count_p = 0;
        }
        if (choice == 2)
        {
            argumentsForGraph(count_g, count_av, count_p,&Div_A:: oop);
            draw( count_g, count_av, count_p);
            count_g = 0;
            count_av = 0;
            count_p = 0;
        }
        if (choice == 3)
        {
            argumentsForGraph(count_g, count_av, count_p,&Div_A:: cg);      
            draw( count_g, count_av, count_p);
            count_g = 0;
            count_av = 0;
            count_p = 0;
        }
        if (choice == 4)
        {
            argumentsForGraph(count_g, count_av, count_p,&Div_A:: deld);
            draw( count_g, count_av, count_p);
            count_g = 0;
            count_av = 0;
            count_p = 0;
        }
        if (choice == 5)
        {
            argumentsForGraph(count_g, count_av, count_p,&Div_A:: dm);
            draw( count_g, count_av, count_p);
            count_g = 0;
            count_av = 0;
            count_p = 0;
        }
    }
}


    //This function opens the data file where all the entries of students are stored and it sorts them according to their surnames and displays the sorted list
void display_data()
{
    cout<<"Following is the list of the students present in Class: \n";
    for(int i=1; i <= Div_A ::count_a; i++)
    {
        cout << A[i]->full_name<<endl;
        cout << "Class: " << A[i]->cls << " Divsion: " << A[i]->div << " Roll No. : " << A[i]->roll_no<<endl; 
        cout << "FDS: " << A[i]->fds << " "<< "CG: " << A[i]->cg << " "<< "OOP: " << A[i]->oop  << " "<< "DELD: " <<A[i]->deld << " "<<"DM: " << A[i]->dm  << " "<<"Percentage: " << A[i]->percentage <<endl;
        cout << "\n";
    }

}

    //This function asks the user for which student you want to enter the marks and checks if it present in the list, if it is then it will call the set_marks() function
void mark_entry()
{
    string name;
    Div_A::count_a_s++;
    cout<<"Enter the full name of Student which marks you want to set (Surname FirstName): ";
            cin.ignore();
            getline(cin,name);
            
            for(int i = 1;i<=Div_A::count_a;i++){
                if (A[i]->full_name == name)
                {   
                    if (A[i]->fds == 0 && A[i]->cg == 0 && A[i]->oop == 0 && A[i]->dm == 0 && A[i]->deld == 0)
                    {
                        A[i]->set_marks(A[i], 0);
                        break;
                    } else 
                    {
                        int choice_update = 0;
                        cout<<"The marks are already set do you want to update marks?"<<endl;
                        cout<<"Press 1 for yes and 0 for no : ";
                        cin>>choice_update;
                        cout<<endl;
                        if (choice_update == 1)
                        {
                            A[i]->set_marks(A[i],1);
                            break;        
                        }
                        
                    } 
                    
                }
            }
}

    //This function asks the user for which subject or aggreagate it wants and displays the required choice
void topper()
{
    int c;
    cout<<"\n1.Overall Percentage Topper \n2.FDS Topper \n3.CG Topper \n4.OOP Topper \n5.DELD Topper \n6.DM Topper\n7.Exit"<<endl;
    cout<<"Enter your choice: ";
    cin>>c;
    switch(c)
    {
        case 1:
            cout<<"Overall Topper: "<<A_aggre[0]->full_name<<" : "<<A_aggre[0]->percentage<<endl;
            cout << "Class: " << A_aggre[0]->cls << " Divsion: " << A_aggre[0]->div << " Roll No. : " << A_aggre[0]->roll_no<<endl;
            break;

        case 2:
            cout<<"FDS Topper: "<<A_aggre[0]->full_name<<" : "<<A_aggre[0]->fds<<endl;
            cout << "Class: " << A_aggre[0]->cls << " Divsion: " << A_aggre[0]->div << " Roll No. : " << A_aggre[0]->roll_no<<endl;
            break;

        case 3:
            cout<<"CG Topper: "<<A_aggre[0]->full_name<<" : "<<A_aggre[0]->cg<<endl;
            cout << "Class: " << A_aggre[0]->cls << " Divsion: " << A_aggre[0]->div << " Roll No. : " << A_aggre[0]->roll_no<<endl;
            break;
        case 4:
            cout<<"OOP Topper: "<<A_aggre[0]->full_name<<" : "<<A_aggre[0]->oop<<endl;
            cout << "Class: " << A_aggre[0]->cls << " Divsion: " << A_aggre[0]->div << " Roll No. : " << A_aggre[0]->roll_no<<endl;     
            break;

        case 5:
            cout<<"DELD Topper: "<<A_aggre[0]->full_name<<" : "<<A_aggre[0]->deld<<endl;
            cout << "Class: " << A_aggre[0]->cls << " Divsion: " << A_aggre[0]->div << " Roll No. : " << A_aggre[0]->roll_no<<endl;
            break;

        case 6:
            cout<<"DM Topper: "<<A_aggre[0]->full_name<<" : "<<A_aggre[0]->dm<<endl;
            cout << "Class: " << A_aggre[0]->cls << " Divsion: " << A_aggre[0]->div << " Roll No. : " << A_aggre[0]->roll_no<<endl;
            break;
    }
}

    //This function searches the student and if it is found in the student data then displays the student's data
void search_student()
{   
    string name;
    int found = 0;
    cout<<"Enter the full name of the student: ";
    cin.ignore();
    getline(cin,name);
    for(int i = 1;i<=Div_A::count_a;i++)
    {
                if (A[i]->full_name == name)
                {   
                    found = 1;
                    cout<<"Student's Data: "<<endl;
                    cout << A[i]->full_name<<endl;
                    cout << "Class: " << A[i]->cls << " Divsion: " << A[i]->div << " Roll No. : " << A[i]->roll_no<<endl; 
                    cout << "FDS: " << A[i]->fds << " "<< "CG: " << A[i]->cg << " "<< "OOP: " << A[i]->oop  << " "<< "DELD: " <<A[i]->deld << " "<<"DM: " << A[i]->dm  << " "<<"Percentage: " << A[i]->percentage <<endl;
                    break;
                }
    }
    if (found = 0)
    {
        cout<<"Student not found"<<endl;
    }
    
}

void dltData()
{
    ofstream file("raw.txt", ios::out);
    file << "0" << endl;
    Div_A :: count_a = Div_A :: count_a_m = Div_A :: count_poor = Div_A :: count_avg = 
    Div_A :: count_good = Div_A :: count_temp = Div_A :: count_a_s = Div_A :: count_a_fds = 
    Div_A :: count_a_cg = Div_A :: count_a_deld = Div_A :: count_a_oop = Div_A :: count_a_dm = 0;

    file.close();

    delete[] A[100];
    delete[] A_aggre[100];
    delete[] A_fds[100];
    delete[] A_cg[100];
    delete[] A_deld[100];
    delete[] A_dm[100];
    delete[] A_oop[100];
    delete[] A_temp[100];

    read();
}

int main(){
    read();
    A_sortpercent();
    int ch;
    int checkSure;
    do {
    cout<<"\n-------------------------------------------------------------------------------------------"<<endl;
    cout<<"\n1.Create a new entry \n2.View Student Data \n3.Graphical Representation \n4.Enter marks\n5.Save Data";
    cout<<"\n6.Topper \n7.Search a Student \n8.To delete all data \n9.Exit";
    cout<<"\nSelect your option: ";
    cin>>ch;
    cout<<"-------------------------------------------------------------------------------------------"<<endl;  
    
   switch(ch)
    {
        case 1:
            A[Div_A::count_a] = new Div_A;  
            A[Div_A::count_a]->set_data();
            student_data();
            setdata();
            break;
        case 2:
            display_data();
            break;
        case 3:
            graph();
            break;
        case 4:
            mark_entry();  
            break;
        case 5:
            A_sortpercent();
            w_marks();
            student_data();
            write();
            break;
        case 6:
            topper();
            break;
        case 7:
            search_student();
            break;
        case 8:
            cout<<"Are you sure you want to delete all data?"<<endl;
            cout<<"Press 1 for yes and 0 for no : ";
            cin>>checkSure;
            if (checkSure == 1)
            {
                dltData();
            }        
            break;

    }
    }while(ch!=9);
    return 0;
}