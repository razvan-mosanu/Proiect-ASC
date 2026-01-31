# 🚀 Movfuscator v1.0 - Proiect ASC (FMI Edition)

## 📌 Descriere Proiect
Acest proiect implementează un translator de instrucțiuni x86 (sintaxă AT&T) bazat pe paradigma **OISC** (One Instruction Set Computer). Scopul principal este înlocuirea a **cât mai multe** instrucțiuni standard cu instrucțiunea `MOV`, utilizând tabele de lookup precalculate pentru simularea logicii hardware.

**Notă:** O implementare completă `MOV-only` pentru întreg setul x86 ar reprezenta un proiect de complexitate ridicată. Proiectul actual acoperă setul esențial de instrucțiuni necesar laboratoarelor de ASC.

---

## 🏗️ Structură și Implementare
Codul este organizat modular pentru a facilita mentenanța și dezvoltarea ulterioară:
* **`src/movinit.cpp`**: Gestionează inițializarea tabelelor de lookup în secțiunea `.data` (pentru operații de tip add, sub, mul, div, xor etc.).
* **`src/aritm.cpp`**: Simulează operațiile aritmetice prin indexare în tabelele precalculate.
* **`src/jmp.cpp` & `src/cmp.cpp`**: Implementează gestiunea salturilor condiționate prin utilizarea flag-urilor virtuale (`flag_zero`, `flag_below`, `flag_less`).
* **`src/logic.cpp`**: Oferă suport pentru operații logice pe biți precum `and`, `or`, `xor`, `shl` și `shr`.
* **`src/push.cpp`**: Gestionează operațiunile cu stiva printr-o metodă hibridă ce utilizează registrul `%eax`.
* **`src/lea.cpp` & `src/mov.cpp`**: Se ocupă de calculul adreselor și transferul efectiv al datelor.

---

## 🛠️ Compilare și Build
Proiectul utilizează CMake și necesită suport pentru arhitectura pe **32-bit** (`gcc-multilib`) pentru a asigura compatibilitatea tipurilor de date.

```bash
mkdir -p build
cd build
cmake ..
make -j$(nproc)
```

---

## 📋 Utilizare
Executabilul `movfuscator` primește ca argument fișierul sursă `.s` și generează automat versiunea translatată:

```bash
./movfuscator fisier.s
```
*Programul va genera un fișier de ieșire prefixat, de exemplu: `mov_fisier.s`.*

**Asamblarea codului generat:**
Pentru a obține binarul final, utilizarea flag-ului `-m32` este obligatorie:
```bash
gcc -m32 mov_fisier.s -o binar_final
```

---

## 🧪 Teste și Limitări (Probleme cunoscute)
Proiectul a fost testat cu succes pe exercițiile din **Laboratorul 0x02 și 0x04**. Totuși, există următoarele limitări:

* **Parserul**: Este sensibil la variațiile de formatare (spații, tab-uri) și poate întâmpina dificultăți în procesarea comentariilor intercalate.
* **Vectori**: Adresările de memorie complexe care utilizează indexare scalată (SIB), precum `(%ebx, %esi, 4)`, nu sunt procesate corect de logica actuală.
* **Acoperire**: Instrucțiunile x86 care nu au un modul de translatare dedicat sunt păstrate în forma lor originală în fișierul de ieșire.

---

## 📈 Direcții de dezvoltare
* Creșterea robusteții parserului de text pentru prelucrarea fișierelor sursă.
* Implementarea suportului complet pentru adresări indirecte și lucrul cu vectori.
* Migrarea către un sistem de stivă complet implementat prin instrucțiuni `MOV`.

---
*Proiect realizat pentru disciplina Arhitectura Sistemelor de Calcul.*