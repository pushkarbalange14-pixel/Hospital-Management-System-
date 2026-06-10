/*
 * =====================================================
 *   HOSPITAL MANAGEMENT SYSTEM
 *   Advanced Version - C Programming
 * =====================================================
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_PATIENTS 100
#define LINE "+---------+----------------------+-----+--------+----------------------+------+------------+"

/* ─── Data Structure ─────────────────────────────── */

struct Patient
{
    int    id;
    char   name[50];
    int    age;
    char   gender[10];
    char   disease[50];
    int    roomNo;
    float  bill;
};

struct Patient patients[MAX_PATIENTS];
int count = 0;

/* ─── Utility Functions ──────────────────────────── */

void clearScreen()
{
    printf("\033[2J\033[H");   /* ANSI clear screen */
}

void pressEnter()
{
    printf("\n  Press ENTER to continue...");
    getchar();
    getchar();
}

void printLine()
{
    printf("\n  %s\n", LINE);
}

void toUpperStr(char *str)
{
    int i;
    for (i = 0; str[i]; i++)
        str[i] = toupper((unsigned char)str[i]);
}

int idExists(int id)
{
    int i;
    for (i = 0; i < count; i++)
        if (patients[i].id == id)
            return 1;
    return 0;
}

int findPatient(int id)
{
    int i;
    for (i = 0; i < count; i++)
        if (patients[i].id == id)
            return i;
    return -1;
}

/* ─── Display Header ─────────────────────────────── */

void printHeader()
{
    printf("\n  %-9s %-22s %-5s %-8s %-22s %-6s %-12s",
           "ID", "Name", "Age", "Gender", "Disease", "Room", "Bill (Rs.)");
    printLine();
}

void printPatientRow(struct Patient p)
{
    printf("  | %-7d | %-20s | %-3d | %-6s | %-20s | %-4d | %10.2f |\n",
           p.id, p.name, p.age, p.gender, p.disease, p.roomNo, p.bill);
}

/* ─── Banner ─────────────────────────────────────── */

void showBanner()
{
    clearScreen();
    printf("\n");
    printf("  ╔══════════════════════════════════════════╗\n");
    printf("  ║      HOSPITAL MANAGEMENT SYSTEM          ║\n");
    printf("  ║      Advanced Edition  |  C Language     ║\n");
    printf("  ╚══════════════════════════════════════════╝\n");
}

/* ─── Menu ───────────────────────────────────────── */

void showMenu()
{
    showBanner();
    printf("\n");
    printf("  [ 1 ]  Add Patient\n");
    printf("  [ 2 ]  Display All Patients\n");
    printf("  [ 3 ]  Search Patient\n");
    printf("  [ 4 ]  Update Patient\n");
    printf("  [ 5 ]  Delete Patient\n");
    printf("  [ 6 ]  Total Revenue\n");
    printf("  [ 7 ]  Patient Statistics\n");
    printf("  [ 0 ]  Exit\n");
    printf("\n  ──────────────────────────────────────────\n");
    printf("  Patients Registered: %d / %d\n", count, MAX_PATIENTS);
    printf("  ──────────────────────────────────────────\n");
    printf("\n  Enter Choice: ");
}

/* ─── Feature 1: Add Patient ─────────────────────── */

