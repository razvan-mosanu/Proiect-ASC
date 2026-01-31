#include "movinit.h"
#include "cmp.h"

void ParsareCmp(string linie)
{
    string instructiune, v1, v2;
    instructiune = v1 = v2 = "";
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
}