#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct Node {
    string payload;
    Node* next;
};

Node* newNode(string payload) {
    Node* t;
    t->payload = payload; 
    return t;
}

Node* loadGame(int n, vector<string> names) {
    Node* head = nullptr;
    //Node* prev = nullptr;
    string name;
   //push back the names in reverse order so we get the list of names in normal order
    for (int i = n; i > 0; --i) {
        name = names.at(i);
        Node* t = head;
        head = newNode(name);
        head->next = t;
        
    }
    cout <<"hi" << endl;
   //make circular
   Node* temp = head;
   while(temp->next != nullptr)
   {
      if(temp->next == nullptr)
      {
         cout << "hello" <<endl;
         temp->next = head;
         break;
      }
      temp = temp->next;
   }
   return head;
}

void print(Node* start) { // prints list
    Node* curr = start;
    while (curr != nullptr) {
        cout << curr->payload << endl;
        curr = curr->next;
        if (curr == start) {
            break; // exit circular list
        }
    }
}

Node* runGame(Node* start, int k) { // josephus w circular list, k = num skips
    Node* curr = start;
    Node* prev = curr;
    while (true/** fill in this code **/) { // exit condition, last person standing
        for (int i = 0; i < k; ++i) { // find kth node
          /** fill in this code   
          **/
        }

        /** fill in this code **/ // delete kth node
        delete curr;
        /** fill in this code **/
    }

    return curr; // last person standing
}

/* Driver program to test above functions */
int main() {
    int n=1, k=1;//, max; // n = num names; k = num skips (minus 1)
    string name;
    vector<string> names;

    // get inputs
    cin >> n >> k;
    while (cin >> name && name != ".") { names.push_back(name); } // EOF or . ends input

    // initialize and run game
    Node* startPerson = loadGame(n, names);
   // print(startPerson);
    /*
    Node* lastPerson = runGame(startPerson, k);

    if (lastPerson != nullptr) {
        cout << lastPerson->payload << " wins!" << endl;
    } else {
        cout << "error: null game" << endl;
    }
   */
    return 0;
}

