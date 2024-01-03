#include <iostream>
#include "Node.h"
#include "Student.h"
#include <cstring>

using namespace std;
void ADD(Node* node, Node* &head, Node* current, Node* previous);
void PRINT(Node* head, Node* current);
void DELETE(Node* &head, int deleteid, Node* &current);
void AVERAGE(Node* head, int sum, Node* current, int count);
// main
// by anika gupta
// date: 12/12/23
//linked lists: nodes with student pointer in order of increasing ID #.
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
      float GPA;
      cin >> GPA;
      student->setGPA(GPA);
      
      Node* node = new Node(student);
      
      ADD(node, head, head, head);
    }
    else if (strcmp(input, "PRINT") ==0) {
      //cout << "printing" << endl;
      PRINT(head, head);
    }
    else if (strcmp(input, "DELETE") ==0) {
      //cout << "deleting" << endl;
      cout << "id of what you want to delete " << endl;
      int deleteid;
      cin >> deleteid;
      DELETE(head, deleteid, head);
    }
    else if (strcmp(input, "AVERAGE")==0) {
      AVERAGE(head, 0, head, 0);
    }

  }
  
  return 0;
}
void ADD(Node* node, Node* &head, Node* current, Node* previous) {
  // adds nodes in increasing order according to id.
  //cout << "in the adding place" << endl;
  if (head==NULL) {
    head = node;
    return;
  }
  
  //Node* current = head;
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

void PRINT(Node* head, Node* current) {

  /*
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
  } */

  
    Node* Current = current ;
    if (Current!= NULL  ) {
      cout << Current->getStudent()->getFName() ;
      cout << "  " << current->getStudent()->getLName() ;
      cout << "  ID: " << current->getStudent()->getID();
      cout << "  GPA: " << current->getStudent()->getGPA() << endl;
      Current = current->getNext() ;
      PRINT(head, Current);

    }

    /*
    if (current != NULL) {
      cout << current->getStudent()->getFName() << " " << current->getStudent()->getLName() << "   ID: " << current->getStudent()->getID() << "  GPA: " << current->getStudent()->getGPA()<< endl;

    } */
    //if (current->getNext() == NULL) {
    //cout << current->getStudent()->getFName() << " " << current->getStudent()->getLName() << "   ID: " << current->getStudent()->getID() << "  GPA: " << current->getStudent()->getGPA()<< endl;
      //cout << "next is null " << endl;
      //return;
      //}



   
}

void DELETE(Node* &head, int deleteid, Node* &current) {
  //deletes a student given an ID.

  /*
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

  */
  Node* Current = current ;
  if (head->getStudent() ->getID() ==deleteid) {
    if (current->getNext() != NULL) {
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
  else if (Current->getNext()->getStudent() ->getID() == deleteid) {
    Current->setNext((Current->getNext())->getNext() ) ;
    Current->getNext() -> ~Node();
  }
  else {
    // Node* Current = current ;
    Current = Current->getNext() ;
    DELETE(head, deleteid, Current) ;
  }

  
}

void AVERAGE(Node* head, int sum, Node* current, int count) {
  //prints out average gpa of all students
  cout.setf(ios::fixed, ios::floatfield);
  cout.precision(2); // for 2 decimal places printing out GPA avg

  /*
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
    //cout << "total: " << avg << endl;
    //cout << "count: " << count << endl;
    avg = avg / count ;
    cout << "average: " << avg << endl;
  */

  Node* Current = current;
  cout << "Reached average " << endl;

  /*if (current == NULL) {
    cout << "no students.." << endl;
    return;
  }
  */
  if (current!= NULL) {
    sum = sum + Current->getStudent()->getID() ;
    count ++ ;
    Current = Current->getNext();
    AVERAGE(head, sum, Current, count);
  }
  /*
  if (Current->getNext() != NULL) {
    cout << "current get next isn't null" << endl;
    sum = sum + Current->getStudent()->getID() ;
    count++;
    cout << "added to sum of: " << sum << endl;
    Current = Current->getNext();
    AVERAGE(head, sum, Current, count);

  }

  */
  //sum = sum + Current->getNext()->getStudent()->getID() ;
  if (current == NULL) {
    //cout << "sum is: " << sum << endl;
  //count ++ ;
  int avg = sum / count ;
  //cout << "count is: " << count << endl;
  cout << "avg is: " << avg << endl;

  }
  
  
}
