#include <stdio.h>
#include <limits.h>

#define MAX 10
#define INF 99999

int V = 5;
char locations[MAX][50] = {
    "Main Gate",
    "Library",
    "Computer Department",
    "Laboratory",
    "Auditorium"
};

int adj[MAX][MAX] = {
    {0, 4, 0, 0, 0},
    {4, 0, 3, 8, 0},
    {0, 3, 0, 0, 5},
    {0, 8, 0, 0, 2},
    {0, 0, 5, 2, 0}
};

int source = -1;
int dist[MAX];
int visited[MAX];
int parent[MAX];

// 1. Enter Campus Graph
void enterCampusGraph() {
    printf("Enter number of locations (max %d): ", MAX);
    scanf("%d", &V);
    
    printf("Enter location names:\n");
    for (int i = 0; i < V; i++) {
        printf("Location %d: ", i + 1);
        scanf(" %[^\n]s", locations[i]);
    }

    printf("Enter adjacency matrix (%d x %d):\n", V, V);
    printf("(Note: Enter 0 for diagonal and for locations with no direct connection)\n");
    
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            int val;
            scanf("%d", &val);
            if (val == 0 && i != j) {
                adj[i][j] = INF; // No direct connection treated as Infinity
            } else {
                adj[i][j] = val;
            }
        }
    }
    printf("Campus graph entered successfully!\n");
}

// 2. Display Adjacency Matrix
void displayAdjacencyMatrix() {
    printf("\n--- Campus Adjacency Matrix ---\n");
    printf("%-22s", "Location");
    for (int i = 0; i < V; i++) {
        printf("%-20s", locations[i]);
    }
    printf("\n");

    for (int i = 0; i < V; i++) {
        printf("%-22s", locations[i]);
        for (int j = 0; j < V; j++) {
            if (adj[i][j] == INF)
                printf("%-20s", "0"); // Displaying 0 for no connection as per standard input format
            else
                printf("%-20d", adj[i][j]);
        }
        printf("\n");
    }
}

// 3. Select Source Location
void selectSourceLocation() {
    printf("\nAvailable Campus Locations:\n");
    for (int i = 0; i < V; i++) {
        printf("%d. %s\n", i + 1, locations[i]);
    }
    printf("Enter source location number (1 to %d): ", V);
    int choice;
    scanf("%d", &choice);

    if (choice >= 1 && choice <= V) {
        source = choice - 1;
        printf("Selected source location: %s\n", locations[source]);
    } else {
        printf("Invalid choice! Please select a valid location.\n");
    }
}

// Dijkstra's Algorithm Core Logic
void dijkstra() {
    for (int i = 0; i < V; i++) {
        dist[i] = INF;
        visited[i] = 0;
        parent[i] = -1;
    }
    dist[source] = 0;

    for (int count = 0; count < V - 1; count++) {
        int min = INF, u = -1;
        for (int i = 0; i < V; i++) {
            if (!visited[i] && dist[i] <= min) {
                min = dist[i];
                u = i;
            }
        }

        if (u == -1) break;
        visited[u] = 1;

        for (int v = 0; v < V; v++) {
            if (!visited[v] && adj[u][v] != INF && dist[u] != INF && (dist[u] + adj[u][v] < dist[v])) {
                dist[v] = dist[u] + adj[u][v];
                parent[v] = u;
            }
        }
    }
}

// Helper function to print path recursively
void printPath(int current) {
    if (parent[current] == -1) {
        printf("%s", locations[current]);
        return;
    }
    printPath(parent[current]);
    printf(" -> %s", locations[current]);
}

// 4, 5 & 6. Display Table Format (Shortest Distance and Paths)
void displayResults() {
    if (source == -1) {
        printf("\nPlease select a source location first using option 3!\n");
        return;
    }

    dijkstra();

    printf("\n------------------------------------------------------------------------------------\n");
    printf("%-25s | %-20s | %s\n", "Destination", "Shortest Distance", "Shortest Path");
    printf("------------------------------------------------------------------------------------\n");
    
    for (int i = 0; i < V; i++) {
        if (i == source) continue;
        printf("%-25s | %-20d | ", locations[i], dist[i]);
        printPath(i);
        printf("\n");
    }
    printf("------------------------------------------------------------------------------------\n");
}

int main() {
    int choice;
    do {
        printf("\n=========================================\n");
        printf("   CAMPUS SHORTEST ROUTE FINDER\n");
        printf("=========================================\n");
        printf("1. Enter Campus Graph\n");
        printf("2. Display Adjacency Matrix\n");
        printf("3. Select Source Location\n");
        printf("4. Find Shortest Distance\n");
        printf("5. Display Shortest Paths\n");
        printf("6. Display Distance from Source to All Locations\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                enterCampusGraph();
                break;
            case 2:
                displayAdjacencyMatrix();
                break;
            case 3:
                selectSourceLocation();
                break;
            case 4:
            case 5:
            case 6:
                displayResults();
                break;
            case 7:
                printf("Exiting program. Thank you!\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 7);

    return 0;
}