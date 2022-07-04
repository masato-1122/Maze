#include <stdlib.h>
#include "List.h"

// ���X�g�̏�����
void initList(List* list) {
	list->top = NULL;
	list->bottom = NULL;
}

// �Z���̊m��
Cell* createCell() {
	return (Cell*)malloc(sizeof(Cell));
}

// �Z���̊J��
void disposeCell(Cell* c) {
	free(c);
}

// ���X�g�̐擪�Ƀf�[�^��ǉ�
void addTop(List* list, Cell* c) {
	c->prev = NULL;
	c->next = list->top;
	if (list->top == NULL) {
		list->bottom = c;
	}
	else {
		list->top->prev = c;
	}
	list->top = c;
}

// ���X�g�̖����Ƀf�[�^��ǉ�
void addBottom(List* list, Cell* c) {
	c->prev = list->bottom;
	c->next = NULL;
	if (list->bottom == NULL) {
		list->top = c;
	}
	else {
		list->bottom->next = c;
	}
	list->bottom = c;
}

// �\�[�g�ς݂̃��X�g�Ƀf�[�^��ǉ�
void addSorted(List* list, Cell* c) {
	if (list->top == NULL || c->value <= list->top->value) {
		addTop(list, c);
	}
	else if (list->bottom->value < c->value) {
		addBottom(list, c);
	}
	else if (c->value - list->top->value <= list->bottom->value - c->value) {
		Cell* p;
		for (p = list->top; p->value < c->value; p = p->next);
		p->prev->next = c;
		c->prev = p->prev;
		c->next = p;
		p->prev = c;
	}
	else {
		Cell* p;
		for (p = list->bottom; c->value <= p->value; p = p->prev);
		p->next->prev = c;
		c->next = p->next;
		c->prev = p;
		p->next = c;
	}
}

// ���X�g�̐擪����f�[�^�����o��
Cell* takeTop(List* list) {
	if (list->top == NULL) {
		return NULL;
	}
	else {
		Cell* c = list->top;
		list->top = c->next;
		if (c->next == NULL) {
			list->bottom = NULL;
		}
		else {
			c->next->prev = NULL;
		}
		return c;
	}
}

// ���X�g�̖�������f�[�^�����o��
Cell* takeBottom(List* list) {
	if (list->bottom == NULL) {
		return NULL;
	}
	else {
		Cell* c = list->bottom;
		list->bottom = c->prev;
		if (c->prev == NULL) {
			list->top = NULL;
		}
		else {
			c->prev->next = NULL;
		}
		return c;
	}
}