void addPatient()
{
    if (count >= MAX_PATIENTS)
    {
        printf("\n  [!] Hospital records are full! Cannot add more patients.\n");
        pressEnter();
        return;
    }

    struct Patient p;

    printf("\n  ── ADD NEW PATIENT ──────────────────────\n");

    /* ID with duplicate check */
    while (1)
    {
        printf("\n  Patient ID   : ");
        if (scanf("%d", &p.id) != 1 || p.id <= 0)
        {
            printf("  [!] Invalid ID. Enter a positive number.\n");
            while (getchar() != '\n');
            continue;
        }
        if (idExists(p.id))
        {
            printf("  [!] ID %d already exists. Use a unique ID.\n", p.id);
            continue;
        }
        break;
    }

    /* Name */
    printf("  Name         : ");
    scanf(" %[^\n]", p.name);

    /* Age with validation */
    while (1)
    {
        printf("  Age          : ");
        if (scanf("%d", &p.age) == 1 && p.age > 0 && p.age <= 120)
            break;
        printf("  [!] Invalid age. Enter a value between 1 and 120.\n");
        while (getchar() != '\n');
    }

    /* Gender */
    printf("  Gender (M/F/Other): ");
    scanf("%s", p.gender);
    toUpperStr(p.gender);

    /* Disease */
    printf("  Disease      : ");
    scanf(" %[^\n]", p.disease);

    /* Room Number */
    while (1)
    {
        printf("  Room Number  : ");
        if (scanf("%d", &p.roomNo) == 1 && p.roomNo > 0)
            break;
        printf("  [!] Invalid room number.\n");
        while (getchar() != '\n');
    }

    /* Bill */
    while (1)
    {
        printf("  Bill Amount  : Rs. ");
        if (scanf("%f", &p.bill) == 1 && p.bill >= 0)
            break;
        printf("  [!] Invalid amount.\n");
        while (getchar() != '\n');
    }

    patients[count++] = p;

    printf("\n  [✓] Patient \"%s\" added successfully! (ID: %d)\n", p.name, p.id);
    pressEnter();
}

/* ─── Feature 2: Display All Patients ───────────── */

void displayPatients()
{
    printf("\n  ── ALL PATIENT RECORDS ─────────────────\n");

    if (count == 0)
    {
        printf("\n  [!] No patient records found.\n");
        pressEnter();
        return;
    }

    printLine();
    printHeader();

    int i;
    for (i = 0; i < count; i++)
        printPatientRow(patients[i]);

    printLine();
    printf("\n  Total Records: %d\n", count);
    pressEnter();
}

/* ─── Feature 3: Search Patient ─────────────────── */

void searchPatient()
{
    printf("\n  ── SEARCH PATIENT ───────────────────────\n");

    int id;
    printf("\n  Enter Patient ID: ");
    scanf("%d", &id);

    int idx = findPatient(id);

    if (idx == -1)
    {
        printf("\n  [!] No patient found with ID %d.\n", id);
    }
    else
    {
        struct Patient p = patients[idx];
        printf("\n  ── PATIENT DETAILS ─────────────────────\n");
        printf("\n  ID       : %d",      p.id);
        printf("\n  Name     : %s",      p.name);
        printf("\n  Age      : %d yrs",  p.age);
        printf("\n  Gender   : %s",      p.gender);
        printf("\n  Disease  : %s",      p.disease);
        printf("\n  Room No  : %d",      p.roomNo);
        printf("\n  Bill     : Rs. %.2f\n", p.bill);
    }

    pressEnter();
}

/* ─── Feature 4: Update Patient ─────────────────── */

void updatePatient()
{
    printf("\n  ── UPDATE PATIENT ───────────────────────\n");

    int id;
    printf("\n  Enter Patient ID to Update: ");
    scanf("%d", &id);

    int idx = findPatient(id);

    if (idx == -1)
    {
        printf("\n  [!] Patient with ID %d not found.\n", id);
        pressEnter();
        return;
    }

    struct Patient *p = &patients[idx];

    printf("\n  Updating record for: %s (ID: %d)\n", p->name, p->id);
    printf("  Leave a field blank to keep current value.\n\n");

    char temp[50];

    /* Update Name */
    printf("  New Name [%s]: ", p->name);
    scanf(" %[^\n]", temp);
    if (strlen(temp) > 0) strcpy(p->name, temp);

    /* Update Disease */
    printf("  New Disease [%s]: ", p->disease);
    scanf(" %[^\n]", temp);
    if (strlen(temp) > 0) strcpy(p->disease, temp);

    /* Update Room */
    int newRoom;
    printf("  New Room No [%d] (0 = keep): ", p->roomNo);
    scanf("%d", &newRoom);
    if (newRoom > 0) p->roomNo = newRoom;

    /* Update Bill */
    float newBill;
    printf("  New Bill Amount [%.2f] (-1 = keep): ", p->bill);
    scanf("%f", &newBill);
    if (newBill >= 0) p->bill = newBill;

    printf("\n  [✓] Patient record updated successfully!\n");
    pressEnter();
}

