#include <iostream>
using namespace std;

//declarations
class Biodata;
class Vertex;

class Edge{
public:
    string userName_Edge;
    string ID_Edge;
    Edge* link_Edge;
};

class Biodata{
public:
    string dob;
    string institution;
    string native;
    Biodata(){
        dob="";
        institution="";
        native="";
    }
};

class Vertex{
public:
    string userName_Vertex;
    string ID_Vertex;
    string password_Vertex;
    Biodata bio_Vertex;
    Edge* linkToEdge_Vertex;
    Vertex* linkToVertex_Vertex;
};

class Graph{

private:
    Vertex* start,* ptr_v,*ptrLogin;          //ptrLogin - poiinter to login ID
    Edge* ptr_e;

public:
    Graph(){
        start=NULL;
        ptr_v=NULL;
        ptrLogin=NULL;
    }

    void createVertex(){
        int i=0;
        Vertex* v=new Vertex;
        string old_password="";
        string new_password="";
        cout<<endl<<"Enter ID (no space)  : ";
        cin>>v->ID_Vertex;
        cout<<endl<<"Enter User Name      : ";
        cin>>v->userName_Vertex;
        do{
            if (i!=0){
                cout<<endl<<"Passwords doesnot match ! Enter Again";
            }
            cout<<endl<<"Enter password       : ";
            cin>>old_password;
            cout<<endl<<"Renter Password      : ";
            cin>>new_password;
            i++;
        }while(old_password!=new_password);

        v->password_Vertex=old_password;
        cout<<endl<<"\nAccount Created Successfully !"<<endl;
        char ch;
        cout<<endl<<"Do you want to update your Bio Data (y/n) : ";
        cin>>ch;
        if (ch=='y'){
            cout<<endl<<"Bio Data";
            cout<<endl<<"========";
            cout<<endl<<"DOB         : ";
            cin>>v->bio_Vertex.dob;
            cin.ignore(1000,'\n');
            cout<<endl<<"Institution : ";
            getline(cin,v->bio_Vertex.institution,'\n');
            cout<<endl<<"Native      : ";
            getline(cin,v->bio_Vertex.native,'\n');
        }

        v->linkToEdge_Vertex=NULL;
        v->linkToVertex_Vertex=NULL;
        start=v;
    }

    void viewFollowers(){
        if (ptrLogin->linkToEdge_Vertex==NULL){
            cout<<endl<<"You have no Followers";
        }
        else{
            cout<<endl<<"Followers";
            cout<<endl<<"---------";
            ptr_e=ptrLogin->linkToEdge_Vertex;
            while(ptr_e!=NULL){
                cout<<endl<<ptr_e->ID_Edge;
                ptr_e=ptr_e->link_Edge;
            }
        }
    }

    void viewFollowing(){
        cout<<endl<<"Following";
        cout<<endl<<"---------";
        ptr_v=start;
        while(ptr_v!=NULL){
            ptr_e=ptr_v->linkToEdge_Vertex;
            while(ptr_e!=NULL){
                if (ptrLogin->userName_Vertex==ptr_e->userName_Edge){
                    cout<<endl<<ptr_v->ID_Vertex;
                    break;
                }
                ptr_e=ptr_e->link_Edge;
            }
            ptr_v=ptr_v->linkToVertex_Vertex;
        }
    }

    void PeopleWhoYouDontFollowBack(){
        int flag=0;
        Edge* p=new Edge;                         //another pointer like ptr_e
        if (ptrLogin->linkToEdge_Vertex==NULL){
            cout<<endl<<"You have no Followers";
        }
        else{
            cout<<endl<<"People who you don't Follow Back";
            cout<<endl<<"--------------------------------";
            string id;
            ptr_e=ptrLogin->linkToEdge_Vertex;
            while(ptr_e!=NULL){
                id=ptr_e->ID_Edge;
            
                ptr_v=start;
                while(ptr_v!=NULL){
                    if (ptr_v->ID_Vertex==id){
                        p=ptr_v->linkToEdge_Vertex;
                        flag=0;
                        while(p!=NULL){
                            if (p->ID_Edge==ptrLogin->ID_Vertex){
                                flag=1;
                                break;
                            }
                            p=p->link_Edge;
                        }
                        if (flag==0){
                            cout<<endl<<ptr_v->ID_Vertex;
                        }
                    }
                    ptr_v=ptr_v->linkToVertex_Vertex;
                }
                ptr_e=ptr_e->link_Edge;
            }
        }
    }

