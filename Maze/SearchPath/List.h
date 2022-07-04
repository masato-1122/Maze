typedef struct cell {
	int x, y, value, id;
	struct cell* prev;
	struct cell* next;
} Cell;

typedef struct {
	Cell *top;
	Cell *bottom;
} List;

// ���X�g�̏�����
void initList(List* list);

// �Z���̊m��
Cell* createCell();

// �Z���̊J��
void disposeCell(Cell* c);

// ���X�g�̐擪�Ƀf�[�^��ǉ�
void addTop(List* list, Cell* c);

// ���X�g�̖����Ƀf�[�^��ǉ�
void addBottom(List* list, Cell* c);

// �\�[�g�ς݂̃��X�g�Ƀf�[�^��ǉ�
void addSorted(List* list, Cell* c);

// ���X�g�̐擪����f�[�^�����o��
Cell* takeTop(List* list);

// ���X�g�̖�������f�[�^�����o��
Cell* takeBottom(List* list);