/*
 * Copyright 2023 NXP
 * SPDX-License-Identifier: MIT
 */

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"

extern lv_ui gui_ui;

void setup_scr_screen_1(lv_ui *ui){

	//Write codes screen_1
	ui->screen_1 = lv_obj_create(NULL, NULL);

	//Write style LV_OBJ_PART_MAIN for screen_1
	static lv_style_t style_screen_1_main;
	lv_style_reset(&style_screen_1_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_1_main
	lv_style_set_bg_color(&style_screen_1_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xd7, 0x00));
	lv_style_set_bg_opa(&style_screen_1_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen_1, LV_OBJ_PART_MAIN, &style_screen_1_main);

	//Write codes screen_1_img_1
	ui->screen_1_img_1 = lv_img_create(ui->screen_1, NULL);

	//Write style LV_IMG_PART_MAIN for screen_1_img_1
	static lv_style_t style_screen_1_img_1_main;
	lv_style_reset(&style_screen_1_img_1_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_1_img_1_main
	lv_style_set_image_recolor(&style_screen_1_img_1_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_screen_1_img_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_screen_1_img_1_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen_1_img_1, LV_IMG_PART_MAIN, &style_screen_1_img_1_main);
	lv_obj_set_pos(ui->screen_1_img_1, 69, 49);
	lv_obj_set_size(ui->screen_1_img_1, 40, 40);
	lv_obj_set_click(ui->screen_1_img_1, true);
	lv_img_set_src(ui->screen_1_img_1,&_bbbb_alpha_40x40);
	lv_img_set_pivot(ui->screen_1_img_1, 0,0);
	lv_img_set_angle(ui->screen_1_img_1, 0);

	//Write codes screen_1_label_1
	ui->screen_1_label_1 = lv_label_create(ui->screen_1, NULL);
	lv_label_set_text(ui->screen_1_label_1, "当前温度为26摄氏度 ");
	lv_label_set_long_mode(ui->screen_1_label_1, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->screen_1_label_1, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for screen_1_label_1
	static lv_style_t style_screen_1_label_1_main;
	lv_style_reset(&style_screen_1_label_1_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_1_label_1_main
	lv_style_set_radius(&style_screen_1_label_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen_1_label_1_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_1_label_1_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_1_label_1_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_1_label_1_main, LV_STATE_DEFAULT, 255);
	lv_style_set_text_color(&style_screen_1_label_1_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_1_label_1_main, LV_STATE_DEFAULT, &lv_font_simsun_12);
	lv_style_set_text_letter_space(&style_screen_1_label_1_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen_1_label_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_1_label_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_1_label_1_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_1_label_1_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_1_label_1, LV_LABEL_PART_MAIN, &style_screen_1_label_1_main);
	lv_obj_set_pos(ui->screen_1_label_1, 130, 62);
	lv_obj_set_size(ui->screen_1_label_1, 169, 0);

	//Write codes screen_1_img_2
	ui->screen_1_img_2 = lv_img_create(ui->screen_1, NULL);

	//Write style LV_IMG_PART_MAIN for screen_1_img_2
	static lv_style_t style_screen_1_img_2_main;
	lv_style_reset(&style_screen_1_img_2_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_1_img_2_main
	lv_style_set_image_recolor(&style_screen_1_img_2_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_image_recolor_opa(&style_screen_1_img_2_main, LV_STATE_DEFAULT, 0);
	lv_style_set_image_opa(&style_screen_1_img_2_main, LV_STATE_DEFAULT, 255);
	lv_obj_add_style(ui->screen_1_img_2, LV_IMG_PART_MAIN, &style_screen_1_img_2_main);
	lv_obj_set_pos(ui->screen_1_img_2, 69, 137);
	lv_obj_set_size(ui->screen_1_img_2, 40, 40);
	lv_obj_set_click(ui->screen_1_img_2, true);
	lv_img_set_src(ui->screen_1_img_2,&_cccc_alpha_40x40);
	lv_img_set_pivot(ui->screen_1_img_2, 0,0);
	lv_img_set_angle(ui->screen_1_img_2, 0);

	//Write codes screen_1_label_2
	ui->screen_1_label_2 = lv_label_create(ui->screen_1, NULL);
	lv_label_set_text(ui->screen_1_label_2, "当前湿度为50%RH");
	lv_label_set_long_mode(ui->screen_1_label_2, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->screen_1_label_2, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for screen_1_label_2
	static lv_style_t style_screen_1_label_2_main;
	lv_style_reset(&style_screen_1_label_2_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_1_label_2_main
	lv_style_set_radius(&style_screen_1_label_2_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen_1_label_2_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_1_label_2_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_1_label_2_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_1_label_2_main, LV_STATE_DEFAULT, 255);
	lv_style_set_text_color(&style_screen_1_label_2_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_1_label_2_main, LV_STATE_DEFAULT, &lv_font_simsun_12);
	lv_style_set_text_letter_space(&style_screen_1_label_2_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen_1_label_2_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_1_label_2_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_1_label_2_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_1_label_2_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_1_label_2, LV_LABEL_PART_MAIN, &style_screen_1_label_2_main);
	lv_obj_set_pos(ui->screen_1_label_2, 133, 150);
	lv_obj_set_size(ui->screen_1_label_2, 150, 0);

	//Write codes screen_1_label_3
	ui->screen_1_label_3 = lv_label_create(ui->screen_1, NULL);
	lv_label_set_text(ui->screen_1_label_3, "请注意今天的温湿度情况 ");
	lv_label_set_long_mode(ui->screen_1_label_3, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->screen_1_label_3, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for screen_1_label_3
	static lv_style_t style_screen_1_label_3_main;
	lv_style_reset(&style_screen_1_label_3_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_1_label_3_main
	lv_style_set_radius(&style_screen_1_label_3_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen_1_label_3_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_1_label_3_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_1_label_3_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_1_label_3_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_screen_1_label_3_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_1_label_3_main, LV_STATE_DEFAULT, &lv_font_simsun_16);
	lv_style_set_text_letter_space(&style_screen_1_label_3_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen_1_label_3_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_1_label_3_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_1_label_3_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_1_label_3_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_1_label_3, LV_LABEL_PART_MAIN, &style_screen_1_label_3_main);
	lv_obj_set_pos(ui->screen_1_label_3, 6, 3);
	lv_obj_set_size(ui->screen_1_label_3, 12, 0);

	//Write codes screen_1_label_4
	ui->screen_1_label_4 = lv_label_create(ui->screen_1, NULL);
	lv_label_set_text(ui->screen_1_label_4, "来选择合适的穿衣搭配哦 ");
	lv_label_set_long_mode(ui->screen_1_label_4, LV_LABEL_LONG_BREAK);
	lv_label_set_align(ui->screen_1_label_4, LV_LABEL_ALIGN_CENTER);

	//Write style LV_LABEL_PART_MAIN for screen_1_label_4
	static lv_style_t style_screen_1_label_4_main;
	lv_style_reset(&style_screen_1_label_4_main);

	//Write style state: LV_STATE_DEFAULT for style_screen_1_label_4_main
	lv_style_set_radius(&style_screen_1_label_4_main, LV_STATE_DEFAULT, 0);
	lv_style_set_bg_color(&style_screen_1_label_4_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_1_label_4_main, LV_STATE_DEFAULT, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_1_label_4_main, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_1_label_4_main, LV_STATE_DEFAULT, 0);
	lv_style_set_text_color(&style_screen_1_label_4_main, LV_STATE_DEFAULT, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_1_label_4_main, LV_STATE_DEFAULT, &lv_font_simsun_16);
	lv_style_set_text_letter_space(&style_screen_1_label_4_main, LV_STATE_DEFAULT, 2);
	lv_style_set_pad_left(&style_screen_1_label_4_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_right(&style_screen_1_label_4_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_top(&style_screen_1_label_4_main, LV_STATE_DEFAULT, 0);
	lv_style_set_pad_bottom(&style_screen_1_label_4_main, LV_STATE_DEFAULT, 0);
	lv_obj_add_style(ui->screen_1_label_4, LV_LABEL_PART_MAIN, &style_screen_1_label_4_main);
	lv_obj_set_pos(ui->screen_1_label_4, 24, 60);
	lv_obj_set_size(ui->screen_1_label_4, 15, 0);
}