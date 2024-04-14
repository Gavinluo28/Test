/*
 * Copyright 2023 NXP
 * SPDX-License-Identifier: MIT
 */

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "KQM6600.h"
extern lv_ui gui_ui;

void setup_scr_screen(lv_ui *ui){

	//Write codes screen
	ui->screen = lv_obj_create(NULL, NULL);

	//Write style LV_OBJ_PART_MAIN for screen
	static lv_style_t style_screen_main;
	lv_style_reset(&style_screen_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_main
	lv_style_set_bg_color(&style_screen_main, LV_STATE_DEFAULT, lv_color_make(0x46, 0xbb, 0xd8));
	lv_style_set_bg_opa(&style_screen_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen, LV_OBJ_PART_MAIN, &style_screen_main);

	//Write codes screen_label_1
	ui->screen_label_1 = lv_label_create(ui->screen, NULL);
	lv_label_set_text(ui->screen_label_1, "空气质量检测仪");
	lv_label_set_long_mode(ui->screen_label_1, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->screen_label_1, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for screen_label_1
	static lv_style_t style_screen_label_1_main;
	lv_style_reset(&style_screen_label_1_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_label_1_main
	lv_style_set_radius(&style_screen_label_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen_label_1_main, LV_STATE_DEFAULT, lv_color_make(0x12, 0x8c, 0xb5));
	lv_style_set_bg_grad_color(&style_screen_label_1_main, LV_STATE_DEFAULT, lv_color_make(0x20, 0xc5, 0x68));
	lv_style_set_bg_grad_dir(&style_screen_label_1_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_label_1_main, LV_STATE_DEFAULT, 255);
	lv_style_set_text_color(&style_screen_label_1_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_label_1_main, LV_STATE_DEFAULT, &lv_font_simsun_16);
	lv_style_set_text_letter_space(&style_screen_label_1_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen_label_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_label_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_label_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_label_1_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_label_1, LV_LABEL_PART_MAIN, &style_screen_label_1_main);
	lv_obj_set_pos(ui->screen_label_1, 0, 4);
	lv_obj_set_size(ui->screen_label_1, 320, 0);

	//Write codes screen_label_2
	ui->screen_label_2 = lv_label_create(ui->screen, NULL);
	lv_label_set_text(ui->screen_label_2, "2023/08/08  15：15：45");
	lv_label_set_long_mode(ui->screen_label_2, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->screen_label_2, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for screen_label_2
	static lv_style_t style_screen_label_2_main;
	lv_style_reset(&style_screen_label_2_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_label_2_main
	lv_style_set_radius(&style_screen_label_2_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen_label_2_main, LV_STATE_DEFAULT, lv_color_make(0x0a, 0x95, 0xae));
	lv_style_set_bg_grad_color(&style_screen_label_2_main, LV_STATE_DEFAULT, lv_color_make(0x54, 0xda, 0xf2));
	lv_style_set_bg_grad_dir(&style_screen_label_2_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_label_2_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_screen_label_2_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_label_2_main, LV_STATE_DEFAULT, &lv_font_simsun_12);
	lv_style_set_text_letter_space(&style_screen_label_2_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen_label_2_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_label_2_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_label_2_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_label_2_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_label_2, LV_LABEL_PART_MAIN, &style_screen_label_2_main);
	lv_obj_set_pos(ui->screen_label_2, 42, 30);
	lv_obj_set_size(ui->screen_label_2, 100, 0);

	//Write codes screen_img_1
	ui->screen_img_1 = lv_img_create(ui->screen, NULL);

	//Write style LV_IMG_PART_MAIN for screen_img_1
	static lv_style_t style_screen_img_1_main;
	lv_style_reset(&style_screen_img_1_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_img_1_main
	lv_style_set_image_recolor(&style_screen_img_1_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_screen_img_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_screen_img_1_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen_img_1, LV_IMG_PART_MAIN, &style_screen_img_1_main);
	lv_obj_set_pos(ui->screen_img_1, 6, 29);
	lv_obj_set_size(ui->screen_img_1, 30, 27);
	lv_obj_set_click(ui->screen_img_1, true);
	lv_img_set_src(ui->screen_img_1,&_aaaa_alpha_30x27);
	lv_img_set_pivot(ui->screen_img_1, 0,0);
	lv_img_set_angle(ui->screen_img_1, 0);

	//Write codes screen_img_2
	ui->screen_img_2 = lv_img_create(ui->screen, NULL);

	//Write style LV_IMG_PART_MAIN for screen_img_2
	static lv_style_t style_screen_img_2_main;
	lv_style_reset(&style_screen_img_2_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_img_2_main
	lv_style_set_image_recolor(&style_screen_img_2_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_screen_img_2_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_screen_img_2_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen_img_2, LV_IMG_PART_MAIN, &style_screen_img_2_main);
	lv_obj_set_pos(ui->screen_img_2, 15, 124);
	lv_obj_set_size(ui->screen_img_2, 20, 20);
	lv_obj_set_click(ui->screen_img_2, true);
	lv_img_set_src(ui->screen_img_2,&_eeee_alpha_20x20);
	lv_img_set_pivot(ui->screen_img_2, 0,0);
	lv_img_set_angle(ui->screen_img_2, 0);

	//Write codes screen_label_3
	ui->screen_label_3 = lv_label_create(ui->screen, NULL);
	lv_label_set_text(ui->screen_label_3, "二氧化碳浓度：500ppm");
	lv_label_set_long_mode(ui->screen_label_3, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->screen_label_3, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for screen_label_3
	static lv_style_t style_screen_label_3_main;
	lv_style_reset(&style_screen_label_3_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_label_3_main
	lv_style_set_radius(&style_screen_label_3_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen_label_3_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_label_3_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_label_3_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_label_3_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_screen_label_3_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_label_3_main, LV_STATE_DEFAULT, &lv_font_simsun_12);
	lv_style_set_text_letter_space(&style_screen_label_3_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen_label_3_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_label_3_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_label_3_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_label_3_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_label_3, LV_LABEL_PART_MAIN, &style_screen_label_3_main);
	lv_obj_set_pos(ui->screen_label_3, 40, 127);
	lv_obj_set_size(ui->screen_label_3, 100, 0);

	//Write codes screen_img_3
	ui->screen_img_3 = lv_img_create(ui->screen, NULL);

	//Write style LV_IMG_PART_MAIN for screen_img_3
	static lv_style_t style_screen_img_3_main;
	lv_style_reset(&style_screen_img_3_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_img_3_main
	lv_style_set_image_recolor(&style_screen_img_3_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_screen_img_3_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_screen_img_3_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen_img_3, LV_IMG_PART_MAIN, &style_screen_img_3_main);
	lv_obj_set_pos(ui->screen_img_3, 164, 124);
	lv_obj_set_size(ui->screen_img_3, 20, 20);
	lv_obj_set_click(ui->screen_img_3, true);
	lv_img_set_src(ui->screen_img_3,&_hhhh_alpha_20x20);
	lv_img_set_pivot(ui->screen_img_3, 0,0);
	lv_img_set_angle(ui->screen_img_3, 0);

	//Write codes screen_label_4
	ui->screen_label_4 = lv_label_create(ui->screen, NULL);
	lv_label_set_text(ui->screen_label_4, "voc浓度:0.6mg/m3 ");
	lv_label_set_long_mode(ui->screen_label_4, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->screen_label_4, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for screen_label_4
	static lv_style_t style_screen_label_4_main;
	lv_style_reset(&style_screen_label_4_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_label_4_main
	lv_style_set_radius(&style_screen_label_4_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen_label_4_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_label_4_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_label_4_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_label_4_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_screen_label_4_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_label_4_main, LV_STATE_DEFAULT, &lv_font_simsun_12);
	lv_style_set_text_letter_space(&style_screen_label_4_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen_label_4_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_label_4_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_label_4_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_label_4_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_label_4, LV_LABEL_PART_MAIN, &style_screen_label_4_main);
	lv_obj_set_pos(ui->screen_label_4, 182, 128);
	lv_obj_set_size(ui->screen_label_4, 138, 0);

	//Write codes screen_img_4
	ui->screen_img_4 = lv_img_create(ui->screen, NULL);

	//Write style LV_IMG_PART_MAIN for screen_img_4
	static lv_style_t style_screen_img_4_main;
	lv_style_reset(&style_screen_img_4_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_img_4_main
	lv_style_set_image_recolor(&style_screen_img_4_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_screen_img_4_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_screen_img_4_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen_img_4, LV_IMG_PART_MAIN, &style_screen_img_4_main);
	lv_obj_set_pos(ui->screen_img_4, 16, 194);
	lv_obj_set_size(ui->screen_img_4, 20, 20);
	lv_obj_set_click(ui->screen_img_4, true);
	lv_img_set_src(ui->screen_img_4,&_dddd_alpha_20x20);
	lv_img_set_pivot(ui->screen_img_4, 0,0);
	lv_img_set_angle(ui->screen_img_4, 0);

	//Write codes screen_label_5
	ui->screen_label_5 = lv_label_create(ui->screen, NULL);
	lv_label_set_text(ui->screen_label_5, "甲醛浓度:0.1mg/m³");
	lv_label_set_long_mode(ui->screen_label_5, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->screen_label_5, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for screen_label_5
	static lv_style_t style_screen_label_5_main;
	lv_style_reset(&style_screen_label_5_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_label_5_main
	lv_style_set_radius(&style_screen_label_5_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen_label_5_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_label_5_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_label_5_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_label_5_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_screen_label_5_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_label_5_main, LV_STATE_DEFAULT, &lv_font_simsun_12);
	lv_style_set_text_letter_space(&style_screen_label_5_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen_label_5_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_label_5_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_label_5_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_label_5_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_label_5, LV_LABEL_PART_MAIN, &style_screen_label_5_main);
	lv_obj_set_pos(ui->screen_label_5, 23, 197);
	lv_obj_set_size(ui->screen_label_5, 185, 0);
}