#include <conio.h>
#include <iostream>
#include <stdlib.h>

using namespace std;
template <class T> class AvlTree {
public:
  T data;
  AvlTree<T> *left;
  AvlTree<T> *right;
  AvlTree<T> *father;
  AvlTree(T info) {
    this->info = info;
    this->left = NULL;
    this->right = NULL;
  }

  AvlTree *createNode(T n, AvlTree *father) {

    AvlTree *newNode = new AvlTree();

    newNode->data = n;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->father = father;

    return newNode;
  }
  // Función para insertar nodos en el árbol

  void insert(AvlTree *&root, T n, AvlTree *padre) {

    if (root == NULL) { // Si el arbol está vacío

      AvlTree *newNode = createAvlTree(n);
      root = newNode;

    }

    else { // Si el arbol tiene un nodo o más

      T rootValue = root->data; // Obtener valor de la raíz

      if (n < rootValue) {

        insert(arbol->left, n, root);

      }

      else {

        insert(arbol->right, n, root);
      }
    }
  }
  // Función para mostrar el arbol

  void showTree(AvlTree *root, int cont = 0) {

    if (root == NULL) {

      return;

    }

    else {

      showTree(root->right, cont + 1);

      for (int i = 0; i < cont; i++) {

        cout << "    ";
      }

      cout << root->data << endl;

      showTree(arbol->left, cont + 1);
    }
  }
  // Función para buscar un data en el arbol

  bool search(AvlTree *root, T n) {

    if (root == NULL) {

      return false;

    }

    else if (root->data == n) {

      return true;

    }

    else if (n < root->data) {

      return search(root->left, n);

    }

    else {

      return search(root->right, n);
    }
  }
  // Funcion para recorrido en profundidad - PreOrden

  void preOrden(AvlTree *root) {

    if (root == NULL) {

      return;

    }

    else {

      cout << root->data << " - ";

      preOrden(root->left);

      preOrden(root->right);
    }
  }
  // Funcion para recorrido en profundidad - InOrden

  void inOrden(AvlTree *root) {

    if (root == NULL) {

      return;

    }

    else {

      inOrden(root->left);

      cout << root->data << " - ";

      inOrden(root->right);
    }
  }

  // Funcion para recorrido en profundidad - PostOrden

  void postOrden(AvlTree *root) {

    if (root == NULL) {

      return;

    }

    else {

      postOrden(root->left);

      postOrden(root->right);

      cout << root->data << " - ";
    }
  }

  // Funcion para eliminar el nodo encontrado
  void remove(AvlTree *root, T n) {

    if (root == NULL) {

      return;

    }

    else if (n < root->data) { // Si el valor es menor

      remove(root->left, n); // Busca por la leftuierda

    }

    else if (n > root->data) { // Si el valor es mayor

      remove(root->right, n); // Busca por la rightecha

    }

    else {

      removeNode(root);
    }
  }
  // Funcion para eliminar el nodo encontrado

  void removeNode(AvlTree *node) {

    if (node->left && node->right) {

      AvlTree *lower = min(node->right); // Primero te vas hacia la derecha

      node->data = lower->data;

      removeNode(lower);

    }

    else if (node->left) {

      remplace(node, node->left);

      destryNode(node);

    }

    else if (node->right) {

      remplace(node, node->right);

      destroyNode(node);

    }

    else { // No tiene hijos

      remplace(node, NULL);

      destroyNode(node);
    }
  }

  // Función para determinar el nodo más izquierdo posible

  AvlTree *min(AvlTree *root) {

    if (root == NULL) {

      return NULL;
    }

    if (root->left) { // Si tiene hijo izquierdo

      return min(root->left); // retorna el hijo izquierdo

    }

    else { // Si no tiene hijo izquierdo (significa que él es el más izquierdo)

      return root; // se retorna a sí mismo
    }
  }
  void remplace(AvlTree *root, AvlTree *newAvlTree) {

    if (root->father) {

      // root->padre hay que asignarle su nuevo hijo

      if (root->data == root->father->left->data) {

        root->father->left = newAvlTree;

      }

      else if (root->data == root->father->right->data) {

        root->father->right = newAvlTree;
      }
    }

    if (newAvlTree) {

      // Procedemos a asignarle su nuevo padre

      newAvlTree->father = root->father;
    }
  }
  // Función para destruir un nodo
  void detroyNode(AvlTree *nodo) {

    nodo->left = NULL;

    nodo->right = NULL;

    delete nodo;
  }
};
