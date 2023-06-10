#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define GENERAL_DATA_SIZE 128
#define STUDENTS_LENGTH 50

typedef struct student {
    char name[GENERAL_DATA_SIZE];
    char email[GENERAL_DATA_SIZE];
} student;

typedef struct tree_node {
    uint64_t course_id;
    char title[GENERAL_DATA_SIZE];
    char teacher_name[GENERAL_DATA_SIZE];
    student* students;
    struct tree_node* left;
    struct tree_node* right;
} tree_node;

// Definim functia pentru a aloca un nod
tree_node* creazaCurs(uint32_t course_id,
                            char* course_title,
                            char* teacher_name) {
    // value: int - valoarea pe care o va avea nodul
    // return: tree_node* - returneaza pointer la nod

    tree_node* node = (tree_node*)malloc(sizeof(tree_node) * 1);  // alocam memorie pentru nod

    // verificam daca alocarea a avut loc cu succes
    if (node != NULL) {
        // atribuim valorile legate de curs
        node->course_id = course_id;
        strcpy(node->title, course_title);
        strcpy(node->teacher_name, teacher_name);
        node->students = (student*)malloc(sizeof(student) * STUDENTS_LENGTH);

        // by default, fii din stanga si dreapta vor fi pe NULL, pentru ca noi alocam doar pentru un SINGUR nod, ci anume, nodul parinte
        node->left = NULL; 
        node->right = NULL;
    }
    
    return node;
}

// Definim functia de a insera un nod in arborele binar
void adaugaCurs(tree_node** root, tree_node* node) {
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
    if ((*root)->course_id == node->course_id) {
        return;
    }

    // daca valoarea parametrului este mai mica decat valorea radacinii, inseram in fiul din stanga
    if ((*root)->course_id > node->course_id) {
        adaugaCurs(&(*root)->left, node);
    } else {
        // daca valoarea parametrului este mai mare decat valorea radacinii, inseram in fiul din dreapta
        adaugaCurs(&(*root)->right, node);
    }
}

// Definim functia pentru a parcurge in inordine
void print_inorder(tree_node* root) {
    // root: tree_node* - radacina de la care incepem printarea
    // return: void

    // daca radacina e nula, inseamna ca nodul nu exista, deci iesim din recursivitate
    if (root == NULL) {
        return;
    }

    // din moment ce nu e nula, noi cum vrem sa parcurgem arborele?
    // acum suntem la RADACINA, deci, vom merge mai intai in partea stanga

    print_inorder(root->left);

    (void)printf("%d \n", root->course_id);
    (void)printf("%s \n", root->title);
    (void)printf("%s \n", root->teacher_name);
    (void)printf("\n");
    

    // apoi, dupa ce revenim din prima recursivitate, intram in a doua
    // si vom merge in nodul din dreapta

    print_inorder(root->right);
}


void listareCursuriSortateDupaId(tree_node* root) {
    print_inorder(root);
}


int main(void) {
    tree_node *root = NULL;

    adaugaCurs(&root, creazaCurs(5, "Curs 1", "Name 1"));
    adaugaCurs(&root, creazaCurs(2, "Curs 2", "Name 2"));
    adaugaCurs(&root, creazaCurs(3, "Curs 3", "Name 3"));
    adaugaCurs(&root, creazaCurs(7, "Curs 4", "Name 4"));
    adaugaCurs(&root, creazaCurs(10, "Curs 5", "Name 5"));
    adaugaCurs(&root, creazaCurs(9, "Curs 6", "Name 6"));
    adaugaCurs(&root, creazaCurs(11, "Curs 7", "Name 7"));
    adaugaCurs(&root, creazaCurs(6, "Curs 8", "Name 8"));

    listareCursuriSortateDupaId(root);

    return 0;
}