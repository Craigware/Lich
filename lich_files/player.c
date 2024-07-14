enum Player_State {
    IDLE,
    STUNNED
};

typedef struct {
    Gfx_Image* sprite_sheet;
    char max_health;
    char health;
    Vector2 position;
    enum Player_State state;
}Player;


int player_movement(Player *player, float delta_t) {
    Vector2 input_axis = v2(0,0);
    if (is_key_down('A')) {
        input_axis.x -= 1.0;
    }
    if (is_key_down('D')) {
        input_axis.x += 1.0;
    }
    if (is_key_down('S')) {
        input_axis.y -= 1.0;
    }
    if (is_key_down('W')) {
        input_axis.y += 1.0;
    }

    //player roll
    if (is_key_down(KEY_SPACEBAR)) {

    }

    input_axis = v2_normalize(input_axis);
    player->position = v2_add(player->position, v2_mulf(input_axis, 1.0 * delta_t));
    return 0;
}

int player_update(Player *player, float delta_t) {
    player_movement(player, delta_t);

    Matrix4 image_xform = m4_scalar(1.0);
    image_xform         = m4_translate(image_xform, v3(player->position.x, player->position.y, 0));
    draw_image_xform(player->sprite_sheet, image_xform, v2(.5f, .5f), COLOR_WHITE);
    
    return 0;
}
