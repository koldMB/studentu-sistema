//implimentacija su masyvais

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <cctype>
#include <cstdlib>
#include <random>
#include <chrono>

using std::cout;
using std::cin;
using std::string;
using std::setw;
using std::sort;
using std::isdigit;
using std::stoi;
using std::left;

struct studentas {
    string vardas;
    string pavarde;
    int *nd = nullptr;
    int nd_sk = 0;
    int egz = 0;
    double vidurkis = 0;
    double mediana = 0;
};

void skaitymas(studentas* &stud, int &n);
void skaičiavimai(studentas* stud, int n);
void išvestis(const studentas* stud, int n, int MaxPav, int MaxVard);
void raidės(int &MaxPav, int &MaxVard, studentas* stud, int n);
bool isInteger(const string& s);
void generuotiPazymius(studentas* &stud, int n, int nd_sk);
void ivestiVarPav(studentas* &stud, int n);
void skaitymasVardaiPavardes(studentas* &stud, int n);

int main() {
    studentas* stud = nullptr;
    int n = 0;
    int MaxPav = 0, MaxVard = 0;
    int pasirinkimas;
    do{
        cout << "1. Įvesti duomenis ranka\n"; 
        cout << "2. Generuoti pažymius\n";
        cout << "3. Generuoti vardus ir pavardes bei pažymius\n";
        cout << "4. Darbo pabaiga\n";
        cout << "Pasirinkite veiksmą: ";
        string pasirinkimas_str;
        cin >> pasirinkimas_str;
        while(!isInteger(pasirinkimas_str) || stoi(pasirinkimas_str) < 1 || stoi(pasirinkimas_str) > 4) {
            cout << "Klaidinga įvestis. Bandykite dar kartą: ";
            cin >> pasirinkimas_str;
        }
        pasirinkimas = stoi(pasirinkimas_str);

        switch(pasirinkimas) {
            case 1: 
                {
                    skaitymas(stud, n);
                    skaičiavimai(stud, n);
                    raidės(MaxPav, MaxVard, stud, n);
                    išvestis(stud, n, MaxPav, MaxVard);
                    for (int i = 0; i < n; ++i) {
                        delete[] stud[i].nd;
                    }
                    delete[] stud;
                    stud = nullptr;
                }
            break;
            case 2:
                {
                    int n, nd_sk;
                    cout << "Įveskite kiek studentų duomenų norite generuoti: ";
                    string n_str;
                    cin >> n_str;
                    while(!isInteger(n_str) || stoi(n_str) <= 0) {
                        cout << "Klaidinga įvestis. Bandykite dar kartą: ";
                        cin >> n_str;
                    }
                    n = stoi(n_str);
                    cout << "Įveskite kiek namų darbų pažymių norite generuoti: ";
                    string nd_sk_str;
                    cin >> nd_sk_str;
                    while(!isInteger(nd_sk_str) || stoi(nd_sk_str) <= 0) {
                        cout << "Klaidinga įvestis. Bandykite dar kartą: ";
                        cin >> nd_sk_str;
                    }
                    nd_sk = stoi(nd_sk_str);
                    stud = new studentas[n];
                    for(int i = 0; i < n; i++) {
                        stud[i].nd_sk = nd_sk;
                        stud[i].nd = new int[nd_sk];
                    }
                    skaitymasVardaiPavardes(stud, n); // paprastas vedimas vardų ir pavardžių
                    generuotiPazymius(stud, n, nd_sk); // generuoja pažymius
                    skaičiavimai(stud, n);
                    raidės(MaxPav, MaxVard, stud, n);
                    išvestis(stud, n, MaxPav, MaxVard);
                    for (int i = 0; i < n; ++i) {
                        delete[] stud[i].nd;
                    }
                    delete[] stud;
                    stud = nullptr;
                }
            break;
            case 3:
                {
                    int n, nd_sk;
                    cout << "Įveskite kiek studentų duomenų norite generuoti: ";
                    string n_str;
                    cin >> n_str;
                    while(!isInteger(n_str) || stoi(n_str) <= 0) {
                        cout << "Klaidinga įvestis. Bandykite dar kartą: ";
                        cin >> n_str;
                    }
                    n = stoi(n_str);
                    cout << "Įveskite kiek namų darbų pažymių norite generuoti: ";
                    string nd_sk_str;
                    cin >> nd_sk_str;
                    while(!isInteger(nd_sk_str) || stoi(nd_sk_str) <= 0) {
                        cout << "Klaidinga įvestis. Bandykite dar kartą: ";
                        cin >> nd_sk_str;
                    }
                    nd_sk = stoi(nd_sk_str);
                    
                    stud = new studentas[n];
                    ivestiVarPav(stud, n); // generuoja vardus ir pavardes
                    for(int i = 0; i < n; i++) {
                        stud[i].nd_sk = nd_sk;
                        stud[i].nd = new int[nd_sk];
                    }
                    generuotiPazymius(stud, n, nd_sk); // generuoja pažymius
                    skaičiavimai(stud, n);
                    raidės(MaxPav, MaxVard, stud, n);
                    išvestis(stud, n, MaxPav, MaxVard);
                    
                    for (int i = 0; i < n; ++i) {
                        delete[] stud[i].nd;
                    }
                    delete[] stud;
                    stud = nullptr;
                }
            break;
            case 4:
                {
                    exit(0);
                }
            break;
        }
    } while(true);
    for (int i = 0; i < n; ++i) {
        delete[] stud[i].nd;
    }
    delete[] stud;

    return 0;
}

