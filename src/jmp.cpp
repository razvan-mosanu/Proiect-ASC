#include "movinit.h"
#include "jmp.h"

void ParsareJe(string linie)
{
    Prelucrare_Linie(linie);
    string v = linie.substr(3);
    fout << " cmpb $1, flag_zero\n";
    fout << " je "<< v << "\n";
}

void ParsareJne(string linie)
{
    Prelucrare_Linie(linie);
    string v = linie.substr(4);
    fout << " cmpb $0, flag_zero\n";
    fout << " je " << v << "\n";
}

void ParsareJb(string linie)
{
    Prelucrare_Linie(linie);
    string v = linie.substr(3);
    fout << " cmpb $1, flag_below\n";
    fout << " je " << v << "\n";
}

void ParsareJae(string linie)
{
    Prelucrare_Linie(linie);
    string v = linie.substr(4);
    fout << " cmpb $0, flag_below\n";
    fout << " je " << v << "\n";
}

void ParsareJa(string linie)
{
    Prelucrare_Linie(linie);
    static int label_count = 0;
    string v = linie.substr(3);
    string skip_label = "skip_ja_" + to_string(label_count++);
    fout << " cmpb $1, flag_below\n";
    fout << " je " << skip_label << "\n";
    fout << " cmpb $1, flag_zero\n";
    fout << " je " << skip_label << "\n";
    fout << " jmp " << v << "\n";
    fout << " " << skip_label << ":\n";
}

void ParsareJbe(string linie)
{
    Prelucrare_Linie(linie);
    string v = linie.substr(4);
    fout << " cmpb $1, flag_below\n";
    fout << " je " << v << "\n";
    fout << " cmpb $1, flag_zero\n";
    fout << " je " << v << "\n";
}

void ParsareJl(string linie)
{
    Prelucrare_Linie(linie);
    string v = linie.substr(3);
    fout << " cmpb $1, flag_less\n";
    fout << " je " << v << "\n";
}

void ParsareJle(string linie)
{
    Prelucrare_Linie(linie);
    string v = linie.substr(4);
    fout << " cmpb $1, flag_less\n";
    fout << " je " << v << "\n";
    fout << " cmpb $1, flag_zero\n";
    fout << " je " << v << "\n";
}

void ParsareJge(string linie)
{
    Prelucrare_Linie(linie);
    string v = linie.substr(4);
    fout << " cmpb $0, flag_less\n";
    fout << " je " << v << "\n";
}

void ParsareJg(string linie)
{
    Prelucrare_Linie(linie);
    string v = linie.substr(3);
    static int skip_jg = 0;
    string label = "not_jg_" + to_string(skip_jg++);
    fout << " cmpb $1, flag_less\n";
    fout << " je " << label << "\n";
    fout << " cmpb $1, flag_zero\n";
    fout << " je " << label << "\n";
    fout << " jmp " << v << "\n";
    fout << " " << label << ":\n";
}