    void peopleYouMayKnow(){
        Edge* p=new Edge;
        Edge* ed=new Edge;
        Vertex* vd=new Vertex;    //people you may know with vertex vd and Edge ed
        vd->linkToEdge_Vertex=NULL;
        int flag=0;
        string id;
        ptr_e=ptrLogin->linkToEdge_Vertex;
        while(ptr_e!=NULL){
            id=ptr_e->ID_Edge;
            
            ptr_v=start;
            while(ptr_v!=NULL){
                if (ptr_v->ID_Vertex==id){
                    p=ptr_v->linkToEdge_Vertex;
                    flag=0;
                    while(p!=NULL){
                        if (p->ID_Edge==ptrLogin->ID_Vertex){
                            flag=1;
                            break;
                        }
                        p=p->link_Edge;
                    }
                    if (flag==0){
                        if(vd->linkToEdge_Vertex==NULL){
                            ed->ID_Edge=ptr_v->ID_Vertex;
                            ed->link_Edge=NULL;
                            vd->linkToEdge_Vertex=ed;
                        }
                        else{
                            ed=new Edge;
                            ed->ID_Edge=ptr_v->ID_Vertex;
                            ed->link_Edge=NULL;
                            p=vd->linkToEdge_Vertex;
                            while(p->link_Edge!=NULL){
                                p=p->link_Edge;
                            }
                            p->link_Edge=ed;
                        }
                    }
                }
                ptr_v=ptr_v->linkToVertex_Vertex;
            }
            ptr_e=ptr_e->link_Edge;
        }

        //displaying 
        cout<<endl<<"People you may know";
        cout<<endl<<"--------------------"<<endl;
        p=vd->linkToEdge_Vertex;
        while(p!=NULL){
            cout<<endl<<p->ID_Edge;
            p=p->link_Edge;
        }

        //
        char ch;
        string id2;
        int i=0;
        cout<<endl<<"Do you want to follow any of them (y/n) ? ";
        cin>>ch;
        if (ch=='y'){
            do{
                if (i!=0){
                    cout<<endl<<"User ID not found ! Enter Again";
                }
                cout<<endl<<"Enter user ID : ";
                cin>>id2;
                i++;
            }while(!checkIfVertexAlreadyExist(id2));
            followSomeOne(ptrLogin->ID_Vertex,id2);            
        }

    }

    void PeopleWhoDontFollowYouBack(){
        int flag=1;
        Edge* p=new Edge;                       //another pointer like ptr_e
        string id;
        ptr_v=start;
        while(ptr_v!=NULL){
            ptr_e=ptr_v->linkToEdge_Vertex;
            while(ptr_e!=NULL){
                id=ptr_e->ID_Edge;
                if (id==ptrLogin->ID_Vertex){
                    p=ptrLogin->linkToEdge_Vertex;
                    flag=1;
                    while(p!=NULL){
                        if (ptr_v->ID_Vertex==p->ID_Edge){
                            flag=0;
                            break;
                        }
                        p=p->link_Edge;
                    }
                    if (flag==1){
                        cout<<endl<<ptr_v->ID_Vertex;
                    }
                }
                ptr_e=ptr_e->link_Edge;
            }
            ptr_v=ptr_v->linkToVertex_Vertex;
        }

    }

