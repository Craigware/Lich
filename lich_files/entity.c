typedef struct{
    Vector2 origin;
    Vector2 p1;
    Vector2 p2;
    Vector2 p3;
    Vector2 p4;
}Collision_Rect;

typedef struct{

}GFx_Info;

typedef struct{
    Gfx_Image *sprite_sheet;    
    Vector2 max_cells;
    Vector2 current;
 
    Vector2 position;
    Collision_Rect collision_shape;

    char health;
    float move_speed;
}Entity;
