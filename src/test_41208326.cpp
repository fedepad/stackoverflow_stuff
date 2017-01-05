#include <iostream>
#include <fstream>

using namespace std;

void Export(int data) {
    ofstream out("structures_initial.txt", ios::app);
    out << data << endl;
}


int main() {

    for (int i = 0; i < 10; i++) { //I declared i's type but still the same
        Export(i);
    }
    return 0;
}


//void Export(int data) {
//	ofstream out("structures_initial.txt", ios::app);
//	out << data << endl;
//}

