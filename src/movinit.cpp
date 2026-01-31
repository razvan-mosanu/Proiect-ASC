#include "movinit.h"

ifstream fin;
ofstream fout;

void Variabile();

void Tabel_Signed_Less();
void Indici_Tabel_Signed_Less();

void Tabele_Comparari();
void Indici_Tabele_Comparari();

void Tabel_Xor();
void Indici_Tabel_Xor();
void Tabel_Mascare();

void Tabel_Add();
void Tabel_Carry_Add();
void Carry_Add_Indice_Linie();
void Add_Indice_Linie();

void Tabel_Sub();
void Tabel_Below_Sub();
void Sub_Indice_Linie();

void Tabel_Div();
void Tabel_Mod();
void Indici_Tabel_Div();

void Tabel_And();
void Tabel_Or();
void Indici_Tabele_Logice();

void Tabel_Mul();
void Indici_Tabel_Mul();


void Deschide_Fisiere(string in, string out) 
{
    fin.open(in);
    fout.open(out);
}

void Inchide_Fisiere()
{
    fin.close();
    fout.close();
}

void Eroare()
{
    fout << "NU ESTE BINE SCRIS FISIERUL DAT";
    exit(1);
}

void Init()
{
    fout << " .data\n";
    fout << " .balign 4\n";
    Variabile();
            
    Tabel_Add();
    Tabel_Carry_Add();
    Add_Indice_Linie();
    Carry_Add_Indice_Linie();

    Tabel_Sub();
    Tabel_Below_Sub();
    Sub_Indice_Linie();
            
    Tabel_Mascare();
    Tabele_Comparari();
    Indici_Tabele_Comparari();

    Tabel_Xor();
    Indici_Tabel_Xor();
            
    Tabel_Signed_Less();
    Indici_Tabel_Signed_Less();
            
    Tabel_Div();
    Tabel_Mod();
    Indici_Tabel_Div();
            
    Tabel_And();
    Tabel_Or();
    Indici_Tabele_Logice();

    Tabel_Mul();
}

int mai_mic(int a, int b)
{
    int aux = N / 2;
    if(a >= aux) a = a - N;
    if(b >= aux) b = b - N;
    return a < b;
}

void Tabel_Signed_Less()
{
    fout << "tabel_less:\n";
    for(int i=0; i<N; i++)
    {
        fout << " .byte ";
        for(int j=0; j<N; j++)
            fout << (j == 0 ? "" : ",") << mai_mic(j, i);
        fout << "\n";
    }
}

void Indici_Tabel_Signed_Less()
{
    fout << "less_indice_linie:\n";
    for(int i=0; i<N; i++)
        fout << " .long tabel_less + " << i * N << "\n";
    fout << "\n";
}

void Variabile()
{
    int i;
    fout << "variabile:\n";
    fout << " .long 0";
    for(i=0; i<7; i++)
        fout << ",0";
    fout << "\n";
    fout << "flag_carry: .byte 0\n";
    fout << "flag_zero: .byte 0\n";
    fout << "flag_below: .byte 0\n";
    fout << "flag_less: .byte 0\n";
}

void Tabele_Comparari()
{
    int i, j;
    fout << "tabel_zero:\n";
    for(i=0; i<N; i++)
    {
        fout << " .byte ";
        j = 0;
        fout << (i == j);
        j++;
        for(; j<N; j++)
            fout << "," << (i == j);
        fout << "\n";
    }
    fout << "tabel_below:\n";
    for(i=0; i<N; i++)
    {
        fout << " .byte ";
        j = 0;
        fout << (j < i);
        j++;
        for(; j<N; j++)
            fout << "," << (j < i);
        fout << "\n";
    }
}

void Indici_Tabele_Comparari()
{
    int i;
    fout << "zero_indice_linie:\n";
    for(i=0; i<N; i++)
        fout << " .long tabel_zero + " << i * N << "\n";
    fout << "\n";
    fout << "below_indice_linie:\n";
    for(i=0; i<N; i++)
        fout << " .long tabel_below + " << i * N << "\n";
    fout << "\n";
}

void Tabel_Xor()
{
    int i, j;
    fout << "tabel_xor:\n";
    for(i=0; i<N; i++)
    {
        fout << ".byte ";
        fout << i;
        for(j=1; j<N; j++)
            fout << "," << (i ^ j);
        fout << "\n";
    }
}

void Indici_Tabel_Xor()
{
    int i;
    fout << "xor_indice_linie:\n";
    for(i=0; i<N; i++)
        fout << " .long tabel_xor + " << i * N << "\n";
    fout << "\n";
}

void Tabel_Add()
{
    int i, j;
    fout << "tabel_add:\n";
    for(i=0; i<N; i++)
    {
        fout << " .byte ";
        fout << i % N;
        for(j=1; j<N; j++)
            fout << "," << (i + j) % N;
        fout << "\n";
    }
    fout << "\n";
}

void Add_Indice_Linie()
{
    int i;
    fout << "add_indice_linie:\n";
    for(i=0; i<N; i++)
        fout << " .long tabel_add + " << i * N << "\n";
    fout << "\n";
}

void Tabel_Mascare()
{
    int i, dim;
    fout << "tabel_mask:\n";
    dim = N * N;
    for (i = 0; i < dim; i++)
    {
        if (i % N == 0) fout << " .byte " << i % N;
        else fout << "," << i % N;
        if ((i + 1) % N == 0) fout << "\n";
    }
    fout << "\n";
}

