#include "movinit.h"
#include "push.h"

void ParsarePush(string linie)
{
    string cmd, v, rest;
    Scoatere_Instructiune(linie, cmd, v, rest);
    if(!v.empty() && v[0] == '%')
    {
        string reg = v.substr(1);
        int off = off_set(reg);
        if(off == -1) Eroare();
        fout << " movl variabile+" << off << ", %eax\n";
        fout << " push %eax\n";
    }
    else fout << " " << linie << "\n";
}

void ParsarePop(string linie)
{
    string cmd, v, rest;
    Scoatere_Instructiune(linie, cmd, v, rest);
    if(!v.empty() && v[0] == '%')
    {
        string reg = v.substr(1);
        int off = off_set(reg);
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