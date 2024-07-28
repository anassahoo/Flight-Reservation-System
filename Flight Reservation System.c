#include <stdio.h>
#include <string.h>
// Function to print welcome message
void printing()
{
    printf("\t \t \t \t \t \t===============================================\n");
    printf("\t\t \t \t \t \tWelcome to PIA Online Flight Reservation System\n");
    printf("\t \t \t \t \t \t===============================================\n");
}
// Function to display menu options
void DisplayMenu()
{
    printf("Please Select your Choice:\n\n");
    printf("1. Flight Booking\n\n");
    printf("2. Flight cancellation\n\n");
    printf("3. Check Flight Bookings\n\n");
    printf("4. Exit\n\n");
}
// Structure for storing passenger biodata
struct biodata
{
    char name[100];
    int CNIC;
    int passport;
    int Visa;
};

// Function to input passenger biodata
void BioData(struct biodata *data)
{
    printf("Enter your name: ");
    scanf("%s", data->name);
    printf("Enter your CNIC (Without Dashes): ");
    scanf("%d", &data->CNIC);
    printf("Enter the passport No (Without Dashes): ");
    scanf("%d", &data->passport);
    printf("Enter the Visa number: ");
    scanf("%d", &data->Visa);
}

// Function to calculate fare for domestic flights
float fair_domestic(int destination, float luggage)
{
    float totalFare;
    int baseFare;

    switch (destination)
    {
    case 1: // Islamabad
        baseFare = 15000;
        break;
    case 2: // Karachi
        baseFare = 27000;
        break;
    case 3: // Lahore
        baseFare = 12000;
        break;
    default:
        printf("Invalid destination.\n");
        return -1;
    }

    float extraChargePerKg = 200;
    if (luggage <= 0)
    {
        printf("Invalid luggage weight.\n");
        return -1;
    }
    else if (luggage > 32)
    {
        totalFare = baseFare + (luggage - 32) * extraChargePerKg;
    }
    else
    {
        totalFare = baseFare;
    }

    return totalFare;
}

// Function to calculate fare for international flights
float fair_international(int destination, float luggage)
{
    float totalFare;
    int baseFare;

    switch (destination)
    {
    case 1: // Dubai
        baseFare = 70000;
        break;
    case 2: // Saudi Arabia
        baseFare = 150000;
        break;
    case 3: // America
        baseFare = 100000;
        break;
    default:
        printf("Invalid destination.\n");
        return -1;
    }

    float extraChargePerKg = 200;
    if (luggage <= 0)
    {
        printf("Invalid luggage weight.\n");
        return -1;
    }
    else if (luggage > 32)
    {
        totalFare = baseFare + (luggage - 32) * extraChargePerKg;
    }
    else
    {
        totalFare = baseFare;
    }

    return totalFare;
}

// Function to print ticket details and save to file
void PrintTicket(struct biodata *customer, int destination, float luggage, int isInternational, float fare)
{
    printf("\n\n-------------------------------------------\n");
    printf("               Booking Details             \n");
    printf("-------------------------------------------\n");
    printf("Name: %s\n", customer->name);
    printf("CNIC: %d\n", customer->CNIC);
    printf("Passport: %d\n", customer->passport);
    printf("-------------------------------------------\n");
    printf("Destination: ");
    if (isInternational)
    {
        switch (destination)
        {
        case 1:
            printf("Dubai\n");
            break;
        case 2:
            printf("Saudi Arabia\n");
            break;
        case 3:
            printf("America\n");
            break;
        }
        printf("Total Fare: %.2f\n", fare);
    }
    else
    {
        switch (destination)
        {
        case 1:
            printf("Islamabad\n");
            break;
        case 2:
            printf("Karachi\n");
            break;
        case 3:
            printf("Lahore\n");
            break;
        }
        printf("Total Fare: %.2f\n", fare);
    }
    printf("-------------------------------------------\n\n");

    // Save ticket to file
    char fileName[30];
    sprintf(fileName, "%d_ticket.txt", customer->passport); // Construct filename based on passport number
    FILE *file = fopen(fileName, "w");
    if (file != NULL)
    {
        fprintf(file, "Name: %s\n", customer->name);
        fprintf(file, "CNIC: %d\n", customer->CNIC);
        fprintf(file, "Passport: %d\n", customer->passport);
        fprintf(file, "Destination: ");
        if (isInternational)
        {
            switch (destination)
            {
            case 1:
                fprintf(file, "Dubai\n");
                break;
            case 2:
                fprintf(file, "Saudi Arabia\n");
                break;
            case 3:
                fprintf(file, "America\n");
                break;
            }
            fprintf(file, "Total Fare: %.2f\n", fare);
        }
        else
        {
            switch (destination)
            {
            case 1:
                fprintf(file, "Islamabad\n");
                break;
            case 2:
                fprintf(file, "Karachi\n");
                break;
            case 3:
                fprintf(file, "Lahore\n");
                break;
            }
            fprintf(file, "Total Fare: %.2f\n", fare);
        }
        fprintf(file, "-------------------------------------------\n\n");
        fclose(file);
    }
    else
    {
        printf("Error: File could not be created to save ticket.\n");
    }
}

