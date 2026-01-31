#include "aritm.h"

void ParsareAdd(string linie) 
{
    string instructiune, v1, v2;
    instructiune = v1 = v2 = "";

    Scoatere_Instructiune(linie, instructiune, v1, v2);
    if (v2 == "%esp" || v2 == "%ebp")
    {
        fout << " add " << v1 << ", " << v2 << "\n";
        return;
    }
    if (v1[0] == '$' && v2[0] == '%') // val-reg
    {
        v2 = v2.substr(1);
        int off = off_set(v2);
        if (off == -1)
            Eroare();
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
    else if (v1[0] == '%' && v2[0] == '%') // reg-reg
    {
        v1 = v1.substr(1);
        v2 = v2.substr(1);
        int off1 = off_set(v1);
        if (off1 == -1)
            Eroare();
        int off2 = off_set(v2);
        if (off2 == -1)
            Eroare();
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
    else if (v1[0] != '$' && v1[0] != '%' && v2[0] == '%') // mem-reg
    {
        v2 = v2.substr(1);
        int off = off_set(v2);
        if (off == -1)
            Eroare();
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
    else if (v1[0] == '%' && v2[0] != '$' && v2[0] != '%') // reg-mem
    {
        v1 = v1.substr(1);
        int off = off_set(v1);
        if (off == -1)
            Eroare();
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

void ParsareInc(string linie)
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
}

void ParsareSub(string linie)
{
    string instructiune, v1, v2;
    instructiune = v1 = v2 = "";
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
}

void ParsareDec(string linie)
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
}

void ParsareDiv(string linie)
{
    Prelucrare_Linie(linie);
    string v = "";
    size_t procent = linie.find('%');
    fout << " movzbl variabile+0, %eax\n";
    fout << " movzbl tabel_mask(%eax), %eax\n";
    if(procent != string::npos)
    {
        v = linie.substr(procent + 1);
        int off = off_set(v);
        if(off == -1) Eroare();
        fout << " movzbl variabile+" << off << ", %ebx\n";
    }
    else
    {
        v = linie.substr(4);
        fout << " movzbl " << v << ", %ebx\n";
    }
    fout << " movzbl tabel_mask(%ebx), %ebx\n";
    fout << " movl div_indice_linie(,%eax,4), %ecx\n";
    fout << " movzbl (%ecx,%ebx,1), %edx\n";
    fout << " movl %edx, variabile+0\n";
    fout << " movl mod_indice_linie(,%eax,4), %ecx\n";
    fout << " movzbl (%ecx,%ebx,1), %edx\n";
    fout << " movl %edx, variabile+12\n";
}

