#include <stdio.h>
#include <stdlib.h>

// Структура для представления узла дерева
typedef struct Node {
    int data;
    struct Node* firstChild; // указатель на первого потомка
    struct Node* nextSibling; // указатель на следующего сестринского узла
} Node;

// Рекурсивная функция для подсчета листьев в дереве
int countLeaves(Node* root) {
    if (root == NULL) {
        return 0; // если дерево пустое, количество листьев равно 0
    }
    
    if (root->firstChild == NULL) {
        // Узел является листом, возвращаем 1
        return 1;
    } else {
        int leafCount = 0;
        
        // Рекурсивно обходим всех потомков и суммируем количество листьев
        Node* child = root->firstChild;
        while (child != NULL) {
            leafCount += countLeaves(child);
            child = child->nextSibling;
        }
        
        return leafCount;
    }
}

int main() {
    // Создаем дерево общего вида для тестирования
    Node* root = (Node*)malloc(sizeof(Node));
    root->data = 1;

    Node* child1 = (Node*)malloc(sizeof(Node));
    child1->data = 2;

    Node* child2 = (Node*)malloc(sizeof(Node));
    child2->data = 3;

    Node* child3 = (Node*)malloc(sizeof(Node));
    child3->data = 4;
    
    Node* child4 = (Node*)malloc(sizeof(Node));
    child3->data = 5;

    root->firstChild = child1;
    child1->nextSibling = child2;
    child2->nextSibling = child3;
    child3->nextSibling = child4;

    child1->firstChild = NULL;
    child2->firstChild = NULL;
    child3->firstChild = NULL;

    // Вызываем функцию для подсчета листьев в дереве
    int leafCount = countLeaves(root);

    printf("Количество листьев в дереве: %d\n", leafCount);

    // Освобождаем память, выделенную для узлов дерева
    free(child3);
    free(child2);
    free(child1);
    free(root);

    return 0;
}
