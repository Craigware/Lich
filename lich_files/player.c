enum Player_State {
    IDLE,
    STUNNED
};

typedef struct {
    Gfx_Image* sprite_sheet;
    char max_health;
    char health;
    float32 movement_speed;
    Vector2 position;
    Vector2 velocity;
    enum Player_State state;
    float32 stun_timer;
}Player;

int unstun_player(Player *player) {
    if (player->state != STUNNED) {
        return 1;
    }

    player->stun_timer = 0;
    player->state = IDLE;
    return 0;
}

int stun_player(Player *player, float32 duration) {
    player->stun_timer = duration;
    player->state = STUNNED;
    return 0;
}

int player_movement(Player *player, float64 delta_t) {
    float32 movement_speed = player->movement_speed;
    Vector2 input_axis = v2(0,0);
   
    if (player->state != STUNNED) {
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
        if (is_key_down(KEY_SPACEBAR)) {
            movement_speed *= 20.0;
            stun_player(player, 1);
        }
    }

    input_axis = v2_normalize(input_axis);
    
    if (v2_equals(input_axis, v2(0,0))) {
        player->velocity = v2_move_towards(player->velocity, v2(0,0), movement_speed * delta_t);
    } else {
        player->velocity = v2_mulf(input_axis, movement_speed * delta_t);
    }   
    player->position = v2_add(player->position, player->velocity);

    return 0;
}

int player_update(Player *player, float64 delta_t) {
    player->stun_timer -= delta_t;
    if (player->stun_timer <= 0) {
        unstun_player(player);
    }
    
    player_movement(player, delta_t);

    Matrix4 image_xform = m4_scalar(1.0);
    image_xform         = m4_translate(image_xform, v3(player->position.x, player->position.y, 0));
    Draw_Quad *sprite = draw_image_xform(player->sprite_sheet, image_xform, v2(1.0f, 1.0f), COLOR_WHITE);

    return 0;
}