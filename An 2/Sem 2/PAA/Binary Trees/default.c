#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Definim strctura de tip arbore
typedef struct tree_node {
    int value;  // valoarea de tip int
    struct tree_node *left;  // fiul din partea stanga
    struct tree_node *right;  // fiul din partea dreapta
} tree_node;


// Definim functia pentru a aloca un nod
tree_node* create_tree_node(int value) {
    // value: int - valoarea pe care o va avea nodul
    // return: tree_node* - returneaza pointer la nod

    tree_node* node = (tree_node*)malloc(sizeof(tree_node) * 1);  // alocam memorie pentru nod

    // verificam daca alocarea a avut loc cu succes
    if (node != NULL) {
        node->value = value;  // atribuim valoarea trimisa prin parametru

        // by default, fii din stanga si dreapta vor fi pe NULL, pentru ca noi alocam doar pentru un SINGUR nod, ci anume, nodul parinte
        node->left = NULL; 
        node->right = NULL;
    }
    
    return node;
}

// Definim functia pentru a parcurge in preordine (RSD)
void print_preorder(tree_node* root) {
    // root: tree_node* - radacina de la care incepem printarea
    // return: void

    // daca radacina e nula, inseamna ca nodul nu exista, deci iesim din recursivitate
    if (root == NULL) {
        return;
    }

    // altfel, radacina nu e nula, putem sa o printam

    (void)printf("%d ", root->value);

    // din moment ce nu e nula, noi cum vrem sa parcurgem arborele?
    // acum suntem la RADACINA, deci, vom merge mai intai in partea stanga

    print_preorder(root->left);

    // apoi, dupa ce revenim din prima recursivitate, intram in a doua
    // si vom merge in nodul din dreapta

    print_preorder(root->right);
}


// Definim functia de a insera un nod in arborele binar
void insert_in_tree(tree_node** root, tree_node* node) {
    // root: tree_node** - radacina la care o sa inseram
    // node: tree_node* - nodul pe care o sa il inseram
    // return: void

    // avem pointer la pointer deoarece dorim sa modificam adresa radacinii prin interiorul functiei

    // verificam daca radacina e nula
    if (*root == NULL) {

        // daca e nula, atribuim nodul trimis ca parametru
        *root = node;
    }

    // daca nodul trimis ca parametru exista deja in arbore, nu facem nimic
    if ((*root)->value == node->value) {
        return;
    }

    // daca valoarea parametrului este mai mica decat valorea radacinii, inseram in fiul din stanga
    if ((*root)->value > node->value) {
        insert_in_tree(&(*root)->left, node);
    } else {
        // daca valoarea parametrului este mai mare decat valorea radacinii, inseram in fiul din dreapta
        insert_in_tree(&(*root)->right, node);
    }
}

// Definim o functie de cautare a unei valori in arbore
bool find_value_in_tree(tree_node* root, int value) {
    // node: tree_node* - radacina
    // return: bool - daca am gasit sau nu valoarea

    // daca radacina e nula, returnam fals
    if (root == NULL) {
        return false;
    }

    // daca valoarea radacinii e egala cu valoarea trimisa ca parametru inseamna ca am gasit valorea respectiva in arbore
    if (root->value == value) {
        return true;
    }

    // daca valorea radacinii e mai mare decat valoarea trimisa ca parametru, o cautam in arborele din stanga
    if (root->value > value) {
        return find_value_in_tree(root->left, value);
    } else { 
        // daca valorea radacinii e mai mica decat valoarea trimisa ca parametru, o cautam in arborele din dreapta
        return find_value_in_tree(root->right, value);
    }
}

int main(void) {
    tree_node *root = NULL;

    insert_in_tree(&root, create_tree_node(5));
    insert_in_tree(&root, create_tree_node(2));
    insert_in_tree(&root, create_tree_node(3));
    insert_in_tree(&root, create_tree_node(7));
    insert_in_tree(&root, create_tree_node(10));
    insert_in_tree(&root, create_tree_node(9));
    insert_in_tree(&root, create_tree_node(11));
    insert_in_tree(&root, create_tree_node(6));

    print_preorder(root);
    printf("\n");

    printf("%d ", find_value_in_tree(root, 5));


    return 0;
}