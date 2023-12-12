#include <iostream>
#include "Node.h"
#include "Student.h"
#include <cstring>

using namespace std;
void ADD(Node* node, Node* &head);
void PRINT(Node* head);
void DELETE(Node* &head);
void AVERAGE(Node* head);
// main
// by anika gupta
int main() {
  Node* head = NULL;
  int quit = 0;
  cout << "What would you like to do?" << endl;
  while (quit==0) {
    char input[15];
    cout << "  Options: ADD   PRINT   DELETE  QUIT  AVERAGE" << endl;
    cin >> input;
    if (strcmp(input, "QUIT")==0) {
      quit = 1;
    }
    else if (strcmp(input, "ADD")==0) {
      //cout << "adding" << endl;
      Student* student = new Student();

      //id
      cout << "ID: " ;
      int id;
      cin >> id;
      student->setID(id);

      //first name
      cout << "First Name: " ;
      char fName[15];
      cin >> fName;
      student->setFName(fName);

      //last name
      cout << "Last Name: " ;
      char lName[15];
      cin >> lName;
      student->setLName(lName);

      //gpa
      cout << "GPA: " ;
      int GPA;
      cin >> GPA;
      student->setGPA(GPA);
      
      Node* node = new Node(student);
      
      ADD(node, head);
    }
    else if (strcmp(input, "PRINT") ==0) {
      //cout << "printing" << endl;
      PRINT(head);
    }
    else if (strcmp(input, "DELETE") ==0) {
      //cout << "deleting" << endl;
      DELETE(head);
    }
    else if (strcmp(input, "AVERAGE")==0) {
      AVERAGE(head);
    }
    else {
      cout << "I don't understand what you're trying to say..." << endl;
    }

  }
  
  return 0;
}
void ADD(Node* node, Node* &head) {
  // adds nodes in increasing order according to id.
  //cout << "in the adding place" << endl;
  if (head==NULL) {
    head = node;
    return;
  }
  Node* current = head;
  if (current->getNext()==NULL) { // if only 1 value is there
    
    if (current->getStudent()->getID() > node->getStudent()->getID()) {
      // current > head so they switch.
      head=node;
      head->setNext(current);
      current->setNext(NULL);
    }
    else {
      // head < current, so it goes in proper order.
      head->setNext(node);
      node->setNext(NULL);
    }
    return;
  }

  else if (head->getStudent()->getID() > node->getStudent()->getID() ) {
    // if head is greater than current node, current node becomes new head
    current = head;
    head=node;
    head->setNext(current);
  }
 
  else {
    current = head->getNext();
    Node* previous = head; // one node behind current
    while (current->getNext()!=NULL && ((current->getStudent()->getID()) < (node->getStudent()->getID()))) {
        // if the current node, which starts at next after head, has a smaller id than the next one, then current jumps to the next node
        current = current->getNext();
	previous = previous->getNext();
     }
    if (node->getStudent()->getID() > current->getStudent()->getID() ) {
      //catches exception for when next==null, so while loop iterates one less time.
      previous->setNext(current);
      current->setNext(node);
    }
    else {
      //for all other values than if next==null
      previous->setNext(node);
      node->setNext(current);
    }
    
  }
}

void PRINT(Node* head) {
  // prints the nodes
  //cout << "in printing function" << endl;
  Node* current = head;
  int count = 0;
  cout.setf(ios::fixed, ios::floatfield);
  cout.precision(2); // for 2 decimal places GPA.
  while (current!=NULL && current->getNext()!=NULL) {
    count ++;
    cout << current->getStudent()->getFName();
    cout << " " << current->getStudent()->getLName() ;
    cout << "   ID: ";
    cout << current->getStudent()->getID();
    cout << "   GPA: " << current->getStudent()->getGPA() << endl;
    current = current->getNext();
    //cout << current->getStudent()->getFName() << endl;
   }
  //cout << "count: " << count << endl
  if (current!=NULL) {
    cout << current->getStudent()->getFName() << " " << current->getStudent()->getLName() << "   ID: " << current->getStudent()->getID() << "  GPA: " << current->getStudent()->getGPA()<< endl;
  }
  else {
    cout << "nobody... :( " << endl;
  }
}

void DELETE(Node* &head) {
  //deletes a student given an ID.
  cout << "ID of student to delete: " ;
  int IDdelete;
  cin >> IDdelete;
  Node* current = head;

  if (current->getStudent()->getID() == IDdelete) {
    //if head is thing to delete
    if (current->getNext() !=NULL) {
      Node* next = head->getNext();
      head->~Node();
      head = next;
      
    }
    else {
      head->setNext(NULL);
      head->~Node();
      head = NULL;
    }
    
  }

  else {
    if (current->getNext() != NULL) {
      Node* previous = head;
      Node* current = previous->getNext();
      while (current->getNext()!=NULL) {
	if (current->getStudent()->getID() ==IDdelete) {
	  previous->setNext(current->getNext());
	  current->~Node();
	  return;
	}
      }
      // checking for last value...
      if (current->getStudent()->getID() ==IDdelete) {
	previous->setNext(NULL);
	current->~Node();
      }
    }
    
  }

  
}

void AVERAGE(Node* head) {
  //prints out average gpa of all students
  cout.setf(ios::fixed, ios::floatfield);
  cout.precision(2); // for 2 decimal places printing out GPA avg
  cout << " in avg function" << endl;
  float avg = 0;
  Node* current = head;
  if (current==NULL) {
    cout << "No students..." << endl;
  }
  else if (current->getNext() ==NULL) {
    avg = current->getStudent()->getGPA();
  }
  else {
    int count = 1;
    while(current->getNext() !=NULL) {
      avg += current->getStudent()->getGPA();
      current = current->getNext();
      count ++;
    }
    //now add the last value
    avg += current->getStudent()->getGPA();
    //count++;
    cout << "total: " << avg << endl;
    cout << "count: " << count << endl;
    avg = avg / count ;
    cout << "average: " << avg << endl;
  }
}
