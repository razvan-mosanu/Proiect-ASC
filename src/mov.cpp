#include "mov.h"

void ParsareMov(string linie)
{
	string instructiune, v1, v2;
    instructiune = v1 = v2 = "";
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
		return;
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
    return;
}