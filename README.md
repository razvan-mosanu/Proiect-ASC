# Movfuscator v1.0 - Proiect ASC (FMI Edition)

## 📌 Descriere Proiect
Acest proiect implementează un translator de instrucțiuni x86 (sintaxă AT&T) bazat pe paradigma **OISC** (One Instruction Set Computer). Scopul principal este înlocuirea a **cât mai multe** instrucțiuni standard cu instrucțiunea `MOV`, utilizând tabele de lookup precalculate pentru simularea logicii hardware.

**Notă:** O implementare completă `MOV-only` pentru întreg setul x86 ar reprezenta un proiect de complexitate ridicată. Proiectul actual acoperă setul esențial de instrucțiuni necesar laboratoarelor de ASC.

---

## 👥 Autori
Proiect realizat de:
* **Dumitru Robert Ionuț** (grupa 152)
* **Gheorghică Alexandru-Daniel** (grupa 152)
* **Moșanu Răzvan-Alexandru** (grupa 152)
* **Puică Andrei** (grupa 151)

---

## 🏗️ Structură și Implementare
Codul este organizat modular pentru a facilita mentenanța și dezvoltarea ulterioară:
* **`src/movinit.cpp`**: Gestionează inițializarea tabelelor de lookup în secțiunea `.data`.
* **`src/aritm.cpp`**: Simulează operațiile aritmetice prin indexare în tabele.
* **`src/jmp.cpp` & `src/cmp.cpp`**: Implementează gestiunea salturilor condiționate prin flag-uri virtuale (`flag_zero`, `flag_below`, `flag_less`).
* **`src/logic.cpp`**: Suport pentru operații logice (`and`, `or`, `xor`, `shl`, `shr`).
* **`src/push.cpp`**: Gestiunea stivei printr-o metodă hibridă.
* **`src/lea.cpp` & `src/mov.cpp`**: Calculul adreselor și transferul datelor.

---

## 🛠️ Compilare și Build
Proiectul utilizează CMake și necesită suport pentru arhitectura pe **32-bit** (`gcc-multilib`).

```bash
mkdir -p build
cd build
cmake ..
make -j$(nproc)
cd ..
```

---

## 📋 Utilizare
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

## 🧪 Teste și Limitări (Probleme cunoscute)
Proiectul a fost testat cu succes pe exercițiile din **Laboratorul 0x02 și 0x04**. Există următoarele limitări:

* **Parserul**: Este sensibil la variațiile de formatare și poate întâmpina dificultăți în procesarea comentariilor intercalate.
* **Vectori**: Adresările de memorie complexe care utilizează indexare scalată (SIB), precum `(%ebx, %esi, 4)`, nu sunt procesate corect de logica actuală.
* **Acoperire**: Instrucțiunile x86 care nu au un modul de translatare dedicat sunt păstrate în forma lor originală în fișierul de ieșire.

---

## 📈 Direcții de dezvoltare
* Creșterea robusteții parserului de text pentru prelucrarea fișierelor sursă.
* Implementarea suportului complet pentru adresări indirecte și lucrul cu vectori.
* Migrarea către un sistem de stivă complet implementat prin instrucțiuni `MOV`.

---
*Proiect realizat pentru disciplina Arhitectura Sistemelor de Calcul.*