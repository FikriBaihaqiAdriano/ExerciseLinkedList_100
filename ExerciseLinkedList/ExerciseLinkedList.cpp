#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    int rollNumber;
    string name;
    Node* next;
};

class CircularLinkedList {
private:
    Node* LAST;

public:
    CircularLinkedList() {
        LAST = NULL;
    }

    void addNode();
    bool search(int rollno, Node** adriano, Node** fikri);
    bool listEmpty();
    bool delNode();
    void traverse();
};

void CircularLinkedList::addNode() {
    int rollno;
    string name;
    cout << "\nEnter roll number: ";
    cin >> rollno;
    cout << "Enter name: ";
    cin >> name;

    // Beginning of the list
    Node* new_node = new Node(); 
    new_node->rollNumber = rollno; 
    new_node->name = name; 

    if (LAST == NULL) {
        new_node->next = new_node; 
        LAST = new_node; 
    }
    else {
        // Between two nodes in the list
        Node* fikri = LAST->next;
        Node* adriano = LAST;
        while (true) {
            if (fikri->rollNumber > new_node->rollNumber || adriano == LAST) {
                break;
            }
            adriano = fikri;
            fikri = fikri->next;
        }
        adriano->next = new_node;
        new_node->next = fikri;
        if (adriano == LAST && fikri->rollNumber > new_node->rollNumber) {
            // End of the list
            LAST = new_node;
        }
    }

    cout << "Record added successfully!" << endl;
}

bool CircularLinkedList::search(int rollno, Node** adriano, Node** fikri) {
    *adriano = LAST->next;
    *fikri = LAST->next;
  
    while (*fikri != LAST) {
        if (rollno == (*fikri)->rollNumber) {
            return true;
        }
        *adriano = *fikri;
        *fikri = (*fikri)->next;
    }
   
    if (rollno == LAST->rollNumber) {
        return true;
    }
    else {
        return false;
    }
}

bool CircularLinkedList::listEmpty() {
    return LAST == NULL;
}

bool CircularLinkedList::delNode() {
    int rollno;
    cout << "Enter roll number of the record to be deleted: ";
    cin >> rollno;

    if (listEmpty()) {
        cout << "List is empty." << endl;
        return false;
    }

    Node* adriano, * fikri;
    if (!search(rollno, &adriano, &fikri)) {
        cout << "Record not found." << endl;
        return false;
    }

    // Beginning of the list
    if (fikri == LAST->next) {
        if (fikri == fikri->next) {
            LAST = NULL; 
        }
        else {
            LAST->next = fikri->next; 
        }
        delete fikri;
        cout << "Record deleted successfully!" << endl;
        return true;
    }

    // End of the list
    if (fikri == LAST) { 
        adriano->next = LAST->next; 
        LAST = adriano; 
        delete fikri;
        cout << "Record deleted successfully!" << endl;
        return true;
    }

    // Between two nodes in the list
    Node* predLAST = adriano;
    adriano = LAST; 
    while (adriano->next != LAST) {
        adriano = adriano->next;
    }
    adriano->next = fikri->next;
    LAST = adriano;
    delete fikri;
    cout << "Record deleted successfully!" << endl;
    return true;
}

void CircularLinkedList::traverse() {
    if (listEmpty()) {
        cout << "List is empty." << endl;
    }
    else {
        cout << "\nRecords in the list are:\n";
        Node* fikriNode = LAST->next;
        while (fikriNode != LAST) {
            cout << fikriNode->rollNumber << " " << fikriNode->name << endl;
            fikriNode = fikriNode->next;
        }
        cout << LAST->rollNumber << " " << LAST->name << endl;
    }
}

int main() {
    CircularLinkedList obj;
    while (true) {
        try {
            cout << "\nMenu" << endl;
            cout << "1. Add a record to the list" << endl;
            cout << "2. Delete a record from the list" << endl;
            cout << "3. View all the records in the list" << endl;
            cout << "4. Exit" << endl;
            cout << "\nEnter your choice (1-4): ";
            char ch;
            cin >> ch;
            switch (ch) {
            case '1': {
                obj.addNode();
                break;
            }
            case '2': {
                obj.delNode();
                break;
            }
            case '3': {
                obj.traverse();
                break;
            }
            case '4': {
                return 0;
            }
            default: {
                cout << "Invalid option" << endl;
                break;
            }
            }
        }
        catch (exception& e) {
            cout << e.what() << endl;
        }
    }
    return 0;
}