void skaitymas(studentas* &stud, int &n)
{
    cout << "Įveskite kiek studentų duomenų norite įvesti: ";
    string n_str;
    cin >> n_str;
    while(!isInteger(n_str) || stoi(n_str) <= 0) {
        cout << "Klaidinga įvestis. Bandykite dar kartą: ";
        cin >> n_str;
    }
    n = stoi(n_str);

    stud = new studentas[n];

    for(int i = 0; i < n; i++) {
        cout << "Įveskite " << i + 1 << " studento vardą: ";
        cin >> stud[i].vardas;
        cout << "Įveskite " << i + 1 << " studento pavardę: ";
        cin >> stud[i].pavarde;

        cout << "Įveskite namų darbų skaičių: ";
        string nd_sk_str;
        cin >> nd_sk_str;
        while(!isInteger(nd_sk_str) || stoi(nd_sk_str) <= 0) {
            cout << "Klaidinga įvestis. Bandykite dar kartą: ";
            cin >> nd_sk_str;
        }
        stud[i].nd_sk = stoi(nd_sk_str);
        stud[i].nd = new int[stud[i].nd_sk];

        for(int j = 0; j < stud[i].nd_sk; j++) {
            cout << "Įveskite " << j + 1 << " namų darbų įvertinimą: ";
            string nd_str;
            cin >> nd_str;
            while(!isInteger(nd_str) || stoi(nd_str) < 0) {
                cout << "Klaidinga įvestis. Bandykite dar kartą: ";
                cin >> nd_str;
            }
            stud[i].nd[j] = stoi(nd_str);
        }

        cout << "Įveskite egzamino įvertinimą: ";
        string egz_str;
        cin >> egz_str;
        while(!isInteger(egz_str) || stoi(egz_str) < 0) {
            cout << "Klaidinga įvestis. Bandykite dar kartą: ";
            cin >> egz_str;
        }
        stud[i].egz = stoi(egz_str);
    }
}

void skaičiavimai(studentas* stud, int n)
{
    for(int i = 0; i < n; ++i) {
        studentas &s = stud[i];
        double suma = 0;
        for(int j = 0; j < s.nd_sk; ++j) {
            suma += s.nd[j];
        }
        s.vidurkis = (s.nd_sk > 0) ? suma / s.nd_sk : 0;


        int *nd_kopija = new int[s.nd_sk];
        std::copy(s.nd, s.nd + s.nd_sk, nd_kopija);
        sort(nd_kopija, nd_kopija + s.nd_sk);
        if (s.nd_sk > 0) {
            if (s.nd_sk % 2 == 0) {
                s.mediana = (nd_kopija[s.nd_sk/2 - 1] + nd_kopija[s.nd_sk/2]) / 2.0;
            } else {
                s.mediana = nd_kopija[s.nd_sk/2];
            }
        } else {
            s.mediana = 0;
        }
        delete[] nd_kopija;
    }
}

void išvestis(const studentas* stud, int n, int MaxPav, int MaxVard)
{
    MaxVard = std::max(MaxVard, 12);
    MaxPav  = std::max(MaxPav, 12);

    cout << left << setw(MaxVard + 2) << "Vardas" << setw(MaxPav + 2) << "Pavardė"
            << setw(20) << "Galutinis (vid.)" << setw(20) << "Galutinis (med.)" << "\n";
    cout << string(MaxVard + MaxPav + 44, '-') << "\n";
    for(int i = 0; i < n; ++i) {
        const studentas &s = stud[i];
        cout << left << setw(MaxVard + 2) << s.vardas << setw(MaxPav + 2) << s.pavarde
                << setw(20) << std::fixed << std::setprecision(2) << (0.4 * s.vidurkis + 0.6 * s.egz)
                << setw(20) << std::fixed << std::setprecision(2) << (0.4 * s.mediana + 0.6 * s.egz) << "\n";
    }
}

void raidės(int &MaxPav, int &MaxVard, studentas* stud, int n)
{
    MaxPav = 0;
    MaxVard = 0;
    for(int i = 0; i < n; ++i) {
        const studentas &s = stud[i];
        if(s.pavarde.length() > MaxPav) {
            MaxPav = s.pavarde.length();
        }
        if(s.vardas.length() > MaxVard) {
            MaxVard = s.vardas.length();
        }
    }
}

bool isInteger(const string& s)
{
    if (s.empty()) return false;

    int start = (s[0] == '-' || s[0] == '+') ? 1 : 0;

    for (int i = start; i < s.size(); i++)
        if (!isdigit(s[i]))
            return false;

    return start < s.size();
}

void generuotiPazymius(studentas* &stud, int n, int nd_sk)
{
    std::random_device rd;
    auto seed = std::seed_seq{rd(), static_cast<unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count())};
    std::mt19937 gen(seed);
    std::uniform_int_distribution<> dis(1, 10);

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < nd_sk; j++) {
            stud[i].nd[j] = dis(gen);
        }
        stud[i].egz = dis(gen);
    }
}
void ivestiVarPav(studentas* &stud, int n)
{
    for(int i = 0; i < n; i++) {
        stud[i].vardas = "Vardas" + std::to_string(i + 1);
        stud[i].pavarde = "Pavarde" + std::to_string(i + 1);
    }
}

void skaitymasVardaiPavardes(studentas* &stud, int n)
{
    for(int i = 0; i < n; i++) {
        cout << "Įveskite " << i + 1 << " studento vardą: ";
        cin >> stud[i].vardas;
        cout << "Įveskite " << i + 1 << " studento pavardę: ";
        cin >> stud[i].pavarde;
    }
}