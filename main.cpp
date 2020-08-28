#include<iostream>
using namespace std;
/*
DESCRIPTION:
This structure consists of an character data field and a Node pointer to the next node which will be used to construct Linked List.
1.Addition of large numbers using linked list
2.Subtration of large numbers using linked list
3.Multiplication of large numbers using linked list(Karatsuba can be implemented or fast fourier transform)
*/
struct list
{
    char val;
    struct list *next;
    list(char v,list *l)
    {
        val=v;
        next=l;
    }
    list(char v)
    {
        val=v;
        next=NULL;
    }
    list(list *l)
    {
        next=l;
    }
};
struct list *buildString(string s1)
{
    struct list *temp,*newHead;
    temp=newHead=NULL;
    int n=s1.size();
    for(int i=0;i<n;i+=1)
    {
        if(temp==NULL)
        {
            struct list *temp1=new list(s1[i],NULL);
            temp=newHead=temp1;
            continue;
        }
        else
        {
            struct list *temp1=new list(s1[i],NULL);
            temp->next=temp1;
            temp=temp->next;
        }
    }
    return newHead;
}
void display(list *root)
{
    if(root==NULL)
    return;
    cout<<root->val;
    display(root->next);
}
struct list *reverseList(struct list *root)
{
    if(root->next==NULL)
    return root;
    struct list *newHead=reverseList(root->next);
    root->next->next=root;
    root->next=NULL;
    return newHead;
}
struct list *addition(struct list *root1,struct list *root2)
{
    struct list *s11=reverseList(root1);
    struct list *s1=s11;
    struct list *s22=reverseList(root2);
    struct list *s2=s22;
    struct list *newHead,*temp;
    newHead=NULL;
    temp=newHead;
    int carry=0;
    while(s1 && s2)
    {
        int rem=(s1->val-'0'+s2->val-'0'+carry)%10;
        if(newHead==NULL)
        {
            struct list *temp1=new list(rem+'0',NULL);
            newHead=temp1;
            temp=newHead;
        }
        else
        {
            struct list *temp1=new list(rem+'0',NULL);
            temp->next=temp1;
            temp=temp->next;
        }
        carry=(s1->val-'0'+s2->val-'0'+carry)/10;
        s1=s1->next;
        s2=s2->next;
    }
    while(s1)
    {
        int rem=(s1->val-'0'+carry)%10;
        struct list *temp1=new list(rem+'0',NULL);
        temp->next=temp1;
        temp=temp->next;
        carry=(s1->val-'0'+carry)/10;
        s1=s1->next;    
    }
    while(s2)
    {
        int rem=(s2->val-'0'+carry)%10;
        struct list *temp1=new list(rem+'0',NULL);
        temp->next=temp1;
        temp=temp->next;
        carry=(s2->val-'0'+carry)/10;
        s2=s2->next;
    }
    if(carry)
    {
        struct list *temp1=new list(carry+'0',NULL);
        temp->next=temp1;
    }
    //display(newHead);
   // root1=reverseList(s11);
    //root2=reverseList(s22);
    return newHead;
}
struct list *subtration(struct list *root1,struct list *root2)
{
    struct list *f1=root1;
    struct list *f2=root2;
    struct list *s11=reverseList(root1);
    struct list *s22=reverseList(root2);
    struct list *s1=s11;
    struct list *s2=s22;
    struct list *newHead,*temp;
    newHead=temp=NULL;
    int carry=0;
    while(s1 && s2)
    {
        int n1=s1->val-'0';
        int n2=s2->val-'0';
        if(n1-n2<0)
        {
            struct list *a=s1->next;
            while(a)
            {
                if(a->val-'0'!=0)
                {
                    int n=a->val-'0'-1;
                    a->val=n+'0';
                    break;
                }
                else
                {
                    a->val='9';
                }
                a=a->next;
            }
            n1+=10;
        }
        if(temp==NULL)
        {
            char c=(n1-n2)+'0';
            struct list *temp1=new list(c,NULL);
            newHead=temp1;
            temp=newHead;
        }
        else
        {
            char c=(n1-n2)+'0';
            struct list *temp1=new list(c,NULL);
            temp->next=temp1;
            temp=temp->next;
        }
        s1=s1->next;
        s2=s2->next;
    }
    while(s1)
    {
        struct list *temp1=new list(s1->val,NULL);
        temp->next=temp1;
        temp=temp->next;
        s1=s1->next;
    }
    root1=f1;
    root2=f2;
    return reverseList(newHead);
}
struct list *multiplication(struct list *root1,struct list *root2)
{
    struct list *s1=reverseList(root1);
    struct list *s2=reverseList(root2);
    struct list *ans,*temp;
    ans=temp=NULL;
    int pos=0;
    for(struct list *a1=s1;a1!=NULL;a1=a1->next)
    {
        struct list *temp1=NULL,*newHead;
        int carry=0;
        for(int i=0;i<pos;i+=1)
        {
            if(temp1==NULL)
            {
                struct list *temp=new list('0',NULL);
                newHead=temp;
                temp1=newHead;
            }
            else
            {
                struct list *temp=new list('0',NULL);
                temp1->next=temp;
                temp1=temp1->next;
            }
        }
        for(struct list *a2=s2;a2!=NULL;a2=a2->next)
        {
            int n1=a1->val-'0';
            int n2=a2->val-'0';
            int rem=(n1*n2+carry)%10;
            carry=(n1*n2+carry)/10;
            if(temp1==NULL)
            {
                struct list *temp=new list(rem+'0',NULL);
                newHead=temp;
                temp1=newHead;
            }
            else
            {
                struct list *temp=new list(rem+'0',NULL);
                temp1->next=temp;
                temp1=temp1->next;
            }
        }
        if(carry)
        {
            struct list *temp=new list(carry+'0',NULL);
            temp1->next=temp;
        }
        if(ans==NULL)
        {
            ans=newHead;
        }
        else
        {
            ans=addition(reverseList(ans),reverseList(newHead));
        }
        pos+=1;   
    }
    return reverseList(ans);
}
int main()
{
    string str1,str2;
    cout<<"Enter the two strings"<<endl;
    cin>>str1>>str2;
    while(1)
    {
        cout<<"Enter the choice"<<endl;
        cout<<"1. Addition"<<endl;
        cout<<"2. Subtraction"<<endl;
        cout<<"3. Multiplication"<<endl;
        cout<<"4. Exit"<<endl;
        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            struct list *root1,*root2;
            root1=buildString(str1);
            root2=buildString(str2);
            struct list *ans=addition(root1,root2);
            cout<<"ADDITION OF TWO BIG INTEGERS IS"<<endl;
            display(reverseList(ans));
            cout<<endl;
        }
        else if(ch==2)
        {
            struct list *root1,*root2;
            root1=buildString(str1);
            root2=buildString(str2);
            struct list *ans=subtration(root1,root2);
            cout<<"SUBTRACTION OF TWO BIG INTEGERS IS"<<endl;
            display(ans);
            cout<<endl;
        }
        else if(ch==3)
        {
            struct list *root1,*root2;
            root1=buildString(str1);
            root2=buildString(str2);
            struct list *ans=multiplication(root1,root2);
            cout<<"MULTIPLICATION OF TWO BIG INTEGERS IS"<<endl;
            display(ans);
            cout<<endl;
        }
        else
        return 0;
    }
    return 0;
}