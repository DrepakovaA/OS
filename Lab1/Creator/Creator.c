#include <stdio.h>
#include <stdlib.h>
#include "../Lab1/EmployeesStruct.h"

int main(int argc, char* argv[]) {

	int recordsAmount = atoi(argv[1]);
	struct Employee *employees = (struct Employee*)
		malloc(recordsAmount * sizeof(struct Employee));
	// argv[0] is binary file name
	FILE *fptr = fopen(argv[0], "wb");

	fwrite(&recordsAmount, sizeof(recordsAmount), 1, fptr);
	for (int i = 0; i < recordsAmount; i++) {
		printf("Input number: ");
		scanf("%d", &employees[i].num);

		printf("Input name: ");
		scanf("%s", employees[i].name);

		printf("Input hours: ");
		scanf("%lf", &employees[i].hours);

		printf("--------------------------\n");
	}
	fwrite(employees, sizeof(struct Employee), recordsAmount, fptr);

	// where is better to place fclose(FILE*): before printf or after it?
	fclose(fptr);
	printf("Input finished!\n");
	free(employees);
	return 0;
}