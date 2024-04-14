/*
 * Copyright 2023 NXP
 * SPDX-License-Identifier: MIT
 */

#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"
#include "guider_fonts.h"

typedef struct
{
	lv_obj_t *screen;
	lv_obj_t *screen_label_1;
	lv_obj_t *screen_label_2;
	lv_obj_t *screen_img_1;
	lv_obj_t *screen_img_2;
	lv_obj_t *screen_label_3;
	lv_obj_t *screen_img_3;
	lv_obj_t *screen_label_4;
	lv_obj_t *screen_img_4;
	lv_obj_t *screen_label_5;
	lv_obj_t *screen_1;
	lv_obj_t *screen_1_img_1;
	lv_obj_t *screen_1_label_1;
	lv_obj_t *screen_1_img_2;
	lv_obj_t *screen_1_label_2;
	lv_obj_t *screen_1_label_3;
	lv_obj_t *screen_1_label_4;
	lv_obj_t *screen_2;
	lv_obj_t *screen_2_img_1;
	lv_obj_t *screen_2_img_2;
	lv_obj_t *screen_2_label_1;
	lv_obj_t *screen_2_label_2;
	lv_obj_t *screen_2_label_3;
	lv_obj_t *screen_2_label_4;
}lv_ui;

void setup_ui(lv_ui *ui);
extern lv_ui guider_ui;
void setup_scr_screen(lv_ui *ui);
void setup_scr_screen_1(lv_ui *ui);
void setup_scr_screen_2(lv_ui *ui);
LV_IMG_DECLARE(_dddd_alpha_20x20);
LV_IMG_DECLARE(_bbbb_alpha_40x40);
LV_IMG_DECLARE(_eeee_alpha_20x20);
LV_IMG_DECLARE(_cccc_alpha_40x40);
LV_IMG_DECLARE(_aaaa_alpha_30x27);
LV_IMG_DECLARE(_hhhh_alpha_20x20);
LV_IMG_DECLARE(_ffff_alpha_60x60);
LV_IMG_DECLARE(_gggg_alpha_60x60);

#ifdef __cplusplus
}
#endif
#endif
