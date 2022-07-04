#include <stdlib.h>
#include <stdio.h>

#include "List.h"

#define LEN 256

int maze[LEN][LEN];

void readMaze(const char* filename, int* w, int* h, int maze[LEN][LEN]) {
	FILE* fp;
	int x, y;
	if (0 != fopen_s(&fp, filename, "r")) {
		fprintf(stderr, "�w�肳�ꂽ���H�̓��̓t�@�C�����J�����Ƃ��ł��܂���ł����D\n");
		exit(-1);
	}

	fscanf_s(fp, "%d,%d\n", w, h);
	for (y = 0; y < 2 * *h + 1; y++) {
		for (x = 0; x < 2 * *w + 1; x++) {
			fscanf_s(fp, "%d%*[^-0-9]", &(maze[y][x]));
		}
	}
	fclose(fp);
}

void writeMaze(const char* filename, int w, int h, int maze[LEN][LEN]) {
	FILE* fp;
	int x, y;
	if (0 != fopen_s(&fp, filename, "w")) {
		fprintf(stderr, "�w�肳�ꂽ���H�̏o�̓t�@�C�����J�����Ƃ��ł��܂���ł����D\n");
		exit(-1);
	}

	fprintf_s(fp, "%d,%d\n", w, h);
	for (y = 0; y < 2 * h + 1; y++) {
		for (x = 0; x < 2 * w + 1; x++) {
			fprintf_s(fp, "%d", maze[y][x]);
			if (x < 2 * w) {
				fprintf_s(fp, ",");
			}
			else {
				fprintf_s(fp, "\n");
			}
		}
	}
	fclose(fp);
}

// �V���v���ȃo�[�W�����F�Ȃ�ׂ��E���֍s����Ȃ�E����
int main0(int argc, const char** argv) {
	int w, h;
	int x, y;

	if (argc < 3) {
		fprintf(stderr, "���H�̓��o�̓t�@�C�������w�肵�Ă��������D\n");
		exit(-1);
	}

	// ���H�Ǎ�
	readMaze(argv[1], &w, &h, maze);

	// maze[1][1] ���� maze[2*h-1][2*w-1] �܂ł̃��[�g��T��
	x = 1;	//���W�̏�����
	y = 1;
	int z = 0;

	while (x != 2 * w - 1 || y != 2 * h - 1) {
		//�܂��ʉ߂��Ă��Ȃ��ʘH��T��
		if (maze[y][x + 1] == 0) {		// �E�ɂ܂��s���ĂȂ��H
			maze[y][x] = 1000;
			x = x + 1;
			z = 10;
		}
		else if (maze[y + 1][x] == 0) {	// ���ɂ܂��s���ĂȂ��H
			maze[y][x] = 1000;
			y = y + 1;
			z = 11;
		}
		else if (maze[y][x - 1] == 0) {	// ���ɂ܂��s���ĂȂ��H
			maze[y][x] = 1000;
			x = x - 1;
			z = 12;
		}
		else if (maze[y - 1][x] == 0) {	// ��ɂ܂��s���ĂȂ��H
			maze[y][x] = 1000;
			y = y - 1;
			z = 13;
		}

		//���O�̍s������߂��Ă���
		else if (z == 10) { //�E�ɍs�������A��x�ʉ߂��Ă��邽�߁A�߂�
			maze[y][x] = 1;
			x = x - 1;
			z = 0;
		}
		else if (z == 11) {//���ɍs�������A��x�ʉ߂��Ă��邽�߁A�߂�
			maze[y][x] = 1;
			y = y - 1;
			z = 0;
		}
		else if (z == 12) {//���ɍs�������A��x�ʉ߂��Ă��邽�߁A�߂�
			maze[y][x] = 1;
			x = x + 1;
			z = 0;
		}
		else if (z == 13) {//��ɍs�������A��x�ʉ߂��Ă��邽�߁A�߂�
			maze[y][x] = 1;
			y = y + 1;
			z = 0;
		}


		else if (maze[y][x + 1] == 1000) { // �s���~�܂�Ȃ̂ŉE�Ɉ����Ԃ�
			maze[y][x] = 1;
			x = x + 1;
		}
		else if (maze[y + 1][x] == 1000) { // �s���~�܂�Ȃ̂ŉ��Ɉ����Ԃ�
			maze[y][x] = 1;
			y = y + 1;
		}
		else if (maze[y][x - 1] == 1000) { // �s���~�܂�Ȃ̂ō��Ɉ����Ԃ�
			maze[y][x] = 1;
			x = x - 1;
		}
		else if (maze[y - 1][x] == 1000) { // �s���~�܂�Ȃ̂ŏ�Ɉ����Ԃ�
			maze[y][x] = 1;
			y = y - 1;
		}

		else { // �����܂ł������_�Ńo�O�Ȃ̂ŁC���H�������o���ďI��
			writeMaze(argv[2], w, h, maze);
			return -1;
		}
		//return 0;
	}
	maze[2 * h - 1][2 * w - 1] = 1000; // �S�[��s

	// ���H���o
	writeMaze(argv[2], w, h, maze);
	return 0;
}

int main(int argc, const char** argv) {
	int i;
	const char* (test[])[3] = {
		{ "dummy", "mazeSimpleA1.csv", "mazeSimpleA1-out.csv" },
		{ "dummy", "mazeSimpleA2.csv", "mazeSimpleA2-out.csv" },
		{ "dummy", "mazeSimpleB1.csv", "mazeSimpleB1-out.csv" },
		{ "dummy", "mazeSimpleB2.csv", "mazeSimpleB2-out.csv" },
		{ "dummy", "mazeSimpleC1.csv", "mazeSimpleC1-out.csv" },
		{ "dummy", "mazeSimpleC2.csv", "mazeSimpleC2-out.csv" },
		{ "dummy", "maze8060A.csv", "maze8060A-out.csv" },
		{ "dummy", "maze8060B.csv", "maze8060B-out.csv" },
		{ "dummy", "maze8060C.csv", "maze8060C-out.csv" },
		{ "dummy", "maze8060D.csv", "maze8060D-out.csv" },
		{ "dummy", "maze8060E.csv", "maze8060E-out.csv" },
		{ "dummy", "maze8060F.csv", "maze8060F-out.csv" },
	};

	if (argc == 1) {
		for (i = 0; i < sizeof(test) / sizeof(char* [3]); i++) {
			printf("%s�̖��H���e�X�g\n", test[i][1]);
			if (main0(3, test[i]) == 0) {
				printf("o�F�S�[���܂ł̌o�H��������܂����D�������C�S�~�͂��邩������܂���D\n");
			}
			else {
				printf("x�F�S�[���܂ł̌o�H��������܂���ł����D\n");
			}
		}
		printf("\n�y�S�~�����邩�Ȃ����̊m�F�́C�o�͂��ꂽ���H��UIMaze�ŕ\�����Ċm�F���Ă��������D�z\n\n");
		printf("HIT ENTER KEY");
		while (getchar() != '\n');
		return 0;
	}
	else {
		return main0(argc, argv);
	}
}