//implimentacija su vektoriais

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <random>
#include <chrono>
#include <iomanip>
#include <cctype>
#include <cstdlib>


using std::cout;
using std::cin;
using std::vector;
using std::string;
using std::setw;
using std::sort;
using std::isdigit; //tikrina ar char yra skaitmuo
using std::stoi; //string to int
using std::left;

struct studentas {
    string vardas = "Vardenis";
    string pavarde = "Pavardenis";
    vector<int> nd = {0};
    int egz = 0;
    double vidurkis = 0;
    double mediana = 0;
};

void skaičiavimai(vector<studentas> &stud);
void išvestis(const vector<studentas> &stud, int &MaxPav, int &MaxVard);
void raidės(int &MaxPav, int &MaxVard, vector <studentas> &stud);
bool isInteger(const string& s);
void skaitymas(vector<studentas> &stud); // paprastas vedimas ranka
void skaitymas(vector<studentas> &stud, int &n, int nd_sk); // generuoja n studentų duomenis su nd_sk namų darbų pažymiais
void skaitymas(vector<studentas> &stud, int &n, int nd_sk, int vardPavSk); // generuoja n studentų duomenis su nd_sk namų darbų pažymiais ir vardais/pavardėmis iš vardPavSk dydžio sąrašo


int main() {
    studentas temp;
    int MaxPav = 0, MaxVard = 0;
    vector<studentas> stud;
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
        switch (pasirinkimas) 
        {
            case 1: // veikia
                {
                    skaitymas(stud);
                    skaičiavimai(stud);
                    raidės(MaxPav, MaxVard, stud);
                    išvestis(stud, MaxPav, MaxVard);
                    stud.clear();
                }
            break;
            case 2: //veikia
                {
                    int n, nd_sk;;
                    cout << "Įveskite kiek namų darbų pažymių norite generuoti: ";
                    string nd_sk_str;
                    cin >> nd_sk_str;
                    while(!isInteger(nd_sk_str) || stoi(nd_sk_str) <= 0) {
                        cout << "Klaidinga įvestis. Bandykite dar kartą: ";
                        cin >> nd_sk_str;
                    }
                    nd_sk = stoi(nd_sk_str);
                    skaitymas(stud, n, nd_sk);
                    skaičiavimai(stud);
                    raidės(MaxPav, MaxVard, stud);
                    išvestis(stud, MaxPav, MaxVard);
                    stud.clear();
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
                    skaitymas(stud, n, nd_sk, n); // antras n perduodamas jei bus vardu sarašas
                    skaičiavimai(stud);
                    raidės(MaxPav, MaxVard, stud);
                    išvestis(stud, MaxPav, MaxVard);
                    stud.clear();
                }
            break;
            case 4: //veikia
                {
                exit(0);
                }
            break;
        }
    }while(true);

    return 0;
} 

void skaitymas(vector<studentas> &stud)
{
    studentas temp;
    string laikinas;
    int n = 0;
    cout << "Jeigu norite baigti darba įveskite \\0" << "\n";
    while(true) {
        cout << "Įveskite " << n + 1 << " studento vardą: ";
        cin >> laikinas;
        if(laikinas == "\\0") return;
        temp.vardas = laikinas;
        cout << "Įveskite " << n + 1 << " studento pavardę: ";
        cin >> laikinas;
        if(laikinas == "\\0") return;
        temp.pavarde = laikinas;
        int nd_count;
        cout << "Įveskite namų darbų skaičių: ";
        string nd_sk_str;
        cin >> nd_sk_str;
        if(nd_sk_str == "\\0") return;
        while(!isInteger(nd_sk_str) || stoi(nd_sk_str) <= 0) {
            cout << "Klaidinga įvestis. Bandykite dar kartą: ";
            cin >> nd_sk_str;
            if(nd_sk_str == "\\0") return;
        }
        nd_count = stoi(nd_sk_str);
        temp.nd.resize(nd_count);

        for(int j = 0; j < nd_count; j++) {
            cout << "Įveskite " << j + 1 << " namų darbų įvertinimą: ";
            string nd_str;
            cin >> nd_str;
            if(nd_str == "\\0") {
                temp.nd.resize(j); // sumažina vektoriaus dydį iki įvestų pažymių skaičiaus
                return;
            }
            while(!isInteger(nd_str) || stoi(nd_str) < 0 || stoi(nd_str) > 10) {
                cout << "Klaidinga įvestis. Bandykite dar kartą: ";
                cin >> nd_str;
                if(nd_str == "\\0") return;
            }
            temp.nd[j] = stoi(nd_str);
        }
        cout << "Įveskite egzamino įvertinimą: ";
        string egz_str;
        cin >> egz_str;
        if(egz_str == "\\0") {
            temp.nd.clear();
            return;
        }
        temp.egz = stoi(egz_str);
        stud.push_back(temp);
        n++;
    }
}

