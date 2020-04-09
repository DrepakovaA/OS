#include <stdio.h>
#include <windows.h>
#include "../Lab1/EmployeesStruct.h"

int main() {

	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	char pathCreator[] = "..\\Debug\\Creator.exe";
	char pathReporter[] = "..\\Debug\\Reporter.exe";
	char cmdArgs[100];

	char binFileName[81];
	int recordsAmount;

	printf("Input binary file name: ");
	scanf("%s", binFileName);
	printf("Input amount of records: ");
	scanf("%d", &recordsAmount);
	sprintf(cmdArgs, "%s %d", binFileName, recordsAmount);

	// Creator
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	CreateProcess(pathCreator, cmdArgs, NULL, NULL, FALSE, CREATE_NEW_CONSOLE,
		NULL, NULL, &si, &pi);
	// wait while Creator end up working
	WaitForSingleObject(pi.hProcess, INFINITE);	

	// End up Creator

	// printing binary file contents
	FILE *fptrBin = fopen(binFileName, "rb");
	fread(&recordsAmount, sizeof(recordsAmount), 1, fptrBin);
	struct Employee *employees = (struct Employee*)
		malloc(recordsAmount * sizeof(struct Employee));
	fread(employees, sizeof(struct Employee), recordsAmount, fptrBin);

	printf("\n");
	for (int i = 0; i < recordsAmount; i++)
		printf("ID: %d Name: %s Hours: %lf\n", employees[i].num, employees[i].name, employees[i].hours);
	printf("\tAll information printed!\n\n");
	fclose(fptrBin);
	
	char reportFileName[81];
	double hourlyRate;
	printf("Input report file name (.txt): ");
	scanf("%s", reportFileName);
	printf("Input hourly rate: ");
	scanf("%lf", &hourlyRate);
	sprintf(cmdArgs, "%s %s %lf", binFileName, reportFileName, hourlyRate);
	printf("\n");

	// Reporter
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	CreateProcess(pathReporter, cmdArgs, NULL, NULL, FALSE, CREATE_NEW_CONSOLE,
		NULL, NULL, &si, &pi);
	// wait while Reporter end up working
	WaitForSingleObject(pi.hProcess, INFINITE);
	// End up Reporter

	// print report
	FILE *fptrReport = fopen(reportFileName, "r");
	char c;
	while ((c = getc(fptrReport)) != EOF)
		printf("%c", c);
	free(employees);
	system("pause");
	return 0;
}