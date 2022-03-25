#include <stdlib.h>

#include "raylib.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 450

typedef struct {
    Vector2 position;
    Vector2 scale;
    float rotation;
} TransformComponent;

typedef struct {
    Vector2 size;
    Color color;
} RenderRectangleComponent;

typedef struct {
    TransformComponent *transformComponent;
    RenderRectangleComponent *renderRectangleComponent;
} Components;

typedef struct {
    unsigned int uuid;
    Components components;
} Entity;


void add_transform_component (Entity *e, Vector2 position, Vector2 scale, float rotation);
void add_render_rectangle_component (Entity *e, Color color);
void free_entity (Entity *e);

void RenderEntity (Entity *e) {
    if (!e->components.transformComponent || !e->components.renderRectangleComponent) {
        return;
    }

    DrawRectanglePro ((Rectangle) { e->components.transformComponent->position.x, e->components.transformComponent->position.y, e->components.transformComponent->scale.x * 10, e->components.transformComponent->scale.y * 10}, (Vector2) { 0, 0 }, e->components.transformComponent->rotation, e->components.renderRectangleComponent->color);
}

int main()
{
    Entity rect;
    add_transform_component (&rect, (Vector2) { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 }, (Vector2) {10, 10}, 0);
    add_render_rectangle_component (&rect, LIGHTGRAY);

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "raylib [core] example - basic window");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        RenderEntity (&rect);

        EndDrawing();
    }
    CloseWindow();

    return 0;
}

void add_transform_component (Entity *e, Vector2 position, Vector2 scale, float roation) {
    e->components.transformComponent = malloc (sizeof (TransformComponent));
    e->components.transformComponent->position = position;
    e->components.transformComponent->scale = scale;
    e->components.transformComponent->rotation = roation;
}

void add_render_rectangle_component (Entity *e, Color color) {
    e->components.renderRectangleComponent = malloc (sizeof (RenderRectangleComponent));
    e->components.renderRectangleComponent->color = color;
}

void free_entity (Entity *e) {
    if (e->components.transformComponent) {
        free (e->components.transformComponent);
    }

    if (e->components.renderRectangleComponent) {
        free (e->components.renderRectangleComponent);
    }
}