// Function to cancel ticket
void cancelTicket(const int passportNum) {
    char fileName[30];
    sprintf(fileName, "%d_ticket.txt", passportNum);

    if (remove(fileName) == 0) {
        printf("Ticket with Passport Number %d has been cancelled successfully.\n", passportNum);
    } else {
        printf("No ticket found with Passport Number %d.\n", passportNum);
    }
}

// Function to check booking
void checkBooking(const int passportNum) {
    char fileName[30];
    sprintf(fileName, "%d_ticket.txt", passportNum); // Construct filename based on passport number

    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        printf("No booking found with Passport Number %d.\n", passportNum);
        return;
    }

    printf("Booking Details for Passport Number %d:\n", passportNum);

    char ch;
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }

    fclose(file);
}

// Function for domestic flight booking
void Domestic()
{
    int DomesticChoice;
    float luggageweight;
    struct biodata customer;
    printf("Which City you want to travel:\n");
    printf("1. Islamabad\n");
    printf("2. Karachi\n");
    printf("3. Lahore\n");
    scanf("%d", &DomesticChoice);

    switch (DomesticChoice)
    {
    case 1: // Islamabad
    case 2: // Karachi
    case 3: // Lahore
        BioData(&customer);
        printf("Enter the luggage weight :");
        scanf("%f", &luggageweight);
        float fareDomestic = fair_domestic(DomesticChoice, luggageweight);
        PrintTicket(&customer, DomesticChoice, luggageweight, 0, fareDomestic);
        break;
    default:
        printf("Invalid choice.\n");
        break;
    }
}

// Function for international flight booking
void International()
{
    int InternationalChoice;
    float luggageweight;
    struct biodata customer;
    printf("Which Country you want to travel:\n");
    printf("1. Dubai\n");
    printf("2. Saudi Arabia\n");
    printf("3. America\n");
    scanf("%d", &InternationalChoice);

    switch (InternationalChoice)
    {
    case 1: // Dubai
    case 2: // Saudi Arabia
    case 3: // America
        BioData(&customer);
        printf("Enter the luggage weight :");
        scanf("%f", &luggageweight);
        float fareInternational = fair_international(InternationalChoice, luggageweight);
        PrintTicket(&customer, InternationalChoice, luggageweight, 1, fareInternational);
        break;
    default:
        printf("Invalid choice.\n");
        break;
    }
}

// Main function
int main()
{
    int ch;
    int travel;
    printing();
    printf("\n");
    do
    {
        DisplayMenu();
        printf("Enter your Choice:");
        scanf("%d", &ch);

        switch (ch)
        {
        case 1:
            printf("Do you want to travel Domestic or International? (Press 1 for Domestic and 2 for International): ");
            scanf("%d", &travel);
            if (travel == 1)
            {
                Domestic();
            }
            else if (travel == 2)
            {
                International();
            }
            else{
                printf("The input is invalid\n");
            }
            break;
        case 2:
            printf("Enter your Passport Number for ticket cancellation: ");
            int passportNum;
            scanf("%d", &passportNum);
            cancelTicket(passportNum);
            break;
        case 3:
            printf("Enter your Passport Number to check booking: ");
            int checkPassportNum;
            scanf("%d", &checkPassportNum);
            checkBooking(checkPassportNum);
            break;
        case 4:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid Choice.\n");
            break;
        }
    } while (ch != 4);

    return 0;
}
