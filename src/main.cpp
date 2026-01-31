#include <iostream>

#include "movinit.h"
#include "aritm.h"
#include "cmp.h"
#include "jmp.h"
#include "lea.h"
#include "logic.h"
#include "mov.h"
#include "push.h"

void Parsare()
{
    string linie;
    size_t poz;
    while(getline(fin,linie))
    {
        if (linie.empty()) continue;
        if (linie.find(':') != string::npos && linie.find("indice_linie") == string::npos)
        {
            fout << " " << linie << "\n";
            continue;
        }
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
        poz = linie.find("jmp"); 
        if(poz != string::npos)
        {
            Prelucrare_Linie(linie);
            string v = linie.substr(4);
            fout << " jmp " << v << "\n";
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
        string cmd = "", op1 = "", op2 = ""; 
        Scoatere_Instructiune(linie, cmd, op1, op2);
        if(cmd == "or" || cmd == "orl")
        {
            ParsareOr(op1, op2);
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
            ParsareImul(linie);
            continue;
        }
        poz = linie.find("mul");
        if (poz != string::npos)
        {
            ParsareMul(linie);
            continue;
        }
        poz = linie.find("shl");
        if (poz != string::npos)
        {
            ParsareShl(linie);
            continue;
        }
        poz = linie.find("shr");
        if (poz != string::npos)
        {
            ParsareShr(linie);
            continue;
        }
        poz = linie.find("call"); 
        if(poz != string::npos)
        {
            fout << " " << linie << "\n";
            continue;
        }
        fout << " " << linie << "\n";
    }
}

int main(int args, char *argv[])
{
    if (args == 1)
    {
        cout << "Utilizare: ./movfuscator file1.s file2.s ...\n";
        return 2;
    }
    for (int i = 1; i < args; i++)
    {
        string str_out(argv[i]);
        size_t poz = str_out.rfind("/");
        if (poz != string::npos)
        {
            string nume = str_out.substr(poz + 1, str_out.length() - poz);
            str_out = str_out.substr(0, poz+1) + "mov_" + nume;
        }
        else 
            str_out = "mov_" + str_out;
        
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
