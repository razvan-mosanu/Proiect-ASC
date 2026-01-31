#include "lea.h"

void ParsareLea(string linie)
{
    string instructiune, v1, v2;
    instructiune = v1 = v2 = "";

    size_t p_open = linie.find('(');
    size_t p_close = linie.find(')');

    if(p_open != string::npos && p_close != string::npos)
    {
        string disp = "";
        size_t lea_idx = linie.find("lea");
        disp = linie.substr(lea_idx + 3, p_open - (lea_idx + 3));
        string interior = linie.substr(p_open + 1, p_close - p_open - 1);
        string baza = "", index = "", scara = "1";
        size_t c1 = interior.find(',');
        if(c1 == string::npos) baza = interior;
        else
        {
            baza = interior.substr(0, c1);
            size_t c2 = interior.find(',', c1 + 1);
            if(c2 == string::npos) index = interior.substr(c1 + 1);
            else
            {
                index = interior.substr(c1 + 1, c2 - c1 - 1);
                scara = interior.substr(c2 + 1);
            }
        }

        size_t virgula_ext = linie.find(',', p_close);
        string dest = linie.substr(virgula_ext + 1);
        auto curata = [&](string &s)
        {
            s.erase(remove(s.begin(), s.end(), ' '), s.end());
            s.erase(remove(s.begin(), s.end(), '\t'), s.end());
            s.erase(remove(s.begin(), s.end(), '\r'), s.end());
            if(!s.empty() && s[0] == '%') s = s.substr(1);
        };
        curata(disp);
        curata(baza);
        curata(index);
        curata(scara);
        curata(dest);
        int off_d = off_set(dest);
        if(off_d == -1) Eroare();
        if(!baza.empty())
        {
            int off_b = off_set(baza);
            fout << " movl variabile+" << off_b << ", %ebx\n";
        }
        else fout << " xorl %ebx, %ebx\n";
        if(!index.empty())
        {
            int off_i = off_set(index);
            fout << " movl variabile+" << off_i << ", %esi\n";
        }
        else fout << " xorl %esi, %esi\n";
        string prefix_disp = (disp.empty() ? "" : "$" + disp);
        if(!disp.empty() && isdigit(disp[0])) prefix_disp = disp;
        if(!disp.empty() && !isdigit(disp[0])) fout << " leal " << disp << "(%ebx, %esi, " << scara << "), %eax\n";
        else fout << " leal " << (disp.empty() ? "0" : disp) << "(%ebx, %esi, " << scara << "), %eax\n";
        fout << " movl %eax, variabile+" << off_d << "\n";
    }
    else
    {
        string r = v2;
        if(r[0] == '%') r = r.substr(1);
        int off = off_set(r);
        if(off == -1) Eroare();
        fout << " movl $" << v1 << ", %eax\n";
        fout << " movl %eax, variabile+" << off << "\n";
    }
}