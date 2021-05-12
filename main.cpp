/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: li471
 *
 * Created on 20 de abril de 2021, 11:41
 */

#include <cstdlib>
#include <chrono>
#include "BinarySearchTree.h"
#include "TransactionManagerAVL.h"
#include <vector>
#include <math.h>
using namespace std;
#include <iomanip>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include<utility>

/**
 * Splitter  de l'input segons el dilimitador
 * @param _string el string que es vol fer split
 * @param delimiter el delimitador que es vol fer split
 * @param output l'output en el que es vol guardar les paraules que s'han fet split
 */
void splitter(string const & _string, const char delimiter, vector<string> &output) {
    stringstream string_s(_string);
    string save;
    while (getline(string_s, save, delimiter)) {
        output.push_back(save);
    }
}

/**
 * Mètode que verifica si l'input és un nombre enter
 * @param digit l'input
 * @return false si no és enter; true si és enter.
 */

bool isInteger(string digit) {
    bool is_integer = true;
    if (digit.size() == 0) {
        is_integer = false;
    } else {
        if ((digit[0] != '+' or digit[0] != '-') and !isdigit(digit[0]))
            is_integer = false;
        for (int i = 1; i < digit.size() && is_integer; i++) {
            if (!isdigit(digit[i])) {
                is_integer = false;
            }
        }
    }
    return is_integer;
}

void isData(string dia, string hora) {
    vector<string> vect;
    splitter(dia, '-', vect);
    splitter(hora, ':', vect);
    if (vect.size() != 5)
        throw invalid_argument("Wrong data format");
    if (!isInteger(vect[0]) or vect[0].size() != 4)
        throw invalid_argument("Wrong data format");
    if (!isInteger(vect[1]) or vect[1].size() != 2 or vect[1] < "0" or vect[1] > "12")
        throw invalid_argument("Wrong data format");
    if (!isInteger(vect[2]) or vect[2].size() != 2 or vect[2] < "0" or vect[2] > "31")
        throw invalid_argument("Wrong data format");
    if (!isInteger(vect[3]) or vect[3].size() != 2 or vect[3] < "0" or vect[3] >= "24")
        throw invalid_argument("Wrong data format");
    if (!isInteger(vect[3]) or vect[3].size() != 2 or vect[3] < "0" or vect[3] >= "60")
        throw invalid_argument("Wrong data format");
}

/**
 * Mètode que verifica l'existècia d'un fitxer
 * @param name nombre del fitxer
 * @return true si existeix; false si no existeix
 */

int fileExists(string const& name) {
    ifstream f(name.c_str());
    if (!f.good())
        throw invalid_argument("Fitxer no trobat");
    return 0;
}

/**
 * Mostra el menú i demana a l'usuari l'opció que vol accedir
 * @param arr_options menú dels opcions
 * @return l'opció seleccionat per l'usuari
 */

int showMenu(vector<string> arr_options, string& input) {
    int option = -1;
    cout << "Hola, que vols fer?" << endl;
    for (int i = 0; i < arr_options.size(); i += 1) {
        cout << (i + 1) << ". " << arr_options[i] << endl;
    }
    cin >> input;
    if (isInteger(input))
        option = stoi(input);
    while ((option > arr_options.size() or option <= 0) or !isInteger(input)) {
        cout << "Introdueix un enter del 1 al " << arr_options.size() << endl;
        cin >> input;
        if (isInteger(input))
            option = stoi(input);
    }
    return option;
}

bool isNext(string data_1, string data_2) {
    int d_1 = ((int) data_1[data_1.length() - 1]);
    int d_2 = ((int) data_2[data_2.length() - 1]);
    return (abs(d_1 - d_2) == 1);
}

float option_9(string file_path, pair<string, string> interval, TransactionManagerAVL& tm) {
    float fee_total = 0;
    fstream fichero;

    //Programa principal
    fileExists(file_path);
    fichero.open(file_path);
    cout << "Reading file " << file_path << "...\n\n";
    while (!fichero.eof()) {
        //Llegida de la linea
        getline(fichero, interval.second);
        interval.first = interval.second;
        //Es fa split de l'input
        try {
            fee_total += tm.feesInTimeInterval(interval);
        } catch (exception const& e) {
            cout << "Error";
        }
    }
    cout << endl << endl;
    fichero.close();
    return fee_total;
}