    void createVertex(string id,string user,string pass,string d,string i,string n){
        Vertex* v=new Vertex;
        v->ID_Vertex=id;
        v->userName_Vertex=user;
        v->password_Vertex=pass;
        v->bio_Vertex.dob=d;
        v->bio_Vertex.institution=i;
        v->bio_Vertex.native=n;
        v->linkToEdge_Vertex=NULL;
        v->linkToVertex_Vertex=NULL;
        start=v;
    }

    void insertVertex(string id,string user,string pass,string d,string i,string n){
        if (start==NULL){
            createVertex(id,user,pass,d,i,n);
        }
        else{
            Vertex* v=new Vertex;
            v->ID_Vertex=id;
            v->userName_Vertex=user;
            v->password_Vertex=pass;
            v->bio_Vertex.dob=d;
            v->bio_Vertex.institution=i;
            v->bio_Vertex.native=n;
            v->linkToEdge_Vertex=NULL;
            v->linkToVertex_Vertex=NULL;
            ptr_v=start;
            while(ptr_v->linkToVertex_Vertex!=NULL){
                ptr_v=ptr_v->linkToVertex_Vertex;
            }
            ptr_v->linkToVertex_Vertex=v;
        }

    }

    void searchUser(){
        string id;
        int flag1=0,flag2=0;
        char ch;
        cout<<endl<<"Enter userID you want to search : ";
        cin>>id;
        if (checkIfVertexAlreadyExist(id)){
            cout<<endl<<"UserID Found"<<endl;
            cout<<endl<<"Do you want to view "<<id<<" Status (y/n) ? ";
            cin>>ch;
            if (ch=='y'){
                //whether user is follwing me/not
                ptr_e=ptrLogin->linkToEdge_Vertex;
                while(ptr_e!=NULL){
                    if(ptr_e->ID_Edge==id){
                        cout<<endl<<id<<" follows you\n";
                        flag1=1;
                        break;
                    }
                    ptr_e=ptr_e->link_Edge;
                }
                if (flag1==0){
                    cout<<endl<<id<<" doesnot follow you\n";
                }

                //to check if i follow the given user
                ptr_v=start;
                while(ptr_v!=NULL){
                    if (ptr_v->ID_Vertex==id){
                        ptr_e=ptr_v->linkToEdge_Vertex;
                        while(ptr_e!=NULL){
                            if (ptr_e->ID_Edge==ptrLogin->ID_Vertex){
                                flag2=1;
                                cout<<endl<<"You follow "<<id<<endl;
                                break;
                            }
                            ptr_e=ptr_e->link_Edge;
                        }
                    }
                    ptr_v=ptr_v->linkToVertex_Vertex;
                }
                if (flag2==0){
                    cout<<endl<<"You don't follow "<<id<<endl;
                }
                //printing bio data
                ptr_v=start;
                while(ptr_v!=NULL){
                    if (ptr_v->ID_Vertex==id){
                        break;
                    }
                    ptr_v=ptr_v->linkToVertex_Vertex;
                }
                cout<<endl<<"Bio Data of user "<<id;
                cout<<endl<<"----------------------";
                cout<<endl<<"DOB         : "<<ptr_v->bio_Vertex.dob;
                cout<<endl<<"Institution : "<<ptr_v->bio_Vertex.institution;
                cout<<endl<<"Native      : "<<ptr_v->bio_Vertex.native;
            }
        }
        else{
            cout<<endl<<"UserID not Found"<<endl;
        }
        
    }

