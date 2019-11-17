#include<iostream>
using namespace std;

int count=0;

class node
{
    public:
    char ok;
    char rw;
    int uy;
    node *left;
    node *right;
    node()
    {
        rw='0';                          //for '$'(insert) or'%'(delete)
        uy=0;                            //for augumenting the size of node while insertion 
        ok='3';                             //or deletion
        left=NULL;
        right=NULL;                     //left node for zero and right node for one.
    }
};

class tries
{
    public:
        node *root;
        tries()
        {
            root=new node();                //root cannot be null as it is not containing any thing.
        }
        int search(string f);
        void insert(string b);              //insert for making suffix trie of the given string.
        void insert1(string b);             //insert1 only for given string by the user.
        void remove(string b);              //removing from suffix trie.
        void remove1(string b);             //removing from single string trie.
        int search1(string b);  
        void search2(string p);
        int searchx(node *g,string p,int io,int j);         //this search is called by search2.
};

int tries::search(string b)
{
    node *temp=root;
        int i;
        for(i=0;i<32;i++)                   //searching for the string provided by the user for both the trie,  
        {                                   //as if the main stirng is present in the trie then its suffix will also be present.
            if(temp!=NULL)
            {
                if(b[i]=='0')
                {
                    temp=temp->left;
                }
                else
                {
                    temp=temp->right;
                }
            }
            else
            {
                break;
            }
        }
        if(temp==NULL)          //if in the middle of search temp becomes nill the it is not present. 
        {
            return 0;
        }
        else if(temp->rw=='$')          //if $ is there then the string is present.
        {
            return 1;
        }
        else
        {
            return 0;
        }
}

void tries::insert1(string b)
{
    if(search(b)==0)
    {
        node *qw=root;
        int i;
        for(i=0;i<32;i++)                   //inserting the string provided by the user.
        {
            if(b[i]=='0')                   //if the bit is 0.
            {
                if(qw->left!=NULL)
                {
                    qw=qw->left;            //if it is present then go to the left 
                    qw->uy=(qw->uy)+1;
                }
                else
                {
                    qw->left=new node();       //else make a new node first then 
                    qw=qw->left;               //go to the left 
                    qw->ok='0';                //and insert the bit.
                    qw->uy=(qw->uy)+1;
                }
            }
            else if(b[i]=='1')              //do the same as above if the bit is 1.
            {
                if(qw->right!=NULL)
                {
                    qw=qw->right;
                    qw->uy=(qw->uy)+1;
                }
                else
                {
                    qw->right=new node();
                    qw=qw->right;
                    qw->ok='1';
                    qw->uy=(qw->uy)+1;
                }
            }
        }
    qw->rw='$';             //to tell that the string is inserted and one cannot insert it again.
    }
    else
    {
        return ;
    }   
}

void tries::insert(string f)
{
    if(search(f)==0)
    {
        node *y=new node();
            int i,jk;
            for(i=0;i<32;i++)           //intserting in the suffix trie.
            {
                y=root;
                for(jk=i;jk<32;jk++)
                {
                    if(f[jk]=='0')
                    {
                        if(y->left!=NULL)
                        {
                            y=y->left;
                            y->uy=(y->uy)+1;            //increasing the size.
                        }
                        else
                        {
                            y->left=new node();
                            y=y->left;
                            y->ok='0';
                            y->uy=(y->uy)+1;           
                        }
                    }
                    else if(f[jk]=='1')
                    {
                        if(y->right!=NULL)
                        {
                            y=y->right;
                            y->uy=(y->uy)+1;
                        }
                        else
                        {
                            y->right=new node();
                            y=y->right;
                            y->ok='1';
                            y->uy=(y->uy)+1;
                        }
                    }
                }
                if(y!=NULL&& y->rw=='$')
                {
                    continue;
                }
                else
                {
                    y->rw='$';
                }
            }
    }
    else
    {
        return;
    }
}

