Entity *setup_player(Vector2 spawn_location);
int player_update(Entity *player);

Entity *setup_player(Vector2 spawn_location) {
    Collision_Rect col;
    col.origin = spawn_location;
    col.p1 = v2(-0.5,-0.5);
    col.p2 = v2(0.5, -0.5);
    col.p3 = v2(0.5,0.5);
    col.p4 = v2(-0.5,0.5);

    Entity player, *p_player;
    player.position        = spawn_location;
    player.collision_shape = col;
    player.health          = 10;
    player.move_speed      = 1.0f;

    player.max_cells    = v2(5,5);
    player.current      = v2(0,0);
    player.sprite_sheet = load_image_from_disk(fixed_string("assets/Character.png"), get_heap_allocator());
    assert(player.sprite_sheet, "Spritesheet didnt laod properly")

    p_player = &player;

    return p_player;
}

int player_update(Entity *player) {
    Vector2 scale = v2(0.25, 0.25);

    Matrix4 xform = m4_scalar(1.0);
    xform = m4_translate(xform, v3(player->position.x, player->position.y, 0));
    
    draw_image_xform(player->sprite_sheet, xform, scale, COLOR_WHITE);

    return 0;
}