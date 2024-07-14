enum Boss_State {
    SUMMONING,
    WALKING,
    SPRINTING,
    CHARGING,
    ATTACKING,
    DEAD
};

typedef struct 
{
    Gfx_Image* sprite_sheet;
    Vector2 sprite_position;
    Vector2 position;
    char health;
    enum Boss_State state;
}Boss;

int boss_update(struct Boss *boss) {
    return 1;
}


