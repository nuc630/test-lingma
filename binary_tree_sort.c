/**
 * @file binary_tree_sort.c
 * @brief 二叉树排序实现
 * @description 使用二叉搜索树 (BST) 实现排序功能
 */

#include <stdio.h>
#include <stdlib.h>

/* 二叉树节点结构 */
typedef struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

/**
 * @brief 创建新的树节点
 * @param value 节点值
 * @return 新创建的节点指针
 */
TreeNode* createNode(int value) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (newNode == NULL) {
        fprintf(stderr, "内存分配失败\n");
        exit(1);
    }
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

/**
 * @brief 向二叉搜索树中插入节点
 * @param root 根节点指针的指针
 * @param value 要插入的值
 */
void insert(TreeNode** root, int value) {
    if (*root == NULL) {
        *root = createNode(value);
        return;
    }
    
    if (value < (*root)->data) {
        insert(&((*root)->left), value);
    } else {
        insert(&((*root)->right), value);
    }
}

/**
 * @brief 中序遍历二叉树（得到有序序列）
 * @param root 根节点
 * @param arr 存储结果的数组
 * @param index 当前数组索引的指针
 */
void inorderTraversal(TreeNode* root, int* arr, int* index) {
    if (root == NULL) {
        return;
    }
    
    /* 递归遍历左子树 */
    inorderTraversal(root->left, arr, index);
    
    /* 访问当前节点 */
    arr[(*index)++] = root->data;
    
    /* 递归遍历右子树 */
    inorderTraversal(root->right, arr, index);
}

/**
 * @brief 释放二叉树内存
 * @param root 根节点
 */
void freeTree(TreeNode* root) {
    if (root == NULL) {
        return;
    }
    
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

/**
 * @brief 二叉树排序主函数
 * @param arr 待排序数组
 * @param size 数组大小
 */
void binaryTreeSort(int* arr, int size) {
    if (size <= 1) {
        return;
    }
    
    TreeNode* root = NULL;
    int i;
    
    /* 构建二叉搜索树 */
    for (i = 0; i < size; i++) {
        insert(&root, arr[i]);
    }
    
    /* 中序遍历获取有序序列 */
    int* sortedArr = (int*)malloc(size * sizeof(int));
    if (sortedArr == NULL) {
        fprintf(stderr, "内存分配失败\n");
        freeTree(root);
        exit(1);
    }
    
    int index = 0;
    inorderTraversal(root, sortedArr, &index);
    
    /* 将排序结果复制回原数组 */
    for (i = 0; i < size; i++) {
        arr[i] = sortedArr[i];
    }
    
    free(sortedArr);
    freeTree(root);
}

/**
 * @brief 打印数组
 * @param arr 数组
 * @param size 数组大小
 */
void printArray(int* arr, int size) {
    int i;
    printf("[");
    for (i = 0; i < size; i++) {
        printf("%d", arr[i]);
        if (i < size - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

/* 测试示例 */
int main() {
    int arr1[] = {64, 34, 25, 12, 22, 11, 90};
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    
    printf("原始数组 1: ");
    printArray(arr1, size1);
    
    binaryTreeSort(arr1, size1);
    
    printf("排序后数组 1: ");
    printArray(arr1, size1);
    
    printf("\n");
    
    int arr2[] = {5, 2, 8, 1, 9, 3, 7, 4, 6};
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    
    printf("原始数组 2: ");
    printArray(arr2, size2);
    
    binaryTreeSort(arr2, size2);
    
    printf("排序后数组 2: ");
    printArray(arr2, size2);
    
    printf("\n");
    
    int arr3[] = {1};
    int size3 = 1;
    
    printf("原始数组 3 (单元素): ");
    printArray(arr3, size3);
    
    binaryTreeSort(arr3, size3);
    
    printf("排序后数组 3: ");
    printArray(arr3, size3);
    
    return 0;
}