void skaitymas(vector<studentas> &stud, int &n, int nd_sk)
{
    if (n <= 0 || nd_sk <= 0) 
    {
        cout << "Neteisingi parametrai generavimui. Patikrinkite įvestį.\n";
        return;
    }
    // std::random_device is a uniformly-distributed integer random number generator that produces non-deterministic random numbers. 
    std::random_device rd;
    /*
    static std::chrono::time_point<std::chrono::high_resolution_clock> now() noexcept;
	Returns a time point representing the current point in time. 
    */
    auto seed = std::seed_seq{rd(), static_cast<unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count())};
    // A Mersenne Twister pseudo-random generator of 64-bit numbers with a state size of 19937 bits.
    std::mt19937_64 gen(seed);
    /*
    Produces random integer values i, uniformly distributed on the closed interval [a, b], that is, distributed according to the discrete probability function
    */
    std::uniform_int_distribution<> dist(1, 10);
    string laikinas;
    cout << "Įveskite \\0 norėdami baigti duomenų įvedimą\n";
    int i = 0;
    while(true) {
        studentas temp;
        cout << "Įveskite " << i + 1 << " studento vardą: ";
        cin >> laikinas;
        if(laikinas == "\\0") break;
        temp.vardas = laikinas;
        cout << "Įveskite " << i + 1 << " studento pavardę: ";
        cin >> laikinas;
        if(laikinas == "\\0") break;
        temp.pavarde = laikinas;
        temp.nd.resize(nd_sk);
        for (int j = 0; j < nd_sk; ++j) {
            temp.nd[j] = dist(gen);
        }
        temp.egz = dist(gen);
        stud.push_back(temp);
        i++;
    }
    n = stud.size();
}

void skaitymas(vector<studentas> &stud, int &n, int nd_sk, int VardPavSk)
{
    if (n <= 0 || nd_sk <= 0 || VardPavSk <= 0) 
    {
        cout << "Neteisingi parametrai generavimui. Patikrinkite įvestį.\n";
        return;
    }

    std::random_device rd;
    auto seed = std::seed_seq{rd(), static_cast<unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count())};
    std::mt19937_64 gen(seed);
    std::uniform_int_distribution<> score_dist(1, 10);

    for (int i = 0; i < n; ++i) {
        studentas temp;
        temp.vardas = "Vardas" + std::to_string(i + 1);
        temp.pavarde = "Pavarde" + std::to_string(i + 1);
        temp.nd.resize(nd_sk);
        for (int j = 0; j < nd_sk; ++j) temp.nd[j] = score_dist(gen);
        temp.egz = score_dist(gen);
        stud.push_back(temp);
    }
}

void skaičiavimai(vector<studentas> &stud) // apskaičiuoja vidurkius ir medianas kiekvienam studentui
{
    for(auto &s : stud) {
        double suma = 0;
        for(const auto &nd_ivar : s.nd) {
            suma += nd_ivar;
        }
        s.vidurkis = suma / s.nd.size();

        vector<int> nd_kopija = s.nd;
        sort(nd_kopija.begin(), nd_kopija.end());
        if(nd_kopija.size() % 2 == 0) {
            s.mediana = (nd_kopija[nd_kopija.size()/2 - 1] + nd_kopija[nd_kopija.size()/2]) / 2.0;
        } else {
            s.mediana = nd_kopija[nd_kopija.size()/2];
        }
    }
}

void išvestis(const vector<studentas> &stud, int &MaxPav, int &MaxVard)
{
    MaxVard = std::max(MaxVard, 12);
    MaxPav  = std::max(MaxPav, 12);

    cout << left << setw(MaxVard + 2) << "Vardas" << setw(MaxPav + 2) << "Pavardė"
            << setw(20) << "Galutinis (vid.)" << setw(20) << "Galutinis (med.)" << "\n";
    cout << string(MaxVard + MaxPav + 44, '-') << "\n";
    for(const auto &s : stud) {
        cout << left << setw(MaxVard + 2) << s.vardas << setw(MaxPav + 2) << s.pavarde << setw(20) << std::fixed << std::setprecision(2) << (0.4 * s.vidurkis + 0.6 * s.egz) << setw(20) << std::fixed << std::setprecision(2) << (0.4 * s.mediana + 0.6 * s.egz) << "\n";
    }
}

void raidės(int &MaxPav, int &MaxVard, vector <studentas> &stud)
{
    MaxPav = 0;
    MaxVard = 0;
    for(const auto &s : stud) {
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

    int start = (s[0] == '-' || s[0] == '+') ? 1 : 0; //praleidzia +/- ženklus

    for (int i = start; i < s.size(); i++)
        if (!isdigit(s[i]))
            return false;

    return (s.size() - start) > 0;
}
