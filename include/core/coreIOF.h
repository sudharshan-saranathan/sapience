/*  -----------------------------------
 *  Project     : sapiens
 *  File        : coreIOF.h
 *  Date        : 16.11.2024
 *  Author      : Sudharshan Saranathan
 *  -----------------------------------
 */

#ifndef COREIOF_H
#define COREIOF_H

struct mouse {
    static bool is_pressed_lmb;
    static bool is_pressed_mmb;
    static bool is_pressed_rmb;
};

struct keybr {
    static bool is_pressed_enter;
    static bool is_pressed_shift;
    static bool is_pressed_ctrl;
    static bool is_pressed_caps;
    static bool is_pressed_tab;
    static bool is_pressed_del;
    static bool is_pressed_esc;
};

#endif