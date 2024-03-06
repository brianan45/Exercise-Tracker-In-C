#include <stdio.h>
#include <string.h>

#define MAX_ENTRIES 10
#define MAX_HISTORY 5

// Define structure to store exercise details
struct Exercise {
    char name[50];
    char muscleGroup[50];
    float weight;
    int sets;
    int reps;
    struct ExerciseHistory {
        float weight;
        int sets;
        int reps;
    } history[MAX_HISTORY];
    int historyCount;
};

// Function to find the index of an exercise by name
int findExerciseIndex(struct Exercise exercises[], int numEntries, const char name[]) {
    for (int i = 0; i < numEntries; i++) {
        if (strcmp(exercises[i].name, name) == 0) {
            return i; // Return the index if the exercise is found
        }
    }
    return -1; // Return -1 if the exercise is not found
}

// Function to add an entry to exercise history
void addExerciseHistory(struct Exercise* exercise, float weight, int sets, int reps) {
    if (exercise->historyCount < MAX_HISTORY) {
        exercise->history[exercise->historyCount].weight = weight;
        exercise->history[exercise->historyCount].sets = sets;
        exercise->history[exercise->historyCount].reps = reps;
        exercise->historyCount++;
    } else {
        // Shift the history entries to make space for the new entry
        for (int i = 0; i < MAX_HISTORY - 1; i++) {
            exercise->history[i] = exercise->history[i + 1];
        }
        // Add the new entry at the end
        exercise->history[MAX_HISTORY - 1].weight = weight;
        exercise->history[MAX_HISTORY - 1].sets = sets;
        exercise->history[MAX_HISTORY - 1].reps = reps;
    }
}

// Function to display exercises by muscle group
void viewExercisesByMuscleGroup(struct Exercise exercises[], int numEntries, const char muscleGroup[]) {
    printf("\nExercises in Muscle Group '%s':\n", muscleGroup);
    for (int i = 0; i < numEntries; i++) {
        if (strcmp(exercises[i].muscleGroup, muscleGroup) == 0) {
            printf("\nExercise Name: %s\n", exercises[i].name);
            printf("Muscle Group: %s\n", exercises[i].muscleGroup);
            printf("Weight: %.2f lbs\n", exercises[i].weight);
            printf("Sets: %d\n", exercises[i].sets);
            printf("Reps: %d\n", exercises[i].reps);

            printf("Exercise History:\n");
            for (int j = 0; j < exercises[i].historyCount; j++) {
                printf("  Version %d: Weight %.2f lbs, Sets %d, Reps %d\n", j + 1,
                       exercises[i].history[j].weight, exercises[i].history[j].sets,
                       exercises[i].history[j].reps);
            }
        }
    }
    printf("\n");
}

// Function to display entries for a single exercise
void viewEntriesForSingleExercise(struct Exercise exercises[], int numEntries, const char exerciseName[]) {
    int exerciseIndex = findExerciseIndex(exercises, numEntries, exerciseName);
    if (exerciseIndex != -1) {
        printf("\nEntries for Exercise '%s':\n", exerciseName);
        printf("Muscle Group: %s\n", exercises[exerciseIndex].muscleGroup);
        printf("Weight: %.2f lbs\n", exercises[exerciseIndex].weight);
        printf("Sets: %d\n", exercises[exerciseIndex].sets);
        printf("Reps: %d\n", exercises[exerciseIndex].reps);

        printf("Exercise History:\n");
        for (int j = 0; j < exercises[exerciseIndex].historyCount; j++) {
            printf("  Version %d: Weight %.2f lbs, Sets %d, Reps %d\n", j + 1,
                   exercises[exerciseIndex].history[j].weight, exercises[exerciseIndex].history[j].sets,
                   exercises[exerciseIndex].history[j].reps);
        }
        printf("\n");
    } else {
        printf("Exercise not found.\n\n");
    }
}

