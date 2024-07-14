#include "lich_files/player.c"
#include "lich_files/Skullboss.c"

int entry(int argc, char **argv) {
    //
    // Window Setup
    //
	window.title = STR("Lich");
 
    // We need to set the scaled size if we want to handle system scaling (DPI)
	window.scaled_width = 1280;
	window.scaled_height = 720; 
	
    window.x = 200;
	window.y = 200;
	window.clear_color = hex_to_rgba(0xbebebeff);

    //
    // System Setup
    //
    float64 seconds_counter = 0.0;
    float64 second_counter = 0.0;
    s32 frame_count = 0;
    float64 last_time = os_get_current_time_in_seconds();
    float64 last_fixed_time = os_get_current_time_in_seconds();
    
    //
    // Player Setup
    //
    Gfx_Image* character = load_image_from_disk(fixed_string("assets/Character.png"), get_heap_allocator());
    assert(character, "Character sprite didn't load properly.");
    Player player = {
        character, // Sprite sheet
        20,        // max heal
        20,        // health
        1.0,       // movement speed
        v2(0,0),   // position
        v2(0,0),   // velocity
        IDLE,      // state
        0          // stun timer
    };
    Player *p_player = &player;

    //
    // Boss Setup
    //
    Boss skull_boss = {
        load_image_from_disk(fixed_string("assets/Character.png"), get_heap_allocator()),
        v2(0,0),
        v2(0,0),
        25,
        SUMMONING
    };

    while (!window.should_close) {
    //
    // System related
    //
        reset_temporary_storage();
		os_update();
        if (is_key_just_pressed(KEY_ESCAPE)) {
            window.should_close = true;
        }

        float64 now = os_get_current_time_in_seconds();
        float64 delta_t = now - last_time;
        last_time = now;
    //
    // Game loop
    //


        player_update(p_player, delta_t);
		gfx_update();

    //
    // Cleanup and system
    //
        seconds_counter += delta_t;
        second_counter += delta_t;
        frame_count += 1;
        if (second_counter > 1.0) {
            seconds_counter = roundf(seconds_counter);
            log("Player memory loc: %p", p_player);
            log("Seconds played: %f", seconds_counter);
            log("Fps: %i", frame_count);
            second_counter = 0.0;
            frame_count = 0.0;
        }
	}
    
	return 0;
}