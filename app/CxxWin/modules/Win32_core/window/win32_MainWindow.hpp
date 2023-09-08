/***************************************************************************//**
 * @file win32_MainWindow.hpp
 * @author StoneyDSP (nathanjhood@googlemail.com)
 *
 * @brief Contains a declaration of the 'MainWindow' class which inherits from
 * the 'BaseWindow' class. Inherit this 'MainWindow' class for a basic window
 * functionality.
 *
 * @version 1.0.0
 * @date 2023-08-23
 *
 * @copyright Copyright (c) 2023
 *
 ******************************************************************************/
#pragma once
/**
 * @brief Contains a declaration of the 'MainWindow' class which inherits from
 * the 'BaseWindow' class. Inherit this 'MainWindow' class for a basic window
 * functionality.
 *
 */
#define _WIN32_MAINWINDOW_HPP_

// namespace Win32
// {
// namespace Core
// {
// namespace Window
// {
/**
 * @brief The 'MainWindow' class.
 *
 */
class MainWindow : public BaseWindow<MainWindow>
{
public:
    /** @brief Default-Construct a new Main Window object. */
    inline MainWindow() = default;

    PCWSTR ClassName() CONST;

    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

    __DECLARE_NON_COPYABLE(MainWindow)
    __DECLARE_NON_MOVEABLE(MainWindow)
    __PREVENT_HEAP_ALLOCATION
};

/** @brief The definition carrying the 'MainWindow' datatype. */
#define _MainWindow_T MainWindow
/** @brief The 'MainWindow' datatype. */
typedef class _MainWindow_T MainWindow;

// } // namespace Window
// } // namespace Core
// } // namespace Win32
