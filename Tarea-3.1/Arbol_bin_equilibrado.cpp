#include <iostream>
#include <fstream>
using namespace std;

struct Nodo {
    int dato;
    Nodo* izquierda;
    Nodo* derecha;
    int altura;
};

int altura(Nodo* nodo) {
    if (nodo == NULL) {
        return 0;
    }
    return nodo->altura;
}

int maximo(int a, int b) {
    return (a > b) ? a : b;
}

Nodo* nuevoNodo(int dato) {
    Nodo* nodo = new Nodo();
    nodo->dato = dato;
    nodo->izquierda = NULL;
    nodo->derecha = NULL;
    nodo->altura = 1;
    return nodo;
}

Nodo* rotacionDerecha(Nodo* y) {
    Nodo* x = y->izquierda;
    Nodo* T2 = x->derecha;

    x->derecha = y;
    y->izquierda = T2;

    y->altura = maximo(altura(y->izquierda), altura(y->derecha)) + 1;
    x->altura = maximo(altura(x->izquierda), altura(x->derecha)) + 1;

    return x;
}

Nodo* rotacionIzquierda(Nodo* x) {
    Nodo* y = x->derecha;
    Nodo* T2 = y->izquierda;

    y->izquierda = x;
    x->derecha = T2;

    x->altura = maximo(altura(x->izquierda), altura(x->derecha)) + 1;
    y->altura = maximo(altura(y->izquierda), altura(y->derecha)) + 1;

    return y;
}

int balance(Nodo* nodo) {
    if (nodo == NULL) {
        return 0;
    }
    return altura(nodo->izquierda) - altura(nodo->derecha);
}

Nodo* insertar(Nodo* nodo, int dato) {
    if (nodo == NULL) {
        return nuevoNodo(dato);
    }

    if (dato < nodo->dato) {
        nodo->izquierda = insertar(nodo->izquierda, dato);
    } else if (dato > nodo->dato) {
        nodo->derecha = insertar(nodo->derecha, dato);
    } else {
        return nodo;
    }

    nodo->altura = 1 + maximo(altura(nodo->izquierda), altura(nodo->derecha));

    int factorBalance = balance(nodo);

    if (factorBalance > 1 && dato < nodo->izquierda->dato) {
        return rotacionDerecha(nodo);
    }
    if (factorBalance < -1 && dato > nodo->derecha->dato) {
        return rotacionIzquierda(nodo);
    }
    if (factorBalance > 1 && dato > nodo->izquierda->dato) {
        nodo->izquierda = rotacionIzquierda(nodo->izquierda);
        return rotacionDerecha(nodo);
    }
    if (factorBalance < -1 && dato < nodo->derecha->dato) {
        nodo->derecha = rotacionDerecha(nodo->derecha);
        return rotacionIzquierda(nodo);
    }

    return nodo;
}

void preOrden(Nodo* nodo) {
    if (nodo != NULL) {
        cout << nodo->dato << " ";
        preOrden(nodo->izquierda);
        preOrden(nodo->derecha);
    }
}

void graficarArbol(Nodo* nodo, ofstream& archivoDot) {
    if (nodo != NULL) {
        if (nodo->izquierda != NULL) {
            archivoDot << nodo->dato << " -> " << nodo->izquierda->dato << ";" << endl;
            graficarArbol(nodo->izquierda, archivoDot);
        }
        if (nodo->derecha != NULL) {
            archivoDot << nodo->dato << " -> " << nodo->derecha->dato << ";" << endl;
            graficarArbol(nodo->derecha, archivoDot);
        }
    }
}

void generarImagenDot(Nodo* raiz) {
    ofstream archivoDot("arbol.dot");
    archivoDot << "digraph Arbol {" << endl;
    graficarArbol(raiz, archivoDot);
    archivoDot << "}" << endl;
    archivoDot.close();

    system("dot -Tpng arbol.dot -o arbol.png");
}

int main() {
    Nodo* raiz = NULL;

    raiz = insertar(raiz, 10);
    raiz = insertar(raiz, 20);
    raiz = insertar(raiz, 30);
    raiz = insertar(raiz, 40);
    raiz = insertar(raiz, 50);
    raiz = insertar(raiz, 25);

    cout << "Recorrido preorden del árbol equilibrado:" << endl;
    preOrden(raiz);
    
    generarImagenDot(raiz);

    cout << "Recorrido preorden del árbol equilibrado:" << endl;
    preOrden(raiz);

    return 0;
}