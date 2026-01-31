# Movfuscator v1.0 - Proiect ASC 

## 📌 Descriere Proiect
Acest proiect implementează un translator de instrucțiuni x86 (sintaxă AT&T) bazat pe paradigma **OISC** (One Instruction Set Computer). Scopul principal este înlocuirea a **cât mai multe** instrucțiuni standard cu instrucțiunea `MOV`, utilizând tabele de lookup precalculate pentru simularea logicii hardware.

---

## 👥 Autori
Proiect realizat de:
* **Dumitru Robert Ionuț** (grupa 152)
* **Gheorghică Alexandru-Daniel** (grupa 152)
* **Moșanu Răzvan-Alexandru** (grupa 152)
* **Puică Andrei** (grupa 151)

---

## Structură și Implementare
Codul este organizat modular pentru a facilita mentenanța și dezvoltarea ulterioară:
* **`src/movinit.cpp`**: Gestionează inițializarea tabelelor de lookup în secțiunea `.data`.
* **`src/aritm.cpp`**: Simulează operațiile aritmetice prin indexare în tabele.
* **`src/jmp.cpp` & `src/cmp.cpp`**: Implementează gestiunea salturilor condiționate prin flag-uri virtuale (`flag_zero`, `flag_below`, `flag_less`).
* **`src/logic.cpp`**: Suport pentru operații logice (`and`, `or`, `xor`, `shl`, `shr`).
* **`src/push.cpp`**: Gestiunea stivei printr-o metodă hibridă.
* **`src/lea.cpp` & `src/mov.cpp`**: Calculul adreselor și transferul datelor.

---

## Compilare și Build
Proiectul utilizează CMake și necesită suport pentru arhitectura pe **32-bit** (`gcc-multilib`).

```bash
mkdir -p build
cd build
cmake ..
make -j$(nproc)
cd ..
```

---

## Utilizare
Executabilul `movfuscator` primește ca argument fișierul sursă `.s` și generează automat versiunea translatată:

```bash
./movfuscator fisier.s
```
*Programul va genera un fișier de ieșire prefixat, de exemplu: `mov_fisier.s`.*

**Asamblarea codului generat:**
Utilizarea flag-ului `-m32` este obligatorie pentru binarul final:
```bash
gcc -m32 mov_fisier.s -o binar_final
```

---

## Teste și Limitări (Probleme cunoscute)
Proiectul a fost testat cu succes pe exercițiile din **Laboratorul 0x02 și 0x04**. Există următoarele limitări:

* **Parserul**: Este sensibil la variațiile de formatare și poate întâmpina dificultăți în procesarea comentariilor intercalate.
* **Vectori**: Adresările de memorie complexe care utilizează indexare scalată, precum `(%ebx, %esi, 4)`, nu sunt procesate corect de logica actuală.
* **Acoperire**: Instrucțiunile x86 care nu au un modul de translatare dedicat sunt păstrate în forma lor originală în fișierul de ieșire.

---

## 📚 Referințe și Resurse
Pentru dezvoltarea acestui proiect au fost consultate următoarele resurse privind conceptul de Turing completeness și implementarea originală a Movfuscator-ului:

* **Turing Complete - Computerphile**: O explicație detaliată a conceptului de Turing completeness și a cerințelor minime pentru ca un sistem să poată executa orice calcul.
    * [Vizionează videoclipul](https://www.youtube.com/watch?v=RPQD7-AOjMI)
* **Christopher Domas - The Movfuscator**: Prezentarea originală a proiectului care demonstrează cum o singură instrucțiune (MOV) poate fi suficientă pentru a crea un sistem complet.
    * [Vizionează prezentarea](https://www.youtube.com/watch?v=hsNDLVUzYEs)
* **Christopher Domas - DerbyCon 5**: O prezentare aprofundată despre utilizarea Movfuscator ca tehnică de "anti-reverse engineering" prin eliminarea fluxului de control tradițional.
    * [Vizionează prezentarea de la DerbyCon](https://www.youtube.com/watch?v=wiFI5cqE49q)
* **Proiectul Movfuscator pe GitHub**: Codul sursă și documentația tehnică a compilatorului.
    * [Accesează repository-ul](https://github.com/xoreaxeaxeax/movfuscator)

 ---
 
*Proiect realizat pentru disciplina Arhitectura Sistemelor de Calcul.*