int main() {
    // Declare an array to store exercise details for multiple entries
    struct Exercise exercises[MAX_ENTRIES]; // Assuming a maximum of 10 entries

    int numEntries = 0; // Variable to keep track of the number of entries

    // Menu to guide the user
    printf("Exercise Log Program\n");
    printf("---------------------\n");

    while (1) {
        printf("1. Log Exercise\n");
        printf("2. View Exercise Log\n");
        printf("3. Update Exercise\n");
        printf("4. View Exercises by Muscle Group\n");
        printf("5. View Entries for a Single Exercise\n");
        printf("6. Exit\n");

        int choice;
        printf("Enter your choice (1-6): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Log Exercise
                if (numEntries < MAX_ENTRIES) { // Check if there is space for more entries
                    printf("\nEnter Exercise Details:\n");

                    // Get user input for exercise details
                    printf("Exercise Name: ");
                    scanf(" %[^\n]", exercises[numEntries].name);

                    printf("Muscle Group: ");
                    scanf(" %[^\n]", exercises[numEntries].muscleGroup);

                    printf("Weight (lbs): ");
                    scanf("%f", &exercises[numEntries].weight);

                    printf("Number of Sets: ");
                    scanf("%d", &exercises[numEntries].sets);

                    printf("Number of Reps: ");
                    scanf("%d", &exercises[numEntries].reps);

                    exercises[numEntries].historyCount = 0; // Initialize history count

                    numEntries++; // Increment the number of entries
                    printf("Exercise logged successfully!\n\n");
                } else {
                    printf("Exercise log is full. Cannot add more entries.\n\n");
                }
                break;

            case 2:
                // View Exercise Log
                if (numEntries > 0) {
                    printf("\nExercise Log:\n");
                    for (int i = 0; i < numEntries; i++) {
                        printf("\nEntry %d:\n", i + 1);
                        printf("Exercise Name: %s\n", exercises[i].name);
                        printf("Muscle Group: %s\n", exercises[i].muscleGroup);
                        printf("Weight: %.2f lbs\n", exercises[i].weight);
                        printf("Sets: %d\n", exercises[i].sets);
                        printf("Reps: %d\n", exercises[i].reps);

                        printf("Exercise History:\n");
                        for (int j = 0; j < exercises[i].historyCount; j++) {
                            printf("  Version %d: Weight %.2f lbs, Sets %d, Reps %d\n", j + 1,
                                   exercises[i].history[j].weight, exercises[i].history[j].sets,
                                   exercises[i].history[j].reps);
                        }
                    }
                    printf("\n");
                } else {
                    printf("Exercise log is empty.\n\n");
                }
                break;

            case 3:
                // Update Exercise
                if (numEntries > 0) {
                    char updateName[50];
                    printf("Enter the name of the exercise to update: ");
                    scanf(" %[^\n]", updateName);

                    int exerciseIndex = findExerciseIndex(exercises, numEntries, updateName);
                    if (exerciseIndex != -1) {
                        // Exercise found, update details
                        printf("\nEnter new Exercise Details:\n");

                        // Get user input for updated exercise details
                        printf("New Weight (lbs): ");
                        scanf("%f", &exercises[exerciseIndex].weight);

                        printf("New Number of Sets: ");
                        scanf("%d", &exercises[exerciseIndex].sets);

                        printf("New Number of Reps: ");
                        scanf("%d", &exercises[exerciseIndex].reps);

                        // Add the current version to history
                        addExerciseHistory(&exercises[exerciseIndex], exercises[exerciseIndex].weight,
                                           exercises[exerciseIndex].sets, exercises[exerciseIndex].reps);

                        printf("Exercise updated successfully!\n\n");
                    } else {
                        printf("Exercise not found.\n\n");
                    }
                } else {
                    printf("Exercise log is empty.\n\n");
                }
                break;

            case 4:
                // View Exercises by Muscle Group
                if (numEntries > 0) {
                    char muscleGroup[50];
                    printf("Enter the muscle group to view exercises: ");
                    scanf(" %[^\n]", muscleGroup);
                    viewExercisesByMuscleGroup(exercises, numEntries, muscleGroup);
                } else {
                    printf("Exercise log is empty.\n\n");
                }
                break;

            case 5:
                // View Entries for a Single Exercise
                if (numEntries > 0) {
                    char exerciseName[50];
                    printf("Enter the name of the exercise to view entries: ");
                    scanf(" %[^\n]", exerciseName);
                    viewEntriesForSingleExercise(exercises, numEntries, exerciseName);
                } else {
                    printf("Exercise log is empty.\n\n");
                }
                break;

            case 6:
                // Exit
                printf("Exiting program. Goodbye!\n");
                return 0;

            default:
                printf("Invalid choice. Please enter a number between 1 and 6.\n\n");
        }
    }

    return 0;
}
