#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct _DisjointSet
{
	int size_maze;
	int *ptr_arr;
}DisjointSets;

void init(DisjointSets*,DisjointSets* , int);

void Union(DisjointSets*, int, int);

int find(DisjointSets *, int);

void createMaze(DisjointSets *, DisjointSets *, int);

void printMaze(DisjointSets *, int);

void freeMaze(DisjointSets *, DisjointSets *);

int main(int argc, char* argv[]){

	int num, i;
	FILE *fi = fopen(argv[1], "r");
	DisjointSets *sets, *maze_print;
	fscanf(fi, "%d", &num);
	sets = (DisjointSets*)malloc(sizeof(DisjointSets));
	maze_print = (DisjointSets*)malloc(sizeof(DisjointSets));
	init(sets, maze_print, num);
	createMaze(sets, maze_print, num);
	printMaze(maze_print, num);
	freeMaze(sets, maze_print);

	return 0;
}

void init(DisjointSets *sets, DisjointSets *maze_print, int num){

	sets->size_maze = num * num;

	sets->ptr_arr = malloc(sizeof(int) * (num*num));

	for(int i = 0; i < sets->size_maze; i++){
		sets->ptr_arr[i] = 0; // 셋 다 0으로 초기화함
	}

	maze_print->size_maze = 2*num*num;
	maze_print->ptr_arr = malloc(sizeof(int) * (2*num*num));

	for(int i = 0; i < maze_print->size_maze; i++){
		maze_print->ptr_arr[i] = -1; // 처음엔 모두 벽이 있음
	}
}

void Union(DisjointSets *sets, int i, int j){
	if (sets->ptr_arr[j] < sets->ptr_arr[i])
		sets->ptr_arr[i] = j;
	else{
		if(sets->ptr_arr[i] == sets->ptr_arr[j])
			sets->ptr_arr[i]--;
		sets->ptr_arr[j] = i;
	}
}

int find(DisjointSets *sets, int i){
	if(sets->ptr_arr[i] <= 0) // 본인이 루트라면
		return i;
	return find(sets, sets->ptr_arr[i]); // 재귀적으로 호출
}

void createMaze(DisjointSets *sets, DisjointSets *maze_print, int num){
	int randCell, randWall;
	int set1, set2;
	int root1, root2;
	int first, last;
	int set_size = sets->size_maze;
	srand((unsigned int)time(NULL));
	while(set_size > 1){
		// If last and first Cell joint, -> 이미 같은 셋
		first = find(sets, 0);
		last = find(sets, sets->size_maze);
		if(first == last && first != 0 && last != 0) break;

		randCell = (rand() % sets->size_maze);
		randWall = randCell*2 + (rand() % 2);


		// 가로 세로 벽을 쌓는 형식

		// 외벽두개
		if((randWall+1) % (num*2) == 0)
			continue;
		if(randWall >= (maze_print->size_maze - (num*2))
		   && randWall % 2 == 0)
			continue;

		// 이미 삭제된 벽이라면
		if(maze_print->ptr_arr[randWall] == 0)
			continue;

		set1 = randCell;

		// select a cell over Horizontal wall
		if(randWall % 2 == 0) set2 = randCell + num;

			// select a cell over Vertical wall
		else set2 = randCell + 1;

		root1 = find(sets, set1);
		root2 = find(sets, set2);

		// joint set
		if(root1 == root2 && root1 != 0 && root2 != 0)
			continue;

		// union sets
		Union(sets, root1, root2);
		set_size--;


		maze_print->ptr_arr[randWall] = 0;
	}
}

void printMaze(DisjointSets *sets, int num){
	sets->ptr_arr[sets->size_maze - 1] = 0; // 출구만들기
	// Top line
	for(int i = 0; i < num; i++)
		printf(" _");
	printf("\n");

	// Start
	printf(" ");

	for(int i = 0; i < sets->size_maze; i++){
		if(i % 2 == 0){
			if(sets->ptr_arr[i] == -1)
				printf("_");
			else
				printf(" ");
		}
		else{
			if(sets->ptr_arr[i] == -1)
				printf("|");
			else
				printf(" ");
		}
		if(i != sets->size_maze-1 && (i+1) % (num*2) == 0)
			printf("\n|");
	}
	printf("\n");
}

void freeMaze(DisjointSets *sets, DisjointSets *maze_print){
	free(sets->ptr_arr);
	free(sets);

	free(maze_print->ptr_arr);
	free(maze_print);
}