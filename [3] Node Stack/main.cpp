#include <iostream>
#include <string>
using namespace std;

//need a NODE structure //struct is a keyword, a structure is a thing has a more than 1 component //struct only holds things
struct node
{
	int data;
	struct node *next;
	struct node *previous;
};

//Create a class STACK
//class is like struct that can hold things
//but it can also do things
class stack
{
	struct node *top;
	struct node *bottom;

	public:
	stack() // constructor, is a function that is called when the class is created
	{
		top=NULL;
		bottom=NULL;
   }
int pushBack(int item); //puts in a new item at the back
int popBack(); //removes the last item
int topItem(); //returns the top(last) item without removing it

int pushFront(int item); //puts in a new item at the front
int popFront(); //removes the first item
int bottomItem(); //returns the bottom(first) item without removing it

int size(); //returns the stack size
int showAllFromTop(); //shows each item from the top to the bottom without removing anything
int showAllFromBottom(); //shows each item from the bottom to the top without removing anything

int isEmpty();
};

//pushBack
int stack::pushBack(int item)
{
	struct node *newNodePointer = new node; //allocate memory
	newNodePointer->data = item; //assign value
	newNodePointer->next = NULL; //not necessary but just for safety
	if(top!=NULL)
	{
	    top->next = newNodePointer; //hook up top's prev to new
	    newNodePointer->previous = top;
	} else {
	    bottom = newNodePointer; //moves bottom to new node
	    newNodePointer->previous = NULL;
	}
	top = newNodePointer; //moves top to new node
	return 0;
}

//PUSHFRONT
int stack::pushFront(int item)
{
   struct node *newNodePointer = new node;
	newNodePointer->data = item;
	newNodePointer->previous = NULL;
	if(bottom!=NULL)
	{
	    bottom->previous = newNodePointer;
	    newNodePointer->next=bottom;
	}else{
	    top = newNodePointer;
	    newNodePointer->next = NULL;
	}
	bottom = newNodePointer;
	return 0;
}

//POP
int stack::popBack()
{
   if (top == NULL) return 1; //error can't pop empty stack
	struct node *tempnodepointer = top;
	top = tempnodepointer->previous; //top is now the 2nd top
	delete tempnodepointer;
	top->next=NULL; //2nd top's next is now NULL because the top has been deleted
	return 0; //successfully popped item
}

int stack::popFront()
{
   if (bottom == NULL) return 1;
   struct node *tempnodepointer2 = bottom;
   bottom = tempnodepointer2->next;
   delete tempnodepointer2;
   bottom->previous=NULL;
   return 0;
}

//SHOWS ALL NODES
int stack::showAllFromTop()
{
	struct node * tempnodepointer = top;
	cout <<"---Top of Stack---" << endl;
	while(tempnodepointer!=NULL)
	{
		cout << tempnodepointer->data << endl;
		tempnodepointer=tempnodepointer->previous;
	}
	cout <<"---Bottom of Stack---" << endl;
	return 0;
}

int stack::showAllFromBottom()
{
	struct node * tempnodepointer = bottom;
	cout <<"---Bottom of Stack---" << endl;
	while(tempnodepointer!=NULL)
	{
		cout << tempnodepointer->data << endl;
		tempnodepointer=tempnodepointer->next;
	}
	cout <<"---Top of Stack---" << endl;
	return 0;
}

int stack::bottomItem()
{
   if (bottom == NULL)
   {
       showAllFromBottom();
       cout << "The stack is empty" << endl << endl;
       return 1;
   }
   //showAllFromBottom();
   cout << "The bottom item is " << bottom->data << endl << endl;
   return 0;
}

int stack::topItem()
{
   if (top == NULL)
   {
       showAllFromTop();
       cout << "The stack is empty" << endl << endl;
       return 1;
   }
   showAllFromTop();
   cout << "The top item is " << top->data << endl << endl;
   return 0;
}

int stack::isEmpty(){
    if (top == bottom && top == NULL){
        cout << "The stack is empty." << endl << endl;
    }
    else{
        cout << "The stack is not empty." << endl << endl;
    }
}

int main()
{
   stack myStack;
   myStack.isEmpty();
   myStack.pushFront(1);
   myStack.pushFront(2);
   myStack.pushFront(3);
   myStack.bottomItem();
   myStack.pushFront(4);
   myStack.pushFront(5);
   myStack.pushFront(6);
   myStack.popFront();
   myStack.popBack();
   myStack.bottomItem();
   myStack.pushFront(7);
   myStack.pushFront(8);
   myStack.pushFront(9);
   myStack.isEmpty();
   myStack.showAllFromTop();
}
