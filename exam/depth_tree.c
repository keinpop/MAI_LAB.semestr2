#include <stdio.h>

// Структура для представления узла дерева
typedef struct _node {
    int data;
    struct Node* firstChild; // указатель на первого потомка
    struct Node* nextSibling; // указатель на следующего сестринского узла
} Node;

// Рекурсивная функция для подсчета глубины дерева
int findDepth(Node* root) {
    if (root == NULL) {
        return 0; // если дерево пустое, глубина равна 0
    } else {
        int maxDepth = 0;

        // Рекурсивно обходим всех потомков и выбираем максимальную глубину
        Node* child = root->firstChild;
        while (child != NULL) {
            int depth = findDepth(child);
            if (depth > maxDepth) {
                maxDepth = depth;
            }
            child = child->nextSibling;
        }

        // Добавляем 1 к максимальной глубине узлов текущего уровня
        return maxDepth + 1;
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

    root->firstChild = child1;
    child1->nextSibling = child2;
    child2->nextSibling = child3;
    child3->nextSibling = NULL;

    child1->firstChild = NULL;
    child2->firstChild = NULL;
    child3->firstChild = NULL;

    // Вызываем функцию для подсчета глубины дерева
    int depth = findDepth(root);

    printf("Глубина дерева: %d\n", depth);

    // Освобождаем память, выделенную для узлов дерева
    free(child3);
    free(child2);
    free(child1);
    free(root);

    return 0;
}
