#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <algorithm>
#include <cctype>
using namespace std;

const int N = 16; // 4 biti

extern ifstream fin;
extern ofstream fout;

extern void Deschide_Fisiere(string in, string out);
extern void Inchide_Fisiere();

extern void Eroare();
extern void Init();
extern int off_set(string registru);
extern void Scoatere_Instructiune(string s, string &x, string &y, string &z);
extern void Prelucrare_Linie(string &s);


