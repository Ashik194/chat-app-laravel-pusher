#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the structure for the item
typedef struct item {
    int item_id;
    char name[50];
    float price;
    int quantity;
    struct item *next;
} Item;

// Define the structure for the buyer
typedef struct buyer {
    char name[50];
    float balance;
    struct buyer *next;
} Buyer;

// Define the structure for the seller
typedef struct seller {
    char name[50];
    int num_items;
    Item *items_list;
    struct seller *next;
} Seller;

// Define the structure for the queue
typedef struct queue {
    Buyer *front;
    Buyer *rear;
} Queue;

// Function to add an item to the seller's list
void add_item(Seller *seller, Item *item) {
    if (seller->items_list == NULL) {
        seller->items_list = item;
    } else {
        Item *temp = seller->items_list;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = item;
    }
    seller->num_items++;
}

// Function to remove an item from the seller's list
void remove_item(Seller *seller, int item_id) {
    Item *prev = NULL;
    Item *curr = seller->items_list;
    while (curr != NULL && curr->item_id != item_id) {
        prev = curr;
        curr = curr->next;
    }
    if (curr == NULL) {
        printf("Item not found.\n");
    } else if (prev == NULL) {
        seller->items_list = curr->next;
        free(curr);
        seller->num_items--;
    } else {
        prev->next = curr->next;
        free(curr);
        seller->num_items--;
    }
}

// Function to display all the items in the seller's list
void display_items(Seller *seller) {
    if (seller->num_items == 0) {
        printf("No items to display.\n");
    } else {
        Item *temp = seller->items_list;
        printf("Item ID\tItem Name\tPrice\tQuantity\n");
        while (temp != NULL) {
            printf("%d\t%s\t%.2f\t%d\n", temp->item_id, temp->name, temp->price, temp->quantity);
            temp = temp->next;
        }
    }
}

// Function to add a buyer to the queue
void add_buyer(Queue *queue, Buyer *buyer) {
    buyer->next = NULL;
    if (queue->front == NULL) {
        queue->front = buyer;
        queue->rear = buyer;
    } else {
        queue->rear->next = buyer;
        queue->rear = buyer;
    }
}

// Function to remove a buyer from the queue
void remove_buyer(Queue *queue) {
    if (queue->front == NULL) {
        printf("Queue is empty.\n");
    } else {
        Buyer *temp = queue->front;
        queue->front = queue->front->next;
        free(temp);
    }
}

// Function to display all the buyers in the queue
void display_buyers(Queue *queue) {
    if (queue->front == NULL) {
        printf("No buyers in the queue.\n");
    } else {
        printf("Buyer Name\tBalance\n");
        Buyer *temp = queue->front;
        while (temp != NULL) {
            printf("%s\t%.2f\n", temp->name, temp->balance);
temp = temp->next;
}
}
}

int main() {
int choice, item_id, quantity;
float price, balance;
char name[50];
// Initialize the seller and buyer lists and the queue
Seller *seller_list = NULL;
Buyer *buyer_list = NULL;
Queue *queue = (Queue*)malloc(sizeof(Queue));
queue->front = NULL;
queue->rear = NULL;

while (1) {
    // Display the menu
    printf("\n*** Marketing System ***\n");
    printf("1. Add Seller\n");
    printf("2. Add Buyer\n");
    printf("3. Add Item\n");
    printf("4. Remove Item\n");
    printf("5. Display Items\n");
    printf("6. Add Buyer to Queue\n");
    printf("7. Remove Buyer from Queue\n");
    printf("8. Display Buyers in Queue\n");
    printf("9. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1: // Add seller
            printf("Enter the seller name: ");
            scanf("%s", name);
            Seller *seller = (Seller*)malloc(sizeof(Seller));
            strcpy(seller->name, name);
            seller->num_items = 0;
            seller->items_list = NULL;
            seller->next = seller_list;
            seller_list = seller;
            printf("Seller added successfully.\n");
            break;

        case 2: // Add buyer
            printf("Enter the buyer name: ");
            scanf("%s", name);
            printf("Enter the buyer balance: ");
            scanf("%f", &balance);
            Buyer *buyer = (Buyer*)malloc(sizeof(Buyer));
            strcpy(buyer->name, name);
            buyer->balance = balance;
            buyer->next = buyer_list;
            buyer_list = buyer;
            printf("Buyer added successfully.\n");
            break;

        case 3: // Add item
            printf("Enter the seller name: ");
            scanf("%s", name);
            Seller *temp_seller = seller_list;
            while (temp_seller != NULL && strcmp(temp_seller->name, name) != 0) {
                temp_seller = temp_seller->next;
            }
            if (temp_seller == NULL) {
                printf("Seller not found.\n");
            } else {
                printf("Enter the item name: ");
                scanf("%s", name);
                printf("Enter the item price: ");
                scanf("%f", &price);
                printf("Enter the item quantity: ");
                scanf("%d", &quantity);
                Item *item = (Item*)malloc(sizeof(Item));
                item->item_id = temp_seller->num_items + 1;
                strcpy(item->name, name);
                item->price = price;
                item->quantity = quantity;
                item->next = NULL;
                add_item(temp_seller, item);
                printf("Item added successfully.\n");
            }
            break;

        case 4: // Remove item
            printf("Enter the seller name: ");
            scanf("%s", name);
            temp_seller = seller_list;
            while (temp_seller != NULL && strcmp(temp_seller->name, name) != 0) {
                temp_seller = temp_seller->next;
            }
            if (temp_seller == NULL) {
                printf("Seller not found.\n");
            } else {
                printf("Enter the item ID: ");
                scanf("%d", &item_id);
                remove_item(temp_seller, item_id);
printf("Item removed successfully.\n");
}
break;
case 5: // Display items
            printf("Enter the seller name: ");
            scanf("%s", name);
            temp_seller = seller_list;
            while (temp_seller != NULL && strcmp(temp_seller->name, name) != 0) {
                temp_seller = temp_seller->next;
            }
            if (temp_seller == NULL) {
                printf("Seller not found.\n");
            } else {
                display_items(temp_seller);
            }
            break;

        case 6: // Add buyer to queue
            printf("Enter the buyer name: ");
            scanf("%s", name);
            Buyer *temp_buyer = buyer_list;
            while (temp_buyer != NULL && strcmp(temp_buyer->name, name) != 0) {
                temp_buyer = temp_buyer->next;
            }
            if (temp_buyer == NULL) {
                printf("Buyer not found.\n");
            } else {
                enqueue(queue, temp_buyer);
                printf("Buyer added to queue successfully.\n");
            }
            break;

        case 7: // Remove buyer from queue
            dequeue(queue);
            printf("Buyer removed from queue successfully.\n");
            break;

        case 8: // Display buyers in queue
            display_queue(queue);
            break;

        case 9: // Exit
            printf("Exiting...\n");
            exit(0);
            break;

        default:
            printf("Invalid choice.\n");
    }
}

return 0;
}
