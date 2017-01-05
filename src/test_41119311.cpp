#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

void saveBarChartToFile(vector<int>numbers) {
    ofstream outputfile;

    outputfile.open("graph.txt", std::ios_base::app);


    if (!outputfile.is_open()) {
        cout << "FILE NOT OPEN ERROR!";
    } else {
        for (int i = 0; i < numbers.size(); i++) {
            int stars = 0;
            int starAmount = numbers[i] / 100;
            outputfile << "Shop" << (i + 1) << ":";
            for (int j = 0; j < starAmount; j++) {
                outputfile << "*";
            }
            outputfile << "/n";
        }
        outputfile.close();
    }
}

int main(int argc, char* argv[]) {
    vector<int> sale;
    sale.push_back(40000);
    sale.push_back(50000);
    sale.push_back(60000);
    saveBarChartToFile(sale);

}

