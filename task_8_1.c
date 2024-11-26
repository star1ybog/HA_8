#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50

// Structure to represent a point
typedef struct {
    int x;
    int y;
} point_t;

// Structure to represent a polygon
typedef struct {
    char name[MAX_NAME_LENGTH];
    int num_points;
    point_t *points;
} polygon_t;

// Function prototypes
void print_polygon(const polygon_t *polygon);
void free_polygons(polygon_t *polygons, int count);

int main() {
    FILE *file = fopen("polygons.txt", "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    polygon_t *polygons = NULL;
    int polygon_count = 0;

    while (1) {
        char name[MAX_NAME_LENGTH];
        int num_points;

        // Read the polygon name
        if (fscanf(file, "%s", name) != 1) break;

        // Read the number of points
        if (fscanf(file, "%d", &num_points) != 1) break;

        // Dynamically allocate memory for points
        point_t *points = malloc(num_points * sizeof(point_t));
        if (!points) {
            perror("Error allocating memory for points");
            fclose(file);
            free_polygons(polygons, polygon_count);
            return 1;
        }

        // Read the points
        for (int i = 0; i < num_points; i++) {
            if (fscanf(file, "%d %d", &points[i].x, &points[i].y) != 2) {
                perror("Error reading points");
                free(points);
                fclose(file);
                free_polygons(polygons, polygon_count);
                return 1;
            }
        }

        // Add the polygon to the dynamic array
        polygon_t *temp = realloc(polygons, (polygon_count + 1) * sizeof(polygon_t));
        if (!temp) {
            perror("Error reallocating memory for polygons");
            free(points);
            fclose(file);
            free_polygons(polygons, polygon_count);
            return 1;
        }
        polygons = temp;

        // Initialize the new polygon
        strcpy(polygons[polygon_count].name, name);
        polygons[polygon_count].num_points = num_points;
        polygons[polygon_count].points = points;

        polygon_count++;
    }

    fclose(file);

    // Print all polygons
    for (int i = 0; i < polygon_count; i++) {
        print_polygon(&polygons[i]);
    }

    // Free allocated memory
    free_polygons(polygons, polygon_count);

    return 0;
}

// Function to print a polygon
void print_polygon(const polygon_t *polygon) {
    printf("Polygon: %s\n", polygon->name);
    printf("Points: ");
    for (int i = 0; i < polygon->num_points; i++) {
        printf("(%d, %d)", polygon->points[i].x, polygon->points[i].y);
        if (i < polygon->num_points - 1) {
            printf(", ");
        }
    }
    printf("\n");
}

// Function to free the memory allocated for polygons
void free_polygons(polygon_t *polygons, int count) {
    for (int i = 0; i < count; i++) {
        free(polygons[i].points);
    }
    free(polygons);
}
