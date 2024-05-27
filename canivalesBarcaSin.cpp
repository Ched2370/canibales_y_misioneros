#include <iostream>
#include <conio.h>
#include <locale.h>
using namespace std;

struct Orilla {
    int misioneros; // entero para misioneros
    int canibales;  // entero para canibales

    // Constructor para inicializar el numero de misioneros y canibales.
    Orilla(int m, int c) : misioneros(m), canibales(c) {}

    bool sePuede() const {

        return (misioneros == 0 || misioneros >= canibales) &&
               (misioneros <= 3 && canibales <= 3);
    }
};

struct Juego {
    Orilla ladoIzq;
    Orilla ladoDer;
    bool barco; // true indica izquierda, false indica derecha.

    Juego(int mL, int cL, int mR, int cR, bool posBarco)
        : ladoIzq(mL, cL), ladoDer(mR, cR), barco(posBarco) {}

    bool hasGanado() const {
        return ladoIzq.misioneros == 0 && ladoIzq.canibales == 0 &&
               ladoDer.misioneros == 3 && ladoDer.canibales == 3;
    }

    void mostrarOrillas() const {
        cout << "Orilla izquierda\n Misioneros: " << ladoIzq.misioneros << ", Canibales: " << ladoIzq.canibales << endl;
        cout << "Orilla derecha\n Misioneros: " << ladoDer.misioneros << ", Canibales: " << ladoDer.canibales << endl;
        cout << "\nEl barco esta en la orilla: " << (barco ? "IZQ" : "DER") << endl;
    }
};

bool zarpar(int m, int c, Juego &juego) {

    Orilla tempIzq = juego.ladoIzq;
    Orilla tempDer = juego.ladoDer;

    if (juego.barco) { // si barco en la izquierda
        if (tempIzq.misioneros >= m && tempIzq.canibales >= c) {
            // Restar de la orilla izquierda.
            tempIzq.misioneros -= m;
            tempIzq.canibales -= c;
            // Sumar a la orilla derecha.
            tempDer.misioneros += m;
            tempDer.canibales += c;
        } else {
            return false;
        }
    } else { 
        if (tempDer.misioneros >= m && tempDer.canibales >= c) {
            tempDer.misioneros -= m;
            tempDer.canibales -= c;
            tempIzq.misioneros += m;
            tempIzq.canibales += c;
        } else {
            return false;
        }
    }

    juego.ladoIzq = tempIzq;
    juego.ladoDer = tempDer;
    // Cambiamos la posicion del barco
    juego.barco = !juego.barco;
    return true;
}

int main() {
    setlocale(LC_ALL, "spanish");
    Juego juego(3, 3, 0, 0, true);
    juego.mostrarOrillas();

    bool juegoEnCurso = true;

    while (juegoEnCurso) {
        int misioneros, canibales;
        cout << "Ingrese el numero de misioneros y canibales que van a cruzar (maximo 2 personas)" << endl;
        cout << "misioneros: "; cin >> misioneros; 
        cout << "canibales: "; cin >> canibales;
        cout << endl;

        if (misioneros + canibales > 2 || misioneros < 0 || canibales < 0 || (misioneros + canibales) == 0) {
            cout << "\n***Movimiento no valido. Debe haber entre 1 y 2 personas en el bote.***" << endl;
            continue;
        }

        cout << "Movimiento: " << endl << misioneros << " misioneros y " << canibales << " canibales" << endl;

        if (zarpar(misioneros, canibales, juego)) {
            juego.mostrarOrillas();
            if (juego.hasGanado()) {
                cout << "Todos han cruzado el rio exitosamente!" << endl;
                break;
            }
            // Verificar despues de cada movimiento si el estado es valido
            if (!juego.ladoIzq.sePuede() || !juego.ladoDer.sePuede()) {
                cout << "\n***Has perdido, los canibales se comieron a los misioneros.***" << endl;
                juegoEnCurso = false; // Termina el bucle
            }
        } else {
            cout << "\n***Movimiento no valido***" << endl;
        }
    }

    getch();
    return 0;
}
