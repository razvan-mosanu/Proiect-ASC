#pragma once

#include <fstream>
#include <string>
using namespace std;

const int N = 8; 

extern ifstream fin;
extern ofstream fout;

extern void Deschide_Fisiere(string in, string out);
extern void Inchide_Fisiere();

extern void Eroare();
extern void Init();
extern int off_set(string registru);
extern void Scoatere_Instructiune(string s, string &x, string &y, string &z);
extern void Prelucrare_Linie(string &s);


