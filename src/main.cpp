#include "../include/movinit.h"
#include "../include/mov.h"
#include "../include/aritm.h"
#include "../include/push.h"
#include "../include/cmp.h"
#include "../include/logic.h"
#include "../include/jmp.h"
#include "../include/lea.h"

/**
De facut:
-mul
-shl
-shr
*/

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
            continue;
        }
        poz = linie.find("mov");
        if(poz != string::npos)
        {
            ParsareMov(linie);
            continue;
        }
        poz = linie.find("add");
        if(poz != string::npos)
        {
            ParsareAdd(linie);
            continue;
        }
        poz = linie.find("inc");
        if(poz != string::npos)
        {
            ParsareInc(linie);
            continue;
        }
        poz = linie.find("push");
        if(poz != string::npos)
        {
            ParsarePush(linie);
            continue;
        }
        poz = linie.find("pop");
        if(poz != string::npos)
        {
            ParsarePop(linie);
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
            ParsareCmp(linie);
            continue;
        }
        poz = linie.find("je");
        if(poz != string::npos)
        {
            ParsareJe(linie);
            continue;
        }
        poz = linie.find("jne");
        if(poz == string::npos) poz = linie.find("jnz");
        if(poz != string::npos)
        {
            ParsareJne(linie);
            continue;
        }
        poz = linie.find("jb");
        if(poz == string::npos) poz = linie.find("jc");
        if(poz != string::npos)
        {
            ParsareJb(linie);
            continue;
        }
        poz = linie.find("jae");
        if(poz == string::npos) poz = linie.find("jnb");
        if(poz != string::npos)
        {
            ParsareJae(linie);
            continue;
        }
        poz = linie.find("ja");
        if(poz != string::npos)
        {
            ParsareJa(linie);
            continue;
        }
        poz = linie.find("jbe");
        if(poz != string::npos)
        {
            ParsareJbe(linie);
            continue;
        }
        poz = linie.find("jl");
        if(poz != string::npos && linie.find("jle") == string::npos)
        {
            ParsareJl(linie);
            continue;
        }
        poz = linie.find("jle");
        if(poz != string::npos)
        {
            ParsareJle(linie);
            continue;
        }
        poz = linie.find("jge");
        if(poz != string::npos)
        {
            ParsareJge(linie);
            continue;
        }
        poz = linie.find("jg");
        if(poz != string::npos && linie.find("jge") == string::npos)
        {
            ParsareJg(linie);
            continue;
        }
        poz = linie.find("xor");
        if(poz != string::npos)
        {
            ParsareXor(linie);
            continue;
        }
        poz = linie.find("sub");
        if(poz != string::npos)
        {
            ParsareSub(linie);
            continue;
        }
        poz = linie.find("dec");
        if(poz != string::npos)
        {
            ParsareDec(linie);
            continue;
        }
        poz = linie.find("lea");
        if(poz != string::npos)
        {
            ParsareLea(linie);
            continue;
        }
        poz = linie.find("div");
        if(poz != string::npos)
        {
            ParsareDiv(linie);
            continue;
        }
        poz = linie.find("and");
        if(poz != string::npos && linie.find("and_indice") == string::npos)
        {
            ParsareAnd(linie);
            continue;
        }
        poz = linie.find("or");
        if(poz != string::npos && linie.find("or_indice") == string::npos && linie.find("greater_or_equal") == string::npos)
        {
            ParsareOr(linie);
            continue;
        }
        poz = linie.find("loop");
        if(poz != string::npos)
        {
            Prelucrare_Linie(linie);
            string eticheta = linie.substr(5);
            fout << " movzbl variabile+8, %eax\n";
            fout << " movzbl tabel_mask(%eax), %eax\n";
            fout << " movl $1, %ebx\n";
            fout << " movzbl tabel_mask(%ebx), %ebx\n";
            fout << " movl sub_indice_linie(,%eax,4), %ecx\n";
            fout << " movzbl (%ecx,%ebx,1), %edx\n";
            fout << " movl %edx, variabile+8\n";
            fout << " movl zero_indice_linie(,%edx,4), %ecx\n";
            fout << " movzbl (%ecx,%edx,1), %eax\n";
            fout << " movb %al, flag_zero\n";
            fout << " cmpb $0, flag_zero\n";
            fout << " je " << eticheta << "\n";
            continue;
        }
        poz = linie.find("test");
        if(poz != string::npos)
        {
            ParsareTest(linie);
            continue;
        }
        poz = linie.find("imul");
        if (poz != string::npos)
        {
            continue;
        }
        poz = linie.find("mul");
        if (poz != string::npos)
        {
            continue;
        }
        poz = linie.find("shl");
        if (poz != string::npos)
        {
            continue;
        }
        poz = linie.find("shr");
        {
            continue;
        }
        fout << " " << linie << "\n";
    }
}

int main(int args, char *argv[])
{
    ios_base::sync_with_stdio(0);
    if (args == 1)
    {
        cout << "Utilizare: ./movfuscator file1.s file2.s ...\n";
        return 2;
    }
    for (int i = 1; i < args; i++)
    {
        string str_out(argv[i]);
        str_out = "mov" + str_out;
     
        Deschide_Fisiere(argv[i], str_out);
        if (!fin)
        {
            cout << "Eroare\n";
            return 1;
        }
     
        Parsare();
        
        fin.close();
        fout.close();
    }
    return 0;
}
