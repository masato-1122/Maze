#include <stdlib.h>
#include <stdio.h>

#include "List.h"

#define LEN 256

int maze[LEN][LEN];

void readMaze(const char* filename, int* w, int* h, int maze[LEN][LEN]) {
	FILE* fp;
	int x, y;
	if (0 != fopen_s(&fp, filename, "r")) {
		fprintf(stderr, "指定された迷路の入力ファイルを開くことができませんでした．\n");
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
		fprintf(stderr, "指定された迷路の出力ファイルを開くことができませんでした．\n");
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

// シンプルなバージョン：なるべく右下へ行けるなら右下へ
int main0(int argc, const char** argv) {
	int w, h;
	int x, y;

	if (argc < 3) {
		fprintf(stderr, "迷路の入出力ファイル名を指定してください．\n");
		exit(-1);
	}

	// 迷路読込
	readMaze(argv[1], &w, &h, maze);

	// maze[1][1] から maze[2*h-1][2*w-1] までのルートを探す
	x = 1;	//座標の初期化
	y = 1;
	int z = 0;

	while (x != 2 * w - 1 || y != 2 * h - 1) {
		//まだ通過していない通路を探索
		if (maze[y][x + 1] == 0) {		// 右にまだ行ってない？
			maze[y][x] = 1000;
			x = x + 1;
			z = 10;
		}
		else if (maze[y + 1][x] == 0) {	// 下にまだ行ってない？
			maze[y][x] = 1000;
			y = y + 1;
			z = 11;
		}
		else if (maze[y][x - 1] == 0) {	// 左にまだ行ってない？
			maze[y][x] = 1000;
			x = x - 1;
			z = 12;
		}
		else if (maze[y - 1][x] == 0) {	// 上にまだ行ってない？
			maze[y][x] = 1000;
			y = y - 1;
			z = 13;
		}

		//直前の行動から戻っていく
		else if (z == 10) { //右に行ったが、一度通過しているため、戻る
			maze[y][x] = 1;
			x = x - 1;
			z = 0;
		}
		else if (z == 11) {//下に行ったが、一度通過しているため、戻る
			maze[y][x] = 1;
			y = y - 1;
			z = 0;
		}
		else if (z == 12) {//左に行ったが、一度通過しているため、戻る
			maze[y][x] = 1;
			x = x + 1;
			z = 0;
		}
		else if (z == 13) {//上に行ったが、一度通過しているため、戻る
			maze[y][x] = 1;
			y = y + 1;
			z = 0;
		}


		else if (maze[y][x + 1] == 1000) { // 行き止まりなので右に引き返す
			maze[y][x] = 1;
			x = x + 1;
		}
		else if (maze[y + 1][x] == 1000) { // 行き止まりなので下に引き返す
			maze[y][x] = 1;
			y = y + 1;
		}
		else if (maze[y][x - 1] == 1000) { // 行き止まりなので左に引き返す
			maze[y][x] = 1;
			x = x - 1;
		}
		else if (maze[y - 1][x] == 1000) { // 行き止まりなので上に引き返す
			maze[y][x] = 1;
			y = y - 1;
		}

		else { // ここまできた時点でバグなので，迷路を書き出して終了
			writeMaze(argv[2], w, h, maze);
			return -1;
		}
		//return 0;
	}
	maze[2 * h - 1][2 * w - 1] = 1000; // ゴールs

	// 迷路書出
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
			printf("%sの迷路をテスト\n", test[i][1]);
			if (main0(3, test[i]) == 0) {
				printf("o：ゴールまでの経路が見つかりました．しかし，ゴミはあるかもしれません．\n");
			}
			else {
				printf("x：ゴールまでの経路が見つかりませんでした．\n");
			}
		}
		printf("\n【ゴミがあるかないかの確認は，出力された迷路をUIMazeで表示して確認してください．】\n\n");
		printf("HIT ENTER KEY");
		while (getchar() != '\n');
		return 0;
	}
	else {
		return main0(argc, argv);
	}
}