    void insertVertex(){
        int i=0;
        Vertex* v=new Vertex;
        string old_password="";
        string new_password="";
        int check;
        if (start==NULL){
            createVertex();
        }
        else{
            do{
                cout<<endl<<"Enter ID (no space)  : ";
                cin>>v->ID_Vertex;
                check=checkIfVertexAlreadyExist(v->ID_Vertex);
                if (check==1)
                    cout<<endl<<"User ID exists already ! Try giving some other ID";
            }while(check==1);
            cout<<endl<<"Enter User Name      : ";
            cin>>v->userName_Vertex;
            do{
                if (i!=0){
                    cout<<endl<<"Passwords doesnot match ! Enter Again";
                }
                cout<<endl<<"Enter password       : ";
                cin>>old_password;
                cout<<endl<<"Renter Password      : ";
                cin>>new_password;
                i++;
            }while(old_password!=new_password);
            v->password_Vertex=old_password;
            cout<<endl<<"\nAccount Created Successfully !"<<endl;
            char ch;
            cout<<endl<<"Do you want to update your Bio Data (y/n) : ";
            cin>>ch;
            if (ch=='y'){
                cout<<endl<<"Bio Data";
                cout<<endl<<"========";
                cout<<endl<<"DOB         : ";
                cin>>v->bio_Vertex.dob;
                cin.ignore(1000,'\n');
                cout<<endl<<"Institution : ";
                getline(cin,v->bio_Vertex.institution,'\n');
                cout<<endl<<"Native      : ";
                getline(cin,v->bio_Vertex.native,'\n');
            }
            v->linkToEdge_Vertex=NULL;
            v->linkToVertex_Vertex=NULL;
            ptr_v=start;
            while(ptr_v->linkToVertex_Vertex!=NULL){
                ptr_v=ptr_v->linkToVertex_Vertex;
            }
            ptr_v->linkToVertex_Vertex=v;
        }
    }

    int checkIfVertexAlreadyExist(string id){
        ptr_v=start;
        bool flag=0;
        while(ptr_v!=NULL){
            if (ptr_v->ID_Vertex==id){
                return 1;
            }
            ptr_v=ptr_v->linkToVertex_Vertex;
        }
        return 0;
    }

    void followSomeOne(string id1,string id2){    
        //id1 - Vertex to which edge is to be added
        //id2 - whom id1 wants to follow
        int flag=0;          //to find duplicate follower
        Edge* e=new Edge;
        Vertex* ptrlogin=new Vertex;
        ptr_v=start;
        while(ptr_v!=NULL){
            if (ptr_v->ID_Vertex==id1){
                ptrlogin=ptr_v;
            }
            ptr_v=ptr_v->linkToVertex_Vertex;
        }
        if (checkIfVertexAlreadyExist(id2)){
            ptr_v=start;
            while(ptr_v!=NULL){
                if(ptr_v->ID_Vertex==id2){
                    e->ID_Edge=ptrlogin->ID_Vertex;
                    e->userName_Edge=ptrlogin->userName_Vertex;
                    e->link_Edge=NULL;
                    if (ptr_v->linkToEdge_Vertex==NULL){
                        ptr_v->linkToEdge_Vertex=e;
                    }
                    else{
                        ptr_e=ptr_v->linkToEdge_Vertex;
                        while(ptr_e->link_Edge!=NULL){
                            if (ptr_e->ID_Edge==id2)
                                flag=1;
                            ptr_e=ptr_e->link_Edge;

                        }
                        if (flag==0)
                            ptr_e->link_Edge=e;
                    }
                    break;
                }
                ptr_v=ptr_v->linkToVertex_Vertex;
            }
        }
        else{
            cout<<endl<<"No such userId exists"<<endl;
        }
    }

    void followSomeOne(){
        int flag=0;          //to find duplicate follower
        Edge* e=new Edge;
        string id;
        cout<<endl<<"Enter the userID you want to follow : ";
        cin>>id;
        if (checkIfVertexAlreadyExist(id)){
            ptr_v=start;
            while(ptr_v!=NULL){
                if(ptr_v->ID_Vertex==id){
                    e->ID_Edge=ptrLogin->ID_Vertex;
                    e->userName_Edge=ptrLogin->userName_Vertex;
                    e->link_Edge=NULL;
                    if (ptr_v->linkToEdge_Vertex==NULL){
                        ptr_v->linkToEdge_Vertex=e;
                    }
                    else{
                        ptr_e=ptr_v->linkToEdge_Vertex;
                        while(ptr_e->link_Edge!=NULL){
                            if (ptr_e->ID_Edge==ptrLogin->ID_Vertex){
                                flag=1;
                                cout<<endl<<"You already follow this user ";
                                break;
                            }
                            ptr_e=ptr_e->link_Edge;

                        }
                        if (flag==0)
                            ptr_e->link_Edge=e;
                    }
                    break;
                }
                ptr_v=ptr_v->linkToVertex_Vertex;
            }
        }
        else{
            cout<<endl<<"No such userId exists";
        }
    }
    
