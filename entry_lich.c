#include "lich_files/entity.c"
#include "lich_files/player.c"

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

    float64 seconds_counter = 0.0;
    float64 second_counter = 0.0;
    s32 frame_count = 0;
    float64 last_time = os_get_current_time_in_seconds();
    float64 last_fixed_time = os_get_current_time_in_seconds();

    Entity *player = setup_player(v2(0,0));
    

    while (!window.should_close) {
        reset_temporary_storage();
		os_update();
        if (is_key_just_pressed(KEY_ESCAPE)) {
            window.should_close = true;
        }

        float64 now = os_get_current_time_in_seconds();
        float64 delta_t = now - last_time;
        last_time = now;

        player_update(player);
    
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