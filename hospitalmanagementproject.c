#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATIENTS 200
#define MAX_EMERGENCY_PATIENTS 100
#define MAX_AMBULANCES 100
#define MAX_DOCTORS 50
#define MAX_MEDICATIONS 100
#define MAX_APPOINTMENTS 500
#define MAX_BILLS 1000
#define MAX_MEDICINES 100
#define MAX_STAFF 100

// Define structures for all entities involved in the system
typedef struct {
    int id;
    char name[50];
    int age;
    char disease[100];
    char patientType[20];  // "Outpatient" or "Inpatient"
    char medicalHistory[200]; // Store patient history
    int emergencyStatus;    // 1 for emergency, 0 for regular
} Patient;

typedef struct {
    int id;
    char name[50];
    int age;
    char emergencyType[100];
} EmergencyPatient;

typedef struct {
    int id;
    char patientName[50];
    char pickupLocation[100];
} AmbulanceRequest;

typedef struct {
    int id;
    char name[50];
    int age;
    char specialty[50];
} Doctor;


// Structure for Medicine
typedef struct {
    int id;
    char name[50];
    int quantity;
    float pricePerUnit;
    char expirationDate[10];  // MM-YYYY format
} Medicine;

typedef struct {
    int id;
    char patientName[50];
    char doctorName[50];
    char date[20];
    char time[10];
} Appointment;

typedef struct {
    int id;
    char patientName[50];
    float consultationFee;
    float medicationCost;
    float roomCharges;
    float totalBill;
} Bill;

typedef struct {
    int id;
    char name[50];
    char position[50];
} Staff;

Patient patients[MAX_PATIENTS];
EmergencyPatient emergencyPatients[MAX_EMERGENCY_PATIENTS];
AmbulanceRequest ambulanceRequests[MAX_AMBULANCES];
Doctor doctors[MAX_DOCTORS];
Appointment appointments[MAX_APPOINTMENTS];
Bill bills[MAX_BILLS];
Medicine medicines[MAX_MEDICINES];
Staff staffMembers[MAX_STAFF];

int patientCount = 0;
int emergencyPatientCount = 0;
int ambulanceRequestCount = 0;
int doctorCount = 0;
int medicationCount = 0;
int appointmentCount = 0;
int billCount = 0;
int staffCount = 0;
int medicineCount = 0;
// Function to add a new patient
void addPatient() {
    if (patientCount >= MAX_PATIENTS) {
        printf("\n**\n");
        printf("* Cannot add more patients.            *\n");
        printf("* Hospital is at full capacity.        *\n");
        printf("\n");
        return;
    }

    Patient newPatient;
    newPatient.id = patientCount + 1;

    printf("\n*=========================================*\n");
    printf("|            Add New Patient              |\n");
    printf("===========================================\n");

    printf("Enter patient's name: ");
    scanf(" %[^\n]", newPatient.name);

    printf("Enter patient's age: ");
    scanf("%d", &newPatient.age);

    printf("Enter patient's disease: ");
    scanf(" %[^\n]", newPatient. disease);

    printf("Enter patient type (Outpatient/Inpatient): ");
    scanf(" %[^\n]", newPatient.patientType);

    printf("Enter patient's medical history (optional): ");
    scanf(" %[^\n]", newPatient.medicalHistory);

    patients[patientCount++] = newPatient;
    printf("\n----------------------------------------\n");
    printf("      Patient added successfully!       \n");
    printf("----------------------------------------\n");

}


