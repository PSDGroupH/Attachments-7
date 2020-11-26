/*
Kode ini 
*/
#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <fstream>

int main()
{
    double n, mean, stdev;
    std::ofstream file_output_csv, file_output_dat;
    std::cout << "===========================================================" << std::endl;
    std::cout << "GROUP H | Mesin Pembangkit Bilangan Acak Distribusi Normal" << std::endl;
    std::cout << "===========================================================" << std::endl;
input: 
    file_output_csv.open("data_keluaran.csv");
    file_output_dat.open("data_keluaran.dat");
    std::cout << "Masukan banyak percobaan: ";
    std::cin >> n;
    std::cout << "Masukan mean: ";
    std::cin >> mean;
    std::cout << "Masukan standar deviasi: ";
    std::cin >> stdev;

    std::default_random_engine generator;
    std::normal_distribution<double> dist(mean, stdev);

    std::vector<int>* generatedNum = new std::vector<int>;
    std::vector<std::vector<int>> numThatExist;
 
    for (int i = 0; i < n; i++) {
        generatedNum->push_back(dist(generator));
    }
    
    std::sort(generatedNum->begin(), generatedNum->end());

    int current = 0;
    bool reset = true;

    for (int i = 0; i < n; i++) {
        int firstKind = generatedNum->at(i);
        if (reset) { 
            numThatExist.push_back({ firstKind, 1 });
            reset = false;
            continue;
        }
        if (generatedNum->at(i) == firstKind) {
            numThatExist.at(current)[1] += 1;
        }
        if (i < n-1) {
            if (generatedNum->at(i + 1) != firstKind) {
                current += 1;
                reset = true;
            }
        }

    }
    file_output_csv << "Bilangan;Frekuensi Bilangan";
    for (int i = 0; i < numThatExist.size(); i++) {
        file_output_csv << numThatExist.at(i)[0] << ";" << numThatExist.at(i)[1] << '\n';
        file_output_dat << numThatExist.at(i)[0] << " " << numThatExist.at(i)[1] << '\n';
    }

    file_output_csv.close();
    file_output_dat.close();
    generatedNum->clear();
    delete generatedNum;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