void Tabel_Carry_Add()
{
    int i, j;
    fout << "tabel_carry_add:\n";
    for(i=0; i<N; i++)
    {
        fout << " .byte ";
        fout << i / N;
        for(j=1; j<N; j++)
            fout << "," << (i + j) / N;
        fout << "\n";
    }
    fout << "\n";
}

void Carry_Add_Indice_Linie()
{
    int i;
    fout << "Carry_add_indice_linie:\n";
    for(i=0; i<N; i++)
        fout << " .long tabel_carry_add + " << i * N << "\n";
    fout << "\n";
}

int off_set(string registru)
{
    if (registru == "eax") return 0;
    if (registru == "ebx") return 4;
    if (registru == "ecx") return 8;
    if (registru == "edx") return 12;
    if (registru == "esi") return 16;
    if (registru == "edi") return 20;
    if (registru == "esp") return 24;
    if (registru == "ebp") return 28;
    return -1;
}

void Scoatere_Instructiune(string s, string &x, string &y, string &z)
{
    int i, lungime;
    lungime = s.size();
    for(i=0; i<lungime; i++)
        if(s[i] == ',' || s[i] == '#' || s[i] == ';') s[i] = ' ';
    i = 0;
    while(i < lungime && s[i] == ' ') i++;
    for(; i<lungime && s[i] != ' '; i++)
        x += s[i];
    while(i < lungime && s[i] == ' ') i++;
    for(; i<lungime && s[i] != ' '; i++)
        y += s[i];
    while(i < lungime && s[i] == ' ') i++;
    for(; i<lungime && s[i] != ' '; i++)
        z += s[i];
}

void Prelucrare_Linie(string &s)
{
    int i, l;
    l = s.size();
    string aux = "";
    i = 0;
    while(i < l && s[i] == ' ') i++;
    for(; i<l && s[i] != ' '; i++)
        aux += s[i];
    //fout << aux << "\n";
    aux += ' ';
    while(i < l && s[i] == ' ') i++;
    //fout << aux << "n\n";
    for(; i<l && s[i] != ' ' && s[i] != '#' && s[i] != ';'; i++)
        aux += s[i];
    s = aux;
    //fout << aux << "**";
}

void Tabel_Sub()
{
    int i, j;
    fout << "tabel_sub:\n";
    for(i=0; i<N; i++)
    {
        fout << " .byte ";
        for(j=0; j<N; j++)
        {
            int res = (i - j);
            if(res < 0) res += N;
            fout << (j == 0 ? "" : ",") << res;
        }
        fout << "\n";
    }
    fout << "\n";
}

void Tabel_Below_Sub()
{
    int i, j;
    fout << "tabel_below_sub:\n";
    for(i=0; i<N; i++)
    {
        fout << " .byte ";
        for(j=0; j<N; j++)
            fout << (j == 0 ? "" : ",") << (i < j ? 1 : 0);
        fout << "\n";
    }
    fout << "\n";
}

void Sub_Indice_Linie()
{
    int i;
    fout << "sub_indice_linie:\n";
    for(i=0; i<N; i++)
        fout << " .long tabel_sub + " << i * N << "\n";
    fout << "\n";
    fout << "below_sub_indice_linie:\n";
    for(i=0; i<N; i++)
        fout << " .long tabel_below_sub + " << i * N << "\n";
    fout << "\n";
}

void Tabel_Div()
{
    int i, j, res;
    fout << "tabel_div:\n";
    for (i = 0; i < N; i++)
    {
        fout << " .byte ";
        for (j = 0; j < N; j++)
        {
            res = (j == 0) ? 0 : i / j;
            fout << (j == 0 ? "" : ",") << res;
        }
        fout << "\n";
    }
}

void Tabel_Mod()
{
    int i, j, res;
    fout << "tabel_mod:\n";
    for (i = 0; i < N; i++)
    {
        fout << " .byte ";
        for(j = 0; j < N; j++)
        {
            res = (j == 0) ? 0 : i % j;
            fout << (j == 0 ? "" : ",") << res;
        }
        fout << "\n";
    }
}

void Indici_Tabel_Div()
{
    int i;
    fout << "div_indice_linie:\n";
    for (i = 0; i < N; i++)
        fout << " .long tabel_div + " << i * N << "\n";
    fout << "\n";
    fout << "mod_indice_linie:\n";
    for (i = 0; i < N; i++)
        fout << " .long tabel_mod + " << i * N << "\n";
    fout << "\n";
}

void Tabel_And()
{
    int i, j;
    fout << "tabel_and:\n";
    for (i = 0; i < N; i++)
    {
        fout << " .byte ";
        for (j = 0; j < N; j++)
            fout << (j == 0 ? "" : ",") << (i & j);
        fout << "\n";
    }
}

void Tabel_Or()
{
    int i, j;
    fout << "tabel_or:\n";
    for (i = 0; i < N; i++)
    {
        fout << " .byte ";
        for (j = 0; j < N; j++)
            fout << (j == 0 ? "" : ",") << (i | j);
        fout << "\n";
    }
}

void Indici_Tabele_Logice()
{
    int i;

    fout << "and_indice_linie:\n";
    for (i = 0; i < N; i++)
        fout << " .long tabel_and + " << i * N << "\n";
    fout << "\n";

    fout << "or_indice_linie:\n";
    for (i = 0; i < N; i++)
        fout << " .long tabel_or + " << i * N << "\n";
    fout << "\n";
}

void Tabel_Mul()
{
    
}

void Indici_Tabel_Mul()
{

}