int main(int argc, char** argv) {
    string input, auxiliary;
    int _input, option;
    pair<string, string> par;
    TransactionManagerAVL newTransaccio(0.02, 0.03);
    float fee;
    chrono::steady_clock::time_point begin, end;
    vector<string> arr_options = {"Ruta fitxer",
        "Mostra transaccions de més nous a antics",
        "Mostra transaccions de més antics a nous",
        "Mostrar la transaccio més nou",
        "Mostra la transaccio més antiga",
        "Mostra comissió de totes les transaccions",
        "Mostra la comissió a partir d'una dada determinada",
        "Mostra la comissió entre dos dades",
        "Mostrar balanç de les transaccions",
        "Sortir"};
    do {
        option = showMenu(arr_options, input);
        string input;
        cout << endl << endl;
        try {
            switch (option) {
                case 1:
                    cout << "Nom del fitxer" << endl;
                    cin >> input;
                    begin = chrono::steady_clock::now();
                    newTransaccio.loadFromFile(input);
                    end = chrono::steady_clock::now();
                    cout << "Fitxer carregat correctament";
                    cout << "\nTemps transcorregut: " << chrono::duration_cast<chrono::milliseconds
                            >(end - begin).count() << " ms." << endl;
                    break;
                case 2:
                    cout << "Lestransaccions en ordre de més nou a més antic són: \n\n";
                    newTransaccio.showAll();
                    break;
                case 3:
                    cout << "Lestransaccions en ordre de més antic a més nou són: \n\n";
                    newTransaccio.showAllReverse();
                    break;
                case 4:
                    cout << "La transacció més nova és : " << endl;
                    newTransaccio.showNewest();
                    cout << endl;
                    break;
                case 5:
                    cout << "La transacció més antiga és : " << endl;
                    newTransaccio.showOldest();
                    cout << endl;
                    break;
                case 6:
                    cout << "La comisió total de totes les transaccions és : ";
                    cout << fixed << setprecision(2) << newTransaccio.feesInTotal() << "€";
                    cout << endl;
                    break;
                case 7:
                    cout << "Introdueix el dia amb el format YYYY-MM-DD: " << endl;
                    cin >> auxiliary;
                    cout << "Introdueix l'hora amb el format HH:MM " << endl;
                    cin >> input;
                    isData(auxiliary, input);
                    auxiliary = auxiliary + " " + input;
                    fee = newTransaccio.feesSinceTime(auxiliary);
                    cout << "Les tases en eixe interval de temps són : " << fee << "€";
                    break;
                case 8:
                    cout << "Introdueix el primer dia amb el format YYYY-MM-DD: " << endl;
                    cin >> auxiliary;
                    cout << "Introdueix l'hora amb el format HH:MM " << endl;
                    cin >> input;
                    isData(auxiliary, input);
                    par.first = auxiliary + " " + input;
                    cout << "Introdueix el segon dia amb el format YYYY-MM-DD: " << endl;
                    cin >> auxiliary;
                    cout << "Introdueix l'hora amb el format HH:MM " << endl;
                    cin >> input;
                    isData(auxiliary, input);
                    par.second = auxiliary + " " + input;
                    fee = newTransaccio.feesInTimeInterval(par);
                    cout << fixed << setprecision(2) << "Les tases en eixe interval és : " << fee << "€";
                    break;
                case 9:
                    cout << "Nom del fitxer" << endl;
                    cin >> input;
                    fee = 0;
                    begin = chrono::steady_clock::now();
                    fee = option_9(input, par, newTransaccio);
                    end = chrono::steady_clock::now();
                    cout << fixed << setprecision(2) << "El balaç ix a : " << fee << "€" << endl;
                    cout << "\nTemps transcorregut: " << chrono::duration_cast<chrono::milliseconds
                            >(end - begin).count() << " ms." << endl;

                    break;
                case 10:
                    cout << "Sortint..." << endl << endl;
                    break;

            }
        } catch (exception const& e) {
            cout << e.what() << endl;
        }
        cout << endl << endl;
    } while (option != 10);
    return 0;
}
