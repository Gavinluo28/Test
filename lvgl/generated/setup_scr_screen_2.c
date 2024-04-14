/*
 * Copyright 2023 NXP
 * SPDX-License-Identifier: MIT
 */

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"

extern lv_ui gui_ui;
void setup_scr_screen_2(lv_ui *ui){

	//Write codes screen_2
	ui->screen_2 = lv_obj_create(NULL, NULL);

	//Write style LV_OBJ_PART_MAIN for screen_2
	static lv_style_t style_screen_2_main;
	lv_style_reset(&style_screen_2_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_2_main
	lv_style_set_bg_color(&style_screen_2_main, LV_STATE_DEFAULT, lv_color_make(0x2a, 0x6a, 0x92));
	lv_style_set_bg_opa(&style_screen_2_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen_2, LV_OBJ_PART_MAIN, &style_screen_2_main);

	//Write codes screen_2_img_1
	ui->screen_2_img_1 = lv_img_create(ui->screen_2, NULL);

	//Write style LV_IMG_PART_MAIN for screen_2_img_1
	static lv_style_t style_screen_2_img_1_main;
	lv_style_reset(&style_screen_2_img_1_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_2_img_1_main
	lv_style_set_image_recolor(&style_screen_2_img_1_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_screen_2_img_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_screen_2_img_1_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen_2_img_1, LV_IMG_PART_MAIN, &style_screen_2_img_1_main);
	lv_obj_set_pos(ui->screen_2_img_1, 5, 70);
	lv_obj_set_size(ui->screen_2_img_1, 60, 60);
	lv_obj_set_click(ui->screen_2_img_1, true);
	lv_img_set_src(ui->screen_2_img_1,&_gggg_alpha_60x60);
	lv_img_set_pivot(ui->screen_2_img_1, 0,0);
	lv_img_set_angle(ui->screen_2_img_1, 0);

	//Write codes screen_2_img_2
	ui->screen_2_img_2 = lv_img_create(ui->screen_2, NULL);

	//Write style LV_IMG_PART_MAIN for screen_2_img_2
	static lv_style_t style_screen_2_img_2_main;
	lv_style_reset(&style_screen_2_img_2_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_2_img_2_main
	lv_style_set_image_recolor(&style_screen_2_img_2_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_screen_2_img_2_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_screen_2_img_2_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen_2_img_2, LV_IMG_PART_MAIN, &style_screen_2_img_2_main);
	lv_obj_set_pos(ui->screen_2_img_2, 83, 168);
	lv_obj_set_size(ui->screen_2_img_2, 60, 60);
	lv_obj_set_click(ui->screen_2_img_2, true);
	lv_img_set_src(ui->screen_2_img_2,&_ffff_alpha_60x60);
	lv_img_set_pivot(ui->screen_2_img_2, 0,0);
	lv_img_set_angle(ui->screen_2_img_2, 0);

	//Write codes screen_2_label_1
	ui->screen_2_label_1 = lv_label_create(ui->screen_2, NULL);
	lv_label_set_text(ui->screen_2_label_1, "欢迎查看当前的光照强度和烟雾值 ");
	lv_label_set_long_mode(ui->screen_2_label_1, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->screen_2_label_1, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for screen_2_label_1
	static lv_style_t style_screen_2_label_1_main;
	lv_style_reset(&style_screen_2_label_1_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_2_label_1_main
	lv_style_set_radius(&style_screen_2_label_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen_2_label_1_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_2_label_1_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_2_label_1_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_2_label_1_main, LV_STATE_DEFAULT, 2);
	lv_style_set_text_color(&style_screen_2_label_1_main, LV_STATE_DEFAULT, lv_color_make(0xfb, 0xff, 0x05));
	lv_style_set_text_font(&style_screen_2_label_1_main, LV_STATE_DEFAULT, &lv_font_simsun_12);
	lv_style_set_text_letter_space(&style_screen_2_label_1_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen_2_label_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_2_label_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_2_label_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_2_label_1_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_2_label_1, LV_LABEL_PART_MAIN, &style_screen_2_label_1_main);
	lv_obj_set_pos(ui->screen_2_label_1, 3, 5);
	lv_obj_set_size(ui->screen_2_label_1, 210, 0);

	//Write codes screen_2_label_2
	ui->screen_2_label_2 = lv_label_create(ui->screen_2, NULL);
	lv_label_set_text(ui->screen_2_label_2, "光照强度过大注意护眼哦！");
	lv_label_set_long_mode(ui->screen_2_label_2, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->screen_2_label_2, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for screen_2_label_2
	static lv_style_t style_screen_2_label_2_main;
	lv_style_reset(&style_screen_2_label_2_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_2_label_2_main
	lv_style_set_radius(&style_screen_2_label_2_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen_2_label_2_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_2_label_2_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_2_label_2_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_2_label_2_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_screen_2_label_2_main, LV_STATE_DEFAULT, lv_color_make(0xee, 0xff, 0x05));
	lv_style_set_text_font(&style_screen_2_label_2_main, LV_STATE_DEFAULT, &lv_font_simsun_12);
	lv_style_set_text_letter_space(&style_screen_2_label_2_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen_2_label_2_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_2_label_2_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_2_label_2_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_2_label_2_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_2_label_2, LV_LABEL_PART_MAIN, &style_screen_2_label_2_main);
	lv_obj_set_pos(ui->screen_2_label_2, 132, 24);
	lv_obj_set_size(ui->screen_2_label_2, 175, 0);

	//Write codes screen_2_label_3
	ui->screen_2_label_3 = lv_label_create(ui->screen_2, NULL);
	lv_label_set_text(ui->screen_2_label_3, "烟雾浓度：0.5%毫克每立方 ");
	lv_label_set_long_mode(ui->screen_2_label_3, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->screen_2_label_3, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for screen_2_label_3
	static lv_style_t style_screen_2_label_3_main;
	lv_style_reset(&style_screen_2_label_3_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_2_label_3_main
	lv_style_set_radius(&style_screen_2_label_3_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen_2_label_3_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_2_label_3_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_2_label_3_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_2_label_3_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_screen_2_label_3_main, LV_STATE_DEFAULT, lv_color_make(0xfb, 0xf3, 0x04));
	lv_style_set_text_font(&style_screen_2_label_3_main, LV_STATE_DEFAULT, &lv_font_simsun_12);
	lv_style_set_text_letter_space(&style_screen_2_label_3_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen_2_label_3_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_2_label_3_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_2_label_3_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_2_label_3_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_2_label_3, LV_LABEL_PART_MAIN, &style_screen_2_label_3_main);
	lv_obj_set_pos(ui->screen_2_label_3, 84, 82);
	lv_obj_set_size(ui->screen_2_label_3, 100, 0);

	//Write codes screen_2_label_4
	ui->screen_2_label_4 = lv_label_create(ui->screen_2, NULL);
	lv_label_set_text(ui->screen_2_label_4, "光照强度：3500Lux");
	lv_label_set_long_mode(ui->screen_2_label_4, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->screen_2_label_4, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for screen_2_label_4
	static lv_style_t style_screen_2_label_4_main;
	lv_style_reset(&style_screen_2_label_4_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_2_label_4_main
	lv_style_set_radius(&style_screen_2_label_4_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen_2_label_4_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_2_label_4_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_2_label_4_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_2_label_4_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_screen_2_label_4_main, LV_STATE_DEFAULT, lv_color_make(0xe2, 0xff, 0x0a));
	lv_style_set_text_font(&style_screen_2_label_4_main, LV_STATE_DEFAULT, &lv_font_simsun_12);
	lv_style_set_text_letter_space(&style_screen_2_label_4_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen_2_label_4_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_2_label_4_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_2_label_4_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_2_label_4_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_2_label_4, LV_LABEL_PART_MAIN, &style_screen_2_label_4_main);
	lv_obj_set_pos(ui->screen_2_label_4, 154, 184);
	lv_obj_set_size(ui->screen_2_label_4, 150, 0);
}