    int login(){
        string id;
        string password;
        cout<<endl<<"Enter ID       : ";
        cin>>id;
        cout<<endl<<"Enter password : ";
        cin>>password;
        ptr_v=start;
        while(ptr_v!=NULL){
            if (ptr_v->ID_Vertex==id && ptr_v->password_Vertex==password){
                ptrLogin=ptr_v;
                return 1;
            }
            else if ((ptr_v->ID_Vertex==id) && (ptr_v->password_Vertex!=password)){
                return 2;
            }
            ptr_v=ptr_v->linkToVertex_Vertex;
        }
        return 0;
    }

    void logout(){
        ptrLogin=NULL;
        cout<<endl<<"Logged out Successfully !";
    }

    /*void insertEdge(Vertex* v1,Vertex* v2){
        Edge* e=new Edge;
        

    }*/

    void viewBioData(){
        cout<<endl<<"User ID    : "<<ptrLogin->ID_Vertex;
        cout<<endl<<"User Name  : "<<ptrLogin->userName_Vertex<<endl;
        cout<<endl<<"Bio data";
        cout<<endl<<"--------";
        cout<<endl<<"DOB         :  "<<ptrLogin->bio_Vertex.dob;
        cout<<endl<<"Institution :  "<<ptrLogin->bio_Vertex.institution;
        cout<<endl<<"Native      :  "<<ptrLogin->bio_Vertex.native;
    }

    void updateDOB(){
        cout<<endl<<"Enter DOB : ";
        cin>>ptrLogin->bio_Vertex.dob;
    }

    void updateInstitution(){
        cout<<endl<<"Enter Institution : ";
        cin>>ptrLogin->bio_Vertex.institution;
    }

    void updateNative(){
        cout<<endl<<"Enter Native : ";
        cin>>ptrLogin->bio_Vertex.native;
    }

    void display(){
        ptr_v=start;
        while(ptr_v!=NULL){
            cout<<endl<<"\nID        :  "<<ptr_v->ID_Vertex;
            cout<<endl<<"User Name :  "<<ptr_v->userName_Vertex;
            cout<<endl<<"\n         Bio Data ";
            cout<<endl<<"------------------------";
            cout<<endl<<"DOB         :  "<<ptr_v->bio_Vertex.dob;
            cout<<endl<<"Institution :  "<<ptr_v->bio_Vertex.institution;
            cout<<endl<<"Native      :  "<<ptr_v->bio_Vertex.native;
            ptr_e = ptr_v->linkToEdge_Vertex;
            while(ptr_e!=NULL){
                cout<<"------>"<<ptr_e->ID_Edge;
                ptr_e=ptr_e->link_Edge;
            }
            ptr_v=ptr_v->linkToVertex_Vertex;
        }
    }
};