/* ─── Feature 5: Delete Patient ─────────────────── */

void deletePatient()
{
    printf("\n  ── DELETE PATIENT ───────────────────────\n");

    int id;
    printf("\n  Enter Patient ID to Delete: ");
    scanf("%d", &id);

    int idx = findPatient(id);

    if (idx == -1)
    {
        printf("\n  [!] Patient with ID %d not found.\n", id);
        pressEnter();
        return;
    }

    char confirm;
    printf("\n  Are you sure you want to delete \"%s\"? (y/n): ", patients[idx].name);
    scanf(" %c", &confirm);

    if (tolower(confirm) != 'y')
    {
        printf("\n  [!] Deletion cancelled.\n");
        pressEnter();
        return;
    }

    /* Shift records left */
    int j;
    for (j = idx; j < count - 1; j++)
        patients[j] = patients[j + 1];

    count--;
    printf("\n  [✓] Patient record deleted successfully.\n");
    pressEnter();
}

/* ─── Feature 6: Total Revenue ──────────────────── */

void totalRevenue()
{
    printf("\n  ── HOSPITAL REVENUE ─────────────────────\n");

    if (count == 0)
    {
        printf("\n  [!] No patient records found.\n");
        pressEnter();
        return;
    }

    float total = 0, highest = 0, lowest = patients[0].bill;
    char highName[50], lowName[50];

    int i;
    for (i = 0; i < count; i++)
    {
        total += patients[i].bill;
        if (patients[i].bill > highest)
        {
            highest = patients[i].bill;
            strcpy(highName, patients[i].name);
        }
        if (patients[i].bill < lowest)
        {
            lowest = patients[i].bill;
            strcpy(lowName, patients[i].name);
        }
    }

    printf("\n  Total Patients  : %d",        count);
    printf("\n  Total Revenue   : Rs. %.2f",  total);
    printf("\n  Average Bill    : Rs. %.2f",  total / count);
    printf("\n  Highest Bill    : Rs. %.2f  (%s)", highest, highName);
    printf("\n  Lowest Bill     : Rs. %.2f  (%s)\n", lowest, lowName);

    pressEnter();
}

/* ─── Feature 7: Statistics ──────────────────────── */

void patientStats()
{
    printf("\n  ── PATIENT STATISTICS ───────────────────\n");

    if (count == 0)
    {
        printf("\n  [!] No patient records found.\n");
        pressEnter();
        return;
    }

    int maleCount = 0, femaleCount = 0, otherCount = 0;
    int totalAge = 0, youngest = patients[0].age, oldest = 0;

    int i;
    for (i = 0; i < count; i++)
    {
        char g = toupper((unsigned char)patients[i].gender[0]);
        if (g == 'M')      maleCount++;
        else if (g == 'F') femaleCount++;
        else               otherCount++;

        totalAge += patients[i].age;
        if (patients[i].age > oldest)  oldest   = patients[i].age;
        if (patients[i].age < youngest) youngest = patients[i].age;
    }

    printf("\n  Total Patients  : %d",              count);
    printf("\n  Male            : %d",              maleCount);
    printf("\n  Female          : %d",              femaleCount);
    printf("\n  Other           : %d",              otherCount);
    printf("\n  Average Age     : %.1f yrs",        (float)totalAge / count);
    printf("\n  Youngest        : %d yrs",          youngest);
    printf("\n  Oldest          : %d yrs\n",        oldest);

    pressEnter();
}

/* ─── Main ───────────────────────────────────────── */

int main()
{
    int choice;

    do
    {
        showMenu();
        scanf("%d", &choice);

        switch (choice)
        {
            case 1: addPatient();    break;
            case 2: displayPatients(); break;
            case 3: searchPatient(); break;
            case 4: updatePatient(); break;
            case 5: deletePatient(); break;
            case 6: totalRevenue();  break;
            case 7: patientStats();  break;
            case 0:
                showBanner();
                printf("\n  Thank you for using Hospital Management System.\n\n");
                break;
            default:
                printf("\n  [!] Invalid choice. Please enter 0-7.\n");
                pressEnter();
        }

    } while (choice != 0);

    return 0;
}
