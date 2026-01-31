#include "push.h"

void ParsarePush(string linie)
{
    Prelucrare_Linie(linie);
    string v = linie.substr(5);
    if(v[0] == '%')
    {
        v = v.substr(1);
        int off = off_set(v);
        if(off == -1) Eroare();
        fout << " movl variabile+" << off << ", %" << v << "\n";
        fout << " push %" << v << "\n";
    }
    else fout << " " << linie << "\n";
}

void ParsarePop(string linie)
{
    Prelucrare_Linie(linie);
    string v = linie.substr(4);
    if(v[0] == '%')
    {
        v = v.substr(1);
        int off = off_set(v);
        if(off == -1) Eroare();
        fout << " pop %eax\n";
        fout << " movl %eax, variabile+" << off << "\n";
    }
    else
    {
        fout << " pop %eax\n";
        fout << " movl %eax, " << v << "\n";
    }
}