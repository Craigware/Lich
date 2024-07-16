#define MAX_ENTITY_COUNT 1024

typedef enum EntityTypes{
    EN_null   = 0,
    EN_player = 1
}EntityTypes;

typedef struct {
    bool is_valid;
    EntityTypes entity_type;

    Vector2 scale;
    Vector2 pos;

    bool render_sprite;
    int sprite_size;
    Gfx_Image* sprite_sheet;
}Entity;

typedef struct {
    Entity entities[MAX_ENTITY_COUNT];
}World;
World *world = 0;

typedef enum SpriteID {
    SP_null,
    SP_player,
    SP_MAX
}SpriteID;

Entity* create_entity() {
    Entity* entity_found = 0;
    for(int i = 0; i < MAX_ENTITY_COUNT; i++) {
        Entity* existing_entity =  &world->entities[i];
        if (!existing_entity->is_valid) {
            entity_found = existing_entity;
            break;
        }
    }
    assert(entity_found, "No more free entities");
    return entity_found;
}

void free_entity() {

}

int entry(int argc, char **argv) {
    window.title = STR("Lich");
	window.scaled_width = 1280;
	window.scaled_height = 720; 
    window.x = 200;
	window.y = 200;
	window.clear_color = hex_to_rgba(0xbebebeff);

    float64 seconds_counter = 0.0;
    float64 second_counter = 0.0;
    s32 frame_count = 0;
    float64 last_time = os_get_current_time_in_seconds();
    float64 last_fixed_time = os_get_current_time_in_seconds();

    world = alloc(get_heap_allocator(), sizeof(World));

    Entity* player_en = create_entity();
    player_en->sprite_sheet = load_image_from_disk(fixed_string("assets/character.png"), get_heap_allocator());
    player_en->pos = v2(0,0);
    player_en->scale = v2(16.0,16.0);


    while (!window.should_close) {
        reset_temporary_storage();
		os_update();
        if (is_key_just_pressed(KEY_ESCAPE)) {
            window.should_close = true;
        }

        // :camera
        {
            draw_frame.projection = m4_make_orthographic_projection(window.width * -0.5, window.width * 0.5, window.height * -0.5, window.height * 0.5, -1, 10);
            float zoom = 5.3;
            draw_frame.view = m4_make_scale(v3(1.0/zoom, 1.0/zoom, 1.0));
        }

        float64 now = os_get_current_time_in_seconds();
        float64 delta_t = now - last_time;
        last_time = now;

        for (int i = 0; i < MAX_ENTITY_COUNT; i++) {
            Entity* entity = &world->entities[i];
            Matrix4 xform = m4_scalar(1.0);
            xform = m4_translate(xform, v3(entity->pos.x, entity->pos.y, 0));
            Draw_Quad* quad = draw_image_xform(entity->sprite_sheet, xform, entity->scale, COLOR_WHITE);
        }

		gfx_update();

        seconds_counter += delta_t;
        second_counter += delta_t;
        frame_count += 1;
        if (second_counter > 1.0) {
            seconds_counter = roundf(seconds_counter);
            log("Seconds played: %f", seconds_counter);
            log("Fps: %i", frame_count);
            second_counter = 0.0;
            frame_count = 0.0;
        }
	}  
	return 0;
}