void tries::remove(string f)
{
    if(search(f)==0)
    {
        return;
    }
    else
    {
        node *y=root;                   //removing from the suffix trie.
        int i,jk;
        for(i=0;i<32;i++)
        {
            y=root;
            for(jk=i;jk<32;jk++)
            {
                if(f[jk]=='0')
                {
                    y=y->left;
                    y->uy=(y->uy)-1;
                }
                else if(f[jk]=='1')
                {
                    y=y->right;
                    y->uy=(y->uy)-1;
                }
            }
            y->rw='%';          //to tell that that string is deleted and 
        }                       //if one want to insert it again,it can be inserted.
    }
}

void tries::remove1(string b)
{
    if(search(b)==0)
    {
        return;
    }
    else
    {
        node *y=root;           //deleting from a single string trie.
        int i;
        for(i=0;i<32;i++)
        {
            if(b[i]=='0')
            {
                y=y->left;
                y->uy=(y->uy)-1;
            }
            else if(b[i]=='1')
            {
                y=y->right;
                y->uy=(y->uy)-1;
            }
        }
        y->rw='%';          //to tell that it is deleted.
    }
}

int tries::searchx(node *temp,string p,int io,int j)
{                                           //searching for the same prefix string and adding the 
        if(io==j)                    //length of the matching part of string with the substring provided.
        {
            return 0;                         //this function will have a recursive call for
        }                                     //counting the left and the right part both if 
        else                                  //'?' is present.
        {
            if(io<j)
            {
                if(p[io]=='1')                      //if it is 1 calling the same function for the right part.
                {
                    if(temp->right!=NULL)             //if it is null then no need to call.
                    {
                        temp=temp->right;
                        count=count+(temp->uy);        //adding the size of that node to the value of count.
                        searchx(temp,p,io+1,j);
                    }
                }
                if(p[io]=='0')              //if it is 0 calling the same function for the left part.
                {
                    if(temp->left!=NULL)        //if it is null then no need to call.
                    {
                        temp=temp->left;
                        count=count+(temp->uy);        //adding the size of that node to the value of count.
                        searchx(temp,p,io+1,j);
                    }
                }
                if(p[io]=='?')                     //if  it is '?' then we need to call the same function both for
                {                                   //left and right part.
                    if(temp->left!=NULL)
                    {
                        count=count+(temp->left->uy);       //adding the size of that node to the value of count.
                        searchx(temp->left,p,io+1,j);
                    }
                    if(temp->right!=NULL)
                    {   
                        count=count+(temp->right->uy);
                        searchx(temp->right,p,io+1,j);
                    }
                }
            }
        }
}

int tries::search1(string b)
{
    node *temp=root;
    int j=0;
    while(b[j]!='\0')               //calculating the length of the substring. 
    {
        j++;                        //provided by the user.
    }
    int i;
    for(i=0;i<j;i++)
    {
        if(temp!=NULL)                      //due to augumenting the suffix tree, no. of times the 
        {                                   //substring is present in the string will be counted
            if(b[i]=='0')                   //which is equal to the no. of times it will go to the same path
                {                           //to insert a suffix.
                    temp=temp->left;
                }
                else
                {
                    temp=temp->right;
                }
        }
            else
            {
                break;
            }
    }
    if(i==j)                        //if i==j then only the substring to be found will be 
    {                               //present otherwise not.
        return (temp->uy);  
    }
    else
    {
        return 0;
    }
}

void tries::search2(string p)
{
    node *temp=root;                //this will search in the single string trie.
    int j=0;
    while(p[j]!='\0')               //calulating the lenght of the substring provided.
    {
        j++;
    }
    searchx(temp,p,0,j);            //calling the function.
    return ;
}

int main()
{
    tries rs;
    tries as;
    int m;
    cin>>m;
    int i;
    for(i=1;i<=m;i++)
    {
        int cas;
        cin>>cas;
        if(cas==1)
        {
            string b;
            cin>>b;
            rs.insert(b);
            as.insert1(b);
        }
        else if(cas==2)
        {
            string b;
            cin>>b;
            rs.remove(b);
            as.remove1(b);
        }
        else if(cas==3)
        {
            string p;
            cin>>p;
            int op=rs.search1(p);
            cout<<op<<endl;
        }
        else if(cas==4)
        {
            string p;
            cin>>p;
            count=0;                 //for every search we need to initialize the value of count with zero.
            as.search2(p);
            cout<<count<<endl;
        }
    }
}