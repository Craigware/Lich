
int entry(int argc, char **argv) {
	
	window.title = STR("Lich");
	window.scaled_width = 1280; // We need to set the scaled size if we want to handle system scaling (DPI)
	window.scaled_height = 720; 
	window.x = 200;
	window.y = 200;
	window.clear_color = hex_to_rgba(0xbebebeff);

    Gfx_Image* character = load_image_from_disk(fixed_string("assets/Character.png"), get_heap_allocator());
    assert(character, "Character sprite didn't load properly.");
    Vector2 player_pos = v2(0,0);

    float64 seconds_counter = 0.0;
    s32 frame_count = 0;
    float64 last_time = os_get_current_time_in_seconds();

    while (!window.should_close) {
		reset_temporary_storage();
		os_update();

        float64 now = os_get_current_time_in_seconds();
        float64 delta_t = now - last_time;
        last_time = now;
 
        if (is_key_just_pressed(KEY_ESCAPE)) {
            window.should_close = true;
        }

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
        input_axis = v2_normalize(input_axis);
        player_pos = v2_add(player_pos, v2_mulf(input_axis, 1.0 * delta_t));

		Matrix4 image_xform = m4_scalar(1.0);
		image_xform         = m4_translate(image_xform, v3(player_pos.x, player_pos.y, 0));
		draw_image_xform(character, image_xform, v2(.5f, .5f), COLOR_WHITE);
		
		gfx_update();
        seconds_counter += delta_t;
        frame_count += 1;
        if (seconds_counter > 1.0) {
            log("Fps: %i", frame_count);
            seconds_counter = 0.0;
            frame_count = 0.0;
        }

	}

	return 0;
}