void afterLogin(Graph& g){
    int ch2;
    int ch3;
    do{
        cout<<endl<<"\nWhat do you wanna choose ? Enter 0 to logout";
        cout<<endl<<"--------------------------------------------";
        cout<<endl<<"1) View Biodata";
        cout<<endl<<"2) Update Biodata";
        cout<<endl<<"3) Follow someone";
        cout<<endl<<"4) View Followers";
        cout<<endl<<"5) View Following";
        cout<<endl<<"6) People you may know";
        cout<<endl<<"7) People who don't follow you back";
        cout<<endl<<"8) People who you don't follow back";
        cout<<endl<<"9) Search for a user";
        cout<<endl<<"0) Logout"<<endl;
        cin>>ch2;
        
        switch(ch2){
            case 0: 
                    g.logout();
                    break;
            case 1: 
                    g.viewBioData();
                    break;
            case 2:
                    cout<<endl<<"What do you wanna update ? ";
                    cout<<endl<<"1) DOB";
                    cout<<endl<<"2) Institution";
                    cout<<endl<<"3) Native"<<endl;
                    cin>>ch3;
                    switch(ch3){
                        case 1: g.updateDOB();break;
                        case 2: g.updateInstitution();break;
                        case 3: g.updateNative();break;
                    }
                    break;
            case 3: 
                    g.followSomeOne();
                    break;
            case 4:
                    g.viewFollowers();
                    break;
            case 5: 
                    g.viewFollowing();
                    break;
            case 6:
                    g.peopleYouMayKnow();
                    break;
            case 7:
                    g.PeopleWhoDontFollowYouBack();
                    break;
            case 8:
                    g.PeopleWhoYouDontFollowBack();
                    break;
            case 9: 
                    g.searchUser();
                    break;

        }
    }while(ch2!=0);

}

int main(){
    Graph g;
    int ch1,ch2;
    int login_;

    g.insertVertex("neha@","Raja Neha","rutheesh","10.06.2003","PSG","karur");
    g.insertVertex("kri@","Krithika","Jo","04.01.2004","PSG","Chennai");
    g.insertVertex("preth@","prethika","pathy","26.03.2003","PSG","Chennai");
    g.insertVertex("bhar@","bharathi","shankar","21.07.2003","PSG","Hosur");
    g.insertVertex("sanj@","sanjana","raju","04.03.2004","PSG","Dindigul");
    g.insertVertex("yush@","aayush","akshara","03.01.2004","PSG","Cbe");
    g.insertVertex("ben@","benny","ghkhfd","06.03.2003","PSG","cbe");
    g.insertVertex("jeevi@","jeevika","jas","10.08.2003","PSG","sivakasi");
    g.followSomeOne("neha@","kri@");
    g.followSomeOne("neha@","yush@");
    g.followSomeOne("neha@","sanj@");
    g.followSomeOne("neha@","jeevi@");
    g.followSomeOne("kri@","jeevi@");
    g.followSomeOne("preth@","sanj@");
    g.followSomeOne("preth@","kri@");
    g.followSomeOne("sanj@","kri@");
    g.followSomeOne("sanj@","bhar@");
    g.followSomeOne("sanj@","ben@");
    g.followSomeOne("bhar@","ben@");
    g.followSomeOne("bhar@","sanj@");
    g.followSomeOne("bhar@","preth@");
    g.followSomeOne("yush@","bhar@");
    g.followSomeOne("yush@","preth@");
    g.followSomeOne("ben@","yush@");
    g.followSomeOne("ben@","bhar@");
    g.followSomeOne("ben@","neha@");
    g.followSomeOne("jeevi@","yush@");
    g.followSomeOne("jeevi@","neha@");

    cout<<endl<<"WELCOME TO SOCIAL WEB";
    cout<<endl<<"====================="<<endl<<endl;

    do{
        cout<<endl<<"What do you want to choose ? Enter 0 to exit";
        cout<<endl<<"--------------------------------------------"<<endl;
        cout<<endl<<"4) Print";
        cout<<endl<<"1) Login to existing Account";
        cout<<endl<<"2) Create new Account"<<endl;
        cin>>ch1;
        if (ch1==1){
            login_=g.login();
            if(login_==1){
                cout<<endl<<"Login successful !"<<endl;
                afterLogin(g);


            }
            else if (login_==2){
                cout<<endl<<"Incorrect Password ";
            }
            else{
                cout<<endl<<"User name you have entered doesnot exist !";
            }
        }
        else if(ch1==2){
            g.insertVertex();
        }
        else if (ch1==4){
            g.display();
        }   
    }while(ch1!=0);
}
