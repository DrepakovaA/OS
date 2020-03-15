#include <stdio.h>
#include "../Lab1/EmployeesStruct.h"

int main(int argc, char* argv[]) {

	// argv[0] - binary file name
	// argv[1] - report file name (.txt)
	// argv[2] - hourly rate

	FILE *fptrBin = fopen(argv[0], "rb");
	int recordsAmount = 0;

	fread(&recordsAmount, sizeof(recordsAmount), 1, fptrBin);
	struct Employee *employees = (struct Employee*)
		malloc(recordsAmount * sizeof(struct Employee));
	fread(employees, sizeof(struct Employee), recordsAmount, fptrBin);
	fclose(fptrBin);

	FILE *fptrReport = fopen(argv[1], "w");
	fprintf(fptrReport, "Report on file %s\n", argv[0]);

	double hourlyRate;
	sscanf(argv[2], "%lf", &hourlyRate);

	for (int i = 0; i < recordsAmount; i++) {
		double salary = employees[i].hours * hourlyRate;
		fprintf(fptrReport, "%d\t%s\t%lf\t%lf\n", employees[i].num,
			employees[i].name, employees[i].hours, salary);
	}
	printf("Report finished!\n");

	fclose(fptrReport);
	free(employees);
	return 0;
}