#include "logic.h"

void ParsareAnd(string linie)
{
    string instructiune, v1, v2;
    instructiune = v1 = v2 = "";
    Scoatere_Instructiune(linie, instructiune, v1, v2);
    string r_src = v1;
    if(r_src[0] == '%' || r_src[0] == '$') r_src = r_src.substr(1);
    string r_dest = v2;
    if(r_dest[0] == '%') r_dest = r_dest.substr(1);
    int off_src = (v1[0] == '%') ? off_set(r_src) : -1;
    int off_dest = off_set(r_dest);
    if(off_dest == -1) Eroare();
    if(v1[0] == '$') fout << " movl " << v1 << ", %eax\n";
    else fout << " movzbl variabile+" << off_src << ", %eax\n";
    fout << " movzbl tabel_mask(%eax), %eax\n";
    fout << " movzbl variabile+" << off_dest << ", %ebx\n";
    fout << " movzbl tabel_mask(%ebx), %ebx\n";
    fout << " movl and_indice_linie(,%eax,4), %ecx\n";
    fout << " movzbl (%ecx,%ebx,1), %edx\n";
    fout << " movl %edx, variabile+" << off_dest << "\n";
    fout << " movl zero_indice_linie(,%edx,4), %ecx\n";
    fout << " movzbl (%ecx,%edx,1), %eax\n";
    fout << " movb %al, flag_zero\n";
}

void ParsareOr(string linie)
{
    string instructiune, v1, v2;
    instructiune = v1 = v2 = "";
    Scoatere_Instructiune(linie, instructiune, v1, v2);
    string r_src = v1;
    if(r_src[0] == '%' || r_src[0] == '$') r_src = r_src.substr(1);
    string r_dest = v2;
    if(r_dest[0] == '%') r_dest = r_dest.substr(1);
    int off_src = (v1[0] == '%') ? off_set(r_src) : -1;
    int off_dest = off_set(r_dest);
    if(off_dest == -1) Eroare();
    if(v1[0] == '$') fout << " movl " << v1 << ", %eax\n";
    else fout << " movzbl variabile+" << off_src << ", %eax\n";
    fout << " movzbl tabel_mask(%eax), %eax\n";
    fout << " movzbl variabile+" << off_dest << ", %ebx\n";
    fout << " movzbl tabel_mask(%ebx), %ebx\n";
    fout << " movl or_indice_linie(,%eax,4), %ecx\n";
    fout << " movzbl (%ecx,%ebx,1), %edx\n";
    fout << " movl %edx, variabile+" << off_dest << "\n";
    fout << " movl zero_indice_linie(,%edx,4), %ecx\n";
    fout << " movzbl (%ecx,%edx,1), %eax\n";
    fout << " movb %al, flag_zero\n";
}

void ParsareXor(string linie)
{
    string instructiune, v1, v2;
    instructiune = v1 = v2 = "";
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
}

void ParsareTest(string linie)
{
    string instructiune, v1, v2;
    instructiune = v1 = v2 = "";
    Scoatere_Instructiune(linie, instructiune, v1, v2);
    string r_src = v1;
    if(!r_src.empty() && (r_src[0] == '%' || r_src[0] == '$')) r_src = r_src.substr(1);
    string r_dest = v2;
    if(!r_dest.empty() && r_dest[0] == '%') r_dest = r_dest.substr(1);
    int off_src = (v1[0] == '%') ? off_set(r_src) : -1;
    int off_dest = off_set(r_dest);
    if(off_dest == -1) Eroare();
    if(v1[0] == '$') fout << " movl " << v1 << ", %eax\n";
    else fout << " movzbl variabile+" << off_src << ", %eax\n";
    fout << " movzbl tabel_mask(%eax), %eax\n";
    fout << " movzbl variabile+" << off_dest << ", %ebx\n";
    fout << " movzbl tabel_mask(%ebx), %ebx\n";
    fout << " movl and_indice_linie(,%eax,4), %ecx\n";
    fout << " movzbl (%ecx,%ebx,1), %edx\n";
    fout << " movl zero_indice_linie(,%edx,4), %ecx\n";
    fout << " movzbl (%ecx,%edx,1), %eax\n";
    fout << " movb %al, flag_zero\n";
}
