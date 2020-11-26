/*
Kode berikut adalah ditulis atas nama Kelompok H. 

Kode berikut ditulis dalam bahasa C++. Dalam kode berikut, kami tidak menggunakan library sebagai pembantu.

Dalam C++, untuk membuat sebuah grafik adalah bisa seperti kita menggunakan matplotlib (agaknya lucu menggunakan ini sebab matplotlib milik Python yang mana Python itu sendiri 
di tulis dalam C), gnuplot, koolplot, Qtplot dan lain sebagainnya. Sayangnya, kebanyakan library plotting untuk C++ adalah tua, kebanyakan support C++98 yang mana C++ yang 
kami tulis adalah dalam versi C++17. Demikian, kami memutuskan untuk menggunakan C++ sebagai "mesin" pembuat angka acak bedasarkan sebaran normal yang menghasilkan output
dalam bentuk CSV dan DAT. Kemudian dari titik-titik yang dihasilkan kami plotting menggunakan gnuplot.
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

