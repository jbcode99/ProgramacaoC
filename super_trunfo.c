#include <stdio.h>
#include <string.h> // Required for strcpy

// Defines the structure for a game card, holding its attributes.
struct Card {
    char name[50];  // Name of the card
    int attack;     // Attack power
    int defense;    // Defense power
    int speed;      // Speed value
    int magic;      // Magic power
    int stamina;    // Stamina value
};

// Helper function to retrieve a specific attribute value from a card.
// Parameters:
//   c: The card (struct Card) from which to get the attribute.
//   attribute_id: An integer representing the attribute to retrieve:
//                 1 for Attack, 2 for Defense, 3 for Speed, 4 for Magic, 5 for Stamina.
// Returns:
//   The integer value of the chosen attribute. Returns 0 if the attribute_id is invalid (should not happen with proper use).
int get_attribute_value(struct Card c, int attribute_id) {
    switch (attribute_id) {
        case 1: return c.attack;
        case 2: return c.defense;
        case 3: return c.speed;
        case 4: return c.magic;
        case 5: return c.stamina;
        default:
            printf("Error: Invalid attribute_id %d in get_attribute_value.\n", attribute_id);
            return 0; // Should ideally not be reached if input is validated before calling
    }
}

// Displays all attributes of a given card.
// Parameters:
//   c: The card (struct Card) to display.
void display_card(struct Card c) {
    printf("Card: %s\n", c.name);
    printf("  Attack: %d\n", c.attack);
    printf("  Defense: %d\n", c.defense);
    printf("  Speed: %d\n", c.speed);
    printf("  Magic: %d\n", c.magic);
    printf("  Stamina: %d\n", c.stamina);
    printf("--------------------\n");
}

// Compares two cards based on a single chosen attribute.
// This function was part of Challenge 2.
// Parameters:
//   card1: The first card (player's card).
//   card2: The second card (CPU's card).
//   attribute_choice: An integer representing the attribute to compare:
//                     1 for Attack, 2 for Defense, 3 for Speed, 4 for Magic, 5 for Stamina.
// Returns:
//   1 if card1 wins on the chosen attribute.
//   2 if card2 wins on the chosen attribute.
//   0 if it's a draw on the chosen attribute.
//  -1 if the attribute_choice is invalid.
int compare_cards_multiple_attributes(struct Card card1, struct Card card2, int attribute_choice) {
    // Compare based on the selected attribute_choice
    if (attribute_choice == 1) { // Attack
        if (card1.attack > card2.attack) return 1;
        else if (card2.attack > card1.attack) return 2;
        else return 0; // Draw
    } else if (attribute_choice == 2) { // Defense
        if (card1.defense > card2.defense) return 1;
        else if (card2.defense > card1.defense) return 2;
        else return 0; // Draw
    } else if (attribute_choice == 3) { // Speed
        if (card1.speed > card2.speed) return 1;
        else if (card2.speed > card1.speed) return 2;
        else return 0; // Draw
    } else if (attribute_choice == 4) { // Magic
        if (card1.magic > card2.magic) return 1;
        else if (card2.magic > card1.magic) return 2;
        else return 0; // Draw
    } else if (attribute_choice == 5) { // Stamina
        if (card1.stamina > card2.stamina) return 1;
        else if (card2.stamina > card1.stamina) return 2;
        else return 0; // Draw
    } else {
        printf("Error: Invalid attribute_choice %d in compare_cards_multiple_attributes.\n", attribute_choice);
        return -1; // Indicate an error for invalid attribute choice
    }
}

// Compares two cards based on the sum of two chosen attributes for each card.
// This function was part of Challenge 3.
// Parameters:
//   card1: The first card (player's card).
//   card2: The second card (CPU's card).
//   attr1_choice: An integer for the first attribute to sum (1-5 mapping to Attack, Defense, etc.).
//   attr2_choice: An integer for the second attribute to sum (1-5 mapping).
// Returns:
//   1 if card1's sum of chosen attributes is greater.
//   2 if card2's sum of chosen attributes is greater.
//   0 if the sums are equal (a draw).
//   It relies on get_attribute_value to fetch attribute values.
//   The final comparison (win/loss/draw) is determined using the ternary operator.
int compare_cards_two_attributes(struct Card card1, struct Card card2, int attr1_choice, int attr2_choice) {
    // Calculate the total power for player's card by summing the values of the two chosen attributes.
    int player_total_power = get_attribute_value(card1, attr1_choice) + get_attribute_value(card1, attr2_choice);
    // Calculate the total power for CPU's card similarly.
    int cpu_total_power = get_attribute_value(card2, attr1_choice) + get_attribute_value(card2, attr2_choice);

    printf("\nPlayer's combined power (Attr %d + Attr %d): %d\n", attr1_choice, attr2_choice, player_total_power);
    printf("CPU's combined power (Attr %d + Attr %d): %d\n", attr1_choice, attr2_choice, cpu_total_power);

    // Use the ternary operator to determine the winner:
    // If player's power > CPU's power, return 1 (player wins).
    // Else, if CPU's power > player's power, return 2 (CPU wins).
    // Else, return 0 (it's a draw).
    return (player_total_power > cpu_total_power) ? 1 :
           (cpu_total_power > player_total_power) ? 2 : 0;
}

