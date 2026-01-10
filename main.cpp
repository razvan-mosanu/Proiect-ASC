#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
using namespace std;

ifstream fin("aranjare.in");
ofstream fout("aranjare.out");

int N = 16; // 4 biti
/**
De facut:
-mul
-div
-and
-or
-test
-shl
-shr
-loop

*/

unordered_map<string, int> fr;

void Eroare()
{
    fout << "NU ESTE BINE SCRIS FISIERUL DAT";
    exit(0);
}

void Init()
{
    fout << " .data\n";
    fout << " .balign 4\n";
    fr["eax"] = 0;
    fr["ebx"] = 4;
    fr["ecx"] = 8;
    fr["edx"] = 12;
    fr["esi"] = 16;
    fr["edi"] = 20;
    fr["esp"] = 24;
    fr["ebp"] = 28;
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
    if(fr.find(registru) == fr.end()) return -1;
    return fr[registru];
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

void Parsare()
{
    string linie;
    size_t poz;
    while(getline(fin,linie))
    {
        string instructiune, v1, v2;
        instructiune = v1 = v2 = "";
        if(linie.size() == 0) continue;
        poz = linie.find(".data");
        if(poz != string::npos)
        {
            Init();
            Variabile();
            Tabel_Add();
            Tabel_Sub();
            Tabel_Carry_Add();
            Tabel_Below_Sub();
            Add_Indice_Linie();
            Sub_Indice_Linie();
            Carry_Add_Indice_Linie();
            Tabel_Mascare();
            Tabele_Comparari();
            Indici_Tabele_Comparari();
            Tabel_Xor();
            Indici_Tabel_Xor();
            Tabel_Signed_Less();
            Indici_Tabel_Signed_Less();
            continue;
        }
        poz = linie.find("mov");
        if(poz != string::npos)
        {
            size_t p1 = linie.find('(');
            size_t p2 = linie.find(')');
            if(p1 != string::npos && p2 != string::npos)
            {
                string interior = linie.substr(p1 + 1, p2 - p1 - 1);
                for(char &c : interior)
                    if(c == ',') c = ' ';
                stringstream ss(interior);
                string baza, index, numar;
                ss >> baza >> index >> numar; // ex: %edi %ecx 4
                if(baza[0] == '%') baza = baza.substr(1);
                if(index[0] == '%') index = index.substr(1);
                size_t virgula_ext = linie.find(',', p2);
                if(virgula_ext != string::npos)
                {
                    string dest = linie.substr(virgula_ext + 1);
                    size_t d_s = dest.find('%');
                    if(d_s != string::npos) dest = dest.substr(d_s + 1);
                    size_t d_e = dest.find_first_of(" \t;#\r\n");
                    if(d_e != string::npos) dest = dest.substr(0, d_e);
                    int off_b = off_set(baza);
                    int off_i = off_set(index);
                    int off_d = off_set(dest);
                    if(off_b == -1 || off_i == -1 || off_d == -1) Eroare();
                    fout << " movl variabile+" << off_b << ", %ebx\n";
                    fout << " movl variabile+" << off_i << ", %esi\n";
                    fout << " movl (%ebx, %esi, " << numar << "), %eax\n";
                    fout << " movl %eax, variabile+" << off_d << "\n";
                }
                else
                {
                    string part1 = linie.substr(0, p1);
                    size_t virgula_pos = part1.find(',');
                    if(virgula_pos == string::npos) Eroare();
                    string src = part1.substr(0, virgula_pos);
                    size_t s_s = src.find('%');
                    if(s_s != string::npos) src = src.substr(s_s + 1);
                    size_t start_src = src.find_first_not_of(" \t");
                    if(start_src != string::npos) src = src.substr(start_src);
                    size_t end_src = src.find_first_of(" \t,");
                    if(end_src != string::npos) src = src.substr(0, end_src);
                    int off_b = off_set(baza);
                    int off_i = off_set(index);
                    int off_s = off_set(src);
                    if(off_b == -1 || off_i == -1 || off_s == -1) Eroare();
                    fout << " movl variabile+" << off_b << ", %ebx\n";
                    fout << " movl variabile+" << off_i << ", %esi\n";
                    fout << " movl variabile+" << off_s << ", %eax\n";
                    fout << " movl %eax, (%ebx, %esi, " << numar << ")\n";

                }
                continue;
            }
            Scoatere_Instructiune(linie, instructiune, v1, v2);
            if(v1[0] == '$')
            {
                v2 = v2.substr(1);
                //fout << v1 << " " << v2 << "\n";
                int off = off_set(v2);
                if(off == -1) Eroare();
                fout << " movl " << v1 << ", variabile+" << off << "\n";
            }
            else if(v1[0] == '%' && v2[0] == '%')
            {
                v1 = v1.substr(1);
                v2 = v2.substr(1);
                int off1 = off_set(v1);
                if(off1 == -1) Eroare();
                int off2 = off_set(v2);
                if(off2 == -1) Eroare();
                fout << " movl variabile+" << off1 << ", %eax\n";
                fout << " movl %eax, variabile+" << off2 << "\n";
            }
            else if(v1[0] != '$' && v1[0] != '%' && v2[0] == '%')
            {
                v2 = v2.substr(1);
                int off = off_set(v2);
                if(off == -1) Eroare();
                fout << " movl " << v1 << ", %eax\n";
                fout << " movl %eax, variabile+" << off << "\n";
            }
            else if(v1[0] == '%' && v2[0] != '$' && v2[0] != '%')
            {
                v1 = v1.substr(1);
                int off = off_set(v1);
                if(off == -1) Eroare();
                fout << " movl variabile+" << off << ", %eax\n";
                fout << " movl %eax, " << v2 << "\n";
            }
            continue;
        }
        poz = linie.find("add");
        if(poz != string::npos)
        {
            Scoatere_Instructiune(linie, instructiune, v1, v2);
            if (v2 == "%esp" || v2 == "%ebp") fout << " add " << v1 << ", " << v2 << "\n";
            else
            {
                if(v1[0] == '$' && v2[0] == '%') // val-reg
                {
                    v2 = v2.substr(1);
                    int off = off_set(v2);
                    if(off == -1) Eroare();
                    fout << " movzbl variabile+" << off << ", %eax\n";
                    fout << " movzbl tabel_mask(%eax), %eax\n";
                    fout << " movl " << v1 << ", %ebx\n";
                    fout << " movzbl tabel_mask(%ebx), %ebx\n";
                    fout << " movl add_indice_linie(,%eax,4), %ecx\n";
                    fout << " movzbl (%ecx,%ebx,1), %edx\n";
                    fout << " movl %edx, variabile+" << off << "\n";
                    fout << " movl Carry_add_indice_linie(,%eax,4), %ecx\n";
                    fout << " movzbl (%ecx,%ebx,1), %edx\n";
                    fout << " movb %dl, flag_carry\n";

                }
                else if(v1[0] == '%' && v2[0] == '%') // reg-reg
                {
                    v1 = v1.substr(1);
                    v2 = v2.substr(1);
                    int off1 = off_set(v1);
                    if(off1 == -1) Eroare();
                    int off2 = off_set(v2);
                    if(off2 == -1) Eroare();
                    fout << " movzbl variabile+" << off1 << ", %ebx\n";
                    fout << " movzbl tabel_mask(%ebx), %ebx\n";
                    fout << " movzbl variabile+" << off2 << ", %eax\n";
                    fout << " movzbl tabel_mask(%eax), %eax\n";
                    fout << " movl add_indice_linie(,%eax,4), %ecx\n";
                    fout << " movzbl (%ecx,%ebx,1), %edx\n";
                    fout << " movl %edx, variabile+" << off2 << "\n";
                    fout << " movl Carry_add_indice_linie(,%eax,4), %ecx\n";
                    fout << " movzbl (%ecx,%ebx,1), %edx\n";
                    fout << " movb %dl, flag_carry\n";
                }
                else if(v1[0] != '$' && v1[0] != '%' && v2[0] == '%') //mem-reg
                {
                    v2 = v2.substr(1);
                    int off = off_set(v2);
                    if(off == -1) Eroare();
                    fout << " movzbl " << v1 << ", %ebx\n";
                    fout << " movzbl tabel_mask(%ebx), %ebx\n";
                    fout << " movzbl variabile+" << off << ", %eax\n";
                    fout << " movzbl tabel_mask(%eax), %eax\n";
                    fout << " movl add_indice_linie(,%eax,4), %ecx\n";
                    fout << " movzbl (%ecx,%ebx,1), %edx\n";
                    fout << " movl %edx, variabile+" << off << "\n";
                    fout << " movl Carry_add_indice_linie(,%eax,4), %ecx\n";
                    fout << " movzbl (%ecx,%ebx,1), %edx\n";
                    fout << " movb %dl, flag_carry\n";
                }
                else if(v1[0] == '%' && v2[0] != '$' && v2[0] != '%') // reg-mem
                {
                    v1 = v1.substr(1);
                    int off = off_set(v1);
                    if(off == -1) Eroare();
                    fout << " movzbl " << v2 << ", %eax\n";
                    fout << " movzbl tabel_mask(%eax), %eax\n";
                    fout << " movzbl variabile+" << off << ", %ebx\n";
                    fout << " movzbl tabel_mask(%ebx), %ebx\n";
                    fout << " movl add_indice_linie(,%eax,4), %ecx\n";
                    fout << " movzbl (%ecx,%ebx,1), %edx\n";
                    fout << " movl %edx, " << v2 << "\n";
                    fout << " movl Carry_add_indice_linie(,%eax,4), %ecx\n";
                    fout << " movzbl (%ecx,%ebx,1), %edx\n";
                    fout << " movb %dl, flag_carry\n";
                }
                else if (v1[0] == '$' && v2[0] != '$' && v2[0] != '%') // val-mem
                {
                    fout << " movzbl " << v2 << ", %eax\n";
                    fout << " movzbl tabel_mask(%eax), %eax\n";
                    fout << " movl " << v1 << ", %ebx\n";
                    fout << " movzbl tabel_mask(%ebx), %ebx\n";
                    fout << " movl add_indice_linie(,%eax,4), %ecx\n";
                    fout << " movzbl (%ecx,%ebx,1), %edx\n";
                    fout << " movl %edx, " << v2 << "\n";
                    fout << " movl Carry_add_indice_linie(,%eax,4), %ecx\n";
                    fout << " movzbl (%ecx,%ebx,1), %edx\n";
                    fout << " movb %dl, flag_carry\n";
                }
            }
            continue;
        }
        poz = linie.find("inc");
        if(poz != string::npos)
        {
            Prelucrare_Linie(linie);
            //fout << "\n" << linie << "\n";
            string v = "";
            size_t procent = linie.find('%');
            if(procent != string::npos)
            {
                v = linie.substr(procent+1);
                int off = off_set(v);
                if(off == -1) Eroare();
                fout << " movzbl variabile+" << off << ", %eax\n";
                fout << " movzbl tabel_mask(%eax), %eax\n";
                fout << " movl $1, %ebx\n";
                fout << " movzbl tabel_mask(%ebx), %ebx\n";
                fout << " movl add_indice_linie(,%eax,4), %ecx\n";
                fout << " movzbl (%ecx,%ebx,1), %edx\n";
                fout << " movl %edx, variabile+" << off << "\n";
                fout << " movl Carry_add_indice_linie(,%eax,4), %ecx\n";
                fout << " movzbl (%ecx,%ebx,1), %edx\n";
                fout << " movb %dl, flag_carry\n";
            }
            else
            {
                v = linie.substr(4);
                fout << " movzbl " << v << ", %eax\n";
                fout << " movzbl tabel_mask(%eax), %eax\n";
                fout << " movl $1, %ebx\n";
                fout << " movzbl tabel_mask(%ebx), %ebx\n";
                fout << " movl add_indice_linie(,%eax,4), %ecx\n";
                fout << " movzbl (%ecx,%ebx,1), %edx\n";
                fout << " movl %edx, " << v << "\n";
                fout << " movl Carry_add_indice_linie(,%eax,4), %ecx\n";
                fout << " movzbl (%ecx,%ebx,1), %edx\n";
                fout << " movb %dl, flag_carry\n";
            }
            continue;
        }
        poz = linie.find("push");
        if(poz != string::npos)
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
            continue;
        }
        poz = linie.find("pop");
        if(poz != string::npos)
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
            continue;
        }
        poz = linie.find("int $0x80");
        if(poz != string::npos)
        {
            fout << " movl variabile+0, %eax\n";
            fout << " movl variabile+4, %ebx\n";
            fout << " movl variabile+8, %ecx\n";
            fout << " movl variabile+12, %edx\n";
            fout << " int $0x80\n";
            continue;
        }
        poz = linie.find("cmp");
        if(poz != string::npos)
        {
            Scoatere_Instructiune(linie, instructiune, v1, v2);
            if(v1[0] == '%' && v2[0] == v1[0])
            {
                v1 = v1.substr(1);
                v2 = v2.substr(1);
                int off1 = off_set(v1);
                if(off1 == -1) Eroare();
                int off2 = off_set(v2);
                if(off2 == -1) Eroare();
                fout << " movzbl variabile+" << off1 << ", %eax\n";
                fout << " movzbl tabel_mask(%eax), %eax\n";
                fout << " movzbl variabile+" << off2 << ", %ebx\n";
                fout << " movzbl tabel_mask(%ebx), %ebx\n";
                fout << " movl zero_indice_linie(,%eax,4), %ecx\n";
                fout << " movzbl (%ecx,%ebx,1), %edx\n";
                fout << " movb %dl, flag_zero\n";
                fout << " movl below_indice_linie(,%eax,4), %ecx\n";
                fout << " movzbl (%ecx,%ebx,1), %edx\n";
                fout << " movb %dl, flag_below\n";
                fout << " movl less_indice_linie(,%eax,4), %ecx\n";
                fout << " movzbl (%ecx,%ebx,1), %edx\n";
                fout << " movb %dl, flag_less\n";
            }
            else if (v1[0] == '$' && v2[0] == '%')
            {
                v2 = v2.substr(1);
                int off = off_set(v2);
                if(off == -1) Eroare();
                fout << " movl " << v1 << ", %eax\n";
                fout << " movzbl tabel_mask(%eax), %eax\n";
                fout << " movzbl variabile+" << off << ", %ebx\n";
                fout << " movzbl tabel_mask(%ebx), %ebx\n";
                fout << " movl zero_indice_linie(,%eax,4), %ecx\n";
                fout << " movzbl (%ecx,%ebx,1), %edx\n";
                fout << " movb %dl, flag_zero\n";
                fout << " movl below_indice_linie(,%eax,4), %ecx\n";
                fout << " movzbl (%ecx,%ebx,1), %edx\n";
                fout << " movb %dl, flag_below\n";
                fout << " movl less_indice_linie(,%eax,4), %ecx\n";
                fout << " movzbl (%ecx,%ebx,1), %edx\n";
                fout << " movb %dl, flag_less\n";
            }
            else if (v1[0] == '$' && v2[0] != '%' && v2[0] != '$')
            {
                fout << " movl " << v1 << ", %eax\n";
                fout << " movzbl tabel_mask(%eax), %eax\n";
                fout << " movzbl " << v2 << ", %ebx\n";
                fout << " movzbl tabel_mask(%ebx), %ebx\n";
                fout << " movl zero_indice_linie(,%eax,4), %ecx\n";
                fout << " movzbl (%ecx,%ebx,1), %edx\n";
                fout << " movb %dl, flag_zero\n";
                fout << " movl below_indice_linie(,%eax,4), %ecx\n";
                fout << " movzbl (%ecx,%ebx,1), %edx\n";
                fout << " movb %dl, flag_below\n";
                fout << " movl less_indice_linie(,%eax,4), %ecx\n";
                fout << " movzbl (%ecx,%ebx,1), %edx\n";
                fout << " movb %dl, flag_less\n";
            }
            else if (v1[0] == '%' && v2[0] != '%' && v2[0] != '$')
            {
                v1 = v1.substr(1);
                int off = off_set(v1);
                if(off == -1) Eroare();
                fout << " movzbl variabile+" << off << ", %eax\n";
                fout << " movzbl tabel_mask(%eax), %eax\n";
                fout << " movzbl " << v2 << ", %ebx\n";
                fout << " movzbl tabel_mask(%ebx), %ebx\n";
                fout << " movl zero_indice_linie(,%eax,4), %ecx\n";
                fout << " movzbl (%ecx,%ebx,1), %edx\n";
                fout << " movb %dl, flag_zero\n";
                fout << " movl below_indice_linie(,%eax,4), %ecx\n";
                fout << " movzbl (%ecx,%ebx,1), %edx\n";
                fout << " movb %dl, flag_below\n";
                fout << " movl less_indice_linie(,%eax,4), %ecx\n";
                fout << " movzbl (%ecx,%ebx,1), %edx\n";
                fout << " movb %dl, flag_less\n";
            }
            else if (v1[0] != '%' && v1[0] != '$' && v2[0] == '%')
            {
                v2 = v2.substr(1);
                int off = off_set(v2);
                if(off == -1) Eroare();
                fout << " movzbl " << v1 << ", %eax\n";
                fout << " movzbl tabel_mask(%eax), %eax\n";
                fout << " movzbl variabile+" << off << ", %ebx\n";
                fout << " movzbl tabel_mask(%ebx), %ebx\n";
                fout << " movl zero_indice_linie(,%eax,4), %ecx\n";
                fout << " movzbl (%ecx,%ebx,1), %edx\n";
                fout << " movb %dl, flag_zero\n";
                fout << " movl below_indice_linie(,%eax,4), %ecx\n";
                fout << " movzbl (%ecx,%ebx,1), %edx\n";
                fout << " movb %dl, flag_below\n";
                fout << " movl less_indice_linie(,%eax,4), %ecx\n";
                fout << " movzbl (%ecx,%ebx,1), %edx\n";
                fout << " movb %dl, flag_less\n";
            }
            continue;
        }
        poz = linie.find("je");
        if(poz != string::npos)
        {
            Prelucrare_Linie(linie);
            string v = linie.substr(3);
            fout << " cmpb $1, flag_zero\n";
            fout << " je "<< v << "\n";
            continue;
        }
        poz = linie.find("jne");
        if(poz == string::npos) poz = linie.find("jnz");
        if(poz != string::npos)
        {
            Prelucrare_Linie(linie);
            string v = linie.substr(4);
            fout << " cmpb $0, flag_zero\n";
            fout << " je " << v << "\n";
            continue;
        }
        poz = linie.find("jb");
        if(poz == string::npos) poz = linie.find("jc");
        if(poz != string::npos)
        {
            Prelucrare_Linie(linie);
            string v = linie.substr(3);
            fout << " cmpb $1, flag_below\n";
            fout << " je " << v << "\n";
            continue;
        }
        poz = linie.find("jae");
        if(poz == string::npos) poz = linie.find("jnb");
        if(poz != string::npos)
        {
            Prelucrare_Linie(linie);
            string v = linie.substr(4);
            fout << " cmpb $0, flag_below\n";
            fout << " je " << v << "\n";
            continue;
        }
        poz = linie.find("ja");
        if(poz != string::npos)
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
            continue;
        }
        poz = linie.find("jbe");
        if(poz != string::npos)
        {
            Prelucrare_Linie(linie);
            string v = linie.substr(4);
            fout << " cmpb $1, flag_below\n";
            fout << " je " << v << "\n";
            fout << " cmpb $1, flag_zero\n";
            fout << " je " << v << "\n";
            continue;
        }
        poz = linie.find("jl");
        if(poz != string::npos && linie.find("jle") == string::npos)
        {
            Prelucrare_Linie(linie);
            string v = linie.substr(3);
            fout << " cmpb $1, flag_less\n";
            fout << " je " << v << "\n";
            continue;
        }
        poz = linie.find("jle");
        if(poz != string::npos)
        {
            Prelucrare_Linie(linie);
            string v = linie.substr(4);
            fout << " cmpb $1, flag_less\n";
            fout << " je " << v << "\n";
            fout << " cmpb $1, flag_zero\n";
            fout << " je " << v << "\n";
            continue;
        }
        poz = linie.find("jge");
        if(poz != string::npos)
        {
            Prelucrare_Linie(linie);
            string v = linie.substr(4);
            fout << " cmpb $0, flag_less\n";
            fout << " je " << v << "\n";
            continue;
        }
        poz = linie.find("jg");
        if(poz != string::npos && linie.find("jge") == string::npos)
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
            continue;
        }
        poz = linie.find("xor");
        if(poz != string::npos)
        {
            Scoatere_Instructiune(linie, instructiune, v1, v2);
            if(v1[0] == '$' && v2[0] == '%')
            {
                v2 = v2.substr(1);
                int off = off_set(v2);
                if(off == -1) Eroare();
                fout << " movl " << v1 << ", %eax\n";
                fout << " movzbl tabel_mask(%eax), %eax\n";
                fout << " movzbl variabile+" << off << ", %ebx\n";
                fout << " movzbl tabel_mask(%ebx), %ebx\n";
                fout << " movl xor_indice_linie(,%eax,4), %ecx\n";
                fout << " movzbl (%ecx,%ebx,1), %edx\n";
                fout << " movl %edx, variabile+" << off << "\n";
                fout << " movl %edx, %eax\n";
                fout << " movl $0, %ebx\n";
                fout << " movl zero_indice_linie(,%eax,4), %ecx\n";
                fout << " movzbl (%ecx,%ebx,1), %edx\n";
                fout << " movb %dl, flag_zero\n";
            }
            else if(v1[0] == '%' && v2[0] == '%')
            {
                v1 = v1.substr(1);
                v2 = v2.substr(1);
                int off1 = off_set(v1);
                if(off1 == -1) Eroare();
                int off2 = off_set(v2);
                if(off2 == -1) Eroare();
                fout << " movzbl variabile+" << off1 << ", %eax\n";
                fout << " movzbl tabel_mask(%eax), %eax\n";
                fout << " movzbl variabile+" << off2 << ", %ebx\n";
                fout << " movzbl tabel_mask(%ebx), %ebx\n";
                fout << " movl xor_indice_linie(,%eax,4), %ecx\n";
                fout << " movzbl (%ecx,%ebx,1), %edx\n";
                fout << " movl %edx, variabile+" << off2 << "\n";
                fout << " movl %edx, %eax\n";
                fout << " movl $0, %ebx\n";
                fout << " movl zero_indice_linie(,%eax,4), %ecx\n";
                fout << " movzbl (%ecx,%ebx,1), %edx\n";
                fout << " movb %dl, flag_zero\n";
            }
            else if(v1[0] != '$' && v1[0] != '%' && v2[0] == '%')
            {
                v2 = v2.substr(1);
                int off = off_set(v2);
                if(off == -1) Eroare();
                fout << " movzbl " << v1 << ", %eax\n";
                fout << " movzbl tabel_mask(%eax), %eax\n";
                fout << " movzbl variabile+" << off << ", %ebx\n";
                fout << " movzbl tabel_mask(%ebx), %ebx\n";
                fout << " movl xor_indice_linie(,%eax,4), %ecx\n";
                fout << " movzbl (%ecx,%ebx,1), %edx\n";
                fout << " movl %edx, variabile+" << off << "\n";
                fout << " movl %edx, %eax\n";
                fout << " movl $0, %ebx\n";
                fout << " movl zero_indice_linie(,%eax,4), %ecx\n";
                fout << " movzbl (%ecx,%ebx,1), %edx\n";
                fout << " movb %dl, flag_zero\n";
            }
            else if(v1[0] == '%' && v2[0] != '$' && v2[0] != '%')
            {
                v1 = v1.substr(1);
                int off = off_set(v1);
                if(off == -1) Eroare();
                fout << " movzbl variabile+" << off << ", %eax\n";
                fout << " movzbl tabel_mask(%eax), %eax\n";
                fout << " movzbl " << v2 << ", %ebx\n";
                fout << " movzbl tabel_mask(%ebx), %ebx\n";
                fout << " movl xor_indice_linie(,%eax,4), %ecx\n";
                fout << " movzbl (%ecx,%ebx,1), %edx\n";
                fout << " movl %edx, " << v2 << "\n";
                fout << " movl %edx, %eax\n";
                fout << " movl $0, %ebx\n";
                fout << " movl zero_indice_linie(,%eax,4), %ecx\n";
                fout << " movzbl (%ecx,%ebx,1), %edx\n";
                fout << " movb %dl, flag_zero\n";
            }
            continue;
        }
        poz = linie.find("sub");
        if(poz != string::npos)
        {
            Scoatere_Instructiune(linie, instructiune, v1, v2);
            if (v2 == "%esp" || v2 == "%ebp") fout << " sub " << v1 << ", " << v2 << "\n";
            else
            {
                if(v1[0] == '$' && v2[0] == '%') // val-reg
                {
                    v2 = v2.substr(1);
                    int off = off_set(v2);
                    if(off == -1) Eroare();
                    fout << " movzbl variabile+" << off << ", %eax\n";
                    fout << " movzbl tabel_mask(%eax), %eax\n";
                    fout << " movl " << v1 << ", %ebx\n";
                    fout << " movzbl tabel_mask(%ebx), %ebx\n";
                    fout << " movl sub_indice_linie(,%eax,4), %ecx\n";
                    fout << " movzbl (%ecx,%ebx,1), %edx\n";
                    fout << " movl %edx, variabile+" << off << "\n";
                    fout << " movl below_sub_indice_linie(,%eax,4), %ecx\n";
                    fout << " movzbl (%ecx,%ebx,1), %edx\n";
                    fout << " movb %dl, flag_below\n";
                }
                else if(v1[0] == '%' && v2[0] == '%') // reg-reg
                {
                    v1 = v1.substr(1);
                    v2 = v2.substr(1);
                    int off1 = off_set(v1);
                    int off2 = off_set(v2);
                    if(off1 == -1 || off2 == -1) Eroare();
                    fout << " movzbl variabile+" << off2 << ", %eax\n";
                    fout << " movzbl tabel_mask(%eax), %eax\n";
                    fout << " movzbl variabile+" << off1 << ", %ebx\n";
                    fout << " movzbl tabel_mask(%ebx), %ebx\n";
                    fout << " movl sub_indice_linie(,%eax,4), %ecx\n";
                    fout << " movzbl (%ecx,%ebx,1), %edx\n";
                    fout << " movl %edx, variabile+" << off2 << "\n";
                    fout << " movl below_sub_indice_linie(,%eax,4), %ecx\n";
                    fout << " movzbl (%ecx,%ebx,1), %edx\n";
                    fout << " movb %dl, flag_below\n";
                }
                else if(v1[0] != '$' && v1[0] != '%' && v2[0] == '%') // mem-reg
                {
                    v2 = v2.substr(1);
                    int off = off_set(v2);
                    if(off == -1) Eroare();
                    fout << " movzbl variabile+" << off << ", %eax\n";
                    fout << " movzbl tabel_mask(%eax), %eax\n";
                    fout << " movzbl " << v1 << ", %ebx\n";
                    fout << " movzbl tabel_mask(%ebx), %ebx\n";
                    fout << " movl sub_indice_linie(,%eax,4), %ecx\n";
                    fout << " movzbl (%ecx,%ebx,1), %edx\n";
                    fout << " movl %edx, variabile+" << off << "\n";
                    fout << " movl below_sub_indice_linie(,%eax,4), %ecx\n";
                    fout << " movzbl (%ecx,%ebx,1), %edx\n";
                    fout << " movb %dl, flag_below\n";
                }
                else if(v1[0] == '%' && v2[0] != '$' && v2[0] != '%') // reg-mem
                {
                    v1 = v1.substr(1);
                    int off = off_set(v1);
                    if(off == -1) Eroare();
                    fout << " movzbl " << v2 << ", %eax\n";
                    fout << " movzbl tabel_mask(%eax), %eax\n";
                    fout << " movzbl variabile+" << off << ", %ebx\n";
                    fout << " movzbl tabel_mask(%ebx), %ebx\n";
                    fout << " movl sub_indice_linie(,%eax,4), %ecx\n";
                    fout << " movzbl (%ecx,%ebx,1), %edx\n";
                    fout << " movl %edx, " << v2 << "\n";
                    fout << " movl below_sub_indice_linie(,%eax,4), %ecx\n";
                    fout << " movzbl (%ecx,%ebx,1), %edx\n";
                    fout << " movb %dl, flag_below\n";
                }
                else if (v1[0] == '$' && v2[0] != '$' && v2[0] != '%') // val-mem
                {
                    fout << " movzbl " << v2 << ", %eax\n";
                    fout << " movzbl tabel_mask(%eax), %eax\n";
                    fout << " movl " << v1 << ", %ebx\n";
                    fout << " movzbl tabel_mask(%ebx), %ebx\n";
                    fout << " movl sub_indice_linie(,%eax,4), %ecx\n";
                    fout << " movzbl (%ecx,%ebx,1), %edx\n";
                    fout << " movl %edx, " << v2 << "\n";
                    fout << " movl below_sub_indice_linie(,%eax,4), %ecx\n";
                    fout << " movzbl (%ecx,%ebx,1), %edx\n";
                    fout << " movb %dl, flag_below\n";
                }
            }
            continue;
        }
        poz = linie.find("dec");
        if(poz != string::npos)
        {
            Prelucrare_Linie(linie);
            string v = "";
            size_t procent = linie.find('%');
            if(procent != string::npos)
            {
                // Cazul pentru registru (ex: dec %eax)
                v = linie.substr(procent+1); // sarim peste "dec %"
                int off = off_set(v);
                if(off == -1) Eroare();
                fout << " movzbl variabile+" << off << ", %eax\n";
                fout << " movzbl tabel_mask(%eax), %eax\n";
                fout << " movl $1, %ebx\n";
                fout << " movzbl tabel_mask(%ebx), %ebx\n";
                fout << " movl sub_indice_linie(,%eax,4), %ecx\n";
                fout << " movzbl (%ecx,%ebx,1), %edx\n";
                fout << " movl %edx, variabile+" << off << "\n";
                fout << " movl below_sub_indice_linie(,%eax,4), %ecx\n";
                fout << " movzbl (%ecx,%ebx,1), %edx\n";
                fout << " movb %dl, flag_below\n";
            }
            else
            {
                // Cazul pentru variabila/memorie (ex: dec x)
                v = linie.substr(4); // sarim peste "dec "
                fout << " movzbl " << v << ", %eax\n";
                fout << " movzbl tabel_mask(%eax), %eax\n";
                fout << " movl $1, %ebx\n";
                fout << " movzbl tabel_mask(%ebx), %ebx\n";
                fout << " movl sub_indice_linie(,%eax,4), %ecx\n";
                fout << " movzbl (%ecx,%ebx,1), %edx\n";
                fout << " movl %edx, " << v << "\n";
                fout << " movl below_sub_indice_linie(,%eax,4), %ecx\n";
                fout << " movzbl (%ecx,%ebx,1), %edx\n";
                fout << " movb %dl, flag_below\n";
            }
            continue;
        }
        poz = linie.find("lea");
        if(poz != string::npos)
        {
            Scoatere_Instructiune(linie, instructiune, v1, v2);
            if(v1[0] != '$' && v1[0] != '%' && v2[0] == '%')
            {
                string reg_dest = v2.substr(1);
                int off = off_set(reg_dest);
                if(off == -1) Eroare();
                fout << " movl $" << v1 << ", %eax\n";
                fout << " movl %eax, variabile+" << off << "\n";
            }
            continue;
        }
        fout << " " << linie << "\n";
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    fin.tie();
    fout.tie();
    Parsare();
    fin.close();
    fout.close();
    return 0;
}
