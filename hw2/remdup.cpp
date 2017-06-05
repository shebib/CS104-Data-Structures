#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;
/*
 * Reads in two lines of ints into two linkedlists
 * then removes duplicates from the first list,
 * and concatenates it with the second list
 * Takes in two args: input.txt output.txt
 * Daniel Shebib
 */

//Stores an int, used for the linklist
struct Item {
    int val;
    Item* next;
};

void removeDuplicates(Item * head);
void readLists(Item*& head1, Item*& head2, char* argv[]);
Item* concatenateLists(Item* head1, Item* head2);
void listadd(Item*& head, int in);
void outputList(Item* head, char*  argv[]);
void catHelp(Item* ptr1, Item* ptr2, Item*& head3);
void remove(Item* head);

//Runs the program, with two arguments.
int main(int argc, char* argv[])
{
    if(argc != 3) { //Check number of arguments 
        cout << "Error: Please enter 2 arguments: [[input.txt]] [[output.txt]]";
        exit(1);
    }
    Item* head1;
    Item* head2;
    readLists(head1, head2, argv);
    removeDuplicates(head1);
    Item* head3;
    head3 = concatenateLists(head1, head2);
    outputList(head3, argv);
    remove(head1);//clean up memory
    remove(head2);
    remove(head3);
    return 0;
}

//Reads in ints from first two lines of a file and puts the in
//two separate linkedlists, head1 and head2
void readLists(Item*& head1, Item*& head2, char* argv[])
{
    ifstream fin(argv[1]);
    if (!fin.good()) { //check if file exists
        cout << "Error: File not found";
        fin.close();
        exit(1);
    }
    
    //first list
    string in;
    getline(fin, in);
    stringstream sin(in);
    head1 = NULL;
    while (sin.peek()!= EOF)
    {
        int tmp;
        sin >> tmp;
        listadd(head1, tmp);
    }
    
    //second list
    getline(fin, in);
    stringstream sin2(in);
    head2 = NULL;
    while (sin2.peek()!= EOF)
    {
        int tmp;
        sin2 >> tmp;
        listadd(head2, tmp);
    }
    fin.close();
}

//Adds an int to the list pointed to by head
void listadd(Item*& head, int in)
{
    if(head == NULL)//if list is empty
    {
        head = new Item;
        head->val = in;
        head->next = NULL;
        return;
    }
    Item* ptr = head;
    while (ptr->next != NULL) //traverse list
    {
        ptr = ptr->next;
    }
    ptr->next = new Item;
    ptr = ptr->next;
    ptr->val = in;
    ptr->next = NULL;
}

//Removes duplicates from the linkedlist pointed to by head
void removeDuplicates(Item* head)
{
    if(head == NULL)
        return;
    if(head->next == NULL)
        return;
    if(head->val == head->next->val)//if there is a duplicate
    {
        Item* tmp = head->next->next;
        delete head->next;
        head->next = tmp; 
        removeDuplicates(head);
    }
    else //move on
    {
    removeDuplicates(head->next);
    }
}

//Concatenates two linkedlists into one, returning the head pointer
//Order is first list, then second list
Item* concatenateLists(Item* head1, Item* head2)
{
    Item* head3 = NULL;
    catHelp(head1, head2, head3);
    return head3;
}

//Helper recursive function for concatentateLists()
void catHelp(Item* ptr1, Item* ptr2, Item*& head3)
{
    if(ptr1 == NULL)//end of first list
    {
        if(ptr2 == NULL)//end of second list
        {
            return;
        }
        else
        {
            listadd(head3, ptr2->val);
            catHelp(ptr1, ptr2->next, head3);
        }
    }
    else
    {
        listadd(head3, ptr1->val);
        catHelp(ptr1->next, ptr2, head3);
    }
}

//outputs the list pointed to by head3 to the second argument
//passed in
void outputList(Item* head3, char* argv[])
{
    ofstream fout; //initialize file output
    fout.open(argv[2]);
    if(!fout.is_open()) {//make sure output file opens
        cout << "Error: Could not create output file";
        fout.close();
        exit(1);
    }

    Item* ptr = head3;
    while (ptr != NULL)
    {
        fout << ptr->val << " ";
        ptr = ptr->next;
    }
    fout.close();
}

//Deletes the list pointed to by head
void remove(Item* head)
{
    if(head == NULL)
        return;
    else if(head->next == NULL)
    {
        delete head;
        head = NULL;
        remove(head);
    }
    else
    {
    Item* ptr = head;
    while(ptr->next->next!=NULL)
    {
        ptr = ptr->next;
    }
    delete ptr->next;
    ptr->next = NULL;
    remove(head);
    }
}