// Main function: Entry point of the Super Trunfo game.
int main() {
    // Card Initialization: Create instances of struct Card for player and CPU.
    struct Card player_card;
    struct Card cpu_card;

    // Assign attributes to player's card.
    strcpy(player_card.name, "Hero Card Alpha");
    player_card.attack = 80;
    player_card.defense = 70;
    player_card.speed = 90;
    player_card.magic = 85;
    player_card.stamina = 75;

    // Assign attributes to CPU's card.
    strcpy(cpu_card.name, "Villain Card Omega");
    cpu_card.attack = 75;
    cpu_card.defense = 85;
    cpu_card.speed = 80;
    cpu_card.magic = 90;
    cpu_card.stamina = 65;

    // Display the initial cards to the player.
    printf("Your Card:\n");
    display_card(player_card);
    printf("CPU's Card:\n");
    display_card(cpu_card);

    // Game Mode Selection: Prompt user to choose the type of comparison.
    int game_mode;
    printf("\n--- Choose Game Mode ---\n");
    printf("1. Compare a single attribute (Challenge 2 rules)\n");
    printf("2. Compare based on the sum of two attributes (Challenge 3 rules)\n");
    printf("Enter your choice (1-2): ");
    scanf("%d", &game_mode);

    int result = -1; // Initialize result to -1 (e.g., error or not yet determined)

    // Logic for Single Attribute Comparison (Challenge 2)
    if (game_mode == 1) {
        int choice;
        printf("\n--- Single Attribute Comparison ---\n");
        printf("Choose attribute (1.Attack, 2.Defense, 3.Speed, 4.Magic, 5.Stamina): ");
        scanf("%d", &choice);

        // Validate choice and call comparison function.
        if (choice >= 1 && choice <= 5) {
            result = compare_cards_multiple_attributes(player_card, cpu_card, choice);
        } else {
            printf("Invalid attribute choice for single comparison. Exiting.\n");
            return 1; // Exit with an error code
        }
    // Logic for Two-Attribute Comparison (Challenge 3)
    } else if (game_mode == 2) {
        int attr1_choice, attr2_choice;
        printf("\n--- Two Attributes Combined Comparison ---\n");
        printf("Choose first attribute (1.Attack, 2.Defense, 3.Speed, 4.Magic, 5.Stamina): ");
        scanf("%d", &attr1_choice);
        printf("Choose second attribute (1.Attack, 2.Defense, 3.Speed, 4.Magic, 5.Stamina): ");
        scanf("%d", &attr2_choice);

        // Validate choices.
        if ((attr1_choice < 1 || attr1_choice > 5) || (attr2_choice < 1 || attr2_choice > 5)) {
            printf("Invalid attribute choice(s) for combined comparison. Exiting.\n");
            return 1; // Exit with an error code
        }
        if (attr1_choice == attr2_choice) {
            printf("Note: You chose the same attribute twice (its value will be effectively doubled for the sum).\n");
        }
        result = compare_cards_two_attributes(player_card, cpu_card, attr1_choice, attr2_choice);
    } else {
        printf("Invalid game mode selected (%d). Exiting.\n", game_mode);
        return 1; // Exit with an error code
    }

    // Final Result Printing: Display the outcome of the round.
    printf("\n--- Round Result ---\n");
    if (result == 1) {
        printf("Player wins the round!\n");
    } else if (result == 2) {
        printf("CPU wins the round!\n");
    } else if (result == 0) {
        printf("It's a draw!\n");
    } else {
        // This case should ideally not be reached if all paths correctly set 'result'.
        // It might indicate an issue if result remains -1 from initialization without valid comparison.
        printf("Error: The game result could not be determined.\n");
    }

    return 0; // Successful execution
}