void displayPatients() {
    if (patientCount == 0) {
        printf("\n-------------------------------------------------------------\n");
        printf("|                No patients to display at the moment!       |\n");
        printf("-------------------------------------------------------------\n");
        return;
    }


     printf("----------------------------------------------------------------------------------------------------------\n");
    printf("|                                      Patient List                                                      |\n");
     printf("----------------------------------------------------------------------------------------------------------\n");
    printf("| %-5s | %-20s | %-3s | %-15s | %-15s | %-29s |\n",
           "ID", "Name", "Age", "Disease", "Type", "Medical History");
    printf("----------------------------------------------------------------------------------------------------------\n");

    // Displaying each patient's information in a neat table
    for (int i = 0; i < patientCount; i++) {
        printf("| %-5d | %-20s | %-3d | %-15s | %-15s | %-29s |\n",
               patients[i].id, patients[i].name, patients[i].age, patients[i].disease,
               patients[i].patientType, patients[i].medicalHistory);
    }


     printf("----------------------------------------------------------------------------------------------------------\n");
}
// Function to search a patient by ID
void updatePatient() {
    int id;
    printf("\n*===========================================================*\n");
      printf("|                     Update Patient Info                   |\n");
      printf("=============================================================\n");
    printf("Enter patient ID to update: ");
    scanf("%d", &id);

    if (id < 1 || id > patientCount) {
        printf("\n-------------------------------------------------------------\n");
          printf("|           Patient with ID %d not found.                   |\n", id);
          printf("-------------------------------------------------------------\n");
        return;
    }
    Patient* p = &patients[id - 1];  // Get pointer to the patient
     printf("\n*-----------------------------------------------------------*\n");
       printf("|                   Update Patient Details                  |\n");
       printf("-------------------------------------------------------------\n");

    printf("Update patient name: ");
    scanf(" %[^\n]", p->name);

    printf("Update patient age: ");
    scanf("%d", &p->age);

    printf("Update patient  disease: ");
    scanf(" %[^\n]", p-> disease);

    printf("Update patient type (Outpatient/Inpatient): ");
    scanf(" %[^\n]", p->patientType);

    printf("Update patient's medical history (optional): ");
    scanf(" %[^\n]", p->medicalHistory);
   // printf("Patient updated successfully!\n");
    printf("\n-------------------------------------------------------------\n");
      printf("|                Patient updated successfully!              |\n");
      printf("-------------------------------------------------------------\n");
}
// Function to delete a patient by ID
void deletePatient() {
    if (patientCount == 0) {
        printf("\n+-------------------------------------------------------------+\n");
        printf("| No patients available to delete.                            |\n");
        printf("+-------------------------------------------------------------+\n");
        return;
    }

    int patientID;
    printf("\n+-------------------------------------------------------------+\n");
    printf("|                  Delete Patient                             |\n");
    printf("+-------------------------------------------------------------+\n");

    printf("Enter the ID of the patient you want to delete: ");
    scanf("%d", &patientID);

    // Check if the ID is valid
    if (patientID <= 0 || patientID > patientCount) {
        printf("\n+-------------------------------------------------------------+\n");
        printf("| Patient with ID %d not found. Please try again.             |\n", patientID);
        printf("+-------------------------------------------------------------+\n");
        return;
    }

    // Search for the patient by ID and delete
    int found = 0;
    for (int i = 0; i < patientCount; i++) {
        if (patients[i].id == patientID) {
            // Shift all patients after the deleted one to the left
            for (int j = i; j < patientCount - 1; j++) {
                patients[j] = patients[j + 1];  // Move the next patient to the current index
            }
            patientCount--;  // Decrease the total count of patients
            printf("\n+-------------------------------------------------------------+\n");
            printf("| Patient with ID %d has been successfully deleted.            |\n", patientID);
            printf("+-------------------------------------------------------------+\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\n+------------------------------------------------------------+\n");
        printf("|  Patient with ID %d not found. Please try again.               |\n", patientID);
        printf("+------------------------------------------------------------+\n");
    }
}

// Emergency Patient Management Functions
void addEmergencyPatient() {
    if (emergencyPatientCount >= MAX_EMERGENCY_PATIENTS) {
        printf("\n+-------------------------------------------------------------+\n");
        printf("              Cannot add more emergency patients!          \n");
        printf(" +-------------------------------------------------------------+\n");
        return;
    }

    EmergencyPatient newPatient;
    newPatient.id = emergencyPatientCount + 1;

    printf("Enter emergency patient's name: ");
    scanf(" %[^\n]", newPatient.name);

    printf("Enter emergency patient's age: ");
    scanf("%d", &newPatient.age);

    printf("Enter emergency type (e.g., Heart Attack, Accident, etc.): ");
    scanf(" %[^\n]", newPatient.emergencyType);

    emergencyPatients[emergencyPatientCount++] = newPatient;
    printf("\n-------------------------------------------------------------\n");
      printf("|           Emergency patient added successfully!           |\n");
      printf("-------------------------------------------------------------\n");
}
   // printf("Emergency patient added successfully!\n");


void displayEmergencyPatients() {
    if (emergencyPatientCount == 0) {
       // printf("No emergency patients to display.\n");
        printf("\n+-------------------------------------------------------------+\n");
        printf("          No emergency patients to display at the moment!!    ");
        printf("\n+-------------------------------------------------------------+\n");
        return;
    }
    printf("\n*===========================================================*\n");
      printf("|                  Emergency Patient List                   |\n");
      printf("=============================================================\n");


    for (int i = 0; i < emergencyPatientCount; i++) {
       printf("* %-5s | %-20s | %-3s | %-20s *\n",
               "ID", "Name", "Age", "Emergency Type");
        printf("-------------------------------------------------------------\n");
        printf("* %-5d | %-20s | %-3d | %-20s *\n",emergencyPatients[i].id, emergencyPatients[i].name,emergencyPatients[i].age, emergencyPatients[i].emergencyType);
        printf("-------------------------------------------------------------\n");
    }
}

void addAmbulanceRequest() {
    if (ambulanceRequestCount >= MAX_AMBULANCES) {
        printf("\n+-------------------------------------------------------------+\n");
        printf("|              Cannot add more ambulance requests!            |\n");
        printf("+-------------------------------------------------------------+\n");
        return;
    }

    AmbulanceRequest newRequest;
    newRequest.id = ambulanceRequestCount + 1;

    printf("Enter patient's name for ambulance request: ");
    scanf(" %[^\n]", newRequest.patientName);

    printf("Enter ambulance pickup location: ");
    scanf(" %[^\n]", newRequest.pickupLocation);

    ambulanceRequests[ambulanceRequestCount++] = newRequest;
       printf("\n*-------------------------------------------------------------*\n");
       printf("|           Ambulance request added successfully!             |\n");
       printf("*---------------------------------------------------------------\n");
}


void displayAmbulanceRequests() {
    if (ambulanceRequestCount == 0) {
        printf("\n+-------------------------------------------------------------+\n");
        printf("|                  No ambulance requests to display!          |");
        printf("\n+-------------------------------------------------------------+\n");
        return;
    }
  printf("\n+---------------------------------------------------------+\n");
    printf("|                Ambulance Request List                   |\n");
    printf("+---------------------------------------------------------+\n");
    printf("| %-4s | %-20s | %-25s |\n", "ID", "Patient Name", "Pickup Location");
    printf("+---------------------------------------------------------+\n");
    for (int i = 0; i < ambulanceRequestCount; i++) {
        printf("| %-4d | %-20s | %-25s |\n",
               ambulanceRequests[i].id,
               ambulanceRequests[i].patientName,
               ambulanceRequests[i].pickupLocation);
    }


    printf("+---------------------------------------------------------+\n");
}


void scheduleEmergencyAppointment() {
    if (appointmentCount >= MAX_APPOINTMENTS) {
        printf("+---------------------------------------------------------+\n");
        printf("              ERROR: Cannot add more appointments!        \n");
        printf("+---------------------------------------------------------+\n");
        return;
    }


    Appointment newAppointment;
    newAppointment.id = appointmentCount + 1;
    printf("\n+-----------------------------------------------------------+\n");
    printf("|                  Schedule Emergency Appointment           |\n");
    printf("+-----------------------------------------------------------+\n");

    printf("Enter emergency patient's name: ");
    scanf(" %[^\n]", newAppointment.patientName);

    printf("Enter doctor's name for emergency appointment: ");
    scanf(" %[^\n]", newAppointment.doctorName);


    printf("Enter emergency appointment date (DD/MM/YYYY): ");
    scanf(" %[^\n]", newAppointment.date);


    strcpy(newAppointment.time, "Immediate");

    appointments[appointmentCount++] = newAppointment;
    printf("\n+----------------------------------------------------------+\n");
    printf("| Emergency Appointment Successfully Scheduled!            |\n");
    printf("+----------------------------------------------------------+\n");
}

void displayEmergencyAppointments() {
    if (appointmentCount == 0) {
         printf("+---------------------------------------------------------+\n");
         printf("                  No emergency appointments to display!   \n");
         printf("+---------------------------------------------------------+\n");
        return;
    }
    printf("\n+-------------------------------------------------------------------------------------------------------------+\n");
      printf("|                               Emergency Appointment List                                                    |\n");
    printf("\n+-------------------------------------------------------------------------------------------------------------+\n");
      printf("| %-4s | %-25s | %-25s | %-12s | %-29s |\n", "ID", "Patient Name", "Doctor Name", "Date", "Time");
    printf("\n+-------------------------------------------------------------------------------------------------------------+\n");
    for (int i = 0; i < appointmentCount; i++) {
        printf("| %-4d | %-25s | %-25s | %-12s | %-29s |\n",
               appointments[i].id,
               appointments[i].patientName,
               appointments[i].doctorName,
               appointments[i].date,
               appointments[i].time);
    }
   printf("\n+-------------------------------------------------------------------------------------------------------------+\n");
}
void addDoctor() {
    if (doctorCount >= MAX_DOCTORS) {
        printf("\n===================================================\n");
        printf("   Cannot add more doctors. Maximum capacity reached.\n");
        printf("=====================================================\n\n");
        return;
    }

    Doctor newDoctor;
    newDoctor.id = doctorCount + 1;
    printf("\n======================================\n");
    printf("        Enter Doctor's Information        \n");
    printf("======================================\n");


    printf("-> Enter doctor's name: ");
    scanf(" %[^\n]", newDoctor.name);

    printf("-> Enter doctor's specialty: ");
    scanf(" %[^\n]", newDoctor.specialty);

    doctors[doctorCount++] = newDoctor;
     printf("\nDoctor added successfully!\n");
    printf("+======================================+\n\n");
}
void displayDoctors() {
    if (doctorCount == 0) {
        printf("No doctors to display.\n");
        return;
    }
    printf("\n+-------+----------------------+----------------------+\n");
    printf("| %-5s | %-20s | %-20s |\n", "ID", "Name", "Specialty");
    printf("+-------+----------------------+----------------------+\n");

    for (int i = 0; i < doctorCount; i++) {
    printf("| %-5d | %-20s | %-20s |\n",
               doctors[i].id, doctors[i].name, doctors[i].specialty);
    }

    printf("+-------+----------------------+----------------------+\n");
}
void updateDoctor() {
    int id;
    printf("\n========================================\n");
    printf("       Update Doctor Information       \n");
    printf("========================================\n");
    printf("Enter doctor ID to update: ");
    scanf("%d", &id);


    if (id < 1 || id > doctorCount) {
        printf("\n+--------------------------------------+\n");
        printf("|   Error: Doctor with ID %d not found   |\n", id);
        printf("+--------------------------------------+\n\n");
        return;
    }

    Doctor* d = &doctors[id - 1];  // Get pointer to the doctor
    printf("\n+-------+----------------------+----------------------+\n");
    printf("| %-5s | %-20s | %-20s |\n", "ID", "Name", "Specialty");
    printf("+-------+----------------------+----------------------+\n");
    printf("| %-5d | %-20s | %-20s |\n", d->id, d->name, d->specialty);
    printf("+-------+----------------------+----------------------+\n");

    printf("Update doctor name: ");
    scanf(" %[^\n]", d->name);



    printf("Update doctor specialty: ");
    scanf(" %[^\n]", d->specialty);
    printf("\n+--------------------------------------+\n");
    printf("| Doctor information updated successfully! |\n");
    printf("+--------------------------------------+\n\n");
}


void scheduleAppointment() {
    if (appointmentCount >= MAX_APPOINTMENTS) {
        printf("\n========================================\n");
        printf("      Cannot add more appointments.      \n");
        printf("========================================\n\n");
        return;
    }


    Appointment newAppointment;
    newAppointment.id = appointmentCount + 1;
    printf("-> Enter patient's name: ");
    scanf(" %[^\n]", newAppointment.patientName);
    printf("-> Enter doctor's name: ");
    scanf(" %[^\n]", newAppointment.doctorName);
    printf("-> Enter appointment date (DD/MM/YYYY): ");
    scanf(" %[^\n]", newAppointment.date);
    printf("-> Enter appointment time (HH:MM): ");
    scanf(" %[^\n]", newAppointment.time);

    appointments[appointmentCount++] = newAppointment;
    printf("\n----------------------------------------\n");
    printf("  Appointment scheduled successfully!    \n");
    printf("========================================\n\n");
}

void displayAppointments() {
    if (appointmentCount == 0) {
        printf("\n========================================\n");
        printf("       No appointments to display.      \n");
        printf("========================================\n\n");
        return;
    }
    printf("\n+-------+--------------------+--------------------+-------------------+----------+\n");
    printf("| %-5s | %-18s | %-18s | %-17s | %-8s |\n", "ID", "Patient Name", "Doctor Name", "Date", "Time");
    printf("+-------+--------------------+--------------------+-------------------+----------+\n");

   // printf("\nAppointment List:\n");
    for (int i = 0; i < appointmentCount; i++) {
        printf("| %-5d | %-18s | %-18s | %-17s | %-8s |\n",
               appointments[i].id, appointments[i].patientName, appointments[i].doctorName,
               appointments[i].date, appointments[i].time);
    }

    printf("+-------+--------------------+--------------------+-------------------+----------+\n\n");
}

void generateBill() {
    if (billCount >= MAX_BILLS) {
        printf("\n========================================\n");
        printf("       Cannot generate more bills.      \n");
        printf("========================================\n\n");
        return;
    }

    Bill newBill;
    newBill.id = billCount + 1;

    printf("\n========================================\n");
    printf("           Generate New Bill            \n");
    printf("========================================\n");

    printf("=> Enter patient's name: ");
    scanf(" %[^\n]", newBill.patientName);
    printf("=> Enter consultation fee: ");
    scanf("%f", &newBill.consultationFee);
    printf("=> Enter medication cost: ");
    scanf("%f", &newBill.medicationCost);
    printf("=> Enter room charges: ");
    scanf("%f", &newBill.roomCharges);

    newBill.totalBill = newBill.consultationFee + newBill.medicationCost + newBill.roomCharges;
    bills[billCount++] = newBill;
    printf("\n----------------------------------------\n");
    printf("  Bill generated successfully!          \n");
    printf("  Total Bill: %.2f                     \n", newBill.totalBill);
    printf("========================================\n\n");
}
void displayBills() {
    if (billCount == 0) {
        printf("\n========================================\n");
        printf("           No bills to display.         \n");
        printf("========================================\n\n");
        return;
    }
    printf("\n+-------+--------------------+--------------------+\n");
    printf("| %-5s | %-18s | %-18s |\n", "ID", "Patient Name", "Total Bill");
    printf("+-------+--------------------+--------------------+\n");
    for (int i = 0; i < billCount; i++) {
    printf("| %-5d | %-18s | %-18.2f |\n",
               bills[i].id, bills[i].patientName, bills[i].totalBill);
    }

    printf("+-------+--------------------+--------------------+\n\n");
}


void addStaff() {
    if (staffCount >= MAX_STAFF) {
        printf("\n========================================\n");
        printf("        Cannot add more staff members.  \n");
        printf("========================================\n\n");
        return;
    }
    Staff newStaff;
    newStaff.id = staffCount + 1;

    printf("\n========================================\n");
    printf("        Add New Staff Member            \n");
    printf("========================================\n");

    printf("-> Enter staff name: ");
    scanf(" %[^\n]", newStaff.name);
    printf("-> Enter staff position: ");
    scanf(" %[^\n]", newStaff.position);

    staffMembers[staffCount++] = newStaff;
    printf("\n----------------------------------------\n");
    printf("  Staff added successfully!             \n");
    printf("========================================\n\n");
}

void displayStaff() {
    if (staffCount == 0) {
        printf("\n========================================\n");
        printf("        No staff members to display.    \n");
        printf("========================================\n\n");
        return;
    }

    printf("\n+-------+--------------------+--------------------+\n");
    printf("| %-5s | %-18s | %-18s |\n", "ID", "Name", "Position");
    printf("+-------+--------------------+--------------------+\n");

    for (int i = 0; i < staffCount; i++) {
    printf("| %-5d | %-18s | %-18s |\n",
               staffMembers[i].id, staffMembers[i].name, staffMembers[i].position);
    }

    printf("+-------+--------------------+--------------------+\n\n");
}


void addMedicine() {
    if (medicineCount >= MAX_MEDICINES) {
        printf("\n** Cannot add more medicines. Hospital's pharmacy is full! **\n");
        return;
    }

    Medicine newMedicine;
    newMedicine.id = medicineCount + 1;
    printf("\n*=========================================*\n");
    printf("|            Add New Medicine             |\n");
    printf("===========================================\n");

    printf("Enter medicine name: ");
    scanf(" %[^\n]", newMedicine.name);

    printf("Enter quantity: ");
    scanf("%d", &newMedicine.quantity);

    printf("Enter price per unit: ");
    scanf("%f", &newMedicine.pricePerUnit);

    printf("Enter expiration date (MM-YYYY): ");
    scanf(" %[^\n]", newMedicine.expirationDate);

    medicines[medicineCount++] = newMedicine;
    printf("\n----------------------------------------\n");
    printf("      Medicine added successfully!      \n");
    printf("----------------------------------------\n");
}
// Function to display the list of medicines
void viewMedicines() {
    if (medicineCount == 0) {
        printf("\n-------------------------------------------------------------\n");
        printf("| No medicines available to display.                         |\n");
        printf("-------------------------------------------------------------\n");
        return;
    }


    printf("\n\t\t\t\t\t *** MEDICINE LIST ***\n");
    printf("=================================================================================================================\n");
    printf("| %-12s | %-20s | %-8s | %-15s | %-15s | %-15s |\n",
           "Medicine ID", "Medicine Name", "Quantity", "Price per Unit", "Expiration Date", "Total Cost");
    printf("=================================================================================================================\n");


    for (int i = 0; i < medicineCount; i++) {
        printf("| %-12d | %-20s | %-8d | %-15.2f | %-15s | %-15.2f |\n",
               medicines[i].id, medicines[i].name, medicines[i].quantity, medicines[i].pricePerUnit,
               medicines[i].expirationDate, medicines[i].quantity * medicines[i].pricePerUnit);
    }


    printf("=================================================================================================================\n");
}

void deleteMedicine() {
    if (medicineCount == 0) {
        printf("\n-------------------------------------------------------------\n");
        printf("| No medicines available to delete.                         |\n");
        printf("-------------------------------------------------------------\n");
        return;
    }

    int id;
    printf("\n-------------------------------------------------------------\n");
    printf("|                  Delete Medicine                           |\n");
    printf("-------------------------------------------------------------\n");

    printf("Enter the ID of the medicine to delete: ");
    scanf("%d", &id);

    if (id < 1 || id > medicineCount) {
        printf("\n-------------------------------------------------------------\n");
        printf("| Medicine with ID %d not found. Please try again.           |\n", id);
        printf("-------------------------------------------------------------\n");
        return;
    }


    for (int i = id - 1; i < medicineCount - 1; i++) {
        medicines[i] = medicines[i + 1];
    }
    medicineCount--;
    printf("\n----------------------------------------\n");
    printf("      Medicine with ID %d has been successfully deleted!    \n", id);
    printf("----------------------------------------\n");
}


void updateMedicine() {
    int id;
    printf("\n-------------------------------------------------------------\n");
    printf("|                  Update Medicine Information              |\n");
    printf("-------------------------------------------------------------\n");

    printf("Enter the ID of the medicine to update: ");
    scanf("%d", &id);

    if (id < 1 || id > medicineCount) {
        printf("\n-------------------------------------------------------------\n");
        printf("| Medicine with ID %d not found. Please try again.           |\n", id);
        printf("-------------------------------------------------------------\n");
        return;
    }

    Medicine* m = &medicines[id - 1];
    printf("Update quantity: ");
    scanf("%d", &m->quantity);

    printf("Update price per unit: ");
    scanf("%f", &m->pricePerUnit);

    printf("Update expiration date (MM-YYYY): ");
    scanf(" %[^\n]", m->expirationDate);

    printf("\n----------------------------------------\n");
    printf("      Medicine updated successfully!   \n");
    printf("----------------------------------------\n");
}

void welcomeMessage() {
    printf("\n\n\n\n\n");
    printf("\n\t\t\t    ---------------------------------------------------\n");
    printf("\n\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n\t\t\t        =                  WELCOME                  =");
    printf("\n\t\t\t        =                    TO                     =");
    printf("\n\t\t\t        =                  HOSPITAL                 =");
    printf("\n\t\t\t        =                 MANAGEMENT                =");
    printf("\n\t\t\t        =                   SYSTEM                  =");
    printf("\n\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n");
    printf("\n\t\t\t    ---------------------------------------------------\n");
    printf("\n\n\n\t\t\t Enter any key to continue.....");
    getchar();
}

int authenticate() {
    char username[30], password[30];
    const char correctUsername[] = "admin";
    const char correctPassword[] = "password123";

    fflush(stdin);

    printf("\n\t\t\t Please enter your username: ");
    scanf("%s", username);

    printf("\n\t\t\t Please enter your password: ");
    scanf("%s", password);


    if (strcmp(username, correctUsername) == 0 && strcmp(password, correctPassword) == 0) {
        return 1;
    } else {
        return 0;
    }
}
// Main Menu Function
void mainMenu() {
    int choice;
    while (1) {
printf("\n");
        printf("\n\n");
    printf("\t\t\t ********************************************************\n");
    printf("\t\t\t *                                                      *\n");
    printf("\t\t\t *              WELCOME TO PAF HEALTHCARE HOSPITAL      *\n");
    printf("\t\t\t *       (Patient Assistance and Family Care Hospital)  *\n");
    printf("\t\t\t *                                                      *\n");
    printf("\t\t\t ********************************************************\n");
    printf("\t\t\t *                                                      *\n");
    printf("\t\t\t *         Providing the Best Healthcare Solutions      *\n");
    printf("\t\t\t *                                                      *\n");
    printf("\t\t\t ********************************************************\n");
    printf("\n\n");

        printf("\n\t\t\t*** MAIN MENU ***\n");
        printf("$~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~$\n");
        printf("$------------------------------------------------------$\n");
        printf("1. Patient Management\n");
        printf("2. Emergency Services\n");
        printf("3. Doctor Management \n");
        printf("4. Appointment Scheduling\n");
        printf("5. Billing Management\n");
        printf("6. Staff Management\n");
        printf("7. Pharmacy Management\n");
        printf("8. Exit\n");
        printf("\nPlease choose an option (1-8): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                patientManagementMenu();
                break;
                case 2:
                emergencyServicesMenu();
                break;
                 case 3:
                doctorManagementMenu();
                break;
            case 4:
                appointmentManagementMenu();
                break;
            case 5:
                billingManagementMenu();
                break;
            case 6:
                staffManagementMenu();
                break;
            case 7:
                pharmacyManagementMenu();
                break;
            case 8:
                printf("\nThank you for using the Hospital Management System!\n");
                printf("Exiting the system. Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

void patientManagementMenu() {
    int choice;
    while (1) {
        printf("\n\n");
        printf("                 ===>> PATIENT MANAGEMENT MENU <<===       \n");
        printf("           =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
        printf("\n*** Please choose an option ***         \n");
        printf("=----------------------------------------------------------------------=\n");
        printf("   [1] Add New Patient\n");
        printf("   [2] View Patient List\n");
        printf("   [3] Update Patient Information\n");
        printf("   [4] Delete Patient\n");
        printf("   [5] Back to Main Menu\n");
        printf("=----------------------------------------------------------------------=\n");
        printf("\nPlease choose an option (1-5): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addPatient();
                break;
            case 2:
                displayPatients();
                break;
            case 3:
                updatePatient();
                break;
            case 4:
                deletePatient();
                break;
            case 5:
                return;
            default:
                printf("\nInvalid choice. Please try again with a valid option (1-5).\n");
        }
    }
}
void emergencyServicesMenu() {
    int choice;
    while (1) {
        printf("\n\n");
        printf("              ==>>  EMERGENCY SERVICES MENU  <<==             \n");
        printf("      =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");

        printf("\n*** Choose an option below ***\n");
         printf("=----------------------------------------------------------------------=\n");
        printf("   [1] Add Emergency Patient\n");
        printf("   [2] Display Emergency Patients\n");
        printf("   [3] Add Ambulance Request\n");
        printf("   [4] Display Ambulance Requests\n");
        printf("   [5] Schedule Emergency Appointment\n");
        printf("   [6] Display Emergency Appointments\n");
        printf("   [7] Back to Main Menu\n");
        printf("=----------------------------------------------------------------------=\n");
        printf("\nPlease choose an option (1-7): ");
        scanf("%d", &choice);


        switch (choice) {
            case 1:
                addEmergencyPatient();
                break;
            case 2:
                displayEmergencyPatients();
                break;
            case 3:
                addAmbulanceRequest();
                break;
            case 4:
                displayAmbulanceRequests();
                break;
            case 5:
                scheduleEmergencyAppointment();
                break;
            case 6:
                displayEmergencyAppointments();
                break;
            case 7:
                return;  // Go back to main menu
            default:
               printf("\nInvalid choice. Please select a valid option (1-7).\n");
        }
    }
}
void doctorManagementMenu() {
    int choice;
    while (1) {
        printf("\n\n");
        printf("              ==>>  DOCTOR MANAGEMENT MENU <<===               \n");
        printf("      =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");

        printf("\n*** Please choose an option ***               \n");
        printf("=----------------------------------------------------------------------=\n");
        printf("   [1] Add New Doctor\n");
        printf("   [2] View Doctor List\n");
        printf("   [3] Update Doctor Information\n");
        printf("   [4] Return to Main Menu\n");
        printf("=----------------------------------------------------------------------=\n");
        printf("\nPlease choose an option (1-4): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addDoctor();
                break;
            case 2:
                displayDoctors();
                break;
            case 3:
                updateDoctor();
                break;
            case 4:
                return;
            default:
                 printf("\nInvalid choice. Please try again with a valid option (1-4).\n");
        }
    }
}

void appointmentManagementMenu() {
    int choice;
    while (1) {
        printf("\n\n");
        printf("              ==>>  Appointment SCHEDULING MENU <<===         \n");
        printf("      =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");

        printf("\n*** Please choose an option ***               \n");
        printf("=----------------------------------------------------------------------=\n");
        printf("   [1] Schedule a New Appointment\n");
        printf("   [2] View Existing Appointments\n");
        printf("   [3] Return to Main Menu\n");
        printf("=----------------------------------------------------------------------=\n");
        printf("\nPlease choose an option (1-3): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                scheduleAppointment();
                break;
            case 2:
                displayAppointments();
                break;
            case 3:
                return;
            default:
                printf("\nInvalid choice. Please try again with a valid option (1-3).\n");
        }
    }
}

void billingManagementMenu() {
    int choice;
    while (1) {
        printf("\n\n");
        printf("          ==>> BILLING MANAGEMENT SYSTEM <<==            \n");
        printf("      =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
        printf("\n         *** Please choose an action ***               \n");
        printf("=----------------------------------------------------------------------=\n");
        printf("   [1] Generate a New Bill\n");
        printf("   [2] Display Existing Bills\n");
        printf("   [3] Return to Main Menu\n");
        printf("=----------------------------------------------------------------------=\n");
        printf("\nPlease choose an option (1-3): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                generateBill();
                break;
            case 2:
                displayBills();
                break;
            case 3:
                return;
            default:
                 printf("\nInvalid choice. Please select a valid option (1-3).\n");
        }
    }
}

void staffManagementMenu() {
    int choice;
    while (1) {
       printf("\n\n");
       printf("          ==>> STAFF MANAGEMENT SYSTEM <<==            \n");
        printf("      =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
        printf("\n*** Please choose an action ***              \n");
        printf("=----------------------------------------------------------------------=\n");
        printf("   [1] Add New Staff\n");
        printf("   [2] Display All Staff\n");
        printf("   [3] Return to Main Menu\n");
        printf("=----------------------------------------------------------------------=\n");
        printf("\nPlease choose an option (1-3): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStaff();
                break;
            case 2:
                displayStaff();
                break;
            case 3:
                return;
            default:
            printf("\nInvalid choice. Please select a valid option (1-3).\n");
        }
    }
}
void pharmacyManagementMenu() {
    int choice;
    while (1) {
        printf("\n\n");
        printf("                 ===>> PHARMACY MANAGEMENT MENU <<===       \n");
        printf("           =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
        printf("\n*** Please choose an option ***         \n");
        printf("=----------------------------------------------------------------------=\n");
        printf("   [1] Add New Medicine\n");
        printf("   [2] View Medicine List\n");
        printf("   [3] Update Medicine Information\n");
        printf("   [4] Delete Medicine\n");
        printf("   [5] Back to Main Menu\n");
        printf("=----------------------------------------------------------------------=\n");
        printf("\nPlease choose an option (1-5): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addMedicine();
                break;
            case 2:
                viewMedicines();
                break;
            case 3:
                updateMedicine();
                break;
            case 4:
                deleteMedicine();
                break;
            case 5:
                return;
            default:
                printf("\nInvalid choice. Please try again with a valid option (1-5).\n");
        }
    }
}

    int main() {
    welcomeMessage();

    for (int attempts = 3; attempts > 0; attempts--) {
        if (authenticate()) {
            printf("\n\t\t\t Login successful! Access granted.\n");
            mainMenu();  // After successful login, show the main menu
            return 0;
        }
        printf("\n\t\t\t Invalid credentials. %d attempt(s) remaining.\n", attempts - 1);
    }

    printf("\n\t\t\t Access denied. Please try again later.\n");
    return